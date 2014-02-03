/**
   derived from
   http://www.lysator.liu.se/c/ANSI-C-grammar-y.html

   This defines the c grammar in C++
   to use for language generation and test generation.
**/

#define TOKEN(X) Token X( #X );
#define RULEA(X) Rule _ ## X   ();

// create an instance
//#define RULEB(X) Rule2 X( #X, _ ## X   () );

#define RULEB(X) Rule3 X( #X );
#define RULE(X) RULEA(X) RULEB(X)
#define RULEC(X) X( #X );

#define RULE3(X) RULEC(X)

#include <iostream>

class OutputObject {
 public:
  OutputObject(){};

};

class OutputGenerator
{
 protected:
  const OutputGenerator & r;
 protected:
 OutputGenerator(const OutputGenerator & r):r(r){    }
 public:
 OutputGenerator(OutputGenerator & r):r(r) {
  }
  virtual OutputObject emit() const {
    std::cout << "BASE{" << std::endl;
    //std::cout << (void*)&r;
    
    std::cout << "}ENDBASE" << std::endl;;
    //throw "TODO";
    return OutputObject ();
  }
};

class None : public OutputGenerator {
  virtual OutputObject emit() const {
    std::cout << "NONE" << std::endl;
    return OutputObject();
  }
} none(none);


class Evaluator { 
  //push (
};

/* class OutputGeneratorRef{ */
/*   const OutputGenerator & r; */
/*  public: */
/*  OutputGeneratorRef(const OutputGenerator & r): r(r) { */
/*     //emit(); */
/*   } */
/*   virtual OutputObject emit() {  */
/*     //r.emit();   */
/*   } */
/* }; */

/* class OutputGeneratorPtr : public OutputGenerator{ */
/*   const OutputGenerator * p; */
/*  public: */

/*  OutputGeneratorPtr(const OutputGenerator * p): p(p) { */
/*     //    if (p) { */
/*       //p->emit(); */
/*     //    } */
/*     //emit(); */
/*   } */

/*   virtual OutputObject emit() const { */
/*     std::cout << "PTR:" << std::endl; */
/*     if(p) { p->emit();} */
/*   } */

/* }; */

class Pair : public OutputGenerator {
 protected:
  //  const OutputGenerator & a;
  const OutputGenerator & b;
 public:
 Pair(const OutputGenerator & a, const OutputGenerator & b):  
  OutputGenerator(a), 
    b(b) {  
      //emit(); 
    }
 Pair(const Pair & p)
   : 
  OutputGenerator(p.r), 
    b(p.b) 
      { 
        //emit(); 
      }


};

class Rule : public OutputGenerator {
  /*
    will be called as the return from the parse routine
  */
 public:

  // Rule(const char name [], Rule & func)
  //   : name(name), func(func) {
  //    func.emit();
  //}

  //Rule(const Rule & r):r(r){   std::cout << "INIT1:" << std::endl;  };

 Rule(const OutputGenerator & r):
  OutputGenerator(r)
  {    std::cout << "INIT2:" << std::endl;  };

  // Rule() {}
  // Rule(OutputGenerator func) :func(func) {}
  //  Rule & operator = (Rule & r) {    r.emit();  }
  virtual OutputObject emit() const {
    std::cout << "RULE:" << std::endl;
    return OutputGenerator::emit();
  }

};

class Rule2  : public OutputGenerator {
  //  Rule & func;
  const char * name;
 public:

 Rule2(const char * name , Rule func)
   : 
  OutputGenerator(func) ,
    name(name)
    {

      //std::cout << "creating" << std::endl;
      //emit();
      //func.emit();
    }

  virtual OutputObject emit() const {
    std::cout << "R:" << name << std::endl;
    //r.emit();
    return OutputGenerator::emit();
  }
  //  operator Rule () {   }

};


class Rule3 : public OutputGenerator {
  const char * name;
 public:
 Rule3(const char * name )    : 
  OutputGenerator(none) ,
    name(name)
    {}

  virtual OutputObject emit() const {
    std::cout << "RULE3 " << name << std::endl;
    return OutputGenerator::emit();
  }
};

class Or : public Pair {
 public :
 Or(const OutputGenerator & a, const OutputGenerator & b):  Pair(a,b) {     
    //emit();
  }
  //  operator Rule(){   };

