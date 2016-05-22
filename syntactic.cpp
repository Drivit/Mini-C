#include "syntactic.h"

enum
{
	IDENTIFIER,
	CONSTANT,
	PLUS_OPERATOR,
	MINUS_OPERATOR,
	MULTTIPLICATION_OPERATOR,
	DIVISION_OPERATOR,
	MOD_OPERATOR,
	LESS_THAN_OPERATOR,
	GREATER_THAN_OPERATOR,
	ASSIGMENT_OPERATOR,
	PARENTH_OPEN,
	PARENTH_CLOSE,
	KEY_OPEN,
	KEY_CLOSE,
	COMA,
	NEGATION,
	SPACE,
	NEW_LINE,
	TAB,
	SEMICOLON,
	BLOCK_COMMENT,
	COMMENT,
	LESS_THAN_OR_EQUAL_OPERATOR,
	GREATER_THAN_OR_EQUAL_OPERATOR,
	EQUAL_OPERATOR,
	NOT_EQUAL_OPERATOR,
	RESERVED_WORD
};

Sintactic::Sintactic(std::vector<Token> tokens)
{
	tokenActual_ = 0;
	tokensList_ = tokens;
}

void Sintactic::analize()
{
	TRANSLATION_UNIT();
	matchEOF();
}

void Sintactic::TRANSLATION_UNIT()
{
	if(tokenActual_ < tokensList_.size())
	{
		if(tokenActual_Content() == "int" || tokenActual_Content() == "void")
		{
			nextToken();
			match(IDENTIFIER);
			TRANSLATION_UNIT_P();
		}
		else if(tokenActual_Content() == "\0")
			nextToken();
	}
}

void Sintactic::TRANSLATION_UNIT_P()
{
	if(tokenActual_Content() == "(")
	{
		nextToken();
		PARAMETER_LIST();
		match(")");
		TRANSLATION_UNIT_OP();
	}
	else
	{
		DECLARATOR();
		match(";");
		TRANSLATION_UNIT();
	}
}

void Sintactic::TRANSLATION_UNIT_OP()
{
	if(tokenActual_Content() == ";")
	{
		nextToken();
		TRANSLATION_UNIT();
	}
	else
	{
		match("{");
		STATEMENT();
		match("}");
		TRANSLATION_UNIT();
	}
}

void Sintactic::DECLARATOR()
{
	if(tokenActual_Content() == "=")
	{
		nextToken();
		EXPRESSION();
		DECLARATOR();
	}
	else if(tokenActual_Content() == ",")
	{
		nextToken();
		match(IDENTIFIER);
		DECLARATOR();
	}
}

void Sintactic::DECLARATION()
{
	if(tokenActual_Content() == "=")
	{
		nextToken();
		EXPRESSION();
		DECLARATION();
	}
	else if(tokenActual_Content() == ",")
	{
		nextToken();
		match(IDENTIFIER);
		DECLARATION();
	}
}

void Sintactic::TYPE_OPERAND()
{
	if(tokenActual() == CONSTANT)
		nextToken();
	else
		match(IDENTIFIER);
}

void Sintactic::PARAMETER_LIST()
{
	if(tokenActual_Content() == "int")
	{
		nextToken();
		match(IDENTIFIER);
		PARAMETER_LIST_P();
	}
}

void Sintactic::PARAMETER_LIST_P()
{
	if(tokenActual_Content() == ",")
	{
		nextToken();
		match("int");
		match(IDENTIFIER);
		PARAMETER_LIST_P();
	}
}

void Sintactic::FUNC_CALL()
{
	match("(");

    if (tokenActual() != PARENTH_CLOSE)
        FUNC_PARAMS();

	match(")");
}

void Sintactic::FUNC_PARAMS()
{
    EXPRESSION();
    FUNC_PARAMS_P();
}

void Sintactic::FUNC_PARAMS_P()
{
	if(tokenActual_Content() == ",")
	{
		nextToken();
        EXPRESSION();
		FUNC_PARAMS_P();
	}
}

void Sintactic::FUNC_OR_ASSIGMENT()
{
	if(tokenActual_Content() == "(")
	{
		FUNC_CALL();
		match(";");
	}
	else
	{
		ASSIGMENT_EXPRESSION();
		match(";");
	}
}

void Sintactic::RELATIONAL_EXPRESSION()
{
    ADDITIVE_EXPRESSION();

    while (tokenActual() == LESS_THAN_OPERATOR ||
           tokenActual() == GREATER_THAN_OPERATOR ||
           tokenActual() == LESS_THAN_OR_EQUAL_OPERATOR ||
           tokenActual() == GREATER_THAN_OR_EQUAL_OPERATOR)
    {
		nextToken();
        ADDITIVE_EXPRESSION();
	}
}

void Sintactic::ADDITIVE_EXPRESSION()
{
    MULTIPLICATIVE_EXPRESSION();

    while (tokenActual() == PLUS_OPERATOR || tokenActual() == MINUS_OPERATOR)
	{
		nextToken();
        MULTIPLICATIVE_EXPRESSION();
	}
}

