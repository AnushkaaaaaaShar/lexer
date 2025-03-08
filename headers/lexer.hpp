#ifndef __LEXER_H
#define __LEXER_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


enum type{
  TOKEN_ID, 
  TOKEN_INT, 
  TOKEN_EQUALS, 
  TOKEN_SEMICOLON, 
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN

};

std::string typeTostring(enum type TYPE){
  switch (TYPE)
  {
  case TOKEN_EQUALS: return "equals"; 
  case TOKEN_ID: return "identifier"; 
  case TOKEN_INT: return "Integer"; 
  case TOKEN_LEFT_PAREN: return "Left-parenthesis"; 
  case TOKEN_RIGHT_PAREN: return "right-parathesis"; 
  case TOKEN_SEMICOLON: return "Semicolon"; 
  }
}

struct Token{
  enum type TYPE; 
  std::string VALUE; 

};

class Lexer
{

public: 
Lexer(std::string sourcecode)
{
      source = sourcecode; 
      size = sourcecode.length();
      cursor = 0;  
      current = sourcecode.at(cursor);
      linenumber =1; 
      charcternumber =0; 
}

void checkAndSkip(){
  while(current == ' ' ||current == '\n' ||current == '\t' ||current == '\r' ){
    if( current == '\n'){
      linenumber++; 
      charcternumber = 0;
    }
    advance(); 
  }
}

Token * tokenizeID()
{
  std::stringstream buffer; 
  buffer << advance(); 
    while (isalnum(current) || current == '_')
    {
      buffer << advance(); 
    }
    
    Token * newToken = new Token();
    newToken->TYPE = TOKEN_ID;
    newToken->VALUE = buffer.str();
    return newToken;
}

Token * tokenizeINT()
{
  std::stringstream buffer;
while (isdigit(current)){
  buffer << advance();
}
Token * newToken = new Token();
newToken->TYPE = TOKEN_INT;
newToken->VALUE = buffer.str();
return newToken;


}


Token * tokenizeSpecial(enum type TYPE){
  Token * newToken = new Token();
newToken->TYPE = TYPE;
newToken->VALUE = std::string(1, advance()); 
return newToken;



}


std::vector<Token *> tokenize()
{
  std::vector<Token *> tokens; 
  
  bool NOTEOF = true;  
  while(cursor < size && NOTEOF){
 
    checkAndSkip(); //empty spaces hatayega 
    if(isalpha(current) || current == '_'){ // loic for ids 
      tokens.push_back(tokenizeID());
      // continue; 
    }
    //logic for digit literals 
    else if (isdigit(current))
    {
      tokens.push_back(tokenizeINT());
      // continue;
    }
    else {
      switch (current)
    {
    case ';' :
    {
      tokens.push_back(tokenizeSpecial(TOKEN_SEMICOLON));
      break;
    }
    case '(' :
    {
      tokens.push_back(tokenizeSpecial(TOKEN_LEFT_PAREN));
      break;
    }
    case ')' :
    {
      tokens.push_back(tokenizeSpecial(TOKEN_RIGHT_PAREN));
      break;
    }
    case '=' :
    {
      tokens.push_back(tokenizeSpecial(TOKEN_EQUALS));
      break;
    }
    case 0:{
      break;
    }
    default: 
    {
      std::cout<<"[!]Parser Error: Unidentified Symbol: "<< current << " (ASCII: " 
            << static_cast<int>(current) << ")" << "\nLine:" << linenumber << "\tChar:" << charcternumber << std::endl;
            advance(); 
      exit(1);
    }
    }
    }
    
  }
  return tokens; 
}

char advance() 
{
    if (cursor < size) {
        char temp = current;       // Store the current character in temp
        cursor++;                  // Move cursor to the next character
        charcternumber++;
        current = (cursor < size) ? source[cursor] : '\0';  // Assign next char or null terminator
        
        return temp; 
    }
    else {
      return '\0'; 
    }
}

char peak(int offset = 0) {
    if (cursor + offset < size) {
        return source[cursor + offset]; // Look ahead without moving cursor
    } else {
        return '\0'; // Return null character if out of bounds
    }
}

private: 
  int size; 
  int cursor; 
  std::string source; 
  char current; 
  int linenumber; 
  int charcternumber; 

}; 

#endif
