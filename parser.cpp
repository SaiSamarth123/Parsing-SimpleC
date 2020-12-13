/*parser.cpp*/

//
// Recursive-descent parsing functions for SimpleC programming language
//
// Completed version by
// Author: Sai Samarth, U. of Illinois Chicago, Fall 2020
// Date: 02 November 2020
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
//
//syntaxError: prints a syntax error statement
// given the expecting string and Token
//
//
void syntaxError(string expecting, Token found) // syntaxError function prints when a syntax error is found
{
  cout << "Syntax error: expecting " << "'" << expecting << "', found '" << found.Value << "' @ (" << found.Line << ", " << found.Col << ")" << endl;
}

//
// recursive-descent functions:
//
//
// <simplec> ::= void main ( ) <block> $
//
bool simplec(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<simplec>" << endl;
  }
  Token T = tokens.front();
  if (T.ID == TokenID::VOID_KEYW) { //checks if the token is equal to VOID_KEYW
    tokens.pop_front();
    T = tokens.front();
    if (T.ID == TokenID::MAIN_KEYW) { //checks if the token is equal to MAIN_KEYW
      tokens.pop_front();
      T = tokens.front();
      if (T.ID == TokenID::LEFT_PAREN) { //checks if the token is equal to LEFT_PAREN
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::RIGHT_PAREN) { //checks if the token is equal to RIGHT_PAREN
          tokens.pop_front();
          if (block(tokens, trace)) { //checks if the the following tokens follow the format of block
            T = tokens.front();
            if (T.ID == TokenID::EOS) { //checks if the token is equal to EOS
              tokens.pop_front();
              return true;
            } else {
              syntaxError("EOS", T); //calls syntax error if "EOS" is not found
              return false;
            }
          } else {
            return false;
          }
        } else {
          syntaxError(")", T); //calls syntax error if ")" is not found
          return false;
        }
      } else {
        syntaxError("(", T); //calls syntax error if "(" is not found
        return false;
      }
    } else {
      syntaxError("main", T); //calls syntax error if "main" is not found
      return false;
    }
  } else {
    syntaxError("void", T); //calls syntax error if "void" is not found
    return false;
  }
}

//
//<stmts> ::= <stmt> <stmts>
//            | EMPTY
//
bool stmts(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<stmts>" << endl;
  }
  Token T = tokens.front();

  if (T.ID == TokenID::RIGHT_BRACE || T.ID == TokenID::EOS) { //checks if it is empty or EOS
    return true;
  }

  if (stmt(tokens, trace)) {// checks if the token follows the format of stmt
    if (stmts(tokens, trace)) {// checks if the token follows the format of stmts
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

//
// <stmt> ::= ...
//
bool stmt(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<stmt>" << endl;
  }

  Token T = tokens.front();
  if (T.ID == TokenID::SEMICOLON) { //checks if the token is equal to SEMICOLON
    if (missing(tokens, trace)) { //checks if the the following tokens follow the format of missing
      return true;
    } else {
      return false;
    }
  } else if (T.ID == TokenID::INT_KEYW) { //checks if the token is equal to INT_KEYW
    if (vardecl(tokens, trace)) { //checks if the the following tokens follow the format of vardecl
      return true;
    } else {
      return false;
    }
  } else if (T.ID == TokenID::CIN_KEYW) { //checks if the token is equal to CIN_KEYW
    if (input(tokens, trace)) { //checks if the the following tokens follow the format of input
      return true;
    } else {
      return false;
    }
  } else if (T.ID == TokenID::COUT_KEYW) { //checks if the token is equal to COUT_KEYW
    if (output(tokens, trace)) { //checks if the the following tokens follow the format of output
      return true;
    } else {
      return false;
    }
  } else if (T.ID == TokenID::IDENTIFIER) { //checks if the token is equal to IDENTIFIER
    if (assignment(tokens, trace)) { //checks if the following tokens follow the format of assignment
      return true;
    } else {
      return false;
    }
  } else if (T.ID == TokenID::LEFT_BRACE) { //checks if the token is equal to LEFT_BRACE
    if (block(tokens, trace)) { //checks if the following tokens follow the format of block
      return true;
    } else {
      return false;
    }
  } else if (T.ID == TokenID::WHILE_KEYW) { //checks if the token is equal to WHILE_KEYW
    if (whileloop(tokens, trace)) { //checks if the following tokens follow the format of whileloop
      return true;
    } else {
      return false;
    }
  } else if (T.ID == TokenID::IF_KEYW) { //checks if the token is equal to IF_KEYW
    if (ifthenelse(tokens, trace)) { //checks if the following tokens follow the format of ifthenelse
      return true;
    } else {
      return false;
    }
  } else {
    syntaxError("}", T); //calls syntax error if "}" is not found
    return false;
  }
}

//
// <missing> ::= ;
//
bool missing(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<missing>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::SEMICOLON) { //checks if the token is equal to SEMICOLON
    tokens.pop_front();
    return true;
  } else {
    syntaxError(";", T); //calls syntax error if ";" is not found
    return true;
  }
}

