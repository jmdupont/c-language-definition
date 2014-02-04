/**
   derived from
   http://www.lysator.liu.se/c/ANSI-C-grammar-y.html

   This defines the c grammar in C++
   to use for language generation and test generation.
**/

#define TOKEN(X) Token X( #X );

#define RULEA(X) class _ ## X \
  : public Base {			       \
  public: \
    Rule<Ref> parse ();	\
    const char * get_name() { return #X;} \
  } X;

// create an instance
//#define RULEB(X) 
//template<class T> Rule2<T> X( #X,  );

//#define RULEB(X) _ ## X X( #X );
#define RULE(X) RULEA(X) 
#define RULEC(X) X( #X );
#define RULE3(X) RULEC(X)
#include <tr1/memory>
#include <iostream>

class OutputObject {
 public:
  OutputObject(){};
};

class OutputGenerator
{
 public:
 OutputGenerator(){}
 OutputGenerator(const OutputGenerator & d) {}
 // OutputGenerator(OutputObject r):r(r) {  }
  virtual OutputObject emit() const {
    //std::cout << "BASE{" << std::endl;
    //std::cout << (void*)&r;
    // std::cout << "}ENDBASE" << std::endl;;
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

typedef std::tr1::shared_ptr<OutputGenerator> OutputGeneratorPtr;

class Ref : public OutputGenerator {
 protected:
  OutputGeneratorPtr ptr;
 public:

 Ref(OutputGenerator & r):
  ptr(&r) {}

  // Ref(Ref r):ptr(r.ptr) {}
  // Ref(const Ref r):ptr(r.ptr) {}

 public:
  virtual OutputObject emit() const {
    if (ptr) {
      return ptr->emit();
    }
    return OutputObject();
  }

 Ref(OutputGeneratorPtr & ptr) :ptr(ptr) {}
};

class Pair2 : public OutputGenerator {
 protected:
  OutputGenerator & a;
  OutputGenerator & b;
 public:
 Pair2(OutputGenerator & a, OutputGenerator & b):a(a),b(b) {}
 Pair2(const Pair2 & p):a(p.a),b(p.b){}
};

template <class T> 
class Rule : public OutputGenerator {
  T r;
 public:
  Rule(T r) : r(r){};
 template <class U> Rule(U r) : r(r){};

  virtual OutputObject emit() const {
    std::cout << "RULE:" << std::endl;
    r.emit();
    return OutputGenerator::emit();
  }
};

class Foo {
 public:
  Foo(const char * ) {}

virtual OutputObject emit() const {
    std::cout << "FOO:" << std::endl;
    return OutputObject();
}
  
};

template <class T> class Rule2  : public OutputGenerator {
  T func;
  const char * name;
 public:
 Rule2(const char * name , T func) : func(func), name(name) { }
  
  virtual OutputObject emit() const {
    std::cout << "R:" << name << std::endl;
    func.emit();
    return OutputGenerator::emit();
  }
};


class Rule3 : public OutputGenerator {
  const char * name;
 public:
 Rule3(const char * name )  :  name(name)    {}

  virtual OutputObject emit() const {
    std::cout << "RULE3 " << name << std::endl;
    return OutputGenerator::emit();
  }
};

template <class X, class Y> class Pair : public OutputGenerator {
 protected:
  X a;
  Y b;
 public:
 Pair(X a, Y b):  
  a(a), 
    b(b) {      }

 Pair(const Pair<X,Y> & p)
   : a(p.a), 
    b(p.b)       {       }

};



template <class X, class Y>  class Or : public Pair<X,Y> {
 public :
 Or(X  a, Y b):  Pair<X,Y>(a,b) { }

  OutputObject emit() const {
    Pair<X,Y>::a.emit();
    std::cout << std::endl << "| " ;
    Pair<X,Y>::b.emit();
     return OutputGenerator::emit(); 
  }

};

template <class X, class Y> 
  class Plus : public Pair<X,Y> {
 public :
 Plus(const X & a, const Y & b):  Pair<X,Y>(a,b)     {    }


  OutputObject emit() const {
    Pair<X,Y>::a.emit();
    std::cout << " ";
    Pair<X,Y>::b.emit();
    return OutputGenerator::emit(); 
  }


};

class Token : public OutputGenerator {
 public:
  const char * v;

 Token(const char * v)   : 
    v(v)    {  }

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
   
    v(v)  {
    //emit();
  }
  //  OutputGenerator operator ()() { return OutputGeneratorPtr(this); }

 TokenChar(const TokenChar & t): 
  
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


TokenChar token(const char c) {
  return TokenChar(c);
}

template <class X, class Y>  Ref operator + (X a, Y b) { 
  OutputGeneratorPtr obj(new Plus<X,Y>(a,b));
  return Ref(obj);
}

template <class X, class Y>  Ref operator | (X a, Y b) { 
  OutputGeneratorPtr obj(new Or<X,Y>(a,b));
  return Ref(obj);
}

class Base : public OutputGenerator {};

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

/*
Rule<Ref> _inclusive_or_expression (); 
Foo inclusive_or_expression(
			"inclusive_or_expression"
			);
*/

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
 BaseRule(const char *name): name(name) {}
  virtual OutputObject emit() const{
    std::cout << "R:" << name << " ";

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
  Rule<Ref> parse();
} RULE3(expression);


class LogicalExpression : public BaseExpression {
 public:
 LogicalExpression(const char *name): BaseExpression(name) {}
};

class LogicalAndExpression : public LogicalExpression {
 public:
 LogicalAndExpression(const char *name): LogicalExpression(name) {}
Rule<Ref> parse();
} RULE3(logical_and_expression);

// -----------------------------------------------------------
class LogicalOrExpression : public LogicalExpression {
 public:
 LogicalOrExpression(const char *name): LogicalExpression(name) {}
  Rule<Ref> parse();
} RULE3(logical_or_expression);

Rule<Ref> LogicalOrExpression::parse() {
  return logical_and_expression
    | (logical_or_expression + OR_OP +  logical_and_expression)
    ;
}

// -----------------------------------------------------------
Rule<Ref> LogicalAndExpression::parse() {
  return inclusive_or_expression
    | (logical_and_expression + AND_OP + inclusive_or_expression)
    ;
}

// -----------------------------------------------------------

class ConditionalExpression : public BaseExpression {
 public:
 ConditionalExpression(const char *name): BaseExpression(name) {}
Rule<Ref> parse();
} RULE3(conditional_expression);

Rule<Ref> ConditionalExpression::parse()
{
  return logical_or_expression
    | (logical_or_expression + TOKEN_QUESTION + expression + TOKEN_COLON + conditional_expression);
}

class AssignmentExpression : public BaseExpression {
 public:
 AssignmentExpression(const char *name): BaseExpression(name) {}
Rule<Ref> parse();
} RULE3(assignment_expression);

Rule<Ref> AssignmentExpression::parse()   {
  return
    conditional_expression
    | (unary_expression +  assignment_operator + assignment_expression)
    ;
};

Rule<Ref> Expression::parse()
{
  return assignment_expression
    | (expression + TOKEN_COMMA + assignment_expression)
    ;
}

class PrimaryExpression : public Expression
{
 public:
 PrimaryExpression(const char *name): Expression(name) {}
  Rule<Ref> parse()   {
    return IDENTIFIER
      | CONSTANT
      | STRING_LITERAL
      | (TOKEN_OPEN_PAREN  + expression + TOKEN_CLOSE_PAREN)
      ;
  }
} RULE3(primary_expression);




Rule<Ref>  _postfix_expression::parse() {
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

//Rule<Ref>  _

Rule<Ref>  _argument_expression_list::parse() {
  return assignment_expression
    | (argument_expression_list + TOKEN_COMMA + assignment_expression)
    ;
}


Rule<Ref>  _unary_expression()
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


Rule<Ref>  _cast_expression::parse() {
  return unary_expression
    | (TOKEN_OPEN_PAREN + type_name + TOKEN_CLOSE_PAREN + cast_expression);

}

Rule<Ref>  _unary_operator::parse() {
  return token('&')
    |  token('*')
    |  TOKEN_PLUS
    |  token('-')
    |  token('~')
    |  token('!')
    ;}


Rule<Ref>  _multiplicative_expression::parse() {
  return cast_expression
    | (multiplicative_expression + token('*') + cast_expression)
    | (multiplicative_expression + token('/') + cast_expression)
    | (multiplicative_expression + token('%') + cast_expression)
    ;
}

Rule<Ref>  _additive_expression::parse() {
  return multiplicative_expression
    | (additive_expression + TOKEN_PLUS + multiplicative_expression)
    | (additive_expression + token('-') + multiplicative_expression)
    ;
}

Rule<Ref>  _shift_expression::parse() {
  return additive_expression
    | (shift_expression + LEFT_OP + additive_expression)
    | (shift_expression + RIGHT_OP + additive_expression)
    ;
}

Rule<Ref>  _relational_expression::parse() {
  return shift_expression
    | (relational_expression + token('<') + shift_expression)
    | (relational_expression + token('>') + shift_expression)
    | (relational_expression + LE_OP + shift_expression)
    | (relational_expression + GE_OP + shift_expression)
    ;
}

Rule<Ref>  _equality_expression::parse() {
  return relational_expression
    | (equality_expression + EQ_OP  +relational_expression)
    | (equality_expression + NE_OP  + relational_expression)
    ;
}

Rule<Ref>  _and_expression::parse() {
  return (equality_expression)
    | (and_expression + token('&') + equality_expression)
    ;
}

Rule<Ref>  _exclusive_or_expression::parse() {
    return (and_expression)
      | (exclusive_or_expression + token('^') + and_expression)
    ;
}

Rule<Ref>  _inclusive_or_expression() {
      return (exclusive_or_expression)
        | (inclusive_or_expression + token('|') + exclusive_or_expression)
        ;
}

Rule<Ref>  _assignment_operator::parse() {
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

Rule<Ref>  _constant_expression::parse() {
  return conditional_expression
    ;
}

Rule<Ref>  _declaration::parse() {
  return (declaration_specifiers + token(';'))
    | (declaration_specifiers + init_declarator_list + token(';'))
    ;
}

Rule<Ref>  _declaration_specifiers::parse() {
    return (storage_class_specifier)
    | (storage_class_specifier + declaration_specifiers)
    | (type_specifier)
    | (type_specifier + declaration_specifiers)
    | (type_qualifier)
      | (type_qualifier + declaration_specifiers)
    ;
}

Rule<Ref>  _init_declarator_list() {
      return (init_declarator)
        | (init_declarator_list + TOKEN_COMMA + init_declarator)
    ;
}

Rule<Ref>  _init_declarator() {
        return (declarator)
          | (declarator + token('=') + initializer)
    ;
}

Rule<Ref>  _storage_class_specifier::parse() {
  return TYPEDEF
    | EXTERN
    | STATIC
    | AUTO
    | REGISTER
    ;
}

Rule<Ref>  _type_specifier::parse() {
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

Rule<Ref>  _struct_or_union_specifier::parse() {
  return (struct_or_union + IDENTIFIER + token('{') + struct_declaration_list + token('}'))
    | (struct_or_union + token('{') + struct_declaration_list + token('}'))
    | (struct_or_union + IDENTIFIER)
    ;
}

Rule<Ref>  _struct_or_union::parse() {
  return STRUCT
    | UNION
    ;
}

Rule<Ref>  _struct_declaration_list::parse() {
  return (struct_declaration)
  | (struct_declaration_list + struct_declaration)
    ;
}

Rule<Ref>  _struct_declaration::parse() {
  return specifier_qualifier_list + struct_declarator_list + token(';')
    ;
}

Rule<Ref>  _specifier_qualifier_list::parse() {
  return (type_specifier + specifier_qualifier_list)
    | (type_specifier)
    | (type_qualifier + specifier_qualifier_list)
    | (type_qualifier)
    ;
}

Rule<Ref>  _struct_declarator_list::parse() {
  return (struct_declarator)
    | (struct_declarator_list + TOKEN_COMMA + struct_declarator)
    ;
}

Rule<Ref>  _struct_declarator::parse() {
  return (declarator)
    | (TOKEN_COLON + constant_expression)
    | (declarator + TOKEN_COLON + constant_expression)
    ;
}

Rule<Ref>  _enum_specifier::parse() {
  return (ENUM + token('{') + enumerator_list + token('}'))
    | (ENUM + IDENTIFIER + token('{') + enumerator_list + token('}'))
    | (ENUM + IDENTIFIER)
    ;
}

Rule<Ref>  _enumerator_list::parse() {
  return (enumerator)
    | (enumerator_list + TOKEN_COMMA + enumerator)
    ;
}

Rule<Ref>  _enumerator::parse() {
    return (IDENTIFIER)
      | (IDENTIFIER + token('=') + constant_expression)
    ;
}

Rule<Ref>  _type_qualifier::parse() {
  return CONST
    | VOLATILE
    ;
}

Rule<Ref>  _declarator::parse() {
  return (pointer + direct_declarator)
    | direct_declarator
    ;
}

Rule<Ref>  _direct_declarator::parse() {
  return (IDENTIFIER)
    | (TOKEN_OPEN_PAREN + declarator + TOKEN_CLOSE_PAREN)
    | (direct_declarator + token('[') + constant_expression + token(']'))
    | (direct_declarator + token('[') +  token(']'))
    | (direct_declarator + TOKEN_OPEN_PAREN + parameter_type_list + TOKEN_CLOSE_PAREN)
    | (direct_declarator + TOKEN_OPEN_PAREN + identifier_list + TOKEN_CLOSE_PAREN)
    | (direct_declarator + TOKEN_OPEN_PAREN +  TOKEN_CLOSE_PAREN)
    ;
}

Rule<Ref>  _pointer::parse() {
  return (token('*'))
    | (token('*') + type_qualifier_list)
    | (token('*') + pointer)
    | (token('*') + type_qualifier_list + pointer)
    ;
}

Rule<Ref>  _type_qualifier_list::parse() {
  return (type_qualifier)
    | (type_qualifier_list + type_qualifier)
    ;
}

Rule<Ref>  _parameter_type_list::parse() {
  return (parameter_list)
    | (parameter_list + TOKEN_COMMA + ELLIPSIS)
    ;
}

Rule<Ref>  _parameter_list::parse() {
  return (parameter_declaration)
    | (parameter_list + TOKEN_COMMA + parameter_declaration)
    ;
}

Rule<Ref>  _parameter_declaration::parse() {
    return (declaration_specifiers + declarator)
    | (declaration_specifiers + abstract_declarator)
      | (declaration_specifiers)
    ;
}

Rule<Ref>  _identifier_list() {
      return (IDENTIFIER)
        | (identifier_list + TOKEN_COMMA + IDENTIFIER)
    ;
}

Rule<Ref>  _type_name() {
        return (specifier_qualifier_list)
          | (specifier_qualifier_list + abstract_declarator)
    ;
}

Rule<Ref>  _abstract_declarator() {
          return (pointer)
    | (direct_abstract_declarator)
            | (pointer + direct_abstract_declarator)
    ;
}

Rule<Ref>  _direct_abstract_declarator::parse() {
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

Rule<Ref>  _initializer::parse() {
  return (assignment_expression)
    | (token('{') + initializer_list + token('}'))
    | (token('{') + initializer_list + TOKEN_COMMA +  token('}'))
    ;
}

Rule<Ref>  _initializer_list::parse() {
    return (initializer)
      | (initializer_list + TOKEN_COMMA + initializer)
    ;
}

Rule<Ref>  _statement::parse() {
  return labeled_statement
    | compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    ;
}

Rule<Ref>  _labeled_statement::parse() {
  return (IDENTIFIER + TOKEN_COLON + statement)
    | (CASE + constant_expression + TOKEN_COLON + statement)
        | (DEFAULT + TOKEN_COLON + statement)
    ;
}

Rule<Ref>  _compound_statement::parse() {
  return (token('{') +  token('}'))
    | (token('{') + statement_list + token('}'))
    | (token('{') + declaration_list + token('}'))
    | (token('{') + declaration_list + statement_list + token('}'))
    ;
}

Rule<Ref>  _declaration_list::parse() {
    return (declaration)
      | (declaration_list + declaration)
    ;
}

Rule<Ref>  _statement_list::parse() {
  return (statement)
    | (statement_list + statement)
    ;
}

Rule<Ref>  _expression_statement::parse() {
  return token(';')
    | (expression + token(';'))
    ;
}

Rule<Ref>  _selection_statement::parse() {
  return (IF + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement)
    | (IF + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement + ELSE + statement)
    | (SWITCH + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement)
    ;
}

Rule<Ref>  _iteration_statement::parse() {
    return (WHILE + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN + statement)
    | (DO + statement + WHILE + TOKEN_OPEN_PAREN + expression + TOKEN_CLOSE_PAREN +  token(';'))
    | (FOR + TOKEN_OPEN_PAREN + expression_statement + expression_statement + TOKEN_CLOSE_PAREN + statement)
      | (FOR + TOKEN_OPEN_PAREN + expression_statement + expression_statement + expression + TOKEN_CLOSE_PAREN + statement)
    ;
}

Rule<Ref>  _jump_statement::parse() {
  return (GOTO + IDENTIFIER + token(';'))
    | (CONTINUE + token(';'))
    | (BREAK + token(';'))
    | (RETURN + token(';'))
    | (RETURN + expression + token(';'))
    ;
}

Rule<Ref>  _translation_unit::parse() {
  return (external_declaration)
  | (translation_unit + external_declaration)
    ;
}

Rule<Ref>  _external_declaration::parse() {
  return (function_definition)
    | (declaration)
    ;
}

Rule<Ref>  _function_definition::parse() {
  return (declaration_specifiers + declarator + declaration_list + compound_statement)
    | (declaration_specifiers + declarator + compound_statement)
    | (declarator + declaration_list + compound_statement)
    | (declarator + compound_statement)
    ;
}


int main() {
  translation_unit.parse().emit();
  type_qualifier.parse().emit();
  primary_expression.parse().emit();
  assignment_expression.parse().emit();
  conditional_expression.parse().emit();
  logical_and_expression.parse().emit();
  logical_or_expression.parse().emit();
}