  virtual OutputObject emit() const {
    std::cout << "RULEOK{A:" << std::endl;
    r.emit();
    std::cout << "} _OR_ {" << std::endl;
    b.emit();
    std::cout << "}" << std::endl;
    return OutputGenerator::emit();
  }
};

class Plus : public Pair {
 public :
 Plus(const OutputGenerator & a, const OutputGenerator & b):  Pair(a,b) 
    {
      //emit();   
    }
  //  operator Rule() {   }

  virtual OutputObject emit() const {
    std::cout << "RULEPLUS{A:" << std::endl;
    r.emit();
    std::cout << "} _PLUS_ {" << std::endl;
    b.emit();
    std::cout << "}" << std::endl;
    return OutputGenerator::emit();
  }
};


Or operator | (const OutputGenerator & a, const OutputGenerator & b) {  
  return Or(a,b); }

class Token : public OutputGenerator {
 public:
  const char * v;

 Token(const char * v)   : 
  OutputGenerator(none),
    v(v)
    {
      //emit();
      //    std::cout << "Value:" << v << std::endl;
  }

  virtual OutputObject emit() const {
    //    std::cout << "TOKEN:" << std::endl;
    //OutputGenerator::emit();
    //std::cout << "V:" << v << std::endl;
    std::cout << "Token('" << v << "')";
    return OutputGenerator::emit();
  }
};

class TokenChar : public OutputGenerator {
 public:
  char v;
 TokenChar(char v): 
  OutputGenerator(none), 
    v(v)  {
    //emit();
  }
  //  OutputGenerator operator ()() { return OutputGeneratorPtr(this); }

 TokenChar(const TokenChar & t): 
  OutputGenerator(none),
    v(t.v)
      {
        //emit();
      };

  virtual OutputObject emit() const {
    std::cout << "TOKENc('" << v << "')" << std::endl;
    //  OutputGenerator::emit();
    //std::cout  << v ;
    return OutputGenerator::emit();
  }

};


Plus operator + (const OutputGenerator & a, const OutputGenerator & b ){

  Plus r = Plus(a,b);
  //r.emit();
  return r;
}

//Plus operator + (const TokenChar & a, const Rule2 & b ){  return Plus(a,b);  }



TokenChar token(const char c) {
  return TokenChar(c);
}



TOKEN(ADD_ASSIGN)
TOKEN(AND_ASSIGN)
TOKEN(AND_OP)
TOKEN(AUTO)
TOKEN(BREAK)
TOKEN(CASE)
TOKEN(CHAR)
TOKEN(CONST)
TOKEN(CONSTANT)
TOKEN(CONTINUE)
TOKEN(DEC_OP)
TOKEN(DEFAULT)
TOKEN(DIV_ASSIGN)
TOKEN(DO)
TOKEN(DOUBLE)
TOKEN(ELLIPSIS)
TOKEN(ELSE)
TOKEN(ENUM)
TOKEN(EQ_OP)
TOKEN(EXTERN)
TOKEN(FLOAT)
TOKEN(FOR)
TOKEN(GE_OP)
TOKEN(GOTO)
TOKEN(IDENTIFIER)
TOKEN(IF)
TOKEN(INC_OP)
TOKEN(INT)
TOKEN(LEFT_ASSIGN)
TOKEN(LEFT_OP)
TOKEN(LE_OP)
TOKEN(LONG)
TOKEN(MOD_ASSIGN)
TOKEN(MUL_ASSIGN)
TOKEN(NE_OP)
TOKEN(OR_ASSIGN)
TOKEN(OR_OP)
TOKEN(PTR_OP)
TOKEN(REGISTER)
TOKEN(RETURN)
TOKEN(RIGHT_ASSIGN)
TOKEN(RIGHT_OP)
TOKEN(SHORT)
TOKEN(SIGNED)
TOKEN(SIZEOF)
TOKEN(STATIC)
TOKEN(STRING_LITERAL)
TOKEN(STRUCT)
TOKEN(SUB_ASSIGN)
TOKEN(SWITCH)
TOKEN(TYPEDEF)
TOKEN(TYPE_NAME)
TOKEN(UNION)
TOKEN(UNSIGNED)
TOKEN(VOID)
TOKEN(VOLATILE)
TOKEN(WHILE)
TOKEN(XOR_ASSIGN)


