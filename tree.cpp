#include "tree.h"

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


Tree::Tree(std::vector<Token> tokens)
{
    root_ = NULL;
	tokenActual_ = 0;
    tokensList_ = tokens;

    root_ = TRANSLATION_UNIT();
    matchEOF();
}

Tree::~Tree()
{

}

Statement *Tree::TRANSLATION_UNIT()
{
    Type * type = NULL;
    Statement * aux = NULL;
	Identifier * id = NULL;

	if(tokenActual_ < tokensList_.size())
	{
		if(tokenActual_Content() == "int" || tokenActual_Content() == "void")
		{
			type = new Type(tokenActual_Content());
            nextToken();
			id = new Identifier(tokenActual_Content());
            match(IDENTIFIER);
			aux = TRANSLATION_UNIT_P(type, id);
		}
		else if(tokenActual_Content() == "\0")
            nextToken();
	}

	return aux;
}

Statement *Tree::TRANSLATION_UNIT_P(Type * type, Identifier * id)
{
    VarList * temp = NULL;
    ParamList * list = NULL;
    Statement * aux = NULL;

    if(tokenActual_Content() == "(")
    {
        nextToken();
        list = PARAMETER_LIST();
        match(")");

        aux = TRANSLATION_UNIT_OP(type, id, list);
    }
    else
    {
        temp = DECLARATOR(id);
        aux = new GlobalDeclaration(type, temp);
        match(";");
        aux->nextStatement_ = TRANSLATION_UNIT();
    }

    return aux;
}

Statement *Tree::TRANSLATION_UNIT_OP(Type *type, Identifier *id, ParamList *params)
{
    Statement * aux = NULL;
    Node * statement = NULL;

	if(tokenActual_Content() == ";")
	{
        nextToken();
        aux = new FuncDeclaration(type, id, params);
        aux->nextStatement_ = TRANSLATION_UNIT();
	}
	else
	{
        match("{");
        statement = STATEMENT();
        match("}");

        aux = new FuncDefinition(type, id, params, statement);
        aux->nextStatement_ = TRANSLATION_UNIT();
	}
	return aux;
}

VarList *Tree::DECLARATOR(Node *id)
{
    VarList * aux = NULL;
    Node * tempNode = NULL;

    std::vector<Node *> list;

    tempNode = INIT(id);
    list.push_back(tempNode);

    while(tokenActual() == COMA)
    {
        nextToken();
        tempNode = new Identifier(tokenActual_Content());
        match(IDENTIFIER);
        tempNode = INIT(tempNode);

        list.push_back(tempNode);
    }

    aux = new VarList(list);

    return aux;
}

Node * Tree::TYPE_OPERAND()
{
	Node * aux = NULL;

	if(tokenActual() == CONSTANT)
	{
		aux = new Constant(tokenActual_Content());
        nextToken();
	}
	else
	{
		aux = new Identifier(tokenActual_Content());
        match(IDENTIFIER);
	}

    return aux;
}

Node *Tree::INIT(Node *id)
{
    Node * aux = NULL;

    if(tokenActual() == ASSIGMENT_OPERATOR)
    {
        nextToken();
        Node * exp = EXPRESSION();
        aux = new Assigment(id, exp);
    }
    else
    {
        aux = id;
    }

    return aux;
}

ParamList *Tree::PARAMETER_LIST()
{
    ParamList * aux = NULL;
	Type * type = NULL;
    Identifier * id = NULL;

    std::vector<std::pair<Type *, Identifier *> > params;

    type = new Type(tokenActual_Content());
    if(tokenActual_Content() == "int")
    {
        nextToken();
        id = new Identifier(tokenActual_Content());
        match(IDENTIFIER);

        params.push_back(std::make_pair(type, id));

        while(tokenActual() == COMA)
        {
            nextToken();
            type = new Type("int");
            match("int");
            id = new Identifier(tokenActual_Content());
            match(IDENTIFIER);

            params.push_back(std::make_pair(type, id));
        }

        aux = new ParamList(params);
    }

	return aux;
}

Statement * Tree::FUNC_CALL(Node * id)
{
    Statement * aux = NULL;
    VarList * params = NULL;

    match("(");

    if (tokenActual() != PARENTH_CLOSE)
        params = FUNC_PARAMS();

    match(")");

    aux = new FuncCall(id, params);

	return aux;
}

