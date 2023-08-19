// Amaan Shah, UIC, Spring 2021
// main.cpp

#include <cstdio>
#include <cstring>
#include <cctype>
#include "header.h"

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

// Prototypes:
void processExpression (Token inputToken, TokenReader *tr);
void popAndEval(ValueStack &v, OperatorStack &o);
int eval(int v1, char op, int v2);


int main(int argc, char *argv[])
{
    /***************************************************************/


    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 0;
}

void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack pointers here      */
	ValueStack vals;
	OperatorStack ops;

 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
      	vals.push(inputToken.getValue());
      	//printf(" %d", inputToken.getValue());
      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
      	char op = inputToken.getOperator();
      	//printf(" %c", op);

      	if (op == '(') {
      		ops.push(op);
      	}
      	else if (op == '+' || op == '-') {
      		while ((ops.is_empty() == false) && (ops.top() == '+' || ops.top() == '-' || ops.top() == '*' || ops.top() == '/' || ops.top() == '%')) {
      			popAndEval(vals, ops);
      		}
      		ops.push(op);
      	}
      	else if (op == '*' || op == '/' || op == '%') {
      		while ((ops.is_empty() == false) && (ops.top() == '*' || ops.top() == '/' || ops.top() == '%')) {
      			popAndEval(vals, ops);
      		}
      		ops.push(op);
      	}
      	else if (op == ')') {
      		while ((ops.is_empty() == false) && (ops.top() != '(')) {
      			popAndEval(vals, ops);
      		}
      		if (ops.is_empty() == true) {
      			printf("Invalid expression.\n");
      		} else {
      			ops.pop();
      		}
      	}
      }

    /* get next token from input */
    inputToken = tr->getNextToken ();
   }
 /* The expression has reached its end */
	while(ops.is_empty() == false) {
		popAndEval(vals, ops);
	}

	int answer = vals.top();
	vals.pop();

	if(vals.is_empty() == false) {
		printf("Invalid expression.\n");
	} else {
		printf("Expression result: %d\n", answer);
	}

 	printf ("\n");
}

void popAndEval(ValueStack &v, OperatorStack &o) {
	char op = o.top();
	o.pop();

	int v2 = v.top();
	v.pop();

	int v1 = v.top();
	v.pop();

	int v3 = eval(v1, op, v2);
	v.push(v3);
}

int eval(int v1, char op, int v2) {
	int value = 0;
	if (op == '%') {
		value = v1 % v2;
	} else if (op == '*') {
		value = v1 * v2;
	} else if (op == '/') {
		value = v1 / v2;
	} else if (op == '+') {
		value = v1 + v2;
	} else if (op == '-') {
		value = v1 - v2;
	} else {
		printf("Invalid expression.\n");
		value = -999;
	}
	return value;
}