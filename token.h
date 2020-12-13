/*token.h*/

//
// Token definitions for SimpleC programming language
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 04
//
// DO NOT CHANGE THIS FILE
//

#pragma once

#include <iostream>
#include <istream>
#include <string>
#include <cctype>  // isdigit, isalpha

using namespace std;


//
// Token
// 
// A token in the SimpleC programming language
//
struct Token
{
   int     ID;    // TokenID (see enum below)
   string  Value; // the actual token, e.g. ";", "123", or "x"
   int     Line;  // line containing the token (1-based)
   int     Col;   // column where the token starts (1-based)

   //
   // overload << so we can output a Token easily
   //
   friend ostream& operator<<(ostream& os, const Token& T);  // defined in token.cpp
};


//
// TokenID
//
// Every token in SimpleC has a unique ID number
//
enum TokenID 
{ 
   UNKNOWN = -1, // a character that is not part of SimpleC
   EOS,          // End-Of-Stream
   SEMICOLON,    // ;
   LEFT_PAREN,   // (
   RIGHT_PAREN,  // )
   LEFT_BRACE,   // {
   RIGHT_BRACE,  // }
   PLUS,         // +
   MINUS,        // -
   MULT,         // *
   DIV,          // /
   MOD,          // %
   GT,           // >
   GTE,          // >=
   INPUT,        // >>
   LT,           // <
   LTE,          // <=
   OUTPUT,       // <<
   EQUAL,        // =
   EQUAL_EQUAL,  // ==
   NOT_EQUAL,    // !=
   INT_LITERAL,  // e.g. 123
   STR_LITERAL,  // e.g. "hello cs141"
   IDENTIFIER,   // e.g. count
   VOID_KEYW,    // void
   MAIN_KEYW,    // main
   INT_KEYW,     // int
   CIN_KEYW,     // cin
   COUT_KEYW,    // cout
   ENDL_KEYW,    // endl
   WHILE_KEYW,   // while
   IF_KEYW,      // if
   ELSE_KEYW     // else
};


//
// nextToken() declaration so it can be called from other files:
//
Token nextToken(istream& input, int& line, int& col);
