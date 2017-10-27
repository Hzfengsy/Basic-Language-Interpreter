/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"

#include "../StanfordCPPLib/map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {}

EvalState::~EvalState() {}

void EvalState::setValue(string var, int value)
{
	if (var == "LET" || var == "REM" || var == "PRINT" || var == "INPUT" || var == "END"
		|| var == "IF" || var == "THEN" || var == "GOTO" || var == "RUN" || var == "LIST"
		|| var == "QUIT" || var == "CLEAR" || var == "HELP")
	{
		cout << "SYNTAX ERROR" << endl;
		error("SYNTAX ERROR");
		return;
	}
	symbolTable.put(var, value);
}

int EvalState::getValue(string var)
{
	return symbolTable.get(var);
}

bool EvalState::isDefined(string var)
{
	return symbolTable.containsKey(var);
}

void EvalState::clear()
{
	symbolTable.clear();
}
