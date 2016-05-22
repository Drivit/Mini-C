#ifndef SINTAX_H
#define SINTAX_H

#include <map>
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>

class Node
{
public:

    int semanticType_;
    std::string content_;

    virtual void deleteNode() {}
    virtual void calculateType() {}
    virtual void display(std::fstream & file);
};

class Type : public Node
{
public:

    Type(const std::string content);
    void display(std::fstream & file);
};

class Expression : public Node
{
public:
    Node * prevExpression_;
    Node * nextExpression_;
};

class Identifier : public Expression
{
public:

    void calculateType();
    void display(std::fstream & file);
    Identifier(const std::string content);
};

class Constant : public Expression
{
public:

    void calculateType();
    void display(std::fstream & file);
    Constant(const std::string content);
};

class Assigment : public Expression
{
public:

    Node * id_;

    void deleteNode(){}
    void calculateType();
    void display(std::fstream & file);
    Assigment(Node * id, Node * nextExpression);
};

class Aritmetic : public Expression
{
public:

    void deleteNode(){}
    void calculateType();
    void display(std::fstream & file);
    Aritmetic(const std::string oprtSimbol, Node  * prevExpression, Node * nextExpression);
};

class Equality : public Expression
{
public:

    void deleteNode(){}
    void calculateType();
    void display(std::fstream & file);
    Equality(const std::string oprtSimbol, Node * prevExpression, Node * nextExpression);
};

class Relational : public Expression
{
public:

    void deleteNode(){}
    void calculateType();
    void display(std::fstream & file);
    Relational(const std::string oprtSimbol, Node * prevExpression, Node * nextExpression);
};

class VarList : public Node
{
public:

    std::vector<Node *> list_;

    void deleteNode(){}
    void calculateType(unsigned int listSize);
    void display(std::fstream & file);
    VarList(std::vector<Node *> list);
};

class ParamList : public Node
{
public:

    std::vector<std::pair<Type *, Identifier *> > list_;

    void deleteNode(){}
    void display(std::fstream & file);
    ParamList(std::vector<std::pair<Type *, Identifier *> > list);
};

class Statement : public Node
{
public:
    Node * nextStatement_;
};

class FuncDefinition : public Statement
{
public:

    Node * type_;
    Node * name_;
    Node * statement_;
    ParamList * params_;

    void deleteNode(){}
    void calculateType();
    void display(std::fstream & file);
    FuncDefinition(Node * type, Node * name, ParamList * params, Node * statement_);
};

class FuncDeclaration : public Statement
{
public:

    Node * type_;
    Node * name_;
    ParamList * params_;

    void deleteNode(){}
    void display(std::fstream & file);
    FuncDeclaration(Node * type, Node * name, ParamList * params);
};

class FuncCall : public Statement
{
public:

    Node * name_;
    VarList * params_;

    void deleteNode(){}
    void display(std::fstream & file);
    FuncCall(Node * name, VarList * params);
};

class Assigment_Statement : public Statement
{
public:

    Node * id_;
    Node * expression_;

    void deleteNode(){}
    void display(std::fstream & file);
    Assigment_Statement(Node * id, Node * expression);
};

class VarDeclaration : public Statement
{
public:

    Type * type_;
    VarList * list_;

    void deleteNode(){}
    void display(std::fstream & file);
    VarDeclaration(Type * type, VarList * list);
};

class GlobalDeclaration : public Statement
{
public:

    Type * type_;
    VarList * list_;

    void deleteNode(){}
    void display(std::fstream & file);
    GlobalDeclaration(Type * type, VarList * list);
};

class Selection : public Statement
{
public:

    Node * exp_;
    Node * statement_;
    Node * elseStatement_;

    void deleteNode(){}
    void display(std::fstream & file);
    Selection(std::string function, Node *exp, Node * statement, Node * elseStatement);
};

class Iteration : public Statement
{
public:

    Node * expr1_;
    Node * expr2_;
    Node * expr3_;

    Node * statement_;

    void deleteNode(){}
    void display(std::fstream & file);
    Iteration(std::string type, Node * expr1, Node * expr2, Node * expr3, Node * statement);
};

class Jump : public Statement
{
public:

    Node * exp_;

    void deleteNode(){}
    void display(std::fstream & file);
    Jump(std::string function, Node * exp);
};

class SemanticObjetc
{
public:
    int objType;
    int dataType;
    std::string scope;
    unsigned int parameterListSize;

    SemanticObjetc() {}
};

void semanticERROR(const std::string message);

bool existInThisContext(std::string context);
std::map<std::string, SemanticObjetc>::iterator findIdentifier(std::string identifier);
#endif
