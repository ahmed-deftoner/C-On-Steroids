#include "parser.h"
#include <unistd.h>

Symbol::Symbol() {
    this->id = "";
    this->type = "";
}

Symbol::Symbol(string type, string id) {
    this->id = id;
    this->type = type;
}
void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n" <<_lexer.getCurrentPointer();
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type){
        t.Print();
        syntax_error();
    }
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
    case TokenType::TOKEN_IDENTIFIER:
	case TokenType::TOKEN_VARIABLE:
	case TokenType::TOKEN_NUMBER:
		_lexer.getNextToken();
		break;
    case TokenType::TOKEN_EXECUTE:
		expect(TokenType::TOKEN_EXECUTE);
		expect(TokenType::TOKEN_COLON);
		expect(TokenType::TOKEN_IDENTIFIER);
		expect(TokenType::TOKEN_OPENPARANTHESIS);
        while (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
        {
		    expect(TokenType::TOKEN_VARIABLE);
            while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
            {
                expect(TokenType::TOKEN_COMMA);
                expect(TokenType::TOKEN_VARIABLE);
            }
        }
        
		expect(TokenType::TOKEN_CLOSEPARANTHESIS);
		break;
	case TokenType::TOKEN_OPENPARANTHESIS:
		expect(TokenType::TOKEN_OPENPARANTHESIS);
		expression();
		expect(TokenType::TOKEN_CLOSEPARANTHESIS);
	}
}

void parser::term(){
   // cout<<"factor\n";
    factor();
    while (_lexer.peek(1).tokenType == TokenType::TOKEN_MULTIPLY || _lexer.peek(1).tokenType == TokenType::TOKEN_DIVIDE)
    {
        _lexer.getNextToken();
        factor();
    }
}

void parser::expression() {
    if (_lexer.peek(1).tokenType == TokenType::TOKEN_PLUS || _lexer.peek(1).tokenType == TokenType::TOKEN_MINUS) {
       // cout<<"plus minus\n";
        _lexer.getNextToken();
    }
    //cout<<"term\n";
    term();
    while (_lexer.peek(1).tokenType == TokenType::TOKEN_PLUS || _lexer.peek(1).tokenType == TokenType::TOKEN_MINUS)
    {
        _lexer.getNextToken();
        term();
    }
}

