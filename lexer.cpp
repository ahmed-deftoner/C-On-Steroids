#include "lexer.h"
using namespace std;
//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE",
    "TOKEN_IDENTIFIER",
 	"TOKEN_NUMBER",
 	"TOKEN_VARIABLE",
 	"TOKEN_FUNCTION",
 	"TOKEN_INT",
 	"TOKEN_IF",
 	"TOKEN_ELSE",
 	"TOKEN_DO",
 	"TOKEN_UNTIL",
 	"TOKEN_THEN",
 	"TOKEN_READ",
 	"TOKEN_DISPLAY",
 	"TOKEN_DISPLAYLINE",
 	"TOKEN_RETURN",
 	"TOKEN_EQUAL",
 	"TOKEN_NOTEQUAL",
 	"TOKEN_LESS",
 	"TOKEN_LESSEQUAL",
 	"TOKEN_GREATER",
 	"TOKEN_GREATEREQUAL",
 	"TOKEN_COMMA",
 	"TOKEN_COLON",
 	"TOKEN_SEMICOLON",
 	"TOKEN_DOLLAR",
 	"TOKEN_OPENPARANTHESIS",
 	"TOKEN_CLOSEPARANTHESIS",
 	"TOKEN_PLUS",
 	"TOKEN_MINUS",
 	"TOKEN_DIVIDE", 
 	"TOKEN_MULTIPLY",
 	"TOKEN_MODULUS",
	};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
        << reserved[(int)tokenType] << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}

bool isAlphabet(char &x){
    if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
        return true;
    return false;
}

void lexer::Tokenize()//function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();
	//your implementation goes here
    int line = 1;
    while(it != stream.end())
    {
        /* Skip whitespace.  */
        if (*it == ' ' || *it == '\t' || *it == '\n') {
            if (*it++ == '\n')
                ++line;
        }
        //cout<<"o\n";
        // Identifier or variable or keyword
        if (isalpha(*it) || *it == '_' || *it == '$'){
            //cout<<"i\n";
            size_t i, len;
            string identifier;
            identifier.push_back(*it);
            while (isdigit(*it) || isalpha(*it) || *it == '_'){
                ++it;
                identifier.push_back(*it);
               // cout<<"ii\n";
            }
            identifier.pop_back();
            cout<<identifier<<endl;

            if (identifier.compare("function")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_FUNCTION));
            else if (identifier.compare("int")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_INT));
            else if (identifier.compare("if")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_IF));
            else if (identifier.compare("else")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_ELSE));
            else if (identifier.compare("do")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_DO));
            else if (identifier.compare("until")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_UNTIL));
            else if (identifier.compare("then")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_THEN));
            else if (identifier.compare("read")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_READ));
            else if (identifier.compare("display")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_DISPLAY));
            else if (identifier.compare("displayline")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_DISPLAYLINE));
            else if (identifier.compare("return")==0)
                tokens.push_back(token(identifier,TokenType::TOKEN_RETURN));
            else if (identifier[0] == '$')
                tokens.push_back(token(identifier,TokenType::TOKEN_VARIABLE));
            else 
                tokens.push_back(token(identifier,TokenType::TOKEN_IDENTIFIER));
        }
        ++it;
    }
    cout<<line<<endl;
    
	//push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}
lexer::lexer(const char filename[])
{
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' ');//dummy spaces appended at the end
        stream.push_back(' ');
        //Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                                 // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}