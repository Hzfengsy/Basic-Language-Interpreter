/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>

#include "exp.h"
#include "parser.h"

#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner & scanner)
{
	Expression *exp = readE(scanner, 0);
	if (scanner.hasMoreTokens()) {
		error("parseExp: Found extra token: " + scanner.nextToken());
	}
	return exp;
}

Expression *parseBoolExp(TokenScanner & scanner)
{
	Expression *exp = readE(scanner, 1);
	if (scanner.nextToken() != "THEN")
	{
		error("parseExp: Didn't find \"THE\" ");
	}
	return exp;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int flag, int prec)
{
	Expression *exp = readT(scanner, flag);
	string token;
	while (true) {
		token = scanner.nextToken();
		int newPrec = precedence(token);
		if (newPrec <= prec) break;
		Expression *rhs = readE(scanner, flag, newPrec);
		if (flag && token == "=") token = "==";
		exp = new CompoundExp(token, exp, rhs);
	}
	scanner.saveToken(token);
	return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner, int flag)
{
	string token = scanner.nextToken();
	TokenType type = scanner.getTokenType(token);
	if (type == WORD) return new IdentifierExp(token);
	if (type == NUMBER) return new ConstantExp(stringToInteger(token + " "));
	if (token != "(") error("Illegal term in expression");
	Expression *exp = readE(scanner, flag);
	if (scanner.nextToken() != ")") {
		error("Unbalanced parentheses in expression");
	}
	return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token)
{
	if (token == "=" || token == "<" || token == ">") return 1;
	if (token == "+" || token == "-") return 2;
	if (token == "*" || token == "/") return 3;
	return 0;
}

int stringToInt(string token)
{
	int ans = 0;
	bool flag = token[0] == '-';
	for (int i = token[0] == '-' ? 1 : 0; i < token.length(); i++)
		if (token[i] <'0' || token[i] > '9') error("Illegal integer format");
		else ans = ans * 10 + token[i] - '0';
	return flag ? -ans : ans;
}
