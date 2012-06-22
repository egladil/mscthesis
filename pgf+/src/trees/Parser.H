#ifndef GF_PARSER_HEADER_FILE
#define GF_PARSER_HEADER_FILE

#include<vector>
#include<string>

namespace gf
{
class Tree;
class Lit;

typedef union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  Tree* tree_;
  Lit* lit_;
} YYSTYPE;

Tree* pTree(FILE *inp);
Tree* pTree(const char *str);
Lit* pLit(FILE *inp);
Lit* pLit(const char *str);

}

#define GF__ERROR_ 258
#define GF__SYMB_0 259
#define GF__SYMB_1 260
#define GF__SYMB_2 261
#define GF__SYMB_3 262
#define GF__SYMB_4 263
#define GF__SYMB_5 264
#define GF__STRING_ 265
#define GF__INTEGER_ 266
#define GF__DOUBLE_ 267
#define GF__IDENT_ 268

extern gf::YYSTYPE gfyylval;

#endif
