/*main.cpp*/

//
// main program for testing components of SimpleC parsing project
//
// ???
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 04
//

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <list>

#include "token.h"
#include "parser.h"

using namespace std;


//
// inputSimpleC
//
// Inputs a SimpleC program from either a file or the keyboard.
// If the filename != "" then we try to open the file; if filename
// is "" then we assume keyboard input via cin; the user can 
// simulate EOF on a keyboard via Ctrl-D on Linux or Ctrl-Z then 
// ENTER on Windows.
//
// Pre-condition: filename is "" or a filename containing a 
// SimpleC program.
//
// Post-condition: a list of SimpleC tokens is returned.  If a
// filename was specified and the file could not be opened, an
// error message is output and an empty list is returned.
//
list<Token> inputSimpleC(string filename)
{
   Token        T;
   list<Token>  tokens;
   int          line, col;

   line = 1;
   col = 1;

   //
   // if the filename is "", we use cin as our input stream:
   //
   if (filename == "")
   {
      T = nextToken(cin, line, col);

      while (T.ID != TokenID::EOS)
      {
         tokens.push_back(T);

         T = nextToken(cin, line, col);
      }

      tokens.push_back(T);  // EOS
   }
   else
   {
      //
      // we use the contents of the file as input stream:
      //
      ifstream infile(filename);

      if (!infile.good())
      {
         cout << "**Error, unable to open input file '" << filename << "'" << endl;
         return tokens;  // empty list:
      }

      T = nextToken(infile, line, col);

      while (T.ID != TokenID::EOS)
      {
         tokens.push_back(T);

         T = nextToken(infile, line, col);
      }

      tokens.push_back(T);  // EOS
   }

   //
   // return tokens back to caller:
   //
   return tokens;
}



//
// main
//
int main()
{
   list<Token>  tokens;
   string       filename;

   //
   // First, let's input all the tokens into a list:
   //
   cout << "Enter a SimpleC filename (or press ENTER for keyboard input): ";
   getline(cin, filename);

   tokens = inputSimpleC(filename);

   if (tokens.size() == 0)  // no tokens, end program:
   {
      // error msg about file would have already been output:

      return 0;
   }

   //
   // Let's output the tokens out to the console to make sure things
   // are working:
   //
   cout << endl;

   for (Token T : tokens)  // foreach token T in the list:
   {
      cout << T;  // NOTE: Token struct overrides << to allow this to work

      if (T.ID != TokenID::EOS)
         cout << ", ";
   }

   cout << endl;
   cout << endl;

   //
   // Okay, let's parse the SimpleC program:
   //
//   cout << "Parsing..." << endl;
//   
//   bool success;
//
//   success = simplec(tokens, false /*no trace*/);
//
//   if (success)
//   {
//      cout << "Success, no syntax errors" << endl;
//   }
//   else
//   {
//      cout << "Failed due to syntax error" << endl;
//   }

   return 0;
}
