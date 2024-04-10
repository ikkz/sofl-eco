#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 46
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 49
#define ALIAS_COUNT 0
#define TOKEN_COUNT 35
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 2
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 4

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_module = 2,
  anon_sym_SLASH = 3,
  anon_sym_type = 4,
  anon_sym_EQ = 5,
  sym_int = 6,
  sym_real = 7,
  sym_string = 8,
  sym_char = 9,
  anon_sym_true = 10,
  anon_sym_false = 11,
  anon_sym_nat = 12,
  anon_sym_nat0 = 13,
  anon_sym_real = 14,
  anon_sym_int = 15,
  anon_sym_bool = 16,
  anon_sym_char = 17,
  anon_sym_string = 18,
  anon_sym_LBRACE = 19,
  anon_sym_COMMA = 20,
  anon_sym_RBRACE = 21,
  anon_sym_LT = 22,
  anon_sym_GT = 23,
  anon_sym_set = 24,
  anon_sym_of = 25,
  anon_sym_list = 26,
  anon_sym_composed = 27,
  anon_sym_COLON = 28,
  anon_sym_end = 29,
  anon_sym_map = 30,
  anon_sym_to = 31,
  anon_sym_LPAREN = 32,
  anon_sym_RPAREN = 33,
  sym__semicolon = 34,
  sym_source_file = 35,
  sym_module_definition = 36,
  sym_type_definition = 37,
  sym_type_definition_item = 38,
  sym__type = 39,
  sym_primitive_type = 40,
  sym_enumeration_type = 41,
  sym_enumeration_value = 42,
  sym_set_type = 43,
  sym_list_type = 44,
  sym_composite_type = 45,
  aux_sym_type_definition_repeat1 = 46,
  aux_sym_enumeration_type_repeat1 = 47,
  aux_sym_composite_type_repeat1 = 48,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_module] = "module",
  [anon_sym_SLASH] = "/",
  [anon_sym_type] = "type",
  [anon_sym_EQ] = "=",
  [sym_int] = "int",
  [sym_real] = "real",
  [sym_string] = "string",
  [sym_char] = "char",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [anon_sym_nat] = "nat",
  [anon_sym_nat0] = "nat0",
  [anon_sym_real] = "real",
  [anon_sym_int] = "int",
  [anon_sym_bool] = "bool",
  [anon_sym_char] = "char",
  [anon_sym_string] = "string",
  [anon_sym_LBRACE] = "{",
  [anon_sym_COMMA] = ",",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_set] = "set",
  [anon_sym_of] = "of",
  [anon_sym_list] = "list",
  [anon_sym_composed] = "composed",
  [anon_sym_COLON] = ":",
  [anon_sym_end] = "end",
  [anon_sym_map] = "map",
  [anon_sym_to] = "to",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym__semicolon] = "_semicolon",
  [sym_source_file] = "source_file",
  [sym_module_definition] = "module_definition",
  [sym_type_definition] = "type_definition",
  [sym_type_definition_item] = "type_definition_item",
  [sym__type] = "_type",
  [sym_primitive_type] = "primitive_type",
  [sym_enumeration_type] = "enumeration_type",
  [sym_enumeration_value] = "enumeration_value",
  [sym_set_type] = "set_type",
  [sym_list_type] = "list_type",
  [sym_composite_type] = "composite_type",
  [aux_sym_type_definition_repeat1] = "type_definition_repeat1",
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
  [sym_int] = sym_int,
  [sym_real] = sym_real,
  [sym_string] = sym_string,
  [sym_char] = sym_char,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [anon_sym_nat] = anon_sym_nat,
  [anon_sym_nat0] = anon_sym_nat0,
  [anon_sym_real] = anon_sym_real,
  [anon_sym_int] = anon_sym_int,
  [anon_sym_bool] = anon_sym_bool,
  [anon_sym_char] = anon_sym_char,
  [anon_sym_string] = anon_sym_string,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_set] = anon_sym_set,
  [anon_sym_of] = anon_sym_of,
  [anon_sym_list] = anon_sym_list,
  [anon_sym_composed] = anon_sym_composed,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_end] = anon_sym_end,
  [anon_sym_map] = anon_sym_map,
  [anon_sym_to] = anon_sym_to,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym__semicolon] = sym__semicolon,
  [sym_source_file] = sym_source_file,
  [sym_module_definition] = sym_module_definition,
  [sym_type_definition] = sym_type_definition,
  [sym_type_definition_item] = sym_type_definition_item,
  [sym__type] = sym__type,
  [sym_primitive_type] = sym_primitive_type,
  [sym_enumeration_type] = sym_enumeration_type,
  [sym_enumeration_value] = sym_enumeration_value,
  [sym_set_type] = sym_set_type,
  [sym_list_type] = sym_list_type,
  [sym_composite_type] = sym_composite_type,
  [aux_sym_type_definition_repeat1] = aux_sym_type_definition_repeat1,
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
  [anon_sym_COMMA] = {
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
  [anon_sym_composed] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_end] = {
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
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
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
  [sym_composite_type] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_type_definition_repeat1] = {
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
  field_field_type = 1,
  field_filed_name = 2,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_field_type] = "field_type",
  [field_filed_name] = "filed_name",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 2},
  [2] = {.index = 2, .length = 4},
  [3] = {.index = 6, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_field_type, 2, .inherited = true},
    {field_filed_name, 2, .inherited = true},
  [2] =
    {field_field_type, 0, .inherited = true},
    {field_field_type, 1, .inherited = true},
    {field_filed_name, 0, .inherited = true},
    {field_filed_name, 1, .inherited = true},
  [6] =
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
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(6);
      if (lookahead == '"') ADVANCE(1);
      if (lookahead == '\'') ADVANCE(5);
      if (lookahead == '(') ADVANCE(19);
      if (lookahead == ')') ADVANCE(20);
      if (lookahead == ',') ADVANCE(14);
      if (lookahead == '-') ADVANCE(3);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == ':') ADVANCE(18);
      if (lookahead == ';') ADVANCE(22);
      if (lookahead == '<') ADVANCE(16);
      if (lookahead == '=') ADVANCE(8);
      if (lookahead == '>') ADVANCE(17);
      if (lookahead == '{') ADVANCE(13);
      if (lookahead == '}') ADVANCE(15);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(21);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(11);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '\'') ADVANCE(12);
      END_STATE();
    case 3:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 4:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(10);
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
      ACCEPT_TOKEN(sym_int);
      if (lookahead == '.') ADVANCE(4);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(sym_real);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(10);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym_char);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_COMMA);
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
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(21);
      END_STATE();
    case 22:
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
      if (lookahead == 'r') ADVANCE(10);
      if (lookahead == 's') ADVANCE(11);
      if (lookahead == 't') ADVANCE(12);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(13);
      END_STATE();
    case 2:
      if (lookahead == 'h') ADVANCE(14);
      if (lookahead == 'o') ADVANCE(15);
      END_STATE();
    case 3:
      if (lookahead == 'n') ADVANCE(16);
      END_STATE();
    case 4:
      if (lookahead == 'a') ADVANCE(17);
      END_STATE();
    case 5:
      if (lookahead == 'n') ADVANCE(18);
      END_STATE();
    case 6:
      if (lookahead == 'i') ADVANCE(19);
      END_STATE();
    case 7:
      if (lookahead == 'a') ADVANCE(20);
      if (lookahead == 'o') ADVANCE(21);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(22);
      END_STATE();
    case 9:
      if (lookahead == 'f') ADVANCE(23);
      END_STATE();
    case 10:
      if (lookahead == 'e') ADVANCE(24);
      END_STATE();
    case 11:
      if (lookahead == 'e') ADVANCE(25);
      if (lookahead == 't') ADVANCE(26);
      END_STATE();
    case 12:
      if (lookahead == 'o') ADVANCE(27);
      if (lookahead == 'r') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(29);
      END_STATE();
    case 13:
      if (lookahead == 'o') ADVANCE(30);
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(31);
      END_STATE();
    case 15:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 16:
      if (lookahead == 'd') ADVANCE(33);
      END_STATE();
    case 17:
      if (lookahead == 'l') ADVANCE(34);
      END_STATE();
    case 18:
      if (lookahead == 't') ADVANCE(35);
      END_STATE();
    case 19:
      if (lookahead == 's') ADVANCE(36);
      END_STATE();
    case 20:
      if (lookahead == 'p') ADVANCE(37);
      END_STATE();
    case 21:
      if (lookahead == 'd') ADVANCE(38);
      END_STATE();
    case 22:
      if (lookahead == 't') ADVANCE(39);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_of);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(40);
      END_STATE();
    case 25:
      if (lookahead == 't') ADVANCE(41);
      END_STATE();
    case 26:
      if (lookahead == 'r') ADVANCE(42);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_to);
      END_STATE();
    case 28:
      if (lookahead == 'u') ADVANCE(43);
      END_STATE();
    case 29:
      if (lookahead == 'p') ADVANCE(44);
      END_STATE();
    case 30:
      if (lookahead == 'l') ADVANCE(45);
      END_STATE();
    case 31:
      if (lookahead == 'r') ADVANCE(46);
      END_STATE();
    case 32:
      if (lookahead == 'p') ADVANCE(47);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_end);
      END_STATE();
    case 34:
      if (lookahead == 's') ADVANCE(48);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_int);
      END_STATE();
    case 36:
      if (lookahead == 't') ADVANCE(49);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_map);
      END_STATE();
    case 38:
      if (lookahead == 'u') ADVANCE(50);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_nat);
      if (lookahead == '0') ADVANCE(51);
      END_STATE();
    case 40:
      if (lookahead == 'l') ADVANCE(52);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_set);
      END_STATE();
    case 42:
      if (lookahead == 'i') ADVANCE(53);
      END_STATE();
    case 43:
      if (lookahead == 'e') ADVANCE(54);
      END_STATE();
    case 44:
      if (lookahead == 'e') ADVANCE(55);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_char);
      END_STATE();
    case 47:
      if (lookahead == 'o') ADVANCE(56);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(57);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_list);
      END_STATE();
    case 50:
      if (lookahead == 'l') ADVANCE(58);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_nat0);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_real);
      END_STATE();
    case 53:
      if (lookahead == 'n') ADVANCE(59);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_type);
      END_STATE();
    case 56:
      if (lookahead == 's') ADVANCE(60);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(61);
      END_STATE();
    case 59:
      if (lookahead == 'g') ADVANCE(62);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(63);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_module);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_string);
      END_STATE();
    case 63:
      if (lookahead == 'd') ADVANCE(64);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_composed);
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
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_module] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_type] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [sym_int] = ACTIONS(1),
    [sym_real] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_char] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [anon_sym_nat] = ACTIONS(1),
    [anon_sym_nat0] = ACTIONS(1),
    [anon_sym_real] = ACTIONS(1),
    [anon_sym_int] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [anon_sym_char] = ACTIONS(1),
    [anon_sym_string] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_set] = ACTIONS(1),
    [anon_sym_of] = ACTIONS(1),
    [anon_sym_list] = ACTIONS(1),
    [anon_sym_composed] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_end] = ACTIONS(1),
    [anon_sym_map] = ACTIONS(1),
    [anon_sym_to] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym__semicolon] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(45),
    [sym_module_definition] = STATE(13),
    [anon_sym_module] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 7,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_composed,
    STATE(32), 6,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_composite_type,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
  [33] = 7,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_composed,
    ACTIONS(17), 1,
      sym_identifier,
    STATE(33), 6,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_composite_type,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
  [66] = 7,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_composed,
    ACTIONS(19), 1,
      sym_identifier,
    STATE(27), 6,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_composite_type,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
  [99] = 7,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    ACTIONS(11), 1,
      anon_sym_set,
    ACTIONS(13), 1,
      anon_sym_list,
    ACTIONS(15), 1,
      anon_sym_composed,
    ACTIONS(21), 1,
      sym_identifier,
    STATE(44), 6,
      sym__type,
      sym_primitive_type,
      sym_enumeration_type,
      sym_set_type,
      sym_list_type,
      sym_composite_type,
    ACTIONS(7), 7,
      anon_sym_nat,
      anon_sym_nat0,
      anon_sym_real,
      anon_sym_int,
      anon_sym_bool,
      anon_sym_char,
      anon_sym_string,
  [132] = 3,
    ACTIONS(23), 1,
      ts_builtin_sym_end,
    ACTIONS(25), 1,
      sym_identifier,
    STATE(7), 2,
      sym_type_definition_item,
      aux_sym_type_definition_repeat1,
  [143] = 3,
    ACTIONS(27), 1,
      ts_builtin_sym_end,
    ACTIONS(29), 1,
      sym_identifier,
    STATE(7), 2,
      sym_type_definition_item,
      aux_sym_type_definition_repeat1,
  [154] = 3,
    ACTIONS(32), 1,
      anon_sym_COMMA,
    ACTIONS(34), 1,
      anon_sym_RBRACE,
    STATE(9), 1,
      aux_sym_enumeration_type_repeat1,
  [164] = 3,
    ACTIONS(36), 1,
      anon_sym_COMMA,
    ACTIONS(39), 1,
      anon_sym_RBRACE,
    STATE(9), 1,
      aux_sym_enumeration_type_repeat1,
  [174] = 2,
    ACTIONS(25), 1,
      sym_identifier,
    STATE(6), 2,
      sym_type_definition_item,
      aux_sym_type_definition_repeat1,
  [182] = 3,
    ACTIONS(41), 1,
      sym_identifier,
    ACTIONS(43), 1,
      anon_sym_end,
    STATE(15), 1,
      aux_sym_composite_type_repeat1,
  [192] = 3,
    ACTIONS(41), 1,
      sym_identifier,
    ACTIONS(45), 1,
      anon_sym_end,
    STATE(11), 1,
      aux_sym_composite_type_repeat1,
  [202] = 3,
    ACTIONS(47), 1,
      ts_builtin_sym_end,
    ACTIONS(49), 1,
      anon_sym_type,
    STATE(43), 1,
      sym_type_definition,
  [212] = 3,
    ACTIONS(32), 1,
      anon_sym_COMMA,
    ACTIONS(51), 1,
      anon_sym_RBRACE,
    STATE(8), 1,
      aux_sym_enumeration_type_repeat1,
  [222] = 3,
    ACTIONS(53), 1,
      sym_identifier,
    ACTIONS(56), 1,
      anon_sym_end,
    STATE(15), 1,
      aux_sym_composite_type_repeat1,
  [232] = 1,
    ACTIONS(58), 2,
      ts_builtin_sym_end,
      anon_sym_type,
  [237] = 1,
    ACTIONS(39), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [242] = 1,
    ACTIONS(60), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [247] = 1,
    ACTIONS(62), 2,
      anon_sym_end,
      sym_identifier,
  [252] = 1,
    ACTIONS(64), 2,
      ts_builtin_sym_end,
      anon_sym_type,
  [257] = 2,
    ACTIONS(66), 1,
      anon_sym_LT,
    STATE(14), 1,
      sym_enumeration_value,
  [264] = 2,
    ACTIONS(68), 1,
      anon_sym_SLASH,
    ACTIONS(70), 1,
      sym__semicolon,
  [271] = 2,
    ACTIONS(66), 1,
      anon_sym_LT,
    STATE(17), 1,
      sym_enumeration_value,
  [278] = 1,
    ACTIONS(72), 2,
      ts_builtin_sym_end,
      sym_identifier,
  [283] = 1,
    ACTIONS(74), 1,
      sym_identifier,
  [287] = 1,
    ACTIONS(76), 1,
      sym_identifier,
  [291] = 1,
    ACTIONS(78), 1,
      sym__semicolon,
  [295] = 1,
    ACTIONS(80), 1,
      anon_sym_GT,
  [299] = 1,
    ACTIONS(82), 1,
      anon_sym_of,
  [303] = 1,
    ACTIONS(84), 1,
      sym__semicolon,
  [307] = 1,
    ACTIONS(86), 1,
      anon_sym_of,
  [311] = 1,
    ACTIONS(88), 1,
      sym__semicolon,
  [315] = 1,
    ACTIONS(90), 1,
      sym__semicolon,
  [319] = 1,
    ACTIONS(92), 1,
      sym__semicolon,
  [323] = 1,
    ACTIONS(94), 1,
      anon_sym_COLON,
  [327] = 1,
    ACTIONS(96), 1,
      anon_sym_of,
  [331] = 1,
    ACTIONS(98), 1,
      sym__semicolon,
  [335] = 1,
    ACTIONS(100), 1,
      sym__semicolon,
  [339] = 1,
    ACTIONS(102), 1,
      sym__semicolon,
  [343] = 1,
    ACTIONS(104), 1,
      anon_sym_EQ,
  [347] = 1,
    ACTIONS(106), 1,
      sym_identifier,
  [351] = 1,
    ACTIONS(108), 1,
      sym__semicolon,
  [355] = 1,
    ACTIONS(110), 1,
      ts_builtin_sym_end,
  [359] = 1,
    ACTIONS(112), 1,
      sym__semicolon,
  [363] = 1,
    ACTIONS(114), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 33,
  [SMALL_STATE(4)] = 66,
  [SMALL_STATE(5)] = 99,
  [SMALL_STATE(6)] = 132,
  [SMALL_STATE(7)] = 143,
  [SMALL_STATE(8)] = 154,
  [SMALL_STATE(9)] = 164,
  [SMALL_STATE(10)] = 174,
  [SMALL_STATE(11)] = 182,
  [SMALL_STATE(12)] = 192,
  [SMALL_STATE(13)] = 202,
  [SMALL_STATE(14)] = 212,
  [SMALL_STATE(15)] = 222,
  [SMALL_STATE(16)] = 232,
  [SMALL_STATE(17)] = 237,
  [SMALL_STATE(18)] = 242,
  [SMALL_STATE(19)] = 247,
  [SMALL_STATE(20)] = 252,
  [SMALL_STATE(21)] = 257,
  [SMALL_STATE(22)] = 264,
  [SMALL_STATE(23)] = 271,
  [SMALL_STATE(24)] = 278,
  [SMALL_STATE(25)] = 283,
  [SMALL_STATE(26)] = 287,
  [SMALL_STATE(27)] = 291,
  [SMALL_STATE(28)] = 295,
  [SMALL_STATE(29)] = 299,
  [SMALL_STATE(30)] = 303,
  [SMALL_STATE(31)] = 307,
  [SMALL_STATE(32)] = 311,
  [SMALL_STATE(33)] = 315,
  [SMALL_STATE(34)] = 319,
  [SMALL_STATE(35)] = 323,
  [SMALL_STATE(36)] = 327,
  [SMALL_STATE(37)] = 331,
  [SMALL_STATE(38)] = 335,
  [SMALL_STATE(39)] = 339,
  [SMALL_STATE(40)] = 343,
  [SMALL_STATE(41)] = 347,
  [SMALL_STATE(42)] = 351,
  [SMALL_STATE(43)] = 355,
  [SMALL_STATE(44)] = 359,
  [SMALL_STATE(45)] = 363,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_definition, 2),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_definition_repeat1, 2),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_definition_repeat1, 2), SHIFT_REPEAT(40),
  [32] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [34] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [36] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enumeration_type_repeat1, 2), SHIFT_REPEAT(23),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enumeration_type_repeat1, 2),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [53] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_composite_type_repeat1, 2, .production_id = 2), SHIFT_REPEAT(35),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_composite_type_repeat1, 2, .production_id = 2),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module_definition, 3),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration_value, 3),
  [62] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_composite_type_repeat1, 4, .production_id = 3),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module_definition, 5),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_definition_item, 4),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [82] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration_type, 3),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_set_type, 3),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_type, 3),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_composite_type, 3),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [96] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primitive_type, 1),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enumeration_type, 4),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_composite_type, 4, .production_id = 1),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2),
  [112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [114] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
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
