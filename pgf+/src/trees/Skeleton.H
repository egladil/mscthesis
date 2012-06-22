#ifndef GF_SKELETON_HEADER
#define GF_SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"

namespace gf
{
class Skeleton : public Visitor
{
public:
  void visitTree(Tree* p);
  void visitLit(Lit* p);
  void visitLambda(Lambda* p);
  void visitVariable(Variable* p);
  void visitApplication(Application* p);
  void visitLiteral(Literal* p);
  void visitMetaVariable(MetaVariable* p);
  void visitFunction(Function* p);
  void visitIntLiteral(IntLiteral* p);
  void visitFloatLiteral(FloatLiteral* p);
  void visitStringLiteral(StringLiteral* p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

};
}

#endif
