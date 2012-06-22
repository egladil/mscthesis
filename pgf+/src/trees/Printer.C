/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"

namespace gf
{
//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + 2;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == '}')
  {
     _n_ = _n_ - 2;
     backup();
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(c);
     bufAppend(' ');
  }
}
void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}
void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char* PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}
void PrintAbsyn::visitTree(Tree*p) {} //abstract class

void PrintAbsyn::visitLambda(Lambda* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  render('\\');
  visitIdent(p->ident_);
  render("->");
  _i_ = 0; p->tree_->accept(this);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitVariable(Variable* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  render('$');
  visitInteger(p->integer_);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitApplication(Application* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  render('(');
  _i_ = 0; p->tree_1->accept(this);
  _i_ = 0; p->tree_2->accept(this);
  render(')');

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitLiteral(Literal* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  _i_ = 0; p->lit_->accept(this);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitMetaVariable(MetaVariable* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  render("META_");
  visitInteger(p->integer_);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitFunction(Function* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitLit(Lit*p) {} //abstract class

void PrintAbsyn::visitIntLiteral(IntLiteral* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitFloatLiteral(FloatLiteral* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  visitDouble(p->double_);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitStringLiteral(StringLiteral* p)
{
  int oldi = _i_;
  if (oldi > 0) render(GF__L_PAREN);

  visitString(p->string_);

  if (oldi > 0) render(GF__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void PrintAbsyn::visitString(String s_)
{
  const char *s = s_.c_str() ;
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void PrintAbsyn::visitIdent(String s_)
{
  const char *s = s_.c_str() ;
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char* ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}
void ShowAbsyn::visitTree(Tree* p) {} //abstract class

void ShowAbsyn::visitLambda(Lambda* p)
{
  bufAppend('(');
  bufAppend("Lambda");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->tree_)  p->tree_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitVariable(Variable* p)
{
  bufAppend('(');
  bufAppend("Variable");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitApplication(Application* p)
{
  bufAppend('(');
  bufAppend("Application");
  bufAppend(' ');
  p->tree_1->accept(this);
  bufAppend(' ');
  p->tree_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitLiteral(Literal* p)
{
  bufAppend('(');
  bufAppend("Literal");
  bufAppend(' ');
  bufAppend('[');
  if (p->lit_)  p->lit_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitMetaVariable(MetaVariable* p)
{
  bufAppend('(');
  bufAppend("MetaVariable");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitFunction(Function* p)
{
  bufAppend('(');
  bufAppend("Function");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitLit(Lit* p) {} //abstract class

void ShowAbsyn::visitIntLiteral(IntLiteral* p)
{
  bufAppend('(');
  bufAppend("IntLiteral");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitFloatLiteral(FloatLiteral* p)
{
  bufAppend('(');
  bufAppend("FloatLiteral");
  bufAppend(' ');
  visitDouble(p->double_);
  bufAppend(')');
}
void ShowAbsyn::visitStringLiteral(StringLiteral* p)
{
  bufAppend('(');
  bufAppend("StringLiteral");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s_)
{
  const char *s = s_.c_str() ;
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s_)
{
  const char *s = s_.c_str() ;
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

}
