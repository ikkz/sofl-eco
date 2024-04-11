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
        $.parameter_list,
        ")",
        $.parameter_list,
        $.process_body,
        "end_process",
        $._semicolon,
      ),

    parameter_list: ($) =>
      choice(
        seq($.identifier, repeat(seq(",", $.identifier)), ":", $._type),
        prec.left(seq($.parameter_list, "|", $.parameter_list)),
      ),

    process_body: ($) =>
      seq(
        optional(seq("ext", repeat1($.ext_item))),
        seq("pre", $._expression),
        seq("post", $._expression),
      ),

    ext_item: ($) => seq(choice("wr", "rd"), $.identifier, ":", $._type),

    _type: ($) =>
      choice(
        $.identifier,
        $.primitive_type,
        $.enumeration_type,
        $.set_type,
        $.list_type,
        $.map_type,
        $.composite_type,
      ),

    primitive_type: ($) =>
      choice("nat", "nat0", "real", "int", "bool", "char", "string"),
    enumeration_type: ($) =>
      seq("{", $.enumeration_value, repeat(seq(",", $.enumeration_value)), "}"),
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
        $.identifier,
        $.int,
        $.real,
        $.string,
        $.char,
        $.bool,
        seq("(", $._expression, ")"),
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
