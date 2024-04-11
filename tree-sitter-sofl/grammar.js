/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "sofl",

  word: ($) => $.identifier,
  rules: {
    source_file: ($) =>
      seq(
        $.module_definition,
        optional($.type_definition),
        optional($.variable_definition),
        optional($.process_definition),
      ),

    module_definition: ($) =>
      seq(
        "module",
        field("module_name", $.identifier),
        optional(seq("/", $.identifier)),
        $._semicolon,
      ),

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
        $._semicolon,
      ),

    parameter_list: ($) => sep1($.parameter_item, "|"),
    parameter_item: ($) =>
      seq($.identifier, repeat(seq(",", $.identifier)), ":", $._type),

    process_body: ($) =>
      seq(
        optional(seq("ext", repeat1($.ext_item))),
        seq("pre", $._expression),
        seq("post", $._expression),
      ),

    ext_item: ($) => seq(choice("wr", "rd"), $.identifier, ":", $._type),

    _type: ($) =>
      prec.left(
        1,
        choice(
          $.identifier,
          $.primitive_type,
          $.enumeration_type,
          $.set_type,
          $.list_type,
          $.map_type,
          $.composite_type,
        ),
      ),

    primitive_type: ($) =>
      choice("nat", "nat0", "real", "int", "bool", "char", "string"),
    enumeration_type: ($) => seq("{", commaSep1($.enumeration_value), "}"),
    enumeration_value: ($) => seq("<", $.identifier, ">"),
    set_type: ($) => seq("set", "of", $._type),
    list_type: ($) => seq("list", "of", $._type),
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
              $._semicolon,
            ),
          ),
        ),
        "end",
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
        seq("(", $._expression, ")"),
      ),

    expression_list: ($) => commaSep1($._expression),
    _constant_expression: ($) =>
      choice(
        $.int,
        $.real,
        $.string,
        $.char,
        $.bool,
        $.list_expression,
        $.map_expression,
      ),
    reference_expression: ($) =>
      choice($.identifier, seq($.reference_expression, ".", $.identifier)),
    list_expression: ($) => seq("{", optional($.expression_list), "}"),
    map_expression: ($) =>
      seq(
        "{",
        choice("->", seq($.map_item, repeat(seq(",", $.map_item)))),
        "}",
      ),
    map_item: ($) => seq($._expression, "->", $._expression),
    unary_expression: ($) =>
      prec(10, seq(choice("-", "not", "~"), $._expression)),
    binary_expression: ($) =>
      choice(
        prec.left(
          9,
          seq(
            $._expression,
            choice(
              "*",
              "/",
              "div",
              "rem",
              "mod",
              "=",
              "<>",
              "<",
              "<=",
              ">",
              ">=",
              "inset",
              "notinset",
              "and",
            ),
            $._expression,
          ),
        ),
        prec.left(8, seq($._expression, choice("+", "-", "or"), $._expression)),
        prec.left(7, seq($._expression, choice("=>", "<=>"), $._expression)),
      ),

    modify_expression: ($) =>
      seq(
        "modify",
        "(",
        $.identifier,
        ",",
        commaSep1(seq($.identifier, "->", $._expression)),
        ")",
      ),
    function_expression: ($) =>
      seq($.identifier, "(", optional($.expression_list), ")"),

    quantified_expression: ($) =>
      seq(choice("forall", "exists"), "[", $.binding_list, "]", $._expression),
    binding_list: ($) =>
      commaSep1(
        seq(commaSep1($.identifier), ":", choice($._type, $._expression)),
      ),
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
