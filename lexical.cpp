#include "lexical.h"

enum {
    Q0,
    Q1,
    Q2,
    Q3,
    Q4,
    Q5,
    Q6,
    Q7,
    Q8,
    Q9,
    Q10,
    Q11,
    Q12,
    Q13,
    Q14,
    Q15,
    Q16,
    Q17,
    Q18,
    Q19,
    Q20,
    Q21,
    Q22,
    Q23,
    Q24,
    Q25
};

int transitions[27][21] = {
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q1,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4, Q18, Q17,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q19, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q20, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q21, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q22, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    {Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17, Q17,  Q17, Q0, Q17, Q17, Q17},
    {Q18, Q18, Q18, Q18, Q23, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18, Q18},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9,  Q0, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9,  Q0, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9,  Q0, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9,  Q0, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q24, Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0}, 
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0},
    { Q1,  Q2,  Q3,  Q4,  Q5,  Q6,  Q7,  Q8,  Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,  Q0,  Q0,  Q0, Q25,  Q0}
};

int outputs[27][21] = {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19},
    {-1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { 1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
    { 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3},
    { 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4},
    { 5,  5,  5,  5, -1, -1,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5},
    { 6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6},
    { 7,  7,  7,  7,  7,  7,  7,  7,  7, -1,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7},
    { 8,  8,  8,  8,  8,  8,  8,  8,  8, -1,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8},
    { 9,  9,  9,  9,  9,  9,  9,  9,  9, -1,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9},
    {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
    {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12},
    {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
    {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14},
    {15, 15, 15, 15, 15, 15, 15, 15, 15, -1, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 18, 22},
    {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 19, 23},
    {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 20, 24},
    {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20},
    {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19}
};

void Lexic::loadReservedWords()
{
    reserved_.push_back("auto");
    reserved_.push_back("double");
    reserved_.push_back("const");
    reserved_.push_back("float");
    reserved_.push_back("int");
    reserved_.push_back("short");
    reserved_.push_back("struct");
    reserved_.push_back("unsigned");
    reserved_.push_back("break");
    reserved_.push_back("continue");
    reserved_.push_back("else");
    reserved_.push_back("for");
    reserved_.push_back("long");
    reserved_.push_back("signed");
    reserved_.push_back("switch");
    reserved_.push_back("void");
    reserved_.push_back("case");
    reserved_.push_back("default");
    reserved_.push_back("enum");
    reserved_.push_back("goto");
    reserved_.push_back("register");
    reserved_.push_back("sizeof");
    reserved_.push_back("typedef");
    reserved_.push_back("volatile");
    reserved_.push_back("char");
    reserved_.push_back("do");
    reserved_.push_back("extern");
    reserved_.push_back("if");
    reserved_.push_back("return");
    reserved_.push_back("static");
    reserved_.push_back("union");
    reserved_.push_back("while");
}

Lexic::Lexic(std::string file)
{
    loadReservedWords();
    std::fstream inFile(file.c_str(), std::ios::in);
    int outType = -1, type = -1, state = -1;
    std::string buffer = "";
    char caracter = 0;
    state = Q0;

    if(inFile.is_open())
    {
        while(!inFile.eof())
        {
            inFile.read(&caracter, sizeof(caracter));
            buffer += caracter;

            if(inFile.eof())
            {
                buffer.erase(buffer.size() - 1);
                break;
            }
        }
    }
    else
        std::cerr << "Error al abrir el archivo" << std::endl;

    inFile.close();
    Token temp;

    for (unsigned int i = 0; i <= buffer.size(); ++i)
    {
        type = returnType(buffer[i]);

        if(type != -1)
        {
            outType = outputs[state][type];
            state = transitions[state][type];

            if(outType != -1)
            {
                temp.setType(outType);
                if(temp.getType() != 20 && temp.getType() != 21)
                    tokensList_.push_back(temp);

                temp.setType(-1);
                temp.setContent("");
            }
            
            if(buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n')
                temp.addContent(buffer[i]);
        }
        else
        {
            std::cerr << "ERROR. Existe un token no valido." << std::endl << std:: endl;
            exit(0);
        }
    }

    setReservedType();
    createSymbolsTable();
}

int Lexic::returnType(char caracter)
{
    int type = -1;
    // type = -1: Error        -> Error
    // type =  0: A - Z, a - z -> E1
    // type =  1: 0 - 9        -> E2
    // type =  2: +            -> E3
    // type =  3: -            -> E4
    // type =  4: *            -> E5
    // type =  5: /            -> E6
    // type =  6: %            -> E7
    // type =  7: <            -> E8
    // type =  8: >            -> E9
    // type =  9: =            -> E10
    // type = 10: (            -> E11
    // type = 11: )            -> E12
    // type = 12: {            -> E13
    // type = 13: }            -> E14
    // type = 14: ,            -> E15
    // type = 15: !            -> E16
    // type = 16: \s           -> E17
    // type = 17: \n           -> E18
    // type = 18: \t           -> E19
    // type = 19: ;            -> E20

    if((caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z') || caracter == '_')
        type = 0;
    else if(caracter >= '0' && caracter <= '9')
        type = 1;
    else if(caracter == '+')
        type = 2;
    else if(caracter == '-')
        type = 3;
    else if(caracter == '*')
        type = 4;
    else if(caracter == '/')
        type = 5;
    else if(caracter == '%')
        type = 6;
    else if(caracter == '<')
        type = 7;
    else if(caracter == '>')
        type = 8;
    else if(caracter == '=')
        type = 9;
    else if(caracter == '(')
        type = 10;
    else if(caracter == ')')
        type = 11;
    else if(caracter == '{')
        type = 12;
    else if(caracter == '}')
        type = 13;
    else if(caracter == ',')
        type = 14;
    else if(caracter == '!')
        type = 15;
    else if(caracter == ' ')
        type = 16;
    else if(caracter == '\n')
        type = 17;
    else if(caracter == '\t')
        type = 18;
    else if(caracter == ';')
        type = 19;
    else if(caracter == '\0')
        type = 20;

    return type;
}

std::string Lexic::getTypeName(int type)
{
    std::string name = "";

    if(type == -1)
        name = "ERROR";
    else if(type == 0)
        name = "IDENTIFIER";
    else if(type == 1)
        name = "CONSTANT";
    else if(type == 2)
        name = "PLUS_OPERATOR";
    else if(type == 3)
        name = "MINUS_OPERATOR";
    else if(type == 4)
        name = "MULTTIPLICATION_OPERATOR";
    else if(type == 5)
        name = "DIVISION_OPERATOR";
    else if(type == 6)
        name = "MOD_OPERATOR";
    else if(type == 7)
        name = "LESS_THAN_OPERATOR";
    else if(type == 8)
        name = "GREATER_THAN_OPERATOR";
    else if(type == 9)
        name = "ASSIGMENT_OPERATOR";
    else if(type == 10)
        name = "PARENTH_OPEN";
    else if(type == 11)
        name = "PARENTH_CLOSE";
    else if(type == 12)
        name = "KEY_OPEN";
    else if(type == 13)
        name = "KEY_CLOSE";
    else if(type == 14)
        name = "COMA";
    else if(type == 15)
        name = "NEGATION";
    else if(type == 16)
        name = "SPACE";
    else if(type == 17)
        name = "NEW_LINE";
    else if(type == 18)
        name = "TAB";
    else if(type == 19)
        name = "SEMICOLON";
    else if(type == 20)
        name = "BLOCK_COMMENT";
    else if(type == 21)
        name = "COMMENT";
    else if(type == 22)
        name = "LESS_THAN_OR_EQUAL_OPERATOR";
    else if(type == 23)
        name = "GREATER_THAN_OR_EQUAL_OPERATOR";
    else if(type == 24)
        name = "EQUAL_OPERATOR";
    else if(type == 25)
        name = "NOT_EQUAL_OPERATOR";
    else if(type == 26)
        name = "RESERVED_WORD";

    return name;
}

void Lexic::setReservedType()
{
    std::fstream outFile("salida.txt", std::ios::out);

    if(outFile.is_open())
    {   
        for(unsigned int i = 0; i < tokensList_.size(); i++)
        {
            outFile << tokensList_[i].getType() << std::endl;
            if(tokensList_[i].getType() == 0)
            {
                for(unsigned int x = 0; x < reserved_.size(); x++)
                {
                    if(reserved_[x] == tokensList_[i].getContent())
                        tokensList_[i].setType(26);
                }
            }
        }
    }
    outFile.close();
}

void Lexic::createSymbolsTable()
{
    for (unsigned int i = 0; i < tokensList_.size(); i++)
    {
        if(tokensList_[i].getType() == 0)
        {
            if(symbolsList_.size() != 0)
            {
                bool exist = false;
                for (unsigned int j = 0; j < symbolsList_.size(); j++)
                {
                    if(symbolsList_[j] == tokensList_[i].getContent())
                        exist = true;
                }

                if(!exist)
                    symbolsList_.push_back(tokensList_[i].getContent());
            }
            else
                symbolsList_.push_back(tokensList_[i].getContent());
        }
    }
}

void Lexic::showSymbols()
{
    if(!symbolsList_.empty())
    {
        std::cout << "\n\nTabla de simbolos" << std::endl << std::endl;
        for(unsigned int i = 0; i < symbolsList_.size(); i++)
            if(i != symbolsList_.size() - 1)
                std::cout << symbolsList_[i] << std::endl;
            else
                std::cout << symbolsList_[i] << std::endl << std::endl;
    }
    else
        std::cerr << "No hay simbolos" << std::endl;
}

void Lexic::showTokens()
{
    for(unsigned int i = 0; i < tokensList_.size(); i++)
        if(i != tokensList_.size() - 1)
            std::cout << i << ": " << getTypeName(tokensList_[i].getType()) << " -> " << tokensList_[i].getContent() << std::endl;
        else
            std::cout << i << ": " << getTypeName(tokensList_[i].getType()) << " -> " << tokensList_[i].getContent() << std::endl << std::endl;
}

std::vector<Token> Lexic::getTokensList()
{
    return tokensList_;
}

std::vector<std::string> Lexic::getSymbolsList()
{
    return symbolsList_;
}