//
// <vardecl> ::= int IDENTIFIER ;
//
bool vardecl(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<vardecl>" << endl;
  }

  Token T = tokens.front();
  if (T.ID == TokenID::INT_KEYW) { //checks if the token is equal to INT_KEYW
    tokens.pop_front();
    T = tokens.front();
    if (T.ID == TokenID::IDENTIFIER) { //checks if the token is equal to IDENTIFIER
      tokens.pop_front();
      T = tokens.front();
      if (T.ID == TokenID::SEMICOLON) { //checks if the token is equal to SEMICOLON
        tokens.pop_front();
        return true;
      } else {
        syntaxError(";", T); //calls syntax error if ";" is not found
        return false;
      }
    } else {
      syntaxError("IDENTIFIER", T); //calls syntax error if "IDENTIFIER" is not found
      return false;
    }
  } else {
    syntaxError("int", T); //calls syntax error if "int" is not found
    return false;
  }
}

//
// <input> ::= cin >> IDENTIFIER ;
//
bool input(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<input>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::CIN_KEYW) { //checks if the token is equal to CIN_KEYW
    tokens.pop_front();
    T = tokens.front();
    if (T.ID == TokenID::INPUT) { //checks if the token is equal to INPUT
      tokens.pop_front();
      T = tokens.front();
      if (T.ID == TokenID::IDENTIFIER) { //checks if the token is equal to IDENTIFIER
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::SEMICOLON) { //checks if the token is equal to SEMICOLON
          tokens.pop_front();
          return true;
        } else {
          syntaxError(";", T); //calls syntax error if ";" is not found
          return false;
        }

      } else {
        syntaxError("IDENTIFIER", T); //calls syntax error if "IDENTIFIER" is not found
        return false;
      }

    } else {
      syntaxError(">>", T); //calls syntax error if ">>" is not found
      return false;
    }
  } else {
    syntaxError("cin", T); //calls syntax error if "cin" is not found
    return false;
  }
}

