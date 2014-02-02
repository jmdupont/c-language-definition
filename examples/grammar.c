/**
derived from
http://www.lysator.liu.se/c/ANSI-C-grammar-y.html

This defines the c grammar in C++
to use for language generation and test generation.
**/

#define TOKEN(X) Token X( #X );
#define RULEA(X) Rule _ ## X   ();
#define RULEB(X) Rule2 X( #X, _ ## X   () );
#define RULE(X) RULEA(X) RULEB(X)

#include <iostream>

class OutputGenerator
{
  OutputGenerator(const OutputGenerator & r); // dont implement

 public:
 OutputGenerator() {emit();}
 OutputGenerator(OutputGenerator & r) {
   r.emit();
  }

 void emit() const {
   //std::cout << "TODO" << std::endl;;
    //throw "TODO";
  }
};

 class OutputGeneratorRef{ 
      const OutputGenerator & r; 
        public: 
       OutputGeneratorRef(const OutputGenerator & r): r(r) {emit();} 
      void emit() { r.emit();  } 
      }; 

class OutputGeneratorPtr : public OutputGenerator{
  const OutputGenerator * p;
 public:
 OutputGeneratorPtr(const OutputGenerator * p): p(p) {
    if (p) {
      p->emit();
    }
    emit();
  }

   void emit() const {
    std::cout << "PTR:" << std::endl;
    if(p) { p->emit();}  }
};

class Pair : public OutputGenerator {
 protected:
  const OutputGenerator & a;
  const OutputGenerator & b;
 public:
 Pair(const OutputGenerator & a, const OutputGenerator & b):  a(a), b(b) {  emit(); }   
 Pair(const Pair & p):  a(p.a), b(p.b) { emit(); }


};

class Rule : public OutputGenerator {

 public:
  // Rule(const char name [], Rule & func) 
  //   : name(name), func(func) {      
  //    func.emit();
  //}
 Rule(const Rule & r){
   //r.emit();
 };

  // Rule() {}
  // Rule(OutputGenerator func) :func(func) {}
  //  Rule & operator = (Rule & r) {    r.emit();  }
   void emit() const {
    std::cout << "RULE:" << std::endl;
    //func.emit();  
  }
};

class Or : public Pair { 
 public :
 Or(const OutputGenerator & a, const OutputGenerator & b):  Pair(a,b) {     emit();}   
  operator Rule(){ emit(); };
  void emit() const { 
    a.emit();
    std::cout << "|";    
    b.emit();  
  }
};

class Plus : public Pair { 
 public :
 Plus(const OutputGenerator & a, const OutputGenerator & b):  Pair(a,b) {     emit();   }   
  operator Rule() { emit();  }

  void emit() const { 

    a.emit();    
    std::cout << "+";    
    b.emit();  
  }
};

class Rule2  : public OutputGenerator {
    Rule & func;
    const char * name;
 public:
 Rule2(const char * name , Rule func) 
   : name(name), func(func) {      
      //std::cout << "creating" << std::endl;
      //emit();
      //func.emit();
  }
   void emit() const {
     std::cout << "R:" << name << std::endl;
    func.emit();  
  }
  operator Rule () {
    emit();
    //return Rule(*this);
  }
};


Or operator | (const OutputGenerator & a, const OutputGenerator & b) {  return Or(a,b); }

class Token : public OutputGenerator {
 public:
  const char * v;

 Token(const char * v)   : v(v)   {  
    //emit(); 
    //    std::cout << "Value:" << v << std::endl;
  }

   void emit() const {
     //    std::cout << "TOKEN:" << std::endl;
    //OutputGenerator::emit();
     //std::cout << "V:" << v << std::endl;
     std::cout << "Token" << v;
  }

};

class TokenChar : public OutputGenerator {
 public:
  char v;

 TokenChar(char v)  : v(v) { 
    emit();
  }
  //  OutputGenerator operator ()() { return OutputGeneratorPtr(this); }

 TokenChar(const TokenChar & t): v(t.v) {
    emit();
  };

   void emit() const {
     //std::cout << "TOKENc:" << std::endl;
    //  OutputGenerator::emit();
     std::cout  << v ;
  }

};


