#ifndef PARSER_H
#define PAERSER_H

#include "Token.h"
#include "E_BADTOKEN.h"

struct Parser
{
	Parser(vector<Token*> tokenInput) : tokens(tokenInput) {};
	bool run();
	bool parseProgram();

	vector<Token*> tokens;
	int tokenIdx = 0;
	
	Token curToken(bool expectEOF = false) {
		Token curToken = *tokens[tokenIdx];
		if (expectEOF && curToken.getType() != EOF_TYPE) throwBadToken(curToken);
		return curToken;
	}

	TOKEN_TYPE curTokenType() {
		return curToken().getType();
	}
	bool curTokenIs(TOKEN_TYPE assertType) {
		return curToken().isType(assertType);
	}
	void advanceToken() {
		tokenIdx++;
		while (tokenIdx < tokens.size() && curTokenIs(COMMENT)) tokenIdx++;
	}
	bool throwBadToken(Token badToken) {
		throw E_BADTOKEN(badToken);
		return false;
	}
	bool tryAdvanceIfType(TOKEN_TYPE typeAssert);

	void printFail(E_BADTOKEN& e);
	void printSuccess();

	vector<Token> repeatListOfType(TOKEN_TYPE);

	bool parse_schemeList() {return true; };
	bool parse_scheme();

	bool parse_factList() {return true; };
	bool parse_fact() {return true; };

	bool parse_ruleList() {return true; };
	bool parse_rule() {return true; };

	bool parse_queryList() {return true; };
	bool parse_query() {return true; };

	bool parse_headPredicate() {return true; };
	bool parse_predicate() {return true; };

	bool parse_parameter() {return true; };
};

#endif