void parser::statements() {
    vector<string> vars;
    string temp;
    switch (_lexer.peek(1).tokenType) {
    case TokenType::TOKEN_RETURN:
		expect(TokenType::TOKEN_RETURN);
		expect(TokenType::TOKEN_COLON);
        expect(TokenType::TOKEN_NUMBER);
        expect(TokenType::TOKEN_SEMICOLON);
		break;
    case TokenType::TOKEN_VARIABLE:
        temp = _lexer.peek(1).lexeme;
		expect(TokenType::TOKEN_VARIABLE);
        if (_lexer.peek(1).tokenType == TokenType::TOKEN_EQUALSIGN)
        {
            expect(TokenType::TOKEN_EQUALSIGN);
            expression();
        } else if (_lexer.peek(1).tokenType == TokenType::TOKEN_COLON) {
            expect(TokenType::TOKEN_COLON);
            expect(TokenType::TOKEN_INT);
            vars.push_back(temp);
            if (_lexer.peek(1).tokenType == TokenType::TOKEN_EQUALSIGN)
            {
                expect(TokenType::TOKEN_EQUALSIGN);
                expression();
            }
            else if (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA) {
                while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
                {
                    expect(TokenType::TOKEN_COMMA);
                    vars.push_back(_lexer.peek(1).lexeme);
                    expect(TokenType::TOKEN_VARIABLE);
                    expect(TokenType::TOKEN_COLON);
                    expect(TokenType::TOKEN_INT);
                }
            }
        }
        expect(TokenType::TOKEN_SEMICOLON);
        for (auto x : vars)
        {
            symbol_table.push_back(Symbol(types[0],x));
        }
		break;
	case TokenType::TOKEN_DISPLAYLINE:
		expect(TokenType::TOKEN_DISPLAYLINE);
		expect(TokenType::TOKEN_COLON);
        while (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
        {
            expect(TokenType::TOKEN_VARIABLE);
            expect(TokenType::TOKEN_COMMA);
        }
        expect(TokenType::TOKEN_STRING);
        expect(TokenType::TOKEN_SEMICOLON);
		break;
	case TokenType::TOKEN_DISPLAY:
		expect(TokenType::TOKEN_DISPLAY);
		expect(TokenType::TOKEN_COLON);
        while (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
        {
            expect(TokenType::TOKEN_VARIABLE);
            expect(TokenType::TOKEN_COMMA);
        }
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
        while (_lexer.peek(1).tokenType != TokenType::TOKEN_BLOCKCLOSE)
        {
            statements();
            if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
            {
                syntax_error();
            }
            
        }
		expect(TokenType::TOKEN_BLOCKCLOSE);
        while (_lexer.peek(1).tokenType == TokenType::TOKEN_ELSE)
        {
            expect(TokenType::TOKEN_ELSE);
            if (_lexer.peek(1).tokenType == TokenType::TOKEN_IF)
            {
                expect(TokenType::TOKEN_IF);
                expect(TokenType::TOKEN_OPENPARANTHESIS);
                condition();
                expect(TokenType::TOKEN_CLOSEPARANTHESIS);
                expect(TokenType::TOKEN_THEN);
            }
            expect(TokenType::TOKEN_BLOCKOPEN);
            while (_lexer.peek(1).tokenType != TokenType::TOKEN_BLOCKCLOSE)
            {
                statements();
                if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
                {
                    syntax_error();
                }
            }
            expect(TokenType::TOKEN_BLOCKCLOSE);
        }
        
		break;
    case TokenType::TOKEN_EXECUTE:
		expect(TokenType::TOKEN_EXECUTE);
		expect(TokenType::TOKEN_COLON);
		expect(TokenType::TOKEN_IDENTIFIER);
		expect(TokenType::TOKEN_OPENPARANTHESIS);
        while (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
        {
		    expect(TokenType::TOKEN_VARIABLE);
            while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
            {
                expect(TokenType::TOKEN_COMMA);
                expect(TokenType::TOKEN_VARIABLE);
            }
        }
		expect(TokenType::TOKEN_CLOSEPARANTHESIS);
		break;
    case TokenType::TOKEN_STRING:
		expect(TokenType::TOKEN_STRING);
		expect(TokenType::TOKEN_COLON);
		expect(TokenType::TOKEN_READ);
		expect(TokenType::TOKEN_COLON);
        /*if (_lexer.peek(1).tokenType != TokenType::TOKEN_VARIABLE)
        {
		    expect(TokenType::TOKEN_VARIABLE);
            while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
            {
                expect(TokenType::TOKEN_COMMA);
                expect(TokenType::TOKEN_VARIABLE);
            }
        }*/
        expect(TokenType::TOKEN_VARIABLE);
		expect(TokenType::TOKEN_SEMICOLON);
		break;
	case TokenType::TOKEN_DO:
		expect(TokenType::TOKEN_DO);
		expect(TokenType::TOKEN_UNTIL);
		expect(TokenType::TOKEN_OPENPARANTHESIS);
		condition();
		expect(TokenType::TOKEN_CLOSEPARANTHESIS);
		expect(TokenType::TOKEN_BLOCKOPEN);
		while (_lexer.peek(1).tokenType != TokenType::TOKEN_BLOCKCLOSE)
        {
            statements();
            if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
            {
                syntax_error();
            }
        }
		expect(TokenType::TOKEN_BLOCKCLOSE);
        break;
    default:
        syntax_error();
        break;
	}
}

void parser::outputSymbolTable() {
    fstream fout;
    fout.open("symbol_table.txt", ios::out);
    for (auto x : symbol_table) {
        fout << x.id << " " << x.type << endl;
    }
    fout.close();
}

//this function is for sample purposes only
void parser::block()
{
    /*
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
    }*/
    
    //statements-- > COLON LPAREN start RPAREN
    while (_lexer.peek(1).tokenType != TokenType::END_OF_FILE) {
        if (_lexer.peek(1).tokenType == TokenType::TOKEN_IDENTIFIER)
        {
            vector<string> args;
            string func = _lexer.peek(1).lexeme;
            expect(TokenType::TOKEN_IDENTIFIER);
            expect(TokenType::TOKEN_COLON);
            expect(TokenType::TOKEN_INT);
            expect(TokenType::TOKEN_FUNCARROW);
            expect(TokenType::TOKEN_FUNCTION);
            expect(TokenType::TOKEN_OPENPARANTHESIS);
            while (_lexer.peek(1).tokenType == TokenType::TOKEN_VARIABLE)
            {
                args.push_back(_lexer.peek(1).lexeme);
                expect(TokenType::TOKEN_VARIABLE);
                expect(TokenType::TOKEN_COLON);
                expect(TokenType::TOKEN_INT);
                while (_lexer.peek(1).tokenType == TokenType::TOKEN_COMMA)
                {
                    expect(TokenType::TOKEN_COMMA);
                    args.push_back(_lexer.peek(1).lexeme);
                    expect(TokenType::TOKEN_VARIABLE);
                    expect(TokenType::TOKEN_COLON);
                    expect(TokenType::TOKEN_INT);
                }
            }
            expect(TokenType::TOKEN_CLOSEPARANTHESIS);
            expect(TokenType::TOKEN_BLOCKOPEN);
            while (_lexer.peek(1).tokenType != TokenType::TOKEN_BLOCKCLOSE)
            {
                statements();
                if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
                {
                    syntax_error();
                }
                
            }
            
            expect(TokenType::TOKEN_BLOCKCLOSE);
            for (auto x: args)
            {
                symbol_table.push_back(Symbol(types[0],x));         
            }
            
        }
        //usleep(1000000);
    }
    outputSymbolTable();
}