RULE(abstract_declarator)
RULE(additive_expression)
RULE(and_expression)
RULE(argument_expression_list)
//RULE(assignment_expression)
RULE(assignment_operator)
RULE(cast_expression)
RULE(compound_statement)
//RULE(conditional_expression)
RULE(constant_expression)
RULE(declaration)
RULE(declaration_list)
RULE(declaration_specifiers)
RULE(declarator)
RULE(direct_abstract_declarator)
RULE(direct_declarator)
RULE(enum_specifier)
RULE(enumerator)
RULE(enumerator_list)
RULE(equality_expression)
RULE(exclusive_or_expression)

RULE(expression_statement)
RULE(external_declaration)
RULE(function_definition)
RULE(identifier_list)
RULE(inclusive_or_expression)
RULE(init_declarator)
RULE(init_declarator_list)
RULE(initializer)
RULE(initializer_list)
RULE(iteration_statement)
RULE(jump_statement)
RULE(labeled_statement)
//RULE(logical_and_expression)

RULE(multiplicative_expression)
RULE(parameter_declaration)
RULE(parameter_list)
RULE(pointer)
RULE(postfix_expression)

RULE(relational_expression)
RULE(selection_statement)
RULE(shift_expression)
RULE(specifier_qualifier_list)
RULE(statement)
RULE(statement_list)
RULE(storage_class_specifier)
RULE(struct_declaration)
RULE(struct_declaration_list)
RULE(struct_declarator)
RULE(struct_declarator_list)
RULE(struct_or_union)
RULE(struct_or_union_specifier)
RULE(translation_unit)
RULE(type_name)
RULE(type_qualifier)
RULE(type_qualifier_list)
RULE(type_specifier)
RULE(unary_expression)
RULE(unary_operator)
RULE(parameter_type_list)

TokenChar TOKEN_OPEN_PAREN('(');
TokenChar TOKEN_CLOSE_PAREN (')');
TokenChar TOKEN_PLUS('+');
TokenChar TOKEN_COLON(':');
TokenChar TOKEN_QUESTION('?');
TokenChar TOKEN_COMMA(',');

class BaseRule : public OutputGenerator {
  const char * name;
 public:
  
 BaseRule(const char *name): 
  OutputGenerator(none),
    name(name)
    {}

  //  virtual Rule parse() const {}
  virtual OutputObject emit() const
  {
    std::cout << "BaseRule:" << name << std::endl;;
    //Rule r = parse();

    //r.emit();
    return OutputGenerator::emit();
  }
};

class BaseExpression : public BaseRule {
 public:
 BaseExpression(const char *name): BaseRule(name) {}
};

class Expression : public BaseExpression {
 public:
 Expression(const char *name): BaseExpression(name) {}
  Rule parse();
} RULE3(expression);


class LogicalExpression : public BaseExpression {
 public:
 LogicalExpression(const char *name): BaseExpression(name) {}
};

class LogicalOrExpression : public LogicalExpression {
 public:
 LogicalOrExpression(const char *name): LogicalExpression(name) {}
  Rule parse();
} RULE3(logical_or_expression)


class LogicalAndExpression : public LogicalExpression {
 public:
 LogicalAndExpression(const char *name): LogicalExpression(name) {}
  Rule parse();
  } RULE3(logical_and_expression)

  Rule LogicalAndExpression::parse() {
    return inclusive_or_expression
      | (logical_and_expression + AND_OP + inclusive_or_expression)
      ;
    }


Rule LogicalOrExpression::parse() {
  return logical_and_expression
    | (logical_or_expression + OR_OP +  logical_and_expression)
    ;
}

class ConditionalExpression : public BaseExpression {
 public:
 ConditionalExpression(const char *name): BaseExpression(name) {}
  Rule parse();
} RULE3(conditional_expression);

Rule ConditionalExpression::parse()
{
  return logical_or_expression
    | (logical_or_expression + TOKEN_QUESTION + expression + TOKEN_COLON + conditional_expression);
}