Plus operator + (const OutputGenerator & a, const OutputGenerator & b ){
  
  Plus r = Plus(a,b);  
  r.emit();
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
RULE(assignment_expression)
RULE(assignment_operator)
RULE(cast_expression)
RULE(compound_statement)
RULE(conditional_expression)
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
RULE(expression)
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
RULE(logical_and_expression)
RULE(logical_or_expression)
RULE(multiplicative_expression)
RULE(parameter_declaration)
RULE(parameter_list)
RULE(pointer)
RULE(postfix_expression)
RULE(primary_expression)
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

Rule _primary_expression() {
  return IDENTIFIER
    | CONSTANT
    | STRING_LITERAL
    | token('(')  + expression + token(')')
    ;
}

Rule  _postfix_expression() {
  return primary_expression
    | postfix_expression + token('[') + expression + token(']')
    | postfix_expression + token('(') + token(')')
    | postfix_expression + token('(') + argument_expression_list + token(')')
    | postfix_expression + token('.') + IDENTIFIER
    | postfix_expression + PTR_OP + IDENTIFIER
    | postfix_expression + INC_OP
    | postfix_expression + DEC_OP
    ;
}

Rule _argument_expression_list() {
  return assignment_expression
    | argument_expression_list + token(',') + assignment_expression
    ;
}


Rule _unary_expression() 
{
  return 
    postfix_expression
    | INC_OP + unary_expression
    | DEC_OP + unary_expression
    | unary_operator + cast_expression
    | SIZEOF + unary_expression
    | SIZEOF + token('(') + type_name + token(')');
}

Rule _assignment_expression() 
{
  return 
    conditional_expression
    | unary_expression +  assignment_operator + assignment_expression
    ;
}

Rule _cast_expression() {
  return unary_expression
    | token('(') + type_name + token(')') + cast_expression;

}

Rule _unary_operator() {
  return token('&')
    |  token('*')
    |  token('+')
    |  token('-')
    |  token('~')
    |  token('!')
    ;}


Rule _multiplicative_expression() {
	return cast_expression
	| multiplicative_expression + token('*') + cast_expression
	| multiplicative_expression + token('/') + cast_expression
	| multiplicative_expression + token('%') + cast_expression
	;
}
Rule _additive_expression() {
	return multiplicative_expression
	| additive_expression + token('+') + multiplicative_expression
	| additive_expression + token('-') + multiplicative_expression
	;
}
Rule _shift_expression() {
	return additive_expression
	| shift_expression + LEFT_OP + additive_expression
	| shift_expression + RIGHT_OP + additive_expression
	;
}
Rule _relational_expression() {
	return shift_expression
	| relational_expression + token('<') + shift_expression
	| relational_expression + token('>') + shift_expression
	| relational_expression + LE_OP + shift_expression
	| relational_expression + GE_OP + shift_expression
	;
}
Rule _equality_expression() {
	return relational_expression
	| equality_expression + EQ_OP  +relational_expression
	| equality_expression + NE_OP  + relational_expression
	;
}
Rule _and_expression() {
	return equality_expression
	| and_expression + token('&') + equality_expression
	;
}
Rule _exclusive_or_expression() {
	return and_expression
	| exclusive_or_expression + token('^') + and_expression
	;
}
Rule _inclusive_or_expression() {
	return exclusive_or_expression
	| inclusive_or_expression + token('|') + exclusive_or_expression
	;
}
Rule _logical_and_expression() {
	return inclusive_or_expression
	| logical_and_expression + AND_OP+ inclusive_or_expression
	;
}
Rule _logical_or_expression() {
	return logical_and_expression
	| logical_or_expression + OR_OP+  logical_and_expression
	;
}
Rule _conditional_expression() {
	return logical_or_expression
	| logical_or_expression + token('?') + expression + token(':') + conditional_expression
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
Rule _expression() {
	return assignment_expression
	| expression + token(',') + assignment_expression
	;
}
Rule _constant_expression() {
	return conditional_expression
	;
}
Rule _declaration() {
  return declaration_specifiers + token(';')
	| declaration_specifiers + init_declarator_list + token(';')
	;
}
Rule _declaration_specifiers() {
	return storage_class_specifier
	| storage_class_specifier + declaration_specifiers
	| type_specifier
	| type_specifier + declaration_specifiers
	| type_qualifier
	| type_qualifier + declaration_specifiers
	;
}
Rule _init_declarator_list() {
	return init_declarator
	| init_declarator_list + token(',') + init_declarator
	;
}
Rule _init_declarator() {
	return declarator
	| declarator + token('=') + initializer
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
	return struct_or_union + IDENTIFIER + token('{') + struct_declaration_list + token('}')
	| struct_or_union + token('{') + struct_declaration_list + token('}')
	| struct_or_union + IDENTIFIER
	;
}
Rule _struct_or_union() {
	return STRUCT
	| UNION
	;
}
Rule _struct_declaration_list() {
	return struct_declaration
	| struct_declaration_list + struct_declaration
	;
}
Rule _struct_declaration() {
	return specifier_qualifier_list + struct_declarator_list + token(';')
	;
}
Rule _specifier_qualifier_list() {
	return type_specifier + specifier_qualifier_list
	| type_specifier
	| type_qualifier + specifier_qualifier_list
	| type_qualifier
	;
}
Rule _struct_declarator_list() {
	return struct_declarator
	| struct_declarator_list + token(',') + struct_declarator
	;
}
Rule _struct_declarator() {
	return declarator
	| token(':') + constant_expression
	| declarator + token(':') + constant_expression
	;
}
Rule _enum_specifier() {
	return ENUM + token('{') + enumerator_list + token('}')
	| ENUM + IDENTIFIER + token('{') + enumerator_list + token('}')
	| ENUM + IDENTIFIER
	;
}
Rule _enumerator_list() {
	return enumerator
	| enumerator_list + token(',') + enumerator
	;
}
Rule _enumerator() {
	return IDENTIFIER
	| IDENTIFIER + token('=') + constant_expression
	;
}
Rule _type_qualifier() {
	return CONST
	| VOLATILE
	;
}
Rule _declarator() {
	return pointer + direct_declarator
	| direct_declarator
	;
}
Rule _direct_declarator() {
	return IDENTIFIER
	| token('(') + declarator + token(')')
	| direct_declarator + token('[') + constant_expression + token(']')
	| direct_declarator + token('[') +  token(']')
	| direct_declarator + token('(') + parameter_type_list + token(')')
	| direct_declarator + token('(') + identifier_list + token(')')
	| direct_declarator + token('(') +  token(')')
	;
}
Rule _pointer() {
	return token('*')
	| token('*') + type_qualifier_list
	| token('*') + pointer
	| token('*') + type_qualifier_list + pointer
	;
}
Rule _type_qualifier_list() {
	return type_qualifier
	| type_qualifier_list + type_qualifier
	;
}

Rule _parameter_type_list() {
	return parameter_list
	| parameter_list + token(',') + ELLIPSIS
	;
}
Rule _parameter_list() {
	return parameter_declaration
	| parameter_list + token(',') + parameter_declaration
	;
}
Rule _parameter_declaration() {
	return declaration_specifiers + declarator
	| declaration_specifiers + abstract_declarator
	| declaration_specifiers
	;
}
Rule _identifier_list() {
	return IDENTIFIER
	| identifier_list + token(',') + IDENTIFIER
	;
}
Rule _type_name() {
	return specifier_qualifier_list
	| specifier_qualifier_list + abstract_declarator
	;
}
Rule _abstract_declarator() {
	return pointer
	| direct_abstract_declarator
	| pointer + direct_abstract_declarator
	;
}
Rule _direct_abstract_declarator() {
	return token('(') + abstract_declarator + token(')')
	| token('[') +  token(']')
	| token('[') + constant_expression + token(']')
	| direct_abstract_declarator + token('[') +  token(']')
	| direct_abstract_declarator + token('[') + constant_expression + token(']')
	| token('(') +  token(')')
	| token('(') + parameter_type_list + token(')')
	| direct_abstract_declarator + token('(') +  token(')')
	| direct_abstract_declarator + token('(') + parameter_type_list + token(')')
	;
}
Rule _initializer() {
	return assignment_expression
	| token('{') + initializer_list + token('}')
	| token('{') + initializer_list + token(',') +  token('}')
	;
}
Rule _initializer_list() {
	return initializer
	| initializer_list + token(',') + initializer
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
	return IDENTIFIER + token(':') + statement
	| CASE + constant_expression + token(':') + statement
	| DEFAULT + token(':') + statement
	;
}
Rule _compound_statement() {
	return token('{') +  token('}')
	| token('{') + statement_list + token('}')
	| token('{') + declaration_list + token('}')
	| token('{') + declaration_list + statement_list + token('}')
	;
}
Rule _declaration_list() {
	return declaration
	| declaration_list + declaration
	;
}
Rule _statement_list() {
	return statement
	| statement_list + statement
	;
}
Rule _expression_statement() {
	return token(';')
	| expression + token(';')
	;
}
Rule _selection_statement() {
	return IF + token('(') + expression + token(')') + statement
	| IF + token('(') + expression + token(')') + statement + ELSE + statement
	| SWITCH + token('(') + expression + token(')') + statement
	;
}
Rule _iteration_statement() {
	return WHILE + token('(') + expression + token(')') + statement
	| DO + statement + WHILE + token('(') + expression + token(')') +  token(';')
	| FOR + token('(') + expression_statement + expression_statement + token(')') + statement
	| FOR + token('(') + expression_statement + expression_statement + expression + token(')') + statement
	;
}
Rule _jump_statement() {
	return GOTO + IDENTIFIER + token(';')
	| CONTINUE + token(';')
	| BREAK + token(';')
	| RETURN + token(';')
	| RETURN + expression + token(';')
	;
}
Rule _translation_unit() {
	return external_declaration
	| translation_unit + external_declaration
	;
}

Rule _external_declaration() {
	return function_definition
	| declaration
	;
}

Rule _function_definition() {
	return declaration_specifiers + declarator + declaration_list + compound_statement
	| declaration_specifiers + declarator + compound_statement
	| declarator + declaration_list + compound_statement
	| declarator + compound_statement
	;
 }

int main() {
  //  translation_unit.emit();
  // primary_expression.emit();
  type_qualifier.emit();
}
