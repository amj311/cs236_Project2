#include "pch.h"
#include "../../Project2/Parser.h"


#include <fstream>

string getFile(string path) {
	ifstream ifs(path);
	return string((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));
}


TEST(matchType, SCHEMES_bad) {
	vector<Token*> tokens = {
		new Token()
	};
	Parser parser(tokens);
	EXPECT_THROW(parser.tryAdvanceIfType(SCHEMES), E_BADTOKEN);
}

TEST(matchType, SCHEMES_good) {
	vector<Token*> tokens = {
		new Token(SCHEMES,"SCHEMES",1)
	};
	Parser parser(tokens);
	EXPECT_TRUE(parser.tryAdvanceIfType(SCHEMES));
}




TEST(SkipComments, repeatList) {
	vector<Token*> tokens = {
		new Token(COMMA,",",1),
		new Token(ID,"S",1),
		new Token(COMMENT,"#,",1),
		new Token(COMMENT,"#,",1),
		new Token(COMMENT,"#,",1),
		new Token(COMMA,",",1),
		new Token(ID,"N",1),
		new Token(RIGHT_PAREN,")",1),
	};
	Parser parser(tokens);
	vector<Token> list = parser.repeatListOfType(ID);
	EXPECT_EQ(list.size(), 4);
}


TEST(repeatList, ID_good) {
	vector<Token*> tokens = {
		new Token(COMMA,",",1),
		new Token(ID,"S",1),
		new Token(COMMA,",",1),
		new Token(ID,"N",1),
		new Token(RIGHT_PAREN,")",1),
	};
	Parser parser(tokens);
	vector<Token> list = parser.repeatListOfType(ID);
	EXPECT_EQ(list[0].toString(), "(COMMA,\",\",1)");
}
TEST(repeatList, ID_bad) {
	vector<Token*> tokens = {
		new Token(COMMA,",",1),
		new Token(ID,"S",1),
		new Token(ID,"N",1),
		new Token(RIGHT_PAREN,")",1),
	};
	Parser parser(tokens);
	vector<Token> list = parser.repeatListOfType(ID);
	EXPECT_EQ(list.size(), 2);
}
TEST(repeatList, ID_bad_wrongType) {
	vector<Token*> tokens = {
		new Token(COMMA,",",1),
		new Token(ID,"S",1),
		new Token(COMMA,",",1),
		new Token(STRING,"'N'",1),
		new Token(RIGHT_PAREN,")",1),
	};
	Parser parser(tokens);
	EXPECT_THROW(parser.repeatListOfType(ID), E_BADTOKEN);
}





TEST(parseProgram, throwErrorBeforeEnd) {
	vector<Token*> tokens = {
		new Token(SCHEMES,"Schemes",1),
		new Token(COLON,":",1),
		new Token(ID,"S",2),
		new Token(LEFT_PAREN,"(",2),
		new Token(EOF_TYPE,"",3),
	};
	Parser parser(tokens);
	EXPECT_THROW(parser.parseProgram(), E_BADTOKEN);
}






#include "../../Project2/Lexer.h"

TEST(parseProgram, testFile) {
	string file = getFile("../../Project2/testFile.txt");
	
	Lexer lexer(file);
	lexer.tokenizeInput();

	Parser parser(lexer.getTokenList());
	bool res = parser.parseProgram();
	EXPECT_TRUE(res);
}


