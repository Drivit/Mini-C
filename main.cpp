#include "lexical.h"
#include "syntactic.h"
#include "tree.h"

int main(int argc, char * args[])
{
	std::string file_name = "";
    file_name = argc == 2 ? args[1] : "entrada.txt";

    Lexic lex(file_name);

    lex.showTokens();

    Sintactic sintactic(lex.getTokensList());

    sintactic.analize();
    Tree tree(lex.getTokensList());
    tree.showTree();
	
	return 0;
}
