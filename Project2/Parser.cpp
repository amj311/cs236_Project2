#include "Parser.h"


void Parser::printFail(E_BADTOKEN& e) {
	cout << "Failure!" << endl << e.tokenStr() << endl;
}

void Parser::printSuccess() {
	cout << "Success!" << endl;
}

bool Parser::tryAdvanceIfType(TOKEN_TYPE typeAssert) {
	if (curTokenIs(typeAssert)) {
		// Do parsing stuff.
		advanceToken();
		return true;
	}
	else return throwBadToken(curToken());
}

bool Parser::run() {
	try
	{
		parseProgram();
	}
	catch (E_BADTOKEN e) {
		printFail(e);
		return false;
	}
	return true;
}

bool Parser::parseProgram() {
	tokenIdx = 0;

	tryAdvanceIfType(SCHEMES);
	tryAdvanceIfType(COLON);
	parse_scheme();
	//parse_schemeList();
	
	//tryAdvanceIfType(FACTS);
	//tryAdvanceIfType(COLON);
	//parse_factList();

	//tryAdvanceIfType(RULES);
	//tryAdvanceIfType(COLON);
	//parse_ruleList();

	//tryAdvanceIfType(QUERIES);
	//tryAdvanceIfType(COLON);
	//parse_query();
	//parse_queryList();

	printSuccess();
	return true;
}


vector<Token> Parser::repeatListOfType(TOKEN_TYPE listType) {
	vector<Token> list;

	while (curTokenIs(COMMA)) {
		list.push_back(curToken());
		advanceToken();
		if (curTokenIs(listType)) {
			list.push_back(curToken());
			advanceToken();
		}
		else {
			throwBadToken(curToken());
			break;
		}
	}
	return list;
}

//bool parse_schemeList() {
//	while (curType)
//}

bool Parser::parse_scheme() {
	tryAdvanceIfType(ID);
	tryAdvanceIfType(LEFT_PAREN);
	tryAdvanceIfType(ID);
	repeatListOfType(ID);
	tryAdvanceIfType(RIGHT_PAREN);

	// do parsing stuff.
	return true;
}