/*parser.cpp*/

//
// Recursive-descent parsing functions for SimpleC programming language
//
// ???
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 04
//

#include <iostream>
#include <istream>
#include <string>
#include <list>

#include "token.h"
#include "parser.h"

using namespace std;


//
// recursive-descent functions:
//

//
// <simplec> ::= void main ( ) <block> $
//
bool simplec(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<simplec>" << endl;
   }
   
   //
   // TODO:
   //

   return false;
}


//
// <stmt> ::= ...
//
bool stmt(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<stmt>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <missing> ::= ;
//
bool missing(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<missing>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <vardecl> ::= int IDENTIFIER ;
//
bool vardecl(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<vardecl>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <input> ::= cin >> IDENTIFIER ;
//
bool input(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<input>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <output> ::= cout << <output_elem> ;
//
bool output(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<output>" << endl;
   }
   
   //
   // TODO:
   //

   return false;
}


//
// <output_elem> ::= << <expr>
//                 | << endl
//
bool output_elem(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<output_elem>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <assignment> ::= IDENTIFIER = <expr> ;
//
bool assignment(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<assignment>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <block> ::= { <stmt> }
//
bool block(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<block>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <whileloop> ::= while ( <expr> ) <block>
//
bool whileloop(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<whileloop>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <ifthenelse> ::= if ( <expr> ) <block> <elseblock>
//
bool ifthenelse(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<ifthenelse>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <elseblock> ::= else <block>
//               | EMPTY
//
bool elseblock(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<elseblock>" << endl;
   }

   //
   // TODO:
   //

   return false;
}


//
// <expr> ::= IDENTIFIER
//          | INT_LITERAL
//          | STR_LITERAL
//
bool expr(list<Token>& tokens, bool trace)
{
   if (trace)
   {
      cout << "<expr>" << endl;
   }

   //
   // TODO:
   //

   return false;
}
