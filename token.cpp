/*token.cpp*/

//
// nextToken function needed for parsing of SimpleC programming language
//
// Completed version by
// Author: Sai
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 04
//

#include <iostream>
#include <istream>
#include <string>
#include <cctype>  // isdigit, isalpha

#include "token.h"

using namespace std;


//
// overload << for Token so we can output tokens easily for debugging:
//
ostream& operator<<(ostream& os, const Token& T)
{
   os << "Token(" << T.ID << "," << T.Value << "," << T.Line << "," << T.Col << ")";
   return os;
}

string convertToString(istream& input) {
    string output = "";
    char c;
    
    c = input.peek();
    
    while(isalpha(c) || c == '_' || isdigit(c)) {
        
        c = input.get();
       
        output += static_cast<char>(c);
        c = input.peek();
        }
    return output;
}


//
// nextToken
//
// Summary: finds and returns the next SimpleC token as 
// defined in "token.h" and by the SimpleC programming 
// language.  If the input stream does not contain another
// token, TokenID::EOS (End-Of-Stream) is returned.  The
// longest possible token is always returned, e.g. the 
// input ">=" would be returned as TokenID::GTE instead
// of TokenID::GT followed by TokenID::EQUAL.  If the input
// stream contains a character that is not recognized as 
// part of SimpleC, TokenID::UNKNOWN is returned with 
// the token's value set to the unknown character.
//
// Pre-condition: input must be an open stream denoting
// the source of tokens, with line and col set to current 
// line and column position in this stream.
//
// Post-condition: input stream is advanced based on token 
// that is returned, with line and col advanced similarly.
//
Token nextToken(istream& input, int& line, int& col)
{
   Token T;
   int   c;
   
   c = input.peek();  // look ahead at the next char:

   if (c == EOF)  // end of stream:
   {
      T.ID = TokenID::EOS;
      
      T.Value = "$";
      T.Line  = line;
      T.Col   = col;
   } else if (c == ';') {
       c = input.get();
       T.ID = TokenID::SEMICOLON;
       T.Value = ";";
       T.Line = line;
       T.Col = col;
       col++;
       //return T;
   } else if (c == '(') {
       c = input.get();
       T.ID = TokenID::LEFT_PAREN;
       T.Value = "(";
       T.Line = line;
       T.Col = col;
       col++;
   } else if (c == ')') {
       c = input.get();
       T.ID = TokenID::RIGHT_PAREN;
       T.Value = ")";
       T.Line = line;
       T.Col = col;
       col++;
   } else if (c == '{') {
       c = input.get();
       T.ID = TokenID::LEFT_BRACE;
       T.Value = "{";
       T.Line = line;
       T.Col = col;
       col++;
   } else if (c == '}') {
       c = input.get();
       T.ID = TokenID::RIGHT_BRACE;
       T.Value = "}";
       T.Line = line;
       T.Col = col;
       col++;
   } else if (c == '+') {
       c = input.get();
       T.ID = TokenID::PLUS;
       T.Value = "+";
       T.Line = line;
       T.Col = col;
       col++;
   } else if (c == '-') {
       c = input.get();
       T.ID = TokenID::MINUS;
       T.Value = "-";
       T.Line = line;
       T.Col = col;
       col++;
   } else if (c == '*') {
       c = input.get();
       T.ID = TokenID::MULT;
       T.Value = "*";
       T.Line = line;
       T.Col = col;
       col++;
   } else if (c == '/') {
       
       c = input.get();
       c = input.peek();
       
       T.Col = col;
       
       if(c == '/') {
           string waste = "";
           getline(input, waste);
           col = 1;
           line++;
           T.Line = line;
           T = nextToken(input, line, col);
           
       } else {
       //c = input.get();
       T.ID = TokenID::DIV;
       T.Value = "/";
       T.Line = line;
       col++;
       //T.Col = col;
       }
       
   } else if (c == '%') {
       c = input.get();
       T.ID = TokenID::MOD;
       T.Value = "%";
       T.Line = line;
       T.Col = col;
       
       col++;
   } else if (c == '>') {
       
       c = input.get();
       c = input.peek();
       
       if(c == '=') {
           
       c = input.get();
       T.ID = TokenID::GTE;
       T.Value = ">=";
       T.Line = line;
       T.Col = col;
       
       col+=2;
       } else if (c == '>') {
           c = input.get();
           T.ID = TokenID::INPUT;
           T.Value = ">>";
           T.Line = line;
           T.Col = col;
           
           col+=2;
       } else {
           T.ID = TokenID::GT;
           T.Value = ">";
           T.Line = line;
           T.Col = col;
           col++;
       }
   } else if (c == '<') {
           
           c = input.get();
           c = input.peek();
       
          if (c == '=') {
              c = input.get();
              T.ID = TokenID::LTE;
              T.Value = "<=";
              T.Line = line;
              T.Col = col;
              col +=2;
          } else if (c == '<') {
              c = input.get();
              T.ID = TokenID::OUTPUT;
              T.Value = "<<";
              T.Line = line;
              T.Col = col;
              col+=2;
          } else {
              T.ID = TokenID::LT;
              T.Value = "<";
              T.Line = line;
              T.Col = col;
              col++;
          }
   } else if (c == '=') {
       
       c = input.get();
       c = input.peek();
       
       if (c == '=') {
           c = input.get();
           T.ID = TokenID::EQUAL_EQUAL;
           T.Value = "==";
           T.Line = line;
           T.Col = col;
           col +=2;
       } else {
           T.ID = TokenID::EQUAL;
           T.Value = "=";
           T.Line = line;
           T.Col = col;
           col++;
       }
   } else if (c == '!') {
       c = input.get();
       c = input.peek();
       
       if(c == '=') {
           c = input.get();
           T.ID = TokenID::NOT_EQUAL;
           T.Value = "!=";
           T.Line = line;
           T.Col = col;
           col +=2;
       }
       else {
           T.ID = TokenID::UNKNOWN;
           T.Value = "!";
           T.Line = line;
           T.Col = col;
           col++;
       }
   } else if(isdigit(c)) {
       
       c = input.get();
       T.Value = T.Value + static_cast<char>(c);
       T.Col = col;
       c = input.peek();
       col++;
       while(isdigit(c)) {
           c = input.get();
           T.Value += static_cast<char>(c);
           c = input.peek();
           col++;
       }
       
       T.ID = TokenID::INT_LITERAL;
       T.Line = line;
       
   } else if(c == '"') {
       
       c = input.get();
       T.Value = "\"";
       T.Col = col;
       c = input.peek();
       col++;
       while(c != '"') {
           c = input.get();
           T.Value += static_cast<char>(c);
           c = input.peek();
           col++;
       }
       c = input.get();
       T.Value += static_cast<char>(c);
       col++;
       T.ID = TokenID::STR_LITERAL;
       T.Line = line;
   } else if(isalpha(static_cast<char>(c)) || c == '_') {
       //c = input.get();
       //T.Value = static_cast<char>(c);
       //T.Col = col;
       //col++;
       //c = input.peek();
       //T.Col = col;
       //while(isdigit(static_cast<char>(c)) || isalpha(static_cast<char>(c)) || c == '_') {
           //c = input.get();
           //T.Value += static_cast<char>(c);
           //c = input.peek();
           //col++;     
       
       //c = input.get();
       //T.Value += static_cast<char>(c);
       //col++;
       //T.ID = TokenID::IDENTIFIER;
       //T.Line = line;
       T.Col = col;
       string s = convertToString(input);
       //cout << s<< endl;
       if (s == "void") {
           
           T.Value = s;
           T.ID = TokenID::VOID_KEYW;
           T.Line = line;
           
       } else if (s == "main") {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::MAIN_KEYW;
           T.Line = line;
           
       } else if (s == "int") {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::INT_KEYW;
           T.Line = line;
           
       } else if (s == "cin") {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::CIN_KEYW;
           T.Line = line;
           
       } else if (s == "cout") {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::COUT_KEYW;
           T.Line = line;
           
       } else if (s == "endl") {
         //T.Col = col;
           T.Value = s;
           T.ID = TokenID::ENDL_KEYW;
           T.Line = line;
           
       } else if (s == "while") {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::WHILE_KEYW;
           T.Line = line;
           
       } else if (s == "if") {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::IF_KEYW;
           T.Line = line;
           
       } else if (s == "else") {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::ELSE_KEYW;
           T.Line = line;
           
       } else {
           //T.Col = col;
           T.Value = s;
           T.ID = TokenID::IDENTIFIER;
           T.Line = line;
           //col++;
       }
       col += s.length();
   } else if (c == ' ' || c == '\t' || c == '\r'  || c == '\f') {
       c = input.get();
       col++;
       T = nextToken(input, line, col);
   } else if(c == '\n') {
       c = input.get();
       col = 1;
       line++;
       T = nextToken(input, line, col);
   } 
      
   
  

   
   
  
   
   
   else  // unknown char => UNKNOWN token:
   {
      c = input.get();  // consume char
      
      T.ID = TokenID::UNKNOWN;
      
      T.Value  = "";
      T.Value += static_cast<char>(c);
      T.Line   = line;
      T.Col    = col;
      
      col++;
   }
   
   return T;
}
