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
        // optional($.variable_definition),
        // optional($.process_definition),
      ),

    module_definition: ($) =>
      seq(
        "module",
        $.identifier,
        optional(seq("/", $.identifier)),
        $._semicolon,
      ),

    type_definition: ($) => seq("type", repeat1($.type_definition_item)),

    type_definition_item: ($) => seq($.identifier, "=", $._type, $._semicolon),

    // variable_definition: ($) => seq(),

    // process_definition: ($) =>
    //   seq("func", $.identifier, $.parameter_list, $._type, $.block),

    // parameter_list: ($) =>
    //   seq(
    //     "(",
    //     // TODO: parameters
    //     ")",
    //   ),

    _type: ($) =>
      choice(
        $.primitive_type,
        $.enumeration_type,
        $.set_type,
        $.list_type,
        $.identifier,
        $.composite_type,
      ),

    int: ($) => /-?\d+/,
    real: ($) => /-?\d+\.\d+/,
    string: ($) => /"[^"]*"/,
    char: ($) => /'[^']'/,
    bool: ($) => choice("true", "false"),

    primitive_type: ($) =>
      choice("nat", "nat0", "real", "int", "bool", "char", "string"),
    enumeration_type: ($) =>
      seq("{", $.enumeration_value, repeat(seq(",", $.enumeration_value)), "}"),
    enumeration_value: ($) => seq("<", $.identifier, ">"),
    set_type: ($) => seq("set", "of", $._type),
    list_type: ($) => seq("list", "of", $._type),
    composite_type: ($) =>
      seq(
        "composed",
        "of",
        repeat(
          seq(
            field("filed_name", $.identifier),
            ":",
            field("field_type", $._type),
            $._semicolon,
          ),
        ),
        "end",
      ),
    map_type: ($) => seq("map", $.identifier, "to", $._type),

    _expression: ($) =>
      choice(
        $.identifier,
        $.int,
        $.real,
        $.string,
        $.char,
        seq("(", $._expression, ")"),
      ),

    identifier: ($) => /[_a-zA-Z][_a-zA-Z0-9]*/,

    _semicolon: ($) => ";",
  },
});