Statement *Tree::FUNC_OR_ASSIGMENT(Node *id)
{
    Statement * aux = NULL;

	if(tokenActual_Content() == "(")
		aux = FUNC_CALL(id);
	else
        aux = ASSIGMENT_STATEMENT(id);

	return aux;
}

VarList *Tree::FUNC_PARAMS()
{
    VarList * aux = NULL;
    Node * tempNode = NULL;

    std::vector<Node *> list;

    tempNode = EXPRESSION();

    list.push_back(tempNode);

    while(tokenActual() == COMA)
    {
        nextToken();

        tempNode = EXPRESSION();

        list.push_back(tempNode);
    }

    aux = new VarList(list);

	return aux;
}

Node * Tree::RELATIONAL_EXPRESSION()
{
	Node * aux = NULL;
	std::string tempSimbol = "";

    aux = ADDITIVE_EXPRESSION();

    while(tokenActual() == LESS_THAN_OPERATOR ||
          tokenActual() == GREATER_THAN_OPERATOR ||
          tokenActual() == LESS_THAN_OR_EQUAL_OPERATOR ||
          tokenActual() == GREATER_THAN_OR_EQUAL_OPERATOR)
	{
		tempSimbol = tokenActual_Content();
        nextToken();
        aux = new Relational(tempSimbol, aux, ADDITIVE_EXPRESSION()); // TODO: CHECK
	}

	return aux;
}

Node * Tree::ADDITIVE_EXPRESSION()
{
	Node * aux = NULL;
	std::string tempSimbol = "";

    aux = MULTIPLICATIVE_EXPRESSION();

    while(tokenActual() == PLUS_OPERATOR || tokenActual() == MINUS_OPERATOR)
	{
		tempSimbol = tokenActual_Content();
        nextToken();
        aux = new Aritmetic(tempSimbol, aux, MULTIPLICATIVE_EXPRESSION()); // TODO: CHECK
    }

	return aux;
}

Node * Tree::MULTIPLICATIVE_EXPRESSION()
{
    Node * aux = NULL;
	std::string tempSimbol = "";

    aux = FACTOR();

    while(tokenActual() == MULTTIPLICATION_OPERATOR || tokenActual() == DIVISION_OPERATOR || tokenActual() == MOD_OPERATOR)
	{
		tempSimbol = tokenActual_Content();
        nextToken();
        aux = new Aritmetic(tempSimbol, aux, FACTOR());
	}

    return aux;
}

Node *Tree::FACTOR()
{
    Node * aux = NULL;

    if(tokenActual() == IDENTIFIER)
    {
        aux = new Identifier(tokenActual_Content());
        nextToken();

        if(tokenActual() == ASSIGMENT_OPERATOR)
            aux = ASSIGMENT_EXPRESSION(aux);
        else if (tokenActual() == PARENTH_OPEN)
            aux = FUNC_CALL(aux);
    }
    else if(tokenActual() == CONSTANT)
    {
        aux = new Constant(tokenActual_Content());
        nextToken();
    }
    else if(tokenActual() == PARENTH_OPEN)
    {
        nextToken();
        aux = EXPRESSION();
        match(PARENTH_CLOSE);
    }

    return aux;
}

Node * Tree::EXPRESSION()
{
	Node * aux = NULL;
    std::string tempSimbol = "";

    aux = RELATIONAL_EXPRESSION();

    while(tokenActual() == EQUAL_OPERATOR || tokenActual() == NOT_EQUAL_OPERATOR)
    {
        tempSimbol = tokenActual_Content();
        nextToken();
        aux = new Equality(tempSimbol, aux, RELATIONAL_EXPRESSION());
    }

	return aux;
}

Node * Tree::ASSIGMENT_EXPRESSION(Node * id)
{
	Node * aux = NULL;

    match(ASSIGMENT_OPERATOR);
    aux = new Assigment(id, EXPRESSION());

    return aux;
}

Statement *Tree::ASSIGMENT_STATEMENT(Node *id)
{
    Statement * aux = NULL;
    Node * exp = NULL;

    match(ASSIGMENT_OPERATOR);
    exp = EXPRESSION();
    aux = new Assigment_Statement(id, exp);

    return aux;
}

