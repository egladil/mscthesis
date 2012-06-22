/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"


namespace gf
{
void Skeleton::visitTree(Tree* t) {} //abstract class
void Skeleton::visitLit(Lit* t) {} //abstract class

void Skeleton::visitLambda(Lambda *lambda)
{
  /* Code For Lambda Goes Here */

  visitIdent(lambda->ident_);
  lambda->tree_->accept(this);

}

void Skeleton::visitVariable(Variable *variable)
{
  /* Code For Variable Goes Here */

  visitInteger(variable->integer_);

}

void Skeleton::visitApplication(Application *application)
{
  /* Code For Application Goes Here */

  application->tree_1->accept(this);
  application->tree_2->accept(this);

}

void Skeleton::visitLiteral(Literal *literal)
{
  /* Code For Literal Goes Here */

  literal->lit_->accept(this);

}

void Skeleton::visitMetaVariable(MetaVariable *metavariable)
{
  /* Code For MetaVariable Goes Here */

  visitInteger(metavariable->integer_);

}

void Skeleton::visitFunction(Function *function)
{
  /* Code For Function Goes Here */

  visitIdent(function->ident_);

}

void Skeleton::visitIntLiteral(IntLiteral *intliteral)
{
  /* Code For IntLiteral Goes Here */

  visitInteger(intliteral->integer_);

}

void Skeleton::visitFloatLiteral(FloatLiteral *floatliteral)
{
  /* Code For FloatLiteral Goes Here */

  visitDouble(floatliteral->double_);

}

void Skeleton::visitStringLiteral(StringLiteral *stringliteral)
{
  /* Code For StringLiteral Goes Here */

  visitString(stringliteral->string_);

}



void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}


}
