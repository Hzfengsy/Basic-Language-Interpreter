/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program()
{
	// Replace this stub with your own code
}

Program::~Program()
{
	// Replace this stub with your own code
}

void Program::clear()
{
	// Replace this stub with your own code
	Code.clear();
}

void Program::addSourceLine(int lineNumber, const string & line)
{
	Code[lineNumber].code = line;
}

void Program::removeSourceLine(int lineNumber)
{
	Code.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber)
{
	return Code[lineNumber].code;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt)
{
	Code[lineNumber].stmt = stmt;
}

Statement *Program::getParsedStatement(int lineNumber)
{
	return Code[lineNumber].stmt;
}

int Program::getFirstLineNumber()
{
	if (Code.begin() == Code.end()) return -1;
	return Code.begin()->first;
}

int Program::getNextLineNumber(int lineNumber)
{
	map<int, node>::iterator it =++Code.find(lineNumber);
	if (it == Code.end()) return -1;
	return it->first;
}

void Program::ListCode()
{
	for (int nowLine = getFirstLineNumber(); nowLine >= 0; nowLine = getNextLineNumber(nowLine))
		cout << getSourceLine(nowLine) << endl;
}

void Program::Run(EvalState & state)
{
	int nowLine = getFirstLineNumber();
	while (nowLine != -1)
	{
		int nextLine = getParsedStatement(nowLine)->execute(state);
		if (nextLine == 0) nowLine = getNextLineNumber(nowLine);
		else
		{
			if (nextLine != -1 && Code.find(nextLine) == Code.end())
			{
				cout << "LINE NUMBER ERROR" << endl;
				error("LINE NUMBER ERROR");
				return;
			}
			else nowLine = nextLine;
		}
	}
}
