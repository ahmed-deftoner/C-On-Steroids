#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	TOKEN_IDENTIFIER = 1,
 	TOKEN_NUMBER  = 2,
 	TOKEN_VARIABLE = 3,
 	TOKEN_FUNCTION = 4,
 	TOKEN_INT = 5,
 	TOKEN_IF = 6,
 	TOKEN_ELSE = 7,
 	TOKEN_DO = 8,
 	TOKEN_UNTIL = 9,
 	TOKEN_THEN = 10,
 	TOKEN_READ = 11,
 	TOKEN_DISPLAY = 12,
 	TOKEN_DISPLAYLINE = 13,
 	TOKEN_RETURN = 14,
 	TOKEN_EQUAL = 15,
 	TOKEN_NOTEQUAL = 16,
 	TOKEN_LESS = 17,
 	TOKEN_LESSEQUAL = 18,
 	TOKEN_GREATER = 19,
 	TOKEN_GREATEREQUAL = 20,
 	TOKEN_COMMA = 21,
 	TOKEN_COLON = 22,
 	TOKEN_SEMICOLON = 23,
 	TOKEN_DOLLAR = 24,
 	TOKEN_OPENPARANTHESIS = 25,
 	TOKEN_CLOSEPARANTHESIS = 26,
 	TOKEN_PLUS = 27,
 	TOKEN_MINUS = 28,
 	TOKEN_DIVIDE = 29, 
 	TOKEN_MULTIPLY = 30,
 	TOKEN_MODULUS = 31,
	TOKEN_BLOCKOPEN = 32,
	TOKEN_BLOCKCLOSE = 33,
	TOKEN_EQUALSIGN = 34,
	ERROR = 35

};
//structure of a token 
struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme, TokenType tokenType);
	//constructor default
	token();
	void Print();
};
class lexer
{
	vector<char> stream;  //used for storing file sample_code.ol content
	vector<token> tokens; //vector to store all (tokens,lexeme) pairs
	void Tokenize();//populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();//just print everything as it is present in file
	token getNextToken();//get next token
	void resetPointer();//reset pointer to start getting tokens from start
	int getCurrentPointer();//get where current pointer in tokens vector is
	void setCurrentPointer(int pos);//move current pointer to wherever
	token peek(int);//peek the next token
};

#endif // !_LEXER_H
