
int zero = 0;
int label;
int hex = 0xFFFF;

void AUTO () {
  auto x;
}

char CHAR;

const CONST=1;

void CONTINUE(){
  while (1) {
    continue;
  }
}


int DOBLOCK (cond) {}

void DO (int cond) {
  do {
    cond = DOBLOCK(cond);
  }
  while (cond);
}

  
double DOUBLE;


enum ENUM {
 Default,
 Explicit = 1,
 
};

extern EXTERN;
float FLOAT;

void FORBLOCK(int x) { }
 void FOR(int start, int end, int inc) {
   int x;
  for (x = start;
       x < end;
       x = x + inc)
    {
      FORBLOCK(x);
    }
}


 void LABELED(){}
void test_goto() {
  goto L;
 L:
  LABELED();

}


void IF_TRUE () {}
void IF_FALSE () {}
void TEST_IF(int cond) {
  if (cond) {
    IF_TRUE();
  } else {
    IF_FALSE();
  }
}

int INT;
long LONG;

void aregister () {
  register int a3;
}

short SHORT;
signed SIGNED;

void SIZEOF_FUNCTION () {
  int SIZEOF = sizeof(int);
}

static int STATIC;

struct STRUCT {};

 void DEFAULT(){}
void SWITCH_CASE_BREAK (int x) {
  switch(x) {
  case 0 :
    break;
  default: 
    DEFAULT();
  }
   
};

typedef int TYPEDEF;

union UNION {};


unsigned UNSIGNED;



int WHILEBODY () {}
void WHILE(int condition) {
  while(condition) {
    condition = WHILEBODY();
  }
}


 void TOKEN_ELLIPSIS(int x, ...)		{
}

void TOKEN_RIGHT_ASSIGN(int x, int y) {
  x >>= y;
}

void TOKEN_LEFT_ASSIGN(int x, int y) {
  x <<= y;
}

void TOKEN_ADD_ASSIGN(int x, int y) {
  x <<= y;
}

int ADD_ASSIGN (int x, int y) {
  return x += y;
}

int SUB_ASSIGN (int x, int y) {
  return x -= y;
}

int MUL_ASSIGN (int x, int y) {
  return x *= y;
}

int DIV_ASSIGN (int x, int y) {
  return x /= y;
}

int MOD_ASSIGN (int x, int y) {
  return x %= y;
}

int AND_ASSIGN (int x, int y) {
  return x &= y;
}

int XOR_ASSIGN (int x, int y) {
  return x ^= y;
}

int OR_ASSIGN (int x, int y) {
  return x |= y;
}

int RIGHT_OP (int x, int y) {
  return x >> y;
}

int LEFT_OP (int x, int y) {
  return x << y;
}

int INT_OP (int x) {
  return x++;
}

int DEC_OP (int x) {
  return x--;
}

 struct X {
   void * y;
 };
 
 void * PTR_OP (struct X * x) {
  return x->y;
}

int AND_OP (int  x, int  y) {
  return x && y;
}

int OR_OP (int  x, int  y) {
  return x || y;
}

int LE_OP (int  x, int  y) {
  return x <= y;
}

int GE_OP (int  x, int  y) {
  return x >= y;
}

int EQ_OP (int  x, int  y) {
  return x == y;
}

int NE_OP (int  x, int  y) {
  return x != y;
}


/* "."			{ count(); return('.'); } */
/* "&"			{ count(); return('&'); } */
/* "!"			{ count(); return('!'); } */
/* "~"			{ count(); return('~'); } */
/* "-"			{ count(); return('-'); } */
/* "+"			{ count(); return('+'); } */
/* "*"			{ count(); return('*'); } */
/* "/"			{ count(); return('/'); } */
/* "%"			{ count(); return('%'); } */
/* "<"			{ count(); return('<'); } */
/* ">"			{ count(); return('>'); } */
/* "^"			{ count(); return('^'); } */
/* "|"			{ count(); return('|'); } */
/* "?"			{ count(); return('?'); } */

