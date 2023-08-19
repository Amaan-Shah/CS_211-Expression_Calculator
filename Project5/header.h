// Amaan Shah, UIC, Spring 2021
// header.h

#include <cstdio>
#include <cstring>
#include <cctype>

// Enumarated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

class ValueStack {
	private:
		int* darr;
		int size;
		int inUse;

	public:

	ValueStack();
  ~ValueStack();
	void push(int y);
	void grow();
	void pop();
	int top();
	bool is_empty();
};

class OperatorStack {
	private:
		char* darr;
		int size;
		int inUse;

	public:

	OperatorStack();
  ~OperatorStack();
	void push(char y);
	void grow();
	void pop();
	char top();
	bool is_empty();
};



// Class to hold the Token information
class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:

  Token();
  Token (TokenType t);
  void setToType(TokenType t);
  void setToOperator(char c);
  void setToValue(int v);
  bool equalsType(TokenType t);
  bool equalsOperator(char c);
  char getOperator ();
  int getValue();
};


class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;

  public:

  TokenReader();
  void clearToEoln();
  Token getNextToken();
};
