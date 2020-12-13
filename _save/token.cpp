/*token.cpp*/

//
// nextToken function needed for parsing of SimpleC programming language
//
// ???
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
   }
   
   
   //
   // TODO!
   //
   
   
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