class AssignmentExpression : public BaseExpression {
 public:
 AssignmentExpression(const char *name): BaseExpression(name) {}
  Rule parse();
} RULE3(assignment_expression);

Rule AssignmentExpression::parse()   {
  return
    conditional_expression
    | (unary_expression +  assignment_operator + assignment_expression)
    ;
};

Rule Expression::parse()
{
  return assignment_expression
    | (expression + TOKEN_COMMA + assignment_expression)
    ;
}

class PrimaryExpression : public Expression
{
 public:
 PrimaryExpression(const char *name): Expression(name) {}
  Rule parse()   {
    return IDENTIFIER
      | CONSTANT
      | STRING_LITERAL
      | (TOKEN_OPEN_PAREN  + expression + TOKEN_CLOSE_PAREN)
      ;
  }
} RULE3(primary_expression);




Rule  _postfix_expression() {
  return primary_expression
    | (postfix_expression + token('[') + expression + token(']'))
    | (postfix_expression + TOKEN_OPEN_PAREN + TOKEN_CLOSE_PAREN)
    | (postfix_expression + TOKEN_OPEN_PAREN + argument_expression_list + TOKEN_CLOSE_PAREN)
    | (postfix_expression + token('.') + IDENTIFIER)
    | (postfix_expression + PTR_OP + IDENTIFIER)
    | (postfix_expression + INC_OP)
    | (postfix_expression + DEC_OP)
    ;
}

Rule _argument_expression_list() {
  return assignment_expression
    | (argument_expression_list + TOKEN_COMMA + assignment_expression)
    ;
}


Rule _unary_expression()
{
  return
    postfix_expression
    | (INC_OP + unary_expression)
    | (DEC_OP + unary_expression)
    | (unary_operator + cast_expression)
    | (SIZEOF + unary_expression)
    | (SIZEOF + TOKEN_OPEN_PAREN + type_name + TOKEN_CLOSE_PAREN)
    ;
}


Rule _cast_expression() {
  return unary_expression
    | (TOKEN_OPEN_PAREN + type_name + TOKEN_CLOSE_PAREN + cast_expression);

}

Rule _unary_operator() {
  return token('&')
    |  token('*')
    |  TOKEN_PLUS
    |  token('-')
    |  token('~')
    |  token('!')
    ;}


Rule _multiplicative_expression() {
  return cast_expression
    | (multiplicative_expression + token('*') + cast_expression)
    | (multiplicative_expression + token('/') + cast_expression)
    | (multiplicative_expression + token('%') + cast_expression)
    ;
}

Rule _additive_expression() {
  return multiplicative_expression
    | (additive_expression + TOKEN_PLUS + multiplicative_expression)
    | (additive_expression + token('-') + multiplicative_expression)
    ;
}

Rule _shift_expression() {
  return additive_expression
    | (shift_expression + LEFT_OP + additive_expression)
    | (shift_expression + RIGHT_OP + additive_expression)
    ;
}

Rule _relational_expression() {
  return shift_expression
    | (relational_expression + token('<') + shift_expression)
    | (relational_expression + token('>') + shift_expression)
    | (relational_expression + LE_OP + shift_expression)
    | (relational_expression + GE_OP + shift_expression)
    ;
}
Rule _equality_expression() {
  return relational_expression
    | (equality_expression + EQ_OP  +relational_expression)
    | (equality_expression + NE_OP  + relational_expression)
    ;
}

Rule _and_expression() {
  return (equality_expression)
    | (and_expression + token('&') + equality_expression)
    ;
}

Rule _exclusive_or_expression() {
    return (and_expression)
      | (exclusive_or_expression + token('^') + and_expression)
    ;
}

Rule _inclusive_or_expression() {
      return (exclusive_or_expression)
        | (inclusive_or_expression + token('|') + exclusive_or_expression)
        ;
}

Rule _assignment_operator() {
  return token('=')
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | ADD_ASSIGN
    | SUB_ASSIGN
    | LEFT_ASSIGN
    | RIGHT_ASSIGN
    | AND_ASSIGN
    | XOR_ASSIGN
    | OR_ASSIGN
    ;
}

