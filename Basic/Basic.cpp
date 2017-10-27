/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

int processLine(const string & line, Program & program, EvalState & state);

/* Main program */

int main() {
	//freopen("Test.txt", "r", stdin);
	Program program;
	EvalState state;
	string tmp;
	while (getline(cin, tmp)) {
		try {
			if (processLine(tmp, program, state)) return 0;
		} catch (ErrorException & ex) {
			cerr << "Error: " << ex.getMessage() << endl;
		}
	}
	return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void ShowHelp()
{
	cout << "Help" << endl;
}

int Optration(const string & token, Program & program, TokenScanner & scanner, EvalState & state)
{
	Statement *stmt = NULL;
	if (token == "LIST") program.ListCode();
	if (token == "RUN") program.Run(state);
	if (token == "CLEAR") program.clear(), state.clear();
	if (token == "QUIT") return -1;
	if (token == "REM") stmt = new Comment(scanner);
	if (token == "LET") stmt = new Assignment(scanner);
	if (token == "PRINT") stmt = new Print(scanner);
	if (token == "INPUT") stmt = new Input(scanner);
	if (stmt)
	{
		stmt->execute(state);
		delete stmt;
	}
	return 0;
}

int Coding(int lineNum, const string & line, TokenScanner & scanner, Program & program)
{
	if (scanner.hasMoreTokens())
	{
		program.addSourceLine(lineNum, line);
		program.setParsedStatement(lineNum, readCode(scanner));
	}
	else program.removeSourceLine(lineNum);
	return 0;
}

int processLine(const string & line, Program & program, EvalState & state)
{
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
//	Expression *exp = parseExp(scanner);
//	int value = exp->eval(state);
//	cout << value << endl;
//	delete exp;
	string token = scanner.nextToken();
	TokenType type = scanner.getTokenType(token);
	if (type == WORD) return Optration(token, program, scanner, state);
	if (type == NUMBER) return Coding(stringToInt(token), line, scanner, program);
	error("Illegal term in expression");
	return -1;
}
