#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 103
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 72
#define ALIAS_COUNT 0
#define TOKEN_COUNT 44
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 6
#define MAX_ALIAS_SEQUENCE_LENGTH 9
#define PRODUCTION_ID_COUNT 6

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_module = 2,
  anon_sym_SLASH = 3,
  anon_sym_type = 4,
  anon_sym_EQ = 5,
  anon_sym_var = 6,
  anon_sym_COLON = 7,
  anon_sym_process = 8,
  anon_sym_LPAREN = 9,
  anon_sym_RPAREN = 10,
  anon_sym_end_process = 11,
  anon_sym_COMMA = 12,
  anon_sym_PIPE = 13,
  anon_sym_ext = 14,
  anon_sym_pre = 15,
  anon_sym_post = 16,
  anon_sym_wr = 17,
  anon_sym_rd = 18,
  anon_sym_nat = 19,
  anon_sym_nat0 = 20,
  anon_sym_real = 21,
  anon_sym_int = 22,
  anon_sym_bool = 23,
  anon_sym_char = 24,
  anon_sym_string = 25,
  anon_sym_LBRACE = 26,
  anon_sym_RBRACE = 27,
  anon_sym_LT = 28,
  anon_sym_GT = 29,
  anon_sym_set = 30,
  anon_sym_of = 31,
  anon_sym_list = 32,
  anon_sym_map = 33,
  anon_sym_to = 34,
  anon_sym_composed = 35,
  anon_sym_end = 36,
  sym_int = 37,
  sym_real = 38,
  sym_string = 39,
  sym_char = 40,
  anon_sym_true = 41,
  anon_sym_false = 42,
  sym__semicolon = 43,
  sym_source_file = 44,
  sym_module_definition = 45,
  sym_type_definition = 46,
  sym_type_definition_item = 47,
  sym_variable_definition = 48,
  sym_variable_definition_item = 49,
  sym_process_definition = 50,
  sym_process_definition_item = 51,
  sym_parameter_list = 52,
  sym_process_body = 53,
  sym_ext_item = 54,
  sym__type = 55,
  sym_primitive_type = 56,
  sym_enumeration_type = 57,
  sym_enumeration_value = 58,
  sym_set_type = 59,
  sym_list_type = 60,
  sym_map_type = 61,
  sym_composite_type = 62,
  sym__expression = 63,
  sym_bool = 64,
  aux_sym_type_definition_repeat1 = 65,
  aux_sym_variable_definition_repeat1 = 66,
  aux_sym_process_definition_repeat1 = 67,
  aux_sym_parameter_list_repeat1 = 68,
  aux_sym_process_body_repeat1 = 69,
  aux_sym_enumeration_type_repeat1 = 70,
  aux_sym_composite_type_repeat1 = 71,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_module] = "module",
  [anon_sym_SLASH] = "/",
  [anon_sym_type] = "type",
  [anon_sym_EQ] = "=",
  [anon_sym_var] = "var",
  [anon_sym_COLON] = ":",
  [anon_sym_process] = "process",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_end_process] = "end_process",
  [anon_sym_COMMA] = ",",
  [anon_sym_PIPE] = "|",
  [anon_sym_ext] = "ext",
  [anon_sym_pre] = "pre",
  [anon_sym_post] = "post",
  [anon_sym_wr] = "wr",
  [anon_sym_rd] = "rd",
  [anon_sym_nat] = "nat",
  [anon_sym_nat0] = "nat0",
  [anon_sym_real] = "real",
  [anon_sym_int] = "int",
  [anon_sym_bool] = "bool",
  [anon_sym_char] = "char",
  [anon_sym_string] = "string",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_set] = "set",
  [anon_sym_of] = "of",
  [anon_sym_list] = "list",
  [anon_sym_map] = "map",
  [anon_sym_to] = "to",
  [anon_sym_composed] = "composed",
  [anon_sym_end] = "end",
  [sym_int] = "int",
  [sym_real] = "real",
  [sym_string] = "string",
  [sym_char] = "char",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [sym__semicolon] = "_semicolon",
  [sym_source_file] = "source_file",
  [sym_module_definition] = "module_definition",
  [sym_type_definition] = "type_definition",
  [sym_type_definition_item] = "type_definition_item",
  [sym_variable_definition] = "variable_definition",
  [sym_variable_definition_item] = "variable_definition_item",
  [sym_process_definition] = "process_definition",
  [sym_process_definition_item] = "process_definition_item",
  [sym_parameter_list] = "parameter_list",
  [sym_process_body] = "process_body",
  [sym_ext_item] = "ext_item",
  [sym__type] = "_type",
  [sym_primitive_type] = "primitive_type",
  [sym_enumeration_type] = "enumeration_type",
  [sym_enumeration_value] = "enumeration_value",
  [sym_set_type] = "set_type",
  [sym_list_type] = "list_type",
  [sym_map_type] = "map_type",
  [sym_composite_type] = "composite_type",
  [sym__expression] = "_expression",
  [sym_bool] = "bool",
  [aux_sym_type_definition_repeat1] = "type_definition_repeat1",
  [aux_sym_variable_definition_repeat1] = "variable_definition_repeat1",
  [aux_sym_process_definition_repeat1] = "process_definition_repeat1",
  [aux_sym_parameter_list_repeat1] = "parameter_list_repeat1",
  [aux_sym_process_body_repeat1] = "process_body_repeat1",
  [aux_sym_enumeration_type_repeat1] = "enumeration_type_repeat1",
  [aux_sym_composite_type_repeat1] = "composite_type_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_module] = anon_sym_module,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_type] = anon_sym_type,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_var] = anon_sym_var,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_process] = anon_sym_process,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_end_process] = anon_sym_end_process,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_ext] = anon_sym_ext,
  [anon_sym_pre] = anon_sym_pre,
  [anon_sym_post] = anon_sym_post,
  [anon_sym_wr] = anon_sym_wr,
  [anon_sym_rd] = anon_sym_rd,
  [anon_sym_nat] = anon_sym_nat,
  [anon_sym_nat0] = anon_sym_nat0,
  [anon_sym_real] = anon_sym_real,
  [anon_sym_int] = anon_sym_int,
  [anon_sym_bool] = anon_sym_bool,
  [anon_sym_char] = anon_sym_char,
  [anon_sym_string] = anon_sym_string,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_set] = anon_sym_set,
  [anon_sym_of] = anon_sym_of,
  [anon_sym_list] = anon_sym_list,
  [anon_sym_map] = anon_sym_map,
  [anon_sym_to] = anon_sym_to,
  [anon_sym_composed] = anon_sym_composed,
  [anon_sym_end] = anon_sym_end,
  [sym_int] = sym_int,
  [sym_real] = sym_real,
  [sym_string] = sym_string,
  [sym_char] = sym_char,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [sym__semicolon] = sym__semicolon,
  [sym_source_file] = sym_source_file,
  [sym_module_definition] = sym_module_definition,
  [sym_type_definition] = sym_type_definition,
  [sym_type_definition_item] = sym_type_definition_item,
  [sym_variable_definition] = sym_variable_definition,
  [sym_variable_definition_item] = sym_variable_definition_item,
  [sym_process_definition] = sym_process_definition,
  [sym_process_definition_item] = sym_process_definition_item,
  [sym_parameter_list] = sym_parameter_list,
  [sym_process_body] = sym_process_body,
  [sym_ext_item] = sym_ext_item,
  [sym__type] = sym__type,
  [sym_primitive_type] = sym_primitive_type,
  [sym_enumeration_type] = sym_enumeration_type,
  [sym_enumeration_value] = sym_enumeration_value,
  [sym_set_type] = sym_set_type,
  [sym_list_type] = sym_list_type,
  [sym_map_type] = sym_map_type,
  [sym_composite_type] = sym_composite_type,
  [sym__expression] = sym__expression,
  [sym_bool] = sym_bool,
  [aux_sym_type_definition_repeat1] = aux_sym_type_definition_repeat1,
  [aux_sym_variable_definition_repeat1] = aux_sym_variable_definition_repeat1,
  [aux_sym_process_definition_repeat1] = aux_sym_process_definition_repeat1,
  [aux_sym_parameter_list_repeat1] = aux_sym_parameter_list_repeat1,
  [aux_sym_process_body_repeat1] = aux_sym_process_body_repeat1,
  [aux_sym_enumeration_type_repeat1] = aux_sym_enumeration_type_repeat1,
  [aux_sym_composite_type_repeat1] = aux_sym_composite_type_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_module] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_type] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_var] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_process] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_end_process] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ext] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pre] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_post] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_wr] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rd] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nat] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nat0] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_real] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bool] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_char] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_string] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_set] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_of] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_list] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_map] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_to] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_composed] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_end] = {
    .visible = true,
    .named = false,
  },
  [sym_int] = {
    .visible = true,
    .named = true,
  },
  [sym_real] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_char] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [sym__semicolon] = {
    .visible = false,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_module_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_type_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_type_definition_item] = {
    .visible = true,
    .named = true,
  },
  [sym_variable_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_variable_definition_item] = {
    .visible = true,
    .named = true,
  },
  [sym_process_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_process_definition_item] = {
    .visible = true,
    .named = true,
  },
  [sym_parameter_list] = {
    .visible = true,
    .named = true,
  },
  [sym_process_body] = {
    .visible = true,
    .named = true,
  },
  [sym_ext_item] = {
    .visible = true,
    .named = true,
  },
  [sym__type] = {
    .visible = false,
    .named = true,
  },
  [sym_primitive_type] = {
    .visible = true,
    .named = true,
  },
  [sym_enumeration_type] = {
    .visible = true,
    .named = true,
  },
  [sym_enumeration_value] = {
    .visible = true,
    .named = true,
  },
  [sym_set_type] = {
    .visible = true,
    .named = true,
  },
  [sym_list_type] = {
    .visible = true,
    .named = true,
  },
  [sym_map_type] = {
    .visible = true,
    .named = true,
  },
  [sym_composite_type] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym_bool] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_type_definition_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_variable_definition_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_process_definition_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_parameter_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_process_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_enumeration_type_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_composite_type_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_field = 1,
  field_field_type = 2,
  field_filed_name = 3,
  field_key = 4,
  field_module_name = 5,
  field_value = 6,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_field] = "field",
  [field_field_type] = "field_type",
  [field_filed_name] = "filed_name",
  [field_key] = "key",
  [field_module_name] = "module_name",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 3},
  [4] = {.index = 6, .length = 6},
  [5] = {.index = 12, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_module_name, 1},
  [1] =
    {field_key, 1},
    {field_value, 3},
  [3] =
    {field_field, 2, .inherited = true},
    {field_field_type, 2, .inherited = true},
    {field_filed_name, 2, .inherited = true},
  [6] =
    {field_field, 0, .inherited = true},
    {field_field, 1, .inherited = true},
    {field_field_type, 0, .inherited = true},
    {field_field_type, 1, .inherited = true},
    {field_filed_name, 0, .inherited = true},
    {field_filed_name, 1, .inherited = true},
  [12] =
    {field_field, 1},
    {field_field, 3},
    {field_field_type, 2},
    {field_filed_name, 0},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 100,
  [101] = 101,
  [102] = 102,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(6);
      if (lookahead == '"') ADVANCE(1);
      if (lookahead == '\'') ADVANCE(5);
      if (lookahead == '(') ADVANCE(10);
      if (lookahead == ')') ADVANCE(11);
      if (lookahead == ',') ADVANCE(12);
      if (lookahead == '-') ADVANCE(3);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == ':') ADVANCE(9);
      if (lookahead == ';') ADVANCE(23);
      if (lookahead == '<') ADVANCE(16);
      if (lookahead == '=') ADVANCE(8);
      if (lookahead == '>') ADVANCE(17);
      if (lookahead == '{') ADVANCE(14);
      if (lookahead == '|') ADVANCE(13);
      if (lookahead == '}') ADVANCE(15);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(18);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(22);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(20);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '\'') ADVANCE(21);
      END_STATE();
    case 3:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(18);
      END_STATE();
    case 4:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(19);
      END_STATE();
    case 5:
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(2);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(sym_int);
      if (lookahead == '.') ADVANCE(4);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(18);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(sym_real);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(19);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(sym_char);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(22);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(sym__semicolon);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'b') ADVANCE(1);
      if (lookahead == 'c') ADVANCE(2);
      if (lookahead == 'e') ADVANCE(3);
      if (lookahead == 'f') ADVANCE(4);
      if (lookahead == 'i') ADVANCE(5);
      if (lookahead == 'l') ADVANCE(6);
      if (lookahead == 'm') ADVANCE(7);
      if (lookahead == 'n') ADVANCE(8);
      if (lookahead == 'o') ADVANCE(9);
      if (lookahead == 'p') ADVANCE(10);
      if (lookahead == 'r') ADVANCE(11);
      if (lookahead == 's') ADVANCE(12);
      if (lookahead == 't') ADVANCE(13);
      if (lookahead == 'v') ADVANCE(14);
      if (lookahead == 'w') ADVANCE(15);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(16);
      END_STATE();
    case 2:
      if (lookahead == 'h') ADVANCE(17);
      if (lookahead == 'o') ADVANCE(18);
      END_STATE();
    case 3:
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'x') ADVANCE(20);
      END_STATE();
    case 4:
      if (lookahead == 'a') ADVANCE(21);
      END_STATE();
    case 5:
      if (lookahead == 'n') ADVANCE(22);
      END_STATE();
    case 6:
      if (lookahead == 'i') ADVANCE(23);
      END_STATE();
    case 7:
      if (lookahead == 'a') ADVANCE(24);
      if (lookahead == 'o') ADVANCE(25);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(26);
      END_STATE();
    case 9:
      if (lookahead == 'f') ADVANCE(27);
      END_STATE();
    case 10:
      if (lookahead == 'o') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(29);
      END_STATE();
    case 11:
      if (lookahead == 'd') ADVANCE(30);
      if (lookahead == 'e') ADVANCE(31);
      END_STATE();
    case 12:
      if (lookahead == 'e') ADVANCE(32);
      if (lookahead == 't') ADVANCE(33);
      END_STATE();
    case 13:
      if (lookahead == 'o') ADVANCE(34);
      if (lookahead == 'r') ADVANCE(35);
      if (lookahead == 'y') ADVANCE(36);
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(37);
      END_STATE();
    case 15:
      if (lookahead == 'r') ADVANCE(38);
      END_STATE();
    case 16:
      if (lookahead == 'o') ADVANCE(39);
      END_STATE();
    case 17:
      if (lookahead == 'a') ADVANCE(40);
      END_STATE();
    case 18:
      if (lookahead == 'm') ADVANCE(41);
      END_STATE();
    case 19:
      if (lookahead == 'd') ADVANCE(42);
      END_STATE();
    case 20:
      if (lookahead == 't') ADVANCE(43);
      END_STATE();
    case 21:
      if (lookahead == 'l') ADVANCE(44);
      END_STATE();
    case 22:
      if (lookahead == 't') ADVANCE(45);
      END_STATE();
    case 23:
      if (lookahead == 's') ADVANCE(46);
      END_STATE();
    case 24:
      if (lookahead == 'p') ADVANCE(47);
      END_STATE();
    case 25:
      if (lookahead == 'd') ADVANCE(48);
      END_STATE();
    case 26:
      if (lookahead == 't') ADVANCE(49);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_of);
      END_STATE();
    case 28:
      if (lookahead == 's') ADVANCE(50);
      END_STATE();
    case 29:
      if (lookahead == 'e') ADVANCE(51);
      if (lookahead == 'o') ADVANCE(52);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_rd);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(53);
      END_STATE();
    case 32:
      if (lookahead == 't') ADVANCE(54);
      END_STATE();
    case 33:
      if (lookahead == 'r') ADVANCE(55);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_to);
      END_STATE();
    case 35:
      if (lookahead == 'u') ADVANCE(56);
      END_STATE();
    case 36:
      if (lookahead == 'p') ADVANCE(57);
      END_STATE();
    case 37:
      if (lookahead == 'r') ADVANCE(58);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_wr);
      END_STATE();
    case 39:
      if (lookahead == 'l') ADVANCE(59);
      END_STATE();
    case 40:
      if (lookahead == 'r') ADVANCE(60);
      END_STATE();
    case 41:
      if (lookahead == 'p') ADVANCE(61);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_end);
      if (lookahead == '_') ADVANCE(62);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_ext);
      END_STATE();
    case 44:
      if (lookahead == 's') ADVANCE(63);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_int);
      END_STATE();
    case 46:
      if (lookahead == 't') ADVANCE(64);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_map);
      END_STATE();
    case 48:
      if (lookahead == 'u') ADVANCE(65);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_nat);
      if (lookahead == '0') ADVANCE(66);
      END_STATE();
    case 50:
      if (lookahead == 't') ADVANCE(67);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_pre);
      END_STATE();
    case 52:
      if (lookahead == 'c') ADVANCE(68);
      END_STATE();
    case 53:
      if (lookahead == 'l') ADVANCE(69);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_set);
      END_STATE();
    case 55:
      if (lookahead == 'i') ADVANCE(70);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(71);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(72);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_var);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_char);
      END_STATE();
    case 61:
      if (lookahead == 'o') ADVANCE(73);
      END_STATE();
    case 62:
      if (lookahead == 'p') ADVANCE(74);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(75);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_list);
      END_STATE();
    case 65:
      if (lookahead == 'l') ADVANCE(76);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_nat0);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_post);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(77);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_real);
      END_STATE();
    case 70:
      if (lookahead == 'n') ADVANCE(78);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_type);
      END_STATE();
    case 73:
      if (lookahead == 's') ADVANCE(79);
      END_STATE();
    case 74:
      if (lookahead == 'r') ADVANCE(80);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 76:
      if (lookahead == 'e') ADVANCE(81);
      END_STATE();
    case 77:
      if (lookahead == 's') ADVANCE(82);
      END_STATE();
    case 78:
      if (lookahead == 'g') ADVANCE(83);
      END_STATE();
    case 79:
      if (lookahead == 'e') ADVANCE(84);
      END_STATE();
    case 80:
      if (lookahead == 'o') ADVANCE(85);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_module);
      END_STATE();
    case 82:
      if (lookahead == 's') ADVANCE(86);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_string);
      END_STATE();
    case 84:
      if (lookahead == 'd') ADVANCE(87);
      END_STATE();
    case 85:
      if (lookahead == 'c') ADVANCE(88);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_process);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_composed);
      END_STATE();
    case 88:
      if (lookahead == 'e') ADVANCE(89);
      END_STATE();
    case 89:
      if (lookahead == 's') ADVANCE(90);
      END_STATE();
    case 90:
      if (lookahead == 's') ADVANCE(91);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_end_process);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_module] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_type] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_var] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_process] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_end_process] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_ext] = ACTIONS(1),
    [anon_sym_pre] = ACTIONS(1),
    [anon_sym_post] = ACTIONS(1),
    [anon_sym_wr] = ACTIONS(1),
    [anon_sym_rd] = ACTIONS(1),
    [anon_sym_nat] = ACTIONS(1),
    [anon_sym_nat0] = ACTIONS(1),
    [anon_sym_real] = ACTIONS(1),
    [anon_sym_int] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [anon_sym_char] = ACTIONS(1),
    [anon_sym_string] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_set] = ACTIONS(1),
    [anon_sym_of] = ACTIONS(1),
    [anon_sym_list] = ACTIONS(1),
    [anon_sym_map] = ACTIONS(1),
    [anon_sym_to] = ACTIONS(1),
    [anon_sym_composed] = ACTIONS(1),
    [anon_sym_end] = ACTIONS(1),
    [sym_int] = ACTIONS(1),
    [sym_real] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_char] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [sym__semicolon] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(101),
    [sym_module_definition] = STATE(17),
    [anon_sym_module] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 8,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(86), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [37] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(19), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(52), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [74] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(21), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(82), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [111] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(23), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(43), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [148] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(25), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(18), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [185] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(27), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(21), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [222] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(29), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(84), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [259] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(31), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(79), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [296] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(33), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(41), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [333] = 8,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_map,
    ACTIONS(17), 1,
      anon_sym_composed,
    ACTIONS(35), 1,
      sym_identifier,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
    STATE(22), 7,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_map_type,
      sym_composite_type,
  [370] = 5,
    ACTIONS(39), 1,
      anon_sym_LPAREN,
    ACTIONS(37), 2,
      sym_int,
      sym_identifier,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(102), 2,
      sym__expression,
      sym_bool,
    ACTIONS(41), 3,
      sym_real,
      sym_string,
      sym_char,
  [391] = 5,
    ACTIONS(39), 1,
      anon_sym_LPAREN,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(45), 2,
      sym_int,
      sym_identifier,
    STATE(99), 2,
      sym__expression,
      sym_bool,
    ACTIONS(47), 3,
      sym_real,
      sym_string,
      sym_char,
  [412] = 5,
    ACTIONS(39), 1,
      anon_sym_LPAREN,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(49), 2,
      sym_int,
      sym_identifier,
    STATE(97), 2,
      sym__expression,
      sym_bool,
    ACTIONS(51), 3,
      sym_real,
      sym_string,
      sym_char,
  [433] = 5,
    ACTIONS(39), 1,
      anon_sym_LPAREN,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(53), 2,
      sym_int,
      sym_identifier,
    STATE(93), 2,
      sym__expression,
      sym_bool,
    ACTIONS(55), 3,
      sym_real,
      sym_string,
      sym_char,
  [454] = 5,
    ACTIONS(39), 1,
      anon_sym_LPAREN,
    ACTIONS(43), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(57), 2,
      sym_int,
      sym_identifier,
    STATE(87), 2,
      sym__expression,
      sym_bool,
    ACTIONS(59), 3,
      sym_real,
      sym_string,
      sym_char,
  [475] = 8,
    ACTIONS(61), 1,
      ts_builtin_sym_end,
    ACTIONS(63), 1,
      anon_sym_type,
    ACTIONS(65), 1,
      anon_sym_var,
    ACTIONS(67), 1,
      anon_sym_process,
    STATE(26), 1,
      sym_type_definition,
    STATE(31), 1,
      sym_variable_definition,
    STATE(74), 1,
      sym_process_definition,
    STATE(39), 2,
      sym_process_definition_item,
      aux_sym_process_definition_repeat1,
  [501] = 1,
    ACTIONS(69), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [512] = 1,
    ACTIONS(71), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [523] = 1,
    ACTIONS(73), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [534] = 1,
    ACTIONS(75), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [545] = 1,
    ACTIONS(77), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [556] = 1,
    ACTIONS(79), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [567] = 1,
    ACTIONS(81), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [578] = 1,
    ACTIONS(83), 8,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
      anon_sym_to,
      sym__semicolon,
  [589] = 6,
    ACTIONS(65), 1,
      anon_sym_var,
    ACTIONS(67), 1,
      anon_sym_process,
    ACTIONS(85), 1,
      ts_builtin_sym_end,
    STATE(33), 1,
      sym_variable_definition,
    STATE(96), 1,
      sym_process_definition,
    STATE(39), 2,
      sym_process_definition_item,
      aux_sym_process_definition_repeat1,
  [609] = 4,
    ACTIONS(87), 1,
      ts_builtin_sym_end,
    ACTIONS(89), 1,
      sym_identifier,
    ACTIONS(91), 2,
      anon_sym_var,
      anon_sym_process,
    STATE(28), 2,
      sym_type_definition_item,
      aux_sym_type_definition_repeat1,
  [624] = 4,
    ACTIONS(93), 1,
      ts_builtin_sym_end,
    ACTIONS(95), 1,
      sym_identifier,
    ACTIONS(98), 2,
      anon_sym_var,
      anon_sym_process,
    STATE(28), 2,
      sym_type_definition_item,
      aux_sym_type_definition_repeat1,
  [639] = 3,
    ACTIONS(100), 1,
      anon_sym_pre,
    ACTIONS(102), 2,
      anon_sym_wr,
      anon_sym_rd,
    STATE(29), 2,
      sym_ext_item,
      aux_sym_process_body_repeat1,
  [651] = 4,
    ACTIONS(105), 1,
      ts_builtin_sym_end,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(110), 1,
      anon_sym_process,
    STATE(30), 2,
      sym_variable_definition_item,
      aux_sym_variable_definition_repeat1,
  [665] = 4,
    ACTIONS(67), 1,
      anon_sym_process,
    ACTIONS(85), 1,
      ts_builtin_sym_end,
    STATE(96), 1,
      sym_process_definition,
    STATE(39), 2,
      sym_process_definition_item,
      aux_sym_process_definition_repeat1,
  [679] = 4,
    ACTIONS(112), 1,
      ts_builtin_sym_end,
    ACTIONS(114), 1,
      sym_identifier,
    ACTIONS(116), 1,
      anon_sym_process,
    STATE(30), 2,
      sym_variable_definition_item,
      aux_sym_variable_definition_repeat1,
  [693] = 4,
    ACTIONS(67), 1,
      anon_sym_process,
    ACTIONS(118), 1,
      ts_builtin_sym_end,
    STATE(94), 1,
      sym_process_definition,
    STATE(39), 2,
      sym_process_definition_item,
      aux_sym_process_definition_repeat1,
  [707] = 3,
    ACTIONS(120), 1,
      anon_sym_pre,
    ACTIONS(122), 2,
      anon_sym_wr,
      anon_sym_rd,
    STATE(29), 2,
      sym_ext_item,
      aux_sym_process_body_repeat1,
  [719] = 2,
    ACTIONS(124), 1,
      ts_builtin_sym_end,
    ACTIONS(126), 3,
      anon_sym_var,
      anon_sym_process,
      sym_identifier,
  [728] = 3,
    ACTIONS(128), 1,
      ts_builtin_sym_end,
    ACTIONS(130), 1,
      anon_sym_process,
    STATE(36), 2,
      sym_process_definition_item,
      aux_sym_process_definition_repeat1,
  [739] = 1,
    ACTIONS(133), 4,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
  [746] = 4,
    ACTIONS(135), 1,
      anon_sym_PIPE,
    ACTIONS(137), 1,
      anon_sym_ext,
    ACTIONS(139), 1,
      anon_sym_pre,
    STATE(81), 1,
      sym_process_body,
  [759] = 3,
    ACTIONS(67), 1,
      anon_sym_process,
    ACTIONS(141), 1,
      ts_builtin_sym_end,
    STATE(36), 2,
      sym_process_definition_item,
      aux_sym_process_definition_repeat1,
  [770] = 1,
    ACTIONS(143), 4,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_var,
      anon_sym_process,
  [777] = 1,
    ACTIONS(133), 4,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
  [784] = 1,
    ACTIONS(145), 4,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_var,
      anon_sym_process,
  [791] = 1,
    ACTIONS(147), 4,
      anon_sym_RPAREN,
      anon_sym_PIPE,
      anon_sym_ext,
      anon_sym_pre,
  [798] = 2,
    ACTIONS(122), 2,
      anon_sym_wr,
      anon_sym_rd,
    STATE(34), 2,
      sym_ext_item,
      aux_sym_process_body_repeat1,
  [807] = 1,
    ACTIONS(149), 3,
      anon_sym_RPAREN,
      anon_sym_end_process,
      anon_sym_post,
  [813] = 1,
    ACTIONS(151), 3,
      anon_sym_RPAREN,
      anon_sym_end_process,
      anon_sym_post,
  [819] = 3,
    ACTIONS(153), 1,
      anon_sym_COMMA,
    ACTIONS(155), 1,
      anon_sym_RBRACE,
    STATE(57), 1,
      aux_sym_enumeration_type_repeat1,
  [829] = 3,
    ACTIONS(157), 1,
      sym_identifier,
    ACTIONS(159), 1,
      anon_sym_end,
    STATE(59), 1,
      aux_sym_composite_type_repeat1,
  [839] = 2,
    ACTIONS(161), 1,
      ts_builtin_sym_end,
    ACTIONS(163), 2,
      anon_sym_process,
      sym_identifier,
  [847] = 3,
    ACTIONS(165), 1,
      sym_identifier,
    ACTIONS(168), 1,
      anon_sym_end,
    STATE(50), 1,
      aux_sym_composite_type_repeat1,
  [857] = 3,
    ACTIONS(170), 1,
      anon_sym_COLON,
    ACTIONS(172), 1,
      anon_sym_COMMA,
    STATE(55), 1,
      aux_sym_parameter_list_repeat1,
  [867] = 1,
    ACTIONS(174), 3,
      anon_sym_pre,
      anon_sym_wr,
      anon_sym_rd,
  [873] = 3,
    ACTIONS(176), 1,
      anon_sym_COMMA,
    ACTIONS(179), 1,
      anon_sym_RBRACE,
    STATE(53), 1,
      aux_sym_enumeration_type_repeat1,
  [883] = 2,
    ACTIONS(181), 1,
      sym_identifier,
    STATE(27), 2,
      sym_type_definition_item,
      aux_sym_type_definition_repeat1,
  [891] = 3,
    ACTIONS(183), 1,
      anon_sym_COLON,
    ACTIONS(185), 1,
      anon_sym_COMMA,
    STATE(55), 1,
      aux_sym_parameter_list_repeat1,
  [901] = 3,
    ACTIONS(172), 1,
      anon_sym_COMMA,
    ACTIONS(188), 1,
      anon_sym_COLON,
    STATE(51), 1,
      aux_sym_parameter_list_repeat1,
  [911] = 3,
    ACTIONS(153), 1,
      anon_sym_COMMA,
    ACTIONS(190), 1,
      anon_sym_RBRACE,
    STATE(53), 1,
      aux_sym_enumeration_type_repeat1,
  [921] = 2,
    ACTIONS(192), 1,
      sym_identifier,
    STATE(32), 2,
      sym_variable_definition_item,
      aux_sym_variable_definition_repeat1,
  [929] = 3,
    ACTIONS(157), 1,
      sym_identifier,
    ACTIONS(194), 1,
      anon_sym_end,
    STATE(50), 1,
      aux_sym_composite_type_repeat1,
  [939] = 2,
    ACTIONS(196), 1,
      anon_sym_SLASH,
    ACTIONS(198), 1,
      sym__semicolon,
  [946] = 1,
    ACTIONS(200), 2,
      anon_sym_end,
      sym_identifier,
  [951] = 2,
    ACTIONS(202), 1,
      sym_identifier,
    STATE(38), 1,
      sym_parameter_list,
  [958] = 1,
    ACTIONS(204), 2,
      ts_builtin_sym_end,
      anon_sym_process,
  [963] = 1,
    ACTIONS(183), 2,
      anon_sym_COLON,
      anon_sym_COMMA,
  [968] = 2,
    ACTIONS(206), 1,
      anon_sym_LT,
    STATE(47), 1,
      sym_enumeration_value,
  [975] = 2,
    ACTIONS(135), 1,
      anon_sym_PIPE,
    ACTIONS(208), 1,
      anon_sym_RPAREN,
  [982] = 2,
    ACTIONS(206), 1,
      anon_sym_LT,
    STATE(70), 1,
      sym_enumeration_value,
  [989] = 2,
    ACTIONS(202), 1,
      sym_identifier,
    STATE(66), 1,
      sym_parameter_list,
  [996] = 1,
    ACTIONS(210), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1001] = 1,
    ACTIONS(179), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1006] = 2,
    ACTIONS(202), 1,
      sym_identifier,
    STATE(37), 1,
      sym_parameter_list,
  [1013] = 1,
    ACTIONS(212), 1,
      sym_identifier,
  [1017] = 1,
    ACTIONS(214), 1,
      anon_sym_COLON,
  [1021] = 1,
    ACTIONS(85), 1,
      ts_builtin_sym_end,
  [1025] = 1,
    ACTIONS(216), 1,
      anon_sym_EQ,
  [1029] = 1,
    ACTIONS(218), 1,
      sym_identifier,
  [1033] = 1,
    ACTIONS(220), 1,
      anon_sym_GT,
  [1037] = 1,
    ACTIONS(222), 1,
      sym_identifier,
  [1041] = 1,
    ACTIONS(224), 1,
      anon_sym_to,
  [1045] = 1,
    ACTIONS(226), 1,
      sym_identifier,
  [1049] = 1,
    ACTIONS(228), 1,
      anon_sym_end_process,
  [1053] = 1,
    ACTIONS(230), 1,
      sym__semicolon,
  [1057] = 1,
    ACTIONS(232), 1,
      sym_identifier,
  [1061] = 1,
    ACTIONS(234), 1,
      sym__semicolon,
  [1065] = 1,
    ACTIONS(236), 1,
      sym_identifier,
  [1069] = 1,
    ACTIONS(238), 1,
      sym__semicolon,
  [1073] = 1,
    ACTIONS(240), 1,
      anon_sym_post,
  [1077] = 1,
    ACTIONS(242), 1,
      sym__semicolon,
  [1081] = 1,
    ACTIONS(244), 1,
      anon_sym_of,
  [1085] = 1,
    ACTIONS(246), 1,
      anon_sym_COLON,
  [1089] = 1,
    ACTIONS(248), 1,
      anon_sym_of,
  [1093] = 1,
    ACTIONS(250), 1,
      anon_sym_of,
  [1097] = 1,
    ACTIONS(252), 1,
      anon_sym_RPAREN,
  [1101] = 1,
    ACTIONS(254), 1,
      ts_builtin_sym_end,
  [1105] = 1,
    ACTIONS(256), 1,
      sym__semicolon,
  [1109] = 1,
    ACTIONS(118), 1,
      ts_builtin_sym_end,
  [1113] = 1,
    ACTIONS(258), 1,
      anon_sym_post,
  [1117] = 1,
    ACTIONS(260), 1,
      anon_sym_LPAREN,
  [1121] = 1,
    ACTIONS(262), 1,
      anon_sym_end_process,
  [1125] = 1,
    ACTIONS(264), 1,
      anon_sym_COLON,
  [1129] = 1,
    ACTIONS(266), 1,
      ts_builtin_sym_end,
  [1133] = 1,
    ACTIONS(268), 1,
      anon_sym_end_process,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 37,
  [SMALL_STATE(4)] = 74,
  [SMALL_STATE(5)] = 111,
  [SMALL_STATE(6)] = 148,
  [SMALL_STATE(7)] = 185,
  [SMALL_STATE(8)] = 222,
  [SMALL_STATE(9)] = 259,
  [SMALL_STATE(10)] = 296,
  [SMALL_STATE(11)] = 333,
  [SMALL_STATE(12)] = 370,
  [SMALL_STATE(13)] = 391,
  [SMALL_STATE(14)] = 412,
  [SMALL_STATE(15)] = 433,
  [SMALL_STATE(16)] = 454,
  [SMALL_STATE(17)] = 475,
  [SMALL_STATE(18)] = 501,
  [SMALL_STATE(19)] = 512,
  [SMALL_STATE(20)] = 523,
  [SMALL_STATE(21)] = 534,
  [SMALL_STATE(22)] = 545,
  [SMALL_STATE(23)] = 556,
  [SMALL_STATE(24)] = 567,
  [SMALL_STATE(25)] = 578,
  [SMALL_STATE(26)] = 589,
  [SMALL_STATE(27)] = 609,
  [SMALL_STATE(28)] = 624,
  [SMALL_STATE(29)] = 639,
  [SMALL_STATE(30)] = 651,
  [SMALL_STATE(31)] = 665,
  [SMALL_STATE(32)] = 679,
  [SMALL_STATE(33)] = 693,
  [SMALL_STATE(34)] = 707,
  [SMALL_STATE(35)] = 719,
  [SMALL_STATE(36)] = 728,
  [SMALL_STATE(37)] = 739,
  [SMALL_STATE(38)] = 746,
  [SMALL_STATE(39)] = 759,
  [SMALL_STATE(40)] = 770,
  [SMALL_STATE(41)] = 777,
  [SMALL_STATE(42)] = 784,
  [SMALL_STATE(43)] = 791,
  [SMALL_STATE(44)] = 798,
  [SMALL_STATE(45)] = 807,
  [SMALL_STATE(46)] = 813,
  [SMALL_STATE(47)] = 819,
  [SMALL_STATE(48)] = 829,
  [SMALL_STATE(49)] = 839,
  [SMALL_STATE(50)] = 847,
  [SMALL_STATE(51)] = 857,
  [SMALL_STATE(52)] = 867,
  [SMALL_STATE(53)] = 873,
  [SMALL_STATE(54)] = 883,
  [SMALL_STATE(55)] = 891,
  [SMALL_STATE(56)] = 901,
  [SMALL_STATE(57)] = 911,
  [SMALL_STATE(58)] = 921,
  [SMALL_STATE(59)] = 929,
  [SMALL_STATE(60)] = 939,
  [SMALL_STATE(61)] = 946,
  [SMALL_STATE(62)] = 951,
  [SMALL_STATE(63)] = 958,
  [SMALL_STATE(64)] = 963,
  [SMALL_STATE(65)] = 968,
  [SMALL_STATE(66)] = 975,
  [SMALL_STATE(67)] = 982,
  [SMALL_STATE(68)] = 989,
  [SMALL_STATE(69)] = 996,
  [SMALL_STATE(70)] = 1001,
  [SMALL_STATE(71)] = 1006,
  [SMALL_STATE(72)] = 1013,
  [SMALL_STATE(73)] = 1017,
  [SMALL_STATE(74)] = 1021,
  [SMALL_STATE(75)] = 1025,
  [SMALL_STATE(76)] = 1029,
  [SMALL_STATE(77)] = 1033,
  [SMALL_STATE(78)] = 1037,
  [SMALL_STATE(79)] = 1041,
  [SMALL_STATE(80)] = 1045,
  [SMALL_STATE(81)] = 1049,
  [SMALL_STATE(82)] = 1053,
  [SMALL_STATE(83)] = 1057,
  [SMALL_STATE(84)] = 1061,
  [SMALL_STATE(85)] = 1065,
  [SMALL_STATE(86)] = 1069,
  [SMALL_STATE(87)] = 1073,
  [SMALL_STATE(88)] = 1077,
  [SMALL_STATE(89)] = 1081,
  [SMALL_STATE(90)] = 1085,
  [SMALL_STATE(91)] = 1089,
  [SMALL_STATE(92)] = 1093,
  [SMALL_STATE(93)] = 1097,
  [SMALL_STATE(94)] = 1101,
  [SMALL_STATE(95)] = 1105,
  [SMALL_STATE(96)] = 1109,
  [SMALL_STATE(97)] = 1113,
  [SMALL_STATE(98)] = 1117,
  [SMALL_STATE(99)] = 1121,
  [SMALL_STATE(100)] = 1125,
  [SMALL_STATE(101)] = 1129,
  [SMALL_STATE(102)] = 1133,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(86),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(92),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(89),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(82),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(84),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(102),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(99),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(97),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [55] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(87),
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_type, 4, .production_id = 2),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration_type, 4),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_composite_type, 3),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_type, 3),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_set_type, 3),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration_type, 3),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_composite_type, 4, .production_id = 3),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primitive_type, 1),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_definition, 2),
  [89] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [91] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type_definition, 2),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_definition_repeat1, 2),
  [95] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_type_definition_repeat1, 2), SHIFT_REPEAT(75),
  [98] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_type_definition_repeat1, 2),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_process_body_repeat1, 2),
  [102] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_process_body_repeat1, 2), SHIFT_REPEAT(83),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_variable_definition_repeat1, 2),
  [107] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_variable_definition_repeat1, 2), SHIFT_REPEAT(100),
  [110] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_variable_definition_repeat1, 2),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable_definition, 2),
  [114] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [116] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_variable_definition, 2),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 3),
  [120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_definition_item, 4),
  [126] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type_definition_item, 4),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_process_definition_repeat1, 2),
  [130] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_process_definition_repeat1, 2), SHIFT_REPEAT(85),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_list, 3),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [139] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_process_definition, 1),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module_definition, 5, .production_id = 1),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module_definition, 3, .production_id = 1),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_list, 4),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bool, 1),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 3),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [157] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [159] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable_definition_item, 4),
  [163] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_variable_definition_item, 4),
  [165] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_composite_type_repeat1, 2, .production_id = 4), SHIFT_REPEAT(73),
  [168] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_composite_type_repeat1, 2, .production_id = 4),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ext_item, 4),
  [176] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enumeration_type_repeat1, 2), SHIFT_REPEAT(67),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enumeration_type_repeat1, 2),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameter_list_repeat1, 2),
  [185] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameter_list_repeat1, 2), SHIFT_REPEAT(78),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [194] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [200] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_composite_type_repeat1, 4, .production_id = 5),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [204] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_process_definition_item, 9),
  [206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration_value, 3),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [214] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [216] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 4),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_process_body, 4),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [266] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_process_body, 6),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_sofl() {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