//
// <output> ::= cout << <output_elem> <more_elems> ;
//
bool output(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<output>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::COUT_KEYW) { //checks if the token is equal to COUT_KEYW
    tokens.pop_front();
    if (output_elem(tokens, trace)) { //checks if the following tokens follow the format of output_elem
      if (more_elems(tokens, trace)) {// checks if the following tokens follow the format of more_elems
        T = tokens.front();
        if (T.ID == TokenID::SEMICOLON) { //checks if the token is equal to SEMICOLON
          tokens.pop_front();
          return true;
        } else {
          syntaxError(";", T); //calls syntax error if ";" is not found
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    syntaxError("cout", T); //calls syntax error if "cout" is not found
    return false;
  }
}

//
// <output_elem> ::= << <expr>
//                 | << endl
//
bool output_elem(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<output_elem>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::OUTPUT) { //checks if the token is equal to OUTPUT
    tokens.pop_front();
    T = tokens.front();
    if (T.ID == TokenID::ENDL_KEYW) { //checks if the token is equal to ENDL_KEYW
      tokens.pop_front();
      return true;
    } else {
      if (expr(tokens, trace)) { //checks if the following tokens follow the format of expr
        return true;
      } else {
        return false;
      }

    }
  } else {
    syntaxError("<<", T); //calls syntax error if "<<" is not found
    return false;
  }

}

//
// <more_elems> ::= <output_elem> <more_elems>
//                  | EMPTY
bool more_elems(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<assignment>" << endl;
  }
  Token T = tokens.front();
  if (T.ID != TokenID::OUTPUT) {// checks if the token is equal to OUTPUT
    return true;
  }

  if (output_elem(tokens, trace)) {// checks if the following tokens follow the format of output_elem
    if (more_elems(tokens, trace)) {// checks if the following tokens follow the format of more_elems
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }

}

//
// <assignment> ::= IDENTIFIER = <expr> ;
//
bool assignment(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<assignment>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::IDENTIFIER) {

    tokens.pop_front();
    T = tokens.front();
    if (T.ID == TokenID::EQUAL) { //checks if the token is equal to EQUAL
      tokens.pop_front();
      if (expr(tokens, trace)) {
        T = tokens.front();
        if (T.ID == TokenID::SEMICOLON) { //checks if the token is equal to SEMICOLON
          tokens.pop_front();
          return true;
        } else {
          syntaxError(";", T); //calls syntax error if ";" is not found
          return false;
        }
      } else {
        return false;
      }
    } else {
      syntaxError("=", T); //calls syntax error if "=" is not found
      return false;
    }
  } else {
    syntaxError("IDENTIFIER", T); //calls syntax error if "IDENTIFIER" is not found
    return false;
  }
}

//
// <block> ::= { <stmts> }
//
bool block(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<block>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::LEFT_BRACE) { //checks if token is equal to LEFT_BRACE
    tokens.pop_front();
    if (stmts(tokens, trace)) {
      T = tokens.front();
      if (T.ID == TokenID::RIGHT_BRACE) { //checks if token is equal to RIGHT_BRACE
        tokens.pop_front();
        return true;
      } else {
        syntaxError("}", T); //calls syntax error if "}" is not found
        return false;
      }
    } else {
      return false;
    }
  } else {
    syntaxError("{", T); //calls syntax error if "{" is not found
    return false;
  }
}

//
// <whileloop> ::= while ( <expr> ) <block>
//
bool whileloop(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<whileloop>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::WHILE_KEYW) { //checks if the token is equal to WHILE_KEYW
    tokens.pop_front();
    T = tokens.front();
    if (T.ID == TokenID::LEFT_PAREN) { //checks if the token is equal to LEFT_PAREN
      tokens.pop_front();
      if (expr(tokens, trace)) { //checks if the following tokens follow the format of expr
        T = tokens.front();
        if (T.ID == TokenID::RIGHT_PAREN) { //checks if the token is equal to RIGHT_PAREN
          tokens.pop_front();
          if (block(tokens, trace)) { //checks if the following tokens follow the format of block
            return true;
          } else {
            return false;
          }
        } else {
          syntaxError(")", T); //calls syntax error if ")" is not found
          return false;
        }
      } else {
        return false;
      }
    } else {
      syntaxError("(", T); //calls syntax error if "(" is not found
      return false;
    }
  } else {
    syntaxError("while", T); //calls syntax error if "while" is not found
    return false;
  }
}

//
// <ifthenelse> ::= if ( <expr> ) <block> <elseblock>
//
bool ifthenelse(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<ifthenelse>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::IF_KEYW) { //checks if the token is equal to IF_KEYW
    tokens.pop_front();
    T = tokens.front();
    if (T.ID == TokenID::LEFT_PAREN) { //checks if the token is equal to LEFT_PAREN
      tokens.pop_front();
      if (expr(tokens, trace)) {
        T = tokens.front();
        if (T.ID == TokenID::RIGHT_PAREN) { //checks if the token is equal to RIGHT_PAREN
          tokens.pop_front();
          if (block(tokens, trace)) {
            if (elseblock(tokens, trace)) { //checks if following tokens follow the format of elseblock
              return true;
            } else {
              return false;
            }
          } else {
            return false;
          }
        } else {
          syntaxError(")", T); //calls syntax error if ")" is not found
          return false;
        }
      } else {
        return false;
      }

    } else {
      syntaxError("(", T); //calls syntax error if "(" is not found
      return false;
    }
  } else {
    syntaxError("if", T); //calls syntax error if "if" is not found
    return false;
  }
}

