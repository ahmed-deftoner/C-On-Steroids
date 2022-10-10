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

void parser::condition(){
    expression();
	switch (_lexer.peek(1).tokenType) {
		case TokenType::TOKEN_EQUAL:
		case TokenType::TOKEN_LESS:
		case TokenType::TOKEN_LESSEQUAL:
		case TokenType::TOKEN_GREATER:
		case TokenType::TOKEN_GREATEREQUAL:
		case TokenType::TOKEN_NOTEQUAL:
			_lexer.getNextToken();
			break;
		default:
		    syntax_error();
		}
		expression();
}

void parser::factor(){
    switch (_lexer.peek(1).tokenType) {
	case TokenType::TOKEN_VARIABLE:
	case TokenType::TOKEN_NUMBER:
		_lexer.getNextToken();
		break;
	case TokenType::TOKEN_OPENPARANTHESIS:
		expect(TokenType::TOKEN_OPENPARANTHESIS);
		expression();
		expect(TokenType::TOKEN_CLOSEPARANTHESIS);
	}
}

void parser::term(){
    factor();
    while (_lexer.peek(1).tokenType == TokenType::TOKEN_MULTIPLY || _lexer.peek(1).tokenType == TokenType::TOKEN_DIVIDE)
    {
        _lexer.getNextToken();
        factor();
    }
}

void parser::expression() {
    if (_lexer.peek(1).tokenType == TokenType::TOKEN_PLUS || _lexer.peek(1).tokenType == TokenType::TOKEN_MINUS) {
        _lexer.getNextToken();
    }
    term();
    while (_lexer.peek(1).tokenType == TokenType::TOKEN_PLUS || _lexer.peek(1).tokenType == TokenType::TOKEN_MINUS)
    {
        _lexer.getNextToken();
        term();
    }
}

void parser::statements() {
    switch (_lexer.peek(1).tokenType) {
	case TokenType::TOKEN_DISPLAYLINE:
		expect(TokenType::TOKEN_DISPLAYLINE);
		expect(TokenType::TOKEN_COLON);
        expect(TokenType::TOKEN_STRING);
        expect(TokenType::TOKEN_SEMICOLON);
		break;
	case TokenType::TOKEN_DISPLAY:
		expect(TokenType::TOKEN_DISPLAY);
		expect(TokenType::TOKEN_COLON);
        expect(TokenType::TOKEN_STRING);
        expect(TokenType::TOKEN_SEMICOLON);
		break;
	case TokenType::TOKEN_IF:
		expect(TokenType::TOKEN_IF);
        expect(TokenType::TOKEN_OPENPARANTHESIS);
		condition();
        expect(TokenType::TOKEN_CLOSEPARANTHESIS);
		expect(TokenType::TOKEN_THEN);
		expect(TokenType::TOKEN_BLOCKOPEN);
		statements();
		expect(TokenType::TOKEN_BLOCKCLOSE);
		break;
	case TOK_WHILE:
		expect(TOK_WHILE);
		condition();
		expect(TOK_DO);
		statement();
	}
}

//this function is for sample purposes only
void parser::block()
{
    if (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
    {
        expect(TokenType::TOKEN_VARIABLE);
        expect(TokenType::TOKEN_COLON);
        expect(TokenType::TOKEN_INT);
        if (_lexer.peek(1).tokenType == TokenType::TOKEN_EQUALSIGN)
        {
            expect(TokenType::TOKEN_EQUALSIGN);
            expression();
        }
        else if (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA) {
            while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
            {
                expect(TokenType::TOKEN_COMMA);
                expect(TokenType::TOKEN_VARIABLE);
                expect(TokenType::TOKEN_COLON);
                expect(TokenType::TOKEN_INT);
            }
        }
        expect(TokenType::TOKEN_SEMICOLON);
    }
    
    //statements-- > COLON LPAREN start RPAREN
    if (_lexer.peek(1).tokenType == TokenType::TOKEN_IDENTIFIER)
    {
        expect(TokenType::TOKEN_IDENTIFIER);
        expect(TokenType::TOKEN_COLON);
        expect(TokenType::TOKEN_INT);
        expect(TokenType::TOKEN_FUNCARROW);
        expect(TokenType::TOKEN_FUNCTION);
        expect(TokenType::TOKEN_OPENPARANTHESIS);
        while (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
        {
            expect(TokenType::TOKEN_VARIABLE);
            expect(TokenType::TOKEN_COLON);
            expect(TokenType::TOKEN_INT);
            cout<<"func\n";
            while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
            {
                cout<<"param\n";
                expect(TokenType::TOKEN_COMMA);
                expect(TokenType::TOKEN_VARIABLE);
                expect(TokenType::TOKEN_COLON);
                expect(TokenType::TOKEN_INT);
            }
        }
        expect(TokenType::TOKEN_BLOCKOPEN);
        block();
        expect(TokenType::TOKEN_BLOCKCLOSE);
    }
    cout<<"not found\n";
}