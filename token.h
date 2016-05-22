#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

class Token
{
    public:
        Token();

        void setContent(std::string content);
        void addContent(char content);
        void setType(int type);
        std::string getContent() const;
        int getType() const;

    private:
        
        int type_;
        std::string content_;
};

#endif //TOKEN_H