//
// <elseblock> ::= else <block>
//               | EMPTY
//
bool elseblock(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<elseblock>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::ELSE_KEYW) { //checks if the token is ELSE_KEYW
    tokens.pop_front();
    if (block(tokens, trace)) { //checks if the following tokens have the format of block
      return true;
    } else {
      return false;
    }

  } else {
    return true;
  }

}

//
// <expr> ::= <term> <oper> <expr>
//          | <term>
//
bool expr(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<expr>" << endl;
  }

  if (term(tokens, trace)) {// checks if the following tokens follow the format of term
    Token T = tokens.front();
    if (T.ID == TokenID::PLUS || T.ID == TokenID::MINUS || T.ID == TokenID::MULT || T.ID == TokenID::DIV || T.ID == TokenID::MOD || T.ID == TokenID::LT || T.ID == TokenID::LTE || T.ID == TokenID::GT || T.ID == TokenID::GTE || T.ID == TokenID::EQUAL_EQUAL || T.ID == TokenID::NOT_EQUAL) {
      if (oper(tokens, trace)) {// checks if the following tokens follow the format of oper
        T = tokens.front();
        if (expr(tokens, trace)) {// checks if the following tokens follow the format of expr
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return true;
    }
  } else {
    return false;
  }
}

//
// <term> ::= ( <expr> ) 
//          | IDENTIFIER
//          | INT_LITERAL
//          | STR_LITERAL
//
bool term(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<expr>" << endl;
  }
  Token T = tokens.front();

  if (T.ID == TokenID::LEFT_PAREN) {// checks if the token is equal to LEFT_PAREN
    tokens.pop_front();
    if (expr(tokens, trace)) {// checks if the following tokens follow the format of expr
      T = tokens.front();
      if (T.ID == TokenID::RIGHT_PAREN) {// checks if the token is equal to RIGHT_PAREN
        tokens.pop_front();
        return true;
      } else {
        syntaxError(")", T);// calls syntax error if ")" is not found
        return false;
      }
    } else {
      return false;
    }
  } else if (T.ID == TokenID::IDENTIFIER) {// checks if the token is equal to IDENTIFIER
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::INT_LITERAL) {// checks if the token is equal to INT_LITERAL
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::STR_LITERAL) {// checks if the token is equal to STR_LITERAL
    tokens.pop_front();
    return true;
  } else {
    syntaxError("term", T);// calls syntaxError if "term" is not found
    return false;
  }
}

//
// <oper> ::= .....
//
bool oper(list < Token > & tokens, bool trace) {
  if (trace) {
    cout << "<expr>" << endl;
  }

  Token T = tokens.front();

  if (T.ID == TokenID::PLUS) {// checks if the token is equal to PLUS
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::MINUS) {// checks if the token is equal to MINUS
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::MULT) {// checks if the token is equal to MULT
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::DIV) {// checks if the token is equal to DIV
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::MOD) {// checks if the token is equal to MOD
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::LT) {// checks if the token is equal to LT
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::LTE) {// checks if the token is equal to LTE
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::GT) {// checks if the token is equal to GT
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::GTE) {// checks if the token is equal to GTE
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::EQUAL_EQUAL) {// checks if the token is equal to EQUAL_EQUAL
    tokens.pop_front();
    return true;
  } else if (T.ID == TokenID::NOT_EQUAL) {// checks if the token is equal to NOT_EQUAL
    tokens.pop_front();
    return true;
  } else {
    syntaxError("oper", T);// calls syntaxError if "oper" is not found
    return false;
  }
}