Rule _constant_expression() {
  return conditional_expression
    ;
}
Rule _declaration() {
  return (declaration_specifiers + token(';'))
    | (declaration_specifiers + init_declarator_list + token(';'))
    ;
}
Rule _declaration_specifiers() {
    return (storage_class_specifier)
    | (storage_class_specifier + declaration_specifiers)
    | (type_specifier)
    | (type_specifier + declaration_specifiers)
    | (type_qualifier)
      | (type_qualifier + declaration_specifiers)
    ;
}
Rule _init_declarator_list() {
      return (init_declarator)
        | (init_declarator_list + TOKEN_COMMA + init_declarator)
    ;
}
Rule _init_declarator() {
        return (declarator)
          | (declarator + token('=') + initializer)
    ;
}
Rule _storage_class_specifier() {
  return TYPEDEF
    | EXTERN
    | STATIC
    | AUTO
    | REGISTER
    ;
}
Rule _type_specifier() {
  return VOID
    | CHAR
    | SHORT
    | INT
    | LONG
    | FLOAT
    | DOUBLE
    | SIGNED
    | UNSIGNED
    | struct_or_union_specifier
    | enum_specifier
    | TYPE_NAME
    ;
}
Rule _struct_or_union_specifier() {
  return (struct_or_union + IDENTIFIER + token('{') + struct_declaration_list + token('}'))
    | (struct_or_union + token('{') + struct_declaration_list + token('}'))
    | (struct_or_union + IDENTIFIER)
    ;
}
Rule _struct_or_union() {
  return STRUCT
    | UNION
    ;
}
Rule _struct_declaration_list() {
  return (struct_declaration)
  | (struct_declaration_list + struct_declaration)
    ;
}
Rule _struct_declaration() {
  return specifier_qualifier_list + struct_declarator_list + token(';')
    ;
}
Rule _specifier_qualifier_list() {
  return (type_specifier + specifier_qualifier_list)
    | (type_specifier)
    | (type_qualifier + specifier_qualifier_list)
    | (type_qualifier)
    ;
}
Rule _struct_declarator_list() {
  return (struct_declarator)
    | (struct_declarator_list + TOKEN_COMMA + struct_declarator)
    ;
}
Rule _struct_declarator() {
  return (declarator)
    | (TOKEN_COLON + constant_expression)
    | (declarator + TOKEN_COLON + constant_expression)
    ;
}
Rule _enum_specifier() {
  return (ENUM + token('{') + enumerator_list + token('}'))
    | (ENUM + IDENTIFIER + token('{') + enumerator_list + token('}'))
    | (ENUM + IDENTIFIER)
    ;
}
Rule _enumerator_list() {
  return (enumerator)
    | (enumerator_list + TOKEN_COMMA + enumerator)
    ;
}
Rule _enumerator() {
    return (IDENTIFIER)
      | (IDENTIFIER + token('=') + constant_expression)
    ;
}
Rule _type_qualifier() {
  return CONST
    | VOLATILE
    ;
}
Rule _declarator() {
  return (pointer + direct_declarator)
    | direct_declarator
    ;
}
Rule _direct_declarator() {
  return (IDENTIFIER)
    | (TOKEN_OPEN_PAREN + declarator + TOKEN_CLOSE_PAREN)
    | (direct_declarator + token('[') + constant_expression + token(']'))
    | (direct_declarator + token('[') +  token(']'))
    | (direct_declarator + TOKEN_OPEN_PAREN + parameter_type_list + TOKEN_CLOSE_PAREN)
    | (direct_declarator + TOKEN_OPEN_PAREN + identifier_list + TOKEN_CLOSE_PAREN)
    | (direct_declarator + TOKEN_OPEN_PAREN +  TOKEN_CLOSE_PAREN)
    ;
}
Rule _pointer() {
  return (token('*'))
    | (token('*') + type_qualifier_list)
    | (token('*') + pointer)
    | (token('*') + type_qualifier_list + pointer)
    ;
}
Rule _type_qualifier_list() {
  return (type_qualifier)
    | (type_qualifier_list + type_qualifier)
    ;
}

