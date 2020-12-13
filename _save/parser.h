/*parser.h*/

//
// Recursive-descent parser declarations for SimpleC programming language
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
#include <list>

#include "token.h"

using namespace std;

//
// recursive-descent functions defined in parser.cpp:
//
bool simplec(list<Token>& tokens, bool trace);
bool stmts(list<Token>& tokens, bool trace);
bool stmt(list<Token>& tokens, bool trace);
bool missing(list<Token>& tokens, bool trace);
bool vardecl(list<Token>& tokens, bool trace);
bool input(list<Token>& tokens, bool trace);
bool output(list<Token>& tokens, bool trace);
bool output_elem(list<Token>& tokens, bool trace);
bool more_elems(list<Token>& tokens, bool trace);
bool assignment(list<Token>& tokens, bool trace);
bool block(list<Token>& tokens, bool trace);
bool whileloop(list<Token>& tokens, bool trace);
bool ifthenelse(list<Token>& tokens, bool trace);
bool elseblock(list<Token>& tokens, bool trace);
bool expr(list<Token>& tokens, bool trace);
bool term(list<Token>& tokens, bool trace);
bool oper(list<Token>& tokens, bool trace);