Statement *Tree::COMPOUND_STATEMENT()
{
    Statement * aux = NULL;

    if(tokenActual() == KEY_OPEN)
    {
        nextToken();
        aux = STATEMENT();
        match(KEY_CLOSE);
    }
    else
        aux = STATEMENT_UN();

	return aux;
}

Statement *Tree::STATEMENT()
{
    Statement * aux = NULL;
    VarList * varlist = NULL;
	Type * type = NULL;
    Identifier * id = NULL;

	if(tokenActual_Content() == "int")
	{
		type = new Type("int");
        nextToken();
		id = new Identifier(tokenActual_Content());
        match(IDENTIFIER);
        varlist = DECLARATOR(id);
        match(";");

        aux = new VarDeclaration(type, varlist);
        aux->nextStatement_ = STATEMENT();
	}
    else if(tokenActual_Content() == "if")
	{
        aux = SELECCTION_STATEMENT();
        aux->nextStatement_ = STATEMENT();
    }
    else if(tokenActual_Content() == "for" || tokenActual_Content() == "while" || tokenActual_Content() == "do")
	{
		aux = ITERATION_STATEMENT();
        aux->nextStatement_ = STATEMENT();
	}
	else if(tokenActual_Content() == "break" || tokenActual_Content() == "return")
	{
		aux = JUMP_STATEMENT();
        aux->nextStatement_ = STATEMENT();
    }
	else if(tokenActual() == IDENTIFIER)
	{
        id = new Identifier(tokenActual_Content());
        nextToken();

        aux = FUNC_OR_ASSIGMENT(id);
        match(SEMICOLON);
        aux->nextStatement_ = STATEMENT();
    }

	return aux;
}

Statement *Tree::STATEMENT_UN()
{
    Statement * aux = NULL;
    VarList * temp = NULL;
    Type * type = NULL;
    Identifier * id = NULL;

    if(tokenActual_Content() == "int")
    {
        type = new Type("int");
        nextToken();
        id = new Identifier(tokenActual_Content());
        match(IDENTIFIER);
        temp = DECLARATOR(id);
        match(";");

        aux = new VarDeclaration(type, temp);
        aux->nextStatement_ = NULL;
    }
    else if(tokenActual_Content() == "if")
    {
        aux = SELECCTION_STATEMENT();
        aux->nextStatement_ = NULL;
    }
    else if(tokenActual_Content() == "for" || tokenActual_Content() == "while" || tokenActual_Content() == "do")
    {
        aux = ITERATION_STATEMENT();
        aux->nextStatement_ = NULL;
    }
    else if(tokenActual_Content() == "break" || tokenActual_Content() == "return")
    {
        aux = JUMP_STATEMENT();
        aux->nextStatement_ = NULL;
    }
    else if(tokenActual() == IDENTIFIER)
    {
        id = new Identifier(tokenActual_Content());
        nextToken();

        aux = FUNC_OR_ASSIGMENT(id);
        match(SEMICOLON);
        aux->nextStatement_ = NULL;
    }
    else
    {
        ERROR("SINTAX");
    }

    return aux;
}

Statement *Tree::SELECCTION_STATEMENT()
{
    Statement * aux = NULL;
    Node * exp = NULL;
    std::string strTemp = "";

    if(tokenActual_Content() == "if")
    {
        strTemp = tokenActual_Content();
        nextToken();
        match("(");
        exp = EXPRESSION();
        match(")");
        aux = new Selection(strTemp, exp, COMPOUND_STATEMENT(), SELECCTION_STATEMENT_P());
    }
    else
    {
        ERROR("SINTAX");
    }

	return aux;
}

Statement * Tree::SELECCTION_STATEMENT_P()
{
    Statement * aux = NULL;
    std::string strTemp = "";

    if(tokenActual_Content() == "else")
    {
        strTemp = tokenActual_Content();
        nextToken();
        aux = new Selection(strTemp, NULL, COMPOUND_STATEMENT(), NULL);
    }

	return aux;
}

