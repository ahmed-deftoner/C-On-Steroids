#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
}
void parser::readAndPrintAllInput() //read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}

//this function is for sample purposes only
bool parser::statements()
{
    if (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
    {
        expect(TokenType::TOKEN_VARIABLE);
        expect(TokenType::TOKEN_COLON);
        expect(TokenType::TOKEN_INT);
        while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
        {
            expect(TokenType::TOKEN_COMMA);
            expect(TokenType::TOKEN_VARIABLE);
            expect(TokenType::TOKEN_COLON);
            expect(TokenType::TOKEN_INT);
        }
        
    }
    
    //statements-- > COLON LPAREN start RPAREN
    if (_lexer.peek(1).tokenType == TokenType::TOKEN_IDENTIFIER)
    {
        expect(TokenType::TOKEN_IDENTIFIER);
        if (_lexer.peek(1).tokenType == TokenType::TOKEN_COLON)
        {
            expect(TokenType::TOKEN_COLON);
            if (_lexer.peek(1).tokenType == TokenType::TOKEN_INT)
            {
                expect(TokenType::TOKEN_INT);
                if (_lexer.peek(1).tokenType == TokenType::TOKEN_FUNCARROW)
                {
                    expect(TokenType::TOKEN_FUNCARROW);
                    if (_lexer.peek(1).tokenType == TokenType::TOKEN_FUNCTION)
                    {
                        expect(TokenType::TOKEN_FUNCTION);
                        if (_lexer.peek(1).tokenType == TokenType::TOKEN_OPENPARANTHESIS)
                        {
                            expect(TokenType::TOKEN_OPENPARANTHESIS);
                            while (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE) {
                                expect(TokenType::TOKEN_VARIABLE);
                                if (_lexer.peek(1).tokenType == TokenType::TOKEN_COLON)
                                {
                                    expect(TokenType::TOKEN_COLON);
                                    if (_lexer.peek(1).tokenType == TokenType::TOKEN_INT)
                                    {
                                        expect(TokenType::TOKEN_INT);
                                        while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
                                        {
                                            expect(TokenType::TOKEN_COMMA);
                                            if (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE) {
                                                expect(TokenType::TOKEN_VARIABLE);
                                                if (_lexer.peek(1).tokenType == TokenType::TOKEN_COLON)
                                                {
                                                    expect(TokenType::TOKEN_COLON);
                                                    if (_lexer.peek(1).tokenType == TokenType::TOKEN_INT)
                                                    {
                                                        expect(TokenType::TOKEN_INT);
                                                    }
                                                }
                                            }
                                        }
                                        
                                    }
                                    
                                }
                                
                            }
                            
                            if (_lexer.peek(1).tokenType == TokenType::TOKEN_CLOSEPARANTHESIS)
                            {
                                expect(TokenType::TOKEN_CLOSEPARANTHESIS);
                                if (_lexer.peek(1).tokenType == TokenType::TOKEN_BLOCKOPEN)
                                {
                                    expect(TokenType::TOKEN_BLOCKOPEN);
                                                
                                    cout<<"found\n";
                                    return true;
                                }
                                
                            }
                            
                        }
                    }
                    
                }
                
            }
        }
    }
    cout<<"not found\n";
    return false;
}