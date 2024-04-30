/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "sofl",

  word: ($) => $.identifier,
  rules: {
    source_file: ($) =>
      seq(
        $.module_definition,
        repeat(
          choice(
            $.function_definition,
            $.type_definition,
            $.variable_definition
          )
        ),
        $.process_definition
      ),

    module_definition: ($) =>
      seq(
        "module",
        field("module_name", $.identifier),
        optional(seq("/", $.identifier)),
        $._semicolon
      ),

    function_definition: ($) =>
      seq("function", repeat1($.function_definition_item)),

    function_definition_item: ($) =>
      seq(
        field("function_name", $.identifier),
        optional($.generic_types),
        "(",
        optional(commaSep1(field("parameter", $._type))),
        ")",
        ":",
        field("return_type", $._type),
        $._semicolon
      ),
    generic_types: ($) => seq("<", commaSep1($.identifier), ">"),

    type_definition: ($) => seq("type", repeat1($.type_definition_item)),
    type_definition_item: ($) => seq($.identifier, "=", $._type, $._semicolon),

    variable_definition: ($) => seq("var", repeat1($.variable_definition_item)),
    variable_definition_item: ($) =>
      seq($.identifier, ":", $._type, $._semicolon),

    process_definition: ($) => repeat1($.process_definition_item),
    process_definition_item: ($) =>
      seq(
        "process",
        $.identifier,
        "(",
        optional($.parameter_list),
        ")",
        optional($.parameter_list),
        $.process_body,
        "end_process",
        $._semicolon
      ),

    parameter_list: ($) => sep1($.parameter_item, "|"),
    parameter_item: ($) =>
      seq(
        $.identifier,
        repeat(seq(",", $.identifier)),
        ":",
        choice($._type, $._expression)
      ),

    process_body: ($) =>
      seq(
        optional(seq("ext", repeat1($.ext_item))),
        seq("pre", $._expression),
        seq("post", $._expression)
      ),

    ext_item: ($) => seq(choice("wr", "rd"), $.identifier, ":", $._type),

    _type: ($) =>
      prec.left(
        1,
        choice(
          $.type_identifier,
          $.primitive_type,
          $.enumeration_type,
          $.set_type,
          $.map_type,
          $.composite_type,
        )
      ),

    type_identifier: ($) => prec(1, $.identifier),

    primitive_type: ($) =>
      choice("nat", "nat0", "real", "int", "bool", "char", "string"),
    enumeration_type: ($) => seq("{", commaSep1($.enumeration_value), "}"),
    enumeration_value: ($) => seq("<", $.identifier, ">"),
    set_type: ($) => seq("set", "of", $._type),
    map_type: ($) =>
      seq("map", field("key", $._type), "to", field("value", $._type)),
    composite_type: ($) =>
      seq(
        "composed",
        "of",
        repeat(
          field(
            "field",
            seq(
              field("filed_name", $.identifier),
              ":",
              field("field_type", $._type),
              $._semicolon
            )
          )
        ),
        "end"
      ),
       _expression: ($) =>
      choice(
        $._constant_expression,
        $.unary_expression,
        $.binary_expression,
        $.reference_expression,
        $.modify_expression,
        $.function_expression,
        $.quantified_expression,
        $.bracketed_expression
      ),

    bracketed_expression: ($) => seq("(", $._expression, ")"),

    expression_list: ($) => commaSep1($._expression),
    _constant_expression: ($) =>
      choice(
        $.int,
        $.real,
        $.string,
        $.char,
        $.bool,
        $.set_expression,
        $.map_expression
      ),
    reference_expression: ($) =>
      choice($.identifier, seq($.reference_expression, ".", $.identifier)),
    set_expression: ($) =>
      seq("{", optional(field("items", $.expression_list)), "}"),
    map_expression: ($) =>
      seq(
        "{",
        choice("->", seq($.map_item, repeat(seq(",", $.map_item)))),
        "}"
      ),
    map_item: ($) =>
      seq(field("key", $._expression), "->", field("value", $._expression)),
    unary_expression: ($) =>
      prec(11, seq(choice("-", "not", "~"), $._expression)),
    binary_expression: ($) =>
      choice(
        binary_operators(
          10,
          ["=", "<>", "<", "<=", ">", ">=", "inset", "notinset"],
          $._expression
        ),
        binary_operators(9, ["*", "/", "div", "rem", "mod"], $._expression),
        binary_operators(8, ["+", "-"], $._expression),
        binary_operators(7, ["and"], $._expression),
        binary_operators(6, ["or"], $._expression),
        binary_operators(5, ["=>", "<=>"], $._expression)
      ),

    modify_expression: ($) =>
      seq(
        "modify",
        "(",
        $.reference_expression,
        ",",
        commaSep1(seq($.identifier, "->", $._expression)),
        ")"
      ),
    function_expression: ($) =>
      seq($.reference_expression, "(", optional($.expression_list), ")"),

    quantified_expression: ($) =>
      seq(choice("forall", "exists"), "[", $.binding_list, "]", $._expression),
    binding_list: ($) => commaSep1($.parameter_item),
    int: ($) => /-?\d+/,
    real: ($) => /-?\d+\.\d+/,
    string: ($) => /"[^"]*"/,
    char: ($) => /'[^']'/,
    bool: ($) => choice("true", "false"),
    identifier: ($) => /[_a-zA-Z][_a-zA-Z0-9]*/,

    _semicolon: ($) => ";",
  },
});

function sep1(rule, separator) {
  return seq(rule, repeat(seq(separator, rule)));
}

function commaSep1(rule) {
  return seq(rule, repeat(seq(",", rule)));
}

function commaSep(rule) {
  return optional(commaSep1(rule));
}

function binary_operators(_prec, operators, exp) {
  return prec.left(
    _prec,
    seq(
      field("left", exp),
      field("operator", choice(...operators)),
      field("right", exp)
    )
  );
}
