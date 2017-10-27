/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include <iostream>
#include "statement.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {}

Statement::~Statement() {}

Comment::Comment(TokenScanner & scanner) {}

Comment::~Comment() {}

int Comment::execute(EvalState & state) { return 0; }

Assignment::Assignment(TokenScanner & scanner)
{
	exp = parseExp(scanner);
}

Assignment::~Assignment()
{
	delete exp;
}

int Assignment::execute(EvalState & state)
{
	exp->eval(state);
	return 0;
}

Print::Print(TokenScanner & scanner)
{
	exp = parseExp(scanner);
}

Print::~Print()
{
	delete exp;
}

int Print::execute(EvalState & state)
{
	std::cout << exp->eval(state) << std::endl;
	return 0;
}

Input::Input(TokenScanner & scanner)
{
	var = scanner.nextToken();
	if (scanner.getTokenType(var) == NUMBER || scanner.hasMoreTokens())
		error("SYNTAX ERROR");
}

Input::~Input() {}

int Input::execute(EvalState & state)
{
	while (1)
	{
		std::cout << " ? ";
		string tmp; getline(cin, tmp);
		int ans = 0;
		try
		{
			ans = stringToInt(tmp);
			state.setValue(var, ans);
			break;
		}
		catch(ErrorException & ex)
		{
			cout << "INVALID NUMBER" << endl;
		}
	}
	return 0;
}

END::END(TokenScanner & scanner) {}

END::~END() {}

int END::execute(EvalState & state) { return -1; }

Term::Term(TokenScanner & scanner)
{
	exp = parseBoolExp(scanner);
	gotoExp = parseExp(scanner);
	
}

Term::~Term()
{
	delete exp;
	delete gotoExp;
}

int Term::execute(EvalState & state)
{
	return exp->eval(state) ? gotoExp->eval(state) : 0;
}

Jump::Jump(TokenScanner & scanner)
{
	gotoExp = parseExp(scanner);
}

Jump::~Jump()
{
	delete gotoExp;
}

int Jump::execute(EvalState & state)
{
	return gotoExp->eval(state);
}

Statement* readCode(TokenScanner & scanner)
{
	string token = scanner.nextToken();
	if (token == "REM") return new Comment(scanner);
	if (token == "LET") return new Assignment(scanner);
	if (token == "PRINT") return new Print(scanner);
	if (token == "INPUT") return new Input(scanner);
	if (token == "END") return new END(scanner);
	if (token == "IF") return new Term(scanner);
	if (token == "GOTO") return new Jump(scanner);
	error("Error Statement");
	return NULL;
}

