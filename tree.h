#ifndef TREE_H
#define TREE_H

#include <vector>
#include <fstream>
#include "token.h"
#include "sintax.h"

class Tree
{
    public:
        Tree(std::vector<Token> tokens);
        void showTree();
        void semanticAnalyze();

        ~Tree();

    private:
        std::vector<Token> tokensList_;

        Statement * root_;

        Statement * TRANSLATION_UNIT();
        Statement * TRANSLATION_UNIT_P(Type * type, Identifier * id);
        Statement * TRANSLATION_UNIT_OP(Type * type, Identifier * id, ParamList *params);
        VarList * DECLARATOR(Node * id);
        Node * TYPE_OPERAND();
        Node * INIT(Node * id);
        ParamList * PARAMETER_LIST();
        Statement * FUNC_CALL(Node * id);
        Statement * FUNC_OR_ASSIGMENT(Node * id);
        VarList * FUNC_PARAMS();
        Node * RELATIONAL_EXPRESSION();
        Node * ADDITIVE_EXPRESSION();
        Node * MULTIPLICATIVE_EXPRESSION();
        Node * FACTOR();
        Node * EXPRESSION();
        Node * ASSIGMENT_EXPRESSION(Node * id);
        Statement * ASSIGMENT_STATEMENT(Node * id);
        Statement * COMPOUND_STATEMENT();
        Statement * STATEMENT();
        Statement * STATEMENT_UN();
        Statement * SELECCTION_STATEMENT();
        Statement * SELECCTION_STATEMENT_P();
        Statement * ITERATION_STATEMENT();
        Statement * JUMP_STATEMENT();


        std::string getTokenType(const int tkn);
        void match(const std::string strValue);
        void match(const int strTokenType);
        void matchEOF();

        void ERROR(const int TKN_ERROR);
        void ERROR(const std::string TKN_ERROR);

        int tokenActual() const;
        const std::string tokenActual_Content();

        void nextToken();
        unsigned int tokenActual_;
};

#endif
