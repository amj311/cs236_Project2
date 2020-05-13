#ifndef E_BADTOKEN_H
#define E_BADTOKEN_H

#include "Token.h"
#include <exception>
using namespace std;

struct E_BADTOKEN : public exception
{
	E_BADTOKEN(Token token) : token(token) {}
	Token token;
	string tokenStr() {
		return token.toString();
	}
};

#endif