#ifndef LEXICO_H
#define LEXICO_H

#include <fstream>
#include <vector>

#include "token.h"

class Lexic
{
    public:
        Lexic(std::string file);
        std::vector<Token> getTokensList();
        std::vector<std::string> getSymbolsList();
        void showSymbols();
        void showTokens();
        
    private:
        std::vector<Token> tokensList_;
        std::vector<std::string> symbolsList_;
        std::vector<std::string> reserved_;

        int returnType(const char caracter);
        std::string getTypeName(const int type);
        void setReservedType();
        void createSymbolsTable();
        void loadReservedWords();
};

#endif //LEXICO_H
