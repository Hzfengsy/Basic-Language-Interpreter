/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished varsion, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "parser.h"
#include <iostream>
#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

	Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

	virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

	virtual int execute(EvalState & state) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class Comment : public Statement
{
public:
	Comment(TokenScanner & scanner);
	virtual ~Comment();
	int execute(EvalState & state);
};

class Assignment : public Statement
{
private:
	Expression *exp;
public:
	Assignment(TokenScanner & scanner);
	virtual ~Assignment();
	int execute(EvalState & state);
};

class Print : public Statement
{
private:
	Expression *exp;
public:
	Print(TokenScanner & scanner);
	virtual ~Print();
	int execute(EvalState & state);
};

class Input : public Statement
{
private:
	string var;
public:
	Input(TokenScanner & scanner);
	virtual ~Input();
	int execute(EvalState & state);
};

class END : public Statement
{
public:
	END(TokenScanner & scanner);
	virtual ~END();
	int execute(EvalState & state);
};

class Term : public Statement
{
private:
	Expression *exp, *gotoExp;
public:
	Term(TokenScanner & scanner);
	virtual ~Term();
	int execute(EvalState & state);
};

class Jump : public Statement
{
private:
	Expression *gotoExp;
public:
	Jump(TokenScanner & scanner);
	virtual ~Jump();
	int execute(EvalState & state);
};

Statement* readCode(TokenScanner & scanner);
#endif