Rule _parameter_type_list() {
  return (parameter_list)
    | (parameter_list + TOKEN_COMMA + ELLIPSIS)
    ;
}
Rule _parameter_list() {
  return (parameter_declaration)
    | (parameter_list + TOKEN_COMMA + parameter_declaration)
    ;
}
Rule _parameter_declaration() {
    return (declaration_specifiers + declarator)
    | (declaration_specifiers + abstract_declarator)
      | (declaration_specifiers)
    ;
}
Rule _identifier_list() {
      return (IDENTIFIER)
        | (identifier_list + TOKEN_COMMA + IDENTIFIER)
    ;
}
Rule _type_name() {
        return (specifier_qualifier_list)
          | (specifier_qualifier_list + abstract_declarator)
    ;
}
Rule _abstract_declarator() {
          return (pointer)
    | (direct_abstract_declarator)
            | (pointer + direct_abstract_declarator)
    ;
}
Rule _direct_abstract_declarator() {
  return (TOKEN_OPEN_PAREN + abstract_declarator + TOKEN_CLOSE_PAREN)
    | (token('[') +  token(']'))
    | (token('[') + constant_expression + token(']'))
    | (direct_abstract_declarator + token('[') +  token(']'))
    | (direct_abstract_declarator + token('[') + constant_expression + token(']'))
    | (TOKEN_OPEN_PAREN +  TOKEN_CLOSE_PAREN)
    | (TOKEN_OPEN_PAREN + parameter_type_list + TOKEN_CLOSE_PAREN)
    | (direct_abstract_declarator + TOKEN_OPEN_PAREN +  TOKEN_CLOSE_PAREN)
    | (direct_abstract_declarator + TOKEN_OPEN_PAREN + parameter_type_list + TOKEN_CLOSE_PAREN)
    ;
}
Rule _initializer() {
  return (assignment_expression)
    | (token('{') + initializer_list + token('}'))
    | (token('{') + initializer_list + TOKEN_COMMA +  token('}'))
    ;
}
Rule _initializer_list() {
    return (initializer)
      | (initializer_list + TOKEN_COMMA + initializer)
    ;
}
Rule _statement() {
  return labeled_statement
    | compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    ;
}
Rule _labeled_statement() {
  return (IDENTIFIER + TOKEN_COLON + statement)
    | (CASE + constant_expression + TOKEN_COLON + statement)
        | (DEFAULT + TOKEN_COLON + statement)
    ;
}
Rule _compound_statement() {
  return (token('{') +  token('}'))
    | (token('{') + statement_list + token('}'))
    | (token('{') + declaration_list + token('}'))
    | (token('{') + declaration_list + statement_list + token('}'))
    ;
}
Rule _declaration_list() {
    return (declaration)
      | (declaration_list + declaration)
    ;
}
Rule _statement_list() {
  return (statement)
    | (statement_list + statement)
    ;
}
Rule _expression_statement() {
  return token(';')
    | (expression + token(';'))
    ;
}
Rule _selection_statement() {
  return (IF + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement)
    | (IF + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement + ELSE + statement)
    | (SWITCH + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement)
    ;
}
Rule _iteration_statement() {
    return (WHILE + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement)
    | (DO + statement + WHILE + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN +  token(';'))
    | (FOR + TOKEN_OPEN_PAREN + expression_statement + expression_statement + TOKEN_CLOSE_PAREN + statement)
      | (FOR + TOKEN_OPEN_PAREN + expression_statement + expression_statement + expression + TOKEN_CLOSE_PAREN + statement)
    ;
}
Rule _jump_statement() {
  return (GOTO + IDENTIFIER + token(';'))
    | (CONTINUE + token(';'))
    | (BREAK + token(';'))
    | (RETURN + token(';'))
    | (RETURN + expression + token(';'))
    ;
}
Rule _translation_unit() {
  return (external_declaration)
  | (translation_unit + external_declaration)
    ;
}

Rule _external_declaration() {
  return (function_definition)
    | (declaration)
    ;
}

Rule _function_definition() {
  return (declaration_specifiers + declarator + declaration_list + compound_statement)
    | (declaration_specifiers + declarator + compound_statement)
    | (declarator + declaration_list + compound_statement)
    | (declarator + compound_statement)
    ;
}

int main() {
  //  translation_unit.emit();
  //type_qualifier.emit();
  //primary_expression.parse();
  //assignment_expression.parse();
  //conditional_expression.parse();
  Rule r = logical_or_expression.parse();
  r.emit();
}
