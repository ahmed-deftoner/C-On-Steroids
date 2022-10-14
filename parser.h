#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include <algorithm>

string types[2] = {"variable", "function"} ;

struct Symbol
{
    string type;
    string id;
    Symbol(string type,string id);
    Symbol();
};

//for future assignments leave it as it is
class parser
{
    lexer _lexer;
    vector<Symbol> symbol_table;
public:
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    void statements();
    void expression();
    void term();
    void factor();
    void condition();
    void block();
    void outputSymbolTable();
    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
	//all your parser function goes here
};
#endif