void Sintactic::MULTIPLICATIVE_EXPRESSION()
{
    FACTOR();

    while (tokenActual() == MULTTIPLICATION_OPERATOR || tokenActual() == DIVISION_OPERATOR || tokenActual() == MOD_OPERATOR)
	{
		nextToken();
        FACTOR();
	}
}

void Sintactic::EXPRESSION()
{
    RELATIONAL_EXPRESSION();

    while (tokenActual() == EQUAL_OPERATOR || tokenActual() == NOT_EQUAL_OPERATOR) {
        nextToken();
        RELATIONAL_EXPRESSION();
    }
}

void Sintactic::FACTOR()
{
    if (tokenActual() == IDENTIFIER) {
        nextToken();

        if (tokenActual() == PARENTH_OPEN) {
            FUNC_CALL();
        }
        else if (tokenActual() == ASSIGMENT_OPERATOR) {
            ASSIGMENT_EXPRESSION();
        }
    }
    else if (tokenActual() == CONSTANT) {
        nextToken();
    }
    else if (tokenActual() == PARENTH_OPEN) {
        nextToken();
        EXPRESSION();
        match(PARENTH_CLOSE);
    }
}

void Sintactic::ASSIGMENT_EXPRESSION()
{
	match(ASSIGMENT_OPERATOR);
	EXPRESSION();
}

void Sintactic::COMPOUND_STATEMENT()
{
	if(tokenActual_Content() == "{")
	{
		nextToken();
		STATEMENT();
		match("}");
	}
	else
		STATEMENT_UN();
}

void Sintactic::STATEMENT()
{
	if(tokenActual_Content() == "int")
	{
		nextToken();
		match(IDENTIFIER);
		DECLARATION();
		match(";");
		STATEMENT();
	}
	else if(tokenActual_Content() == "if")
	{
		SELECCTION_STATEMENT();
		STATEMENT();
	}
	else if(tokenActual_Content() == "for" || tokenActual_Content() == "while" || tokenActual_Content() == "do")
	{
		ITERATION_STATEMENT();
		STATEMENT();
	}
	else if(tokenActual_Content() == "break" || tokenActual_Content() == "return")
	{
		JUMP_STATEMENT();
		STATEMENT();
	}
	else if(tokenActual() == IDENTIFIER)
	{
		nextToken();
		FUNC_OR_ASSIGMENT();
		STATEMENT();		
	}
}

void Sintactic::STATEMENT_UN()
{
	if(tokenActual_Content() == "int")
	{
		nextToken();
		match(IDENTIFIER);
		DECLARATION();
		match(";");
	}
	else if(tokenActual_Content() == "if")
	{
		SELECCTION_STATEMENT();
	}
	else if(tokenActual_Content() == "for" || tokenActual_Content() == "while" || tokenActual_Content() == "do")
	{
		ITERATION_STATEMENT();
	}
	else if(tokenActual_Content() == "break" || tokenActual_Content() == "return")
	{
		JUMP_STATEMENT();
	}
	else if(tokenActual() == IDENTIFIER)
	{
		nextToken();
		FUNC_OR_ASSIGMENT();
	}
	else // EXTRA
	{
		ERROR("SINTAX");
	}
}

void Sintactic::SELECCTION_STATEMENT()
{
	if(tokenActual_Content() == "if")
	{
		nextToken();
		match("(");
		EXPRESSION();
		match(")");
		COMPOUND_STATEMENT();
		SELECCTION_STATEMENT_P();
	}
	else // EXTRA
	{
		ERROR("SINTAX");
	}
}

void Sintactic::SELECCTION_STATEMENT_P()
{
	if(tokenActual_Content() == "else")
	{
		nextToken();
		COMPOUND_STATEMENT();
	}
}

void Sintactic::ITERATION_STATEMENT()
{
	if(tokenActual_Content() == "while")
	{
		nextToken();
		match("(");
		EXPRESSION();
		match(")");
		COMPOUND_STATEMENT();
	}
	else if(tokenActual_Content() == "do")
	{
		nextToken();
		COMPOUND_STATEMENT();
		match("while");
		match("(");
		EXPRESSION();
		match(")");
		match(";");
	}
	else if(tokenActual_Content() == "for")
	{
		nextToken();
		match("(");

        if (tokenActual_Content() == ";") {
            nextToken();
        }
        else {
            EXPRESSION();
            match(";");
        }

        if (tokenActual_Content() == ";") {
            nextToken();
        }
        else {
            EXPRESSION();
            match(";");
        }

        if (tokenActual_Content() != ")")
            EXPRESSION();

		match(")");
		COMPOUND_STATEMENT();
	}
	else
		ERROR("SINTAX");
}

void Sintactic::JUMP_STATEMENT()
{
	if(tokenActual_Content() == "break")
	{
		nextToken();
		match(";");
	}
	else if(tokenActual_Content() == "return")
	{
		nextToken();
		if(tokenActual_Content() == "(")
		{
			nextToken();
			EXPRESSION();
			match(")");
			match(";");
		}
		else
		{
			EXPRESSION();
			match(";");
		}
	}
}

