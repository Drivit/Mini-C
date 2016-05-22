#ifndef SINTACTICO_H
#define SINTACTICO_H

#include <fstream>
#include <vector>

#include "token.h"

class Sintactic
{
    private:
       
        std::vector<Token> tokensList_;

        void TRANSLATION_UNIT();
        void TRANSLATION_UNIT_P();
        void TRANSLATION_UNIT_OP();
        void DECLARATOR();
        void DECLARATION();
        void TYPE_OPERAND();
        void PARAMETER_LIST();
        void PARAMETER_LIST_P();
        void FUNC_CALL();
        void FUNC_PARAMS();
        void FUNC_PARAMS_P();
        void FUNC_OR_ASSIGMENT();
        void RELATIONAL_EXPRESSION();
        void ADDITIVE_EXPRESSION();
        void MULTIPLICATIVE_EXPRESSION();
        void EXPRESSION();
        void FACTOR();
        void ASSIGMENT_EXPRESSION();
        void COMPOUND_STATEMENT();
        void STATEMENT();
        void STATEMENT_UN();
        void SELECCTION_STATEMENT();
        void SELECCTION_STATEMENT_P();
        void ITERATION_STATEMENT();
        void JUMP_STATEMENT();

        std::string getTokenType(const int tkn);
        void match(const std::string strValue);
        void match(const int strTokenType);
        void matchEOF();

        void ERROR(const int TKN_ERROR);
        void ERROR(const std::string TKN_ERROR);

        int tokenActual() const ;
        const std::string tokenActual_Content();

        void nextToken();
        unsigned int tokenActual_;
    
    public:
        Sintactic(std::vector<Token> tokens);
        void analize();
};

#endif //SINTACTICO_H