Statement * Tree::ITERATION_STATEMENT()
{
    Statement * aux = NULL;
    Node * exp1 = NULL;
    Node * exp2 = NULL;
    Node * exp3 = NULL;
    Node * compound = NULL;
    std::string function = "";

    if(tokenActual_Content() == "while")
    {
        function = tokenActual_Content();
        nextToken();
        match("(");
        exp1 = EXPRESSION();
        match(")");
        aux = new Iteration(function, exp1, NULL, NULL, COMPOUND_STATEMENT());
    }
    else if(tokenActual_Content() == "do")
    {
        function = tokenActual_Content();
        nextToken();
        compound = COMPOUND_STATEMENT();
        match("while");
        match("(");
        exp1 = EXPRESSION();
        match(")");
        match(";");
        aux = new Iteration(function, exp1, NULL, NULL, compound);
    }
    else if(tokenActual_Content() == "for")
    {
        function = tokenActual_Content();
        nextToken();
        match("(");
        exp1 = EXPRESSION();
        match(";");
        exp2 = EXPRESSION();
        match(";");
        exp3 = EXPRESSION();
        match(")");
        compound = COMPOUND_STATEMENT();
        aux = new Iteration(function, exp1, exp2, exp3, compound);
    }
    else
        ERROR("SINTAX");

	return aux;
}

Statement * Tree::JUMP_STATEMENT()
{
    Statement * aux = NULL;
    Node * exp = NULL;
    std::string function = "";

    if(tokenActual_Content() == "break")
    {
        function = tokenActual_Content();
        nextToken();
        match(";");
        aux = new Jump(function, NULL);
    }
    else if(tokenActual_Content() == "return")
    {
        function = tokenActual_Content();
        nextToken();
        if(tokenActual_Content() == "(")
        {
            nextToken();
            exp = EXPRESSION();
            match(")");
        }
        else
        {
            exp = EXPRESSION();
        }
        match(";");

        aux = new Jump(function, exp);
    }

	return aux;
}

void Tree::showTree()
{
    std::fstream outFile("salida.xml", std::ios::out);

    if(!outFile.is_open())
    {
        std::cerr << "Hubo un error al crear archivo del arbol de salida XML" << std::endl;
        exit(0);
    }

    outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    outFile << "<PROGRAM>" << std::endl;
    if(root_)
        root_->display(outFile);
    outFile << "</PROGRAM>" << std::endl;

    outFile.close();
}

void Tree::semanticAnalyze()
{
    if(root_)
        root_->calculateType();
}

int Tree::tokenActual() const
{
	Token temp = tokensList_[tokenActual_];
	return temp.getType();
}

const std::string Tree::tokenActual_Content()
{
	Token temp = tokensList_[tokenActual_];
	return temp.getContent();
}

void Tree::nextToken()
{
	tokenActual_ ++;
}

void Tree::match(const std::string strValue)
{
	if(tokenActual_ < tokensList_.size())
	{
		if(tokenActual_Content() == strValue)
            nextToken();
		else
			ERROR(strValue);
	}
	else
		ERROR(strValue);
}

void Tree::match(const int tokenType)
{
	if(tokenActual_ < tokensList_.size())
	{
		if(tokenActual() == tokenType)
            nextToken();
		else
			ERROR(tokenType);
	}
	else
		ERROR(tokenType);
}

void Tree::matchEOF()
{
	if(tokenActual_ == tokensList_.size())
		std::cout << "Arbol sintactico contruido correctamente." << std::endl << std::endl;
	else
		std::cout << "El arbol no fue contruido por errores de Sintaxis. Ultimo token analizado: " << tokenActual_ << std::endl << std::endl;
}

void Tree::ERROR(const std::string TKN_ERROR)
{    
	if(TKN_ERROR != "SINTAX")
        std::cerr << "[ERROR ARBOL] Token requerido: " << TKN_ERROR << " -- Token recibido: " << tokenActual_Content() << "\nContador: " << tokenActual_ << std::endl << std::endl;
	else
        std::cerr << "[ERROR ARBOL] Sintaxis en el archivo, en el token: " << tokenActual_ << std::endl << std::endl;

	exit(0);
}

void Tree::ERROR(const int TKN_ERROR)
{    
    std::cerr << "[ERROR ARBOL] Token requerido: " << getTokenType(TKN_ERROR) << " -- Token recibido: " << getTokenType(tokenActual()) << "\nContador: " << tokenActual_ << std::endl << std::endl;
	exit(0);
}

std::string Tree::getTokenType(const int tkn)
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