int Sintactic::tokenActual() const
{
	Token temp = tokensList_[tokenActual_];
	return temp.getType();
}

const std::string Sintactic::tokenActual_Content()
{
	Token temp = tokensList_[tokenActual_];
	return temp.getContent();
}

void Sintactic::nextToken()
{
	tokenActual_ ++;
}

void Sintactic::match(const std::string strValue)
{
	if(tokenActual_ >= tokensList_.size())
		ERROR("SINTAX");

	if(tokenActual_Content() == strValue)
		nextToken();
	else
	{
		std::cout << "ERROR (comprueba) Entrada: " << tokenActual_Content() << " -- Necesario: " << strValue << std::endl;
		std::cout << "Contador: " << tokenActual_ << std::endl;
		exit(0);
	}
}

void Sintactic::match(const int tokenType)
{
	if(tokenActual_ >= tokensList_.size())
		ERROR("SINTAX");

	if(tokenActual() == tokenType)
		nextToken();
	else
		ERROR(tokenType);
}

void Sintactic::matchEOF()
{
	if(tokenActual_ == tokensList_.size())
    {
		std::cout << "Archivo aceptado sitacticamente." << std::endl << std::endl;
    }
	else
    {
		std::cout << "Archivo NO aceptado sitacticamente. Ultimo token analizado: " << tokenActual_ << std::endl << std::endl;
        exit(0);
    }
}

void Sintactic::ERROR(const std::string TKN_ERROR)
{    
	if(TKN_ERROR != "SINTAX")
		std::cerr << "ERROR. Token requerido: " << TKN_ERROR << " -- Token recibido: " << tokenActual_Content() << "\nContador: " << tokenActual_ << std::endl << std::endl;
	else
		std::cerr << "ERROR de sintaxis en el archivo, en el token: " << tokenActual_ << std::endl << std::endl;

	exit(0);
}

void Sintactic::ERROR(const int TKN_ERROR)
{    
	std::cerr << "ERROR. Token requerido: " << getTokenType(TKN_ERROR) << " -- Token recibido: " << getTokenType(tokenActual()) << "\nContador: " << tokenActual_ << std::endl << std::endl;
	exit(0);
}

std::string Sintactic::getTokenType(const int tkn)
{
	std::string res = "";

	if(tkn == IDENTIFIER)
		res = "IDENTIFIER";
	else if(tkn == CONSTANT)
		res = "CONSTANT";
	else if(tkn == PLUS_OPERATOR)
		res = "PLUS_OPERATOR";
	else if(tkn == MINUS_OPERATOR)
		res = "MINUS_OPERATOR";
	else if(tkn == MULTTIPLICATION_OPERATOR)
		res = "MULTTIPLICATION_OPERATOR";
	else if(tkn == DIVISION_OPERATOR)
		res = "DIVISION_OPERATOR";
	else if(tkn == MOD_OPERATOR)
		res = "MOD_OPERATOR";
	else if(tkn == LESS_THAN_OPERATOR)
		res = "LESS_THAN_OPERATOR";
	else if(tkn == GREATER_THAN_OPERATOR)
		res = "GREATER_THAN_OPERATOR";
	else if(tkn == ASSIGMENT_OPERATOR)
		res = "ASSIGMENT_OPERATOR";
	else if(tkn == PARENTH_OPEN)
		res = "PARENTH_OPEN";
	else if(tkn == PARENTH_CLOSE)
		res = "PARENTH_CLOSE";
	else if(tkn == KEY_OPEN)
		res = "KEY_OPEN";
	else if(tkn == KEY_CLOSE)
		res = "KEY_CLOSE";
	else if(tkn == COMA)
		res = "COMA";
	else if(tkn == NEGATION)
		res = "NEGATION";
	else if(tkn == SPACE)
		res = "SPACE";
	else if(tkn == NEW_LINE)
		res = "NEW_LINE";
	else if(tkn == TAB)
		res = "TAB";
	else if(tkn == SEMICOLON)
		res = "SEMICOLON";
	else if(tkn == BLOCK_COMMENT)
		res = "BLOCK_COMMENT";
	else if(tkn == COMMENT)
		res = "COMMENT";
	else if(tkn == LESS_THAN_OR_EQUAL_OPERATOR)
		res = "LESS_THAN_OR_EQUAL_OPERATOR";
	else if(tkn == GREATER_THAN_OR_EQUAL_OPERATOR)
		res = "GREATER_THAN_OR_EQUAL_OPERATOR";
	else if(tkn == EQUAL_OPERATOR)
		res = "EQUAL_OPERATOR";
	else if(tkn == NOT_EQUAL_OPERATOR)
		res = "NOT_EQUAL_OPERATOR";
	else if(tkn == RESERVED_WORD)
		res = "RESERVED_WORD";

	return res;
}
