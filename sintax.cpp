#include "sintax.h"

// Enum to SemanticObject::objType
enum{
    FUNCTION,
    PROTO_FUNCTION,
    VAR
};

// Enum to SemanticObject::dataType
enum {
    INTEGER,
    VOID,
    CORRECT
};

// Global commons
int loopCounter = 0;
int labelCounter = 0;
std::vector<std::string> context_(1, "global");
std::map<std::string, SemanticObjetc> symbolTab_;

// -------------------------------------------------

void Node::display(std::fstream & file)
{
    file << this->content_;
}

Type::Type(const std::string content)
{
    this->content_ = content;
}

void Type::display(std::fstream & file)
{
    Node::display(file);
}

Identifier::Identifier(const std::string content)
{
    this->content_ = content;
    this->nextExpression_ = NULL;
    this->prevExpression_ = NULL;
}

void Identifier::calculateType()
{
    std::map<std::string, SemanticObjetc>::iterator iter;

    iter = findIdentifier(this->content_);

    if(iter == symbolTab_.end())
        semanticERROR(this->content_ + " was not declared");

    bool exist = existInThisContext(iter->second.scope);

    if (exist)
        this->semanticType_ = iter->second.dataType;
    else
        semanticERROR(iter->first + " not declared in this scope");
}

void Identifier::display(std::fstream & file)
{
    file << "<IDENTIFIER>";
    Node::display(file);
    file << "</IDENTIFIER>" << std::endl;
}

Constant::Constant(const std::string content)
{
    this->content_ = content;
    this->nextExpression_ = NULL;
    this->prevExpression_ = NULL;
}

void Constant::calculateType()
{
    this->semanticType_ = INTEGER;
}

void Constant::display(std::fstream & file)
{
    file << "<CONSTANT>";
    Node::display(file);
    file << "</CONSTANT>" << std::endl;
}

Assigment::Assigment(Node *id, Node * nextExpression)
{

    this->id_ = id;
    this->prevExpression_ = NULL;
    this->nextExpression_ = nextExpression;
}

void Assigment::calculateType()
{
    std::map<std::string, SemanticObjetc>::iterator iter;

    // Calcutate identifier type
    this->id_->calculateType();

    // Calculate expression type
    this->nextExpression_->calculateType();

    if (this->id_->semanticType_ == VOID || this->nextExpression_->semanticType_ == VOID)
        semanticERROR("Can't use void functions on expressions");

    if(this->nextExpression_->semanticType_ != iter->second.dataType)
        semanticERROR("Can't assign difference data types");

    this->semanticType_ = iter->second.dataType;

    // TODO: Check new conditions
}

void Assigment::display(std::fstream & file)
{
    file << "<ASSIGMENT var=\"" << this->id_->content_ << "\">" << std::endl;
    if(this->nextExpression_)
        this->nextExpression_->display(file);
    file << "</ASSIGMENT>" << std::endl;
}

Aritmetic::Aritmetic(const std::string oprtSimbol, Node *prevExpression, Node * nextExpression)
{
    this->content_ = oprtSimbol;
    this->prevExpression_ = prevExpression;
    this->nextExpression_ = nextExpression;
}

void Aritmetic::calculateType()
{
    this->prevExpression_->calculateType();
    this->nextExpression_->calculateType();

    if(this->prevExpression_->semanticType_ == VOID || this->nextExpression_->semanticType_ == VOID)
        semanticERROR("Functions \"void\" not allowed to use in expressions");

    if(this->prevExpression_->semanticType_ != this->nextExpression_->semanticType_)
        semanticERROR("Different operand types");
    else
        this->semanticType_ = this->prevExpression_->semanticType_;
}

void Aritmetic::display(std::fstream & file)
{
    std::string typeOperation = "";

    if(this->content_ == "+")
        typeOperation = "ADD";
    else if(this->content_ == "-")
        typeOperation = "SUB";
    else if(this->content_ == "*")
        typeOperation = "MUL";
    else if(this->content_ == "/")
        typeOperation = "DIV";
    else if(this->content_ == "%")
         typeOperation = "MOD";

    file << "<" << typeOperation << ">" << std::endl;
    if(this->prevExpression_)
        prevExpression_->display(file);
    if(this->nextExpression_)
        this->nextExpression_->display(file);
    file << "</" << typeOperation << ">" << std::endl;
}

Equality::Equality(const std::string oprtSimbol, Node *prevExpression, Node * nextExpression)
{
    this->content_ = oprtSimbol;
    this->prevExpression_ = prevExpression;
    this->nextExpression_ = nextExpression;
}

void Equality::calculateType()
{
    this->prevExpression_->calculateType();
    this->nextExpression_->calculateType();

    if(this->prevExpression_->semanticType_ == VOID || this->nextExpression_->semanticType_ == VOID)
        semanticERROR("Functions \"void\" not allowed to use in expressions");

    if(this->prevExpression_->semanticType_ != this->nextExpression_->semanticType_)
        semanticERROR("Different operand types");
    else
        this->semanticType_ = this->prevExpression_->semanticType_;
}

void Equality::display(std::fstream & file)
{
    std::string typeOperation = "";

    if(this->content_ == "==")
         typeOperation = "EQUAL";
    else if(this->content_ == "!=")
        typeOperation = "NOT-EQUAL";

    file << "<" << typeOperation << ">" << std::endl;
    if(this->prevExpression_)
        this->prevExpression_->display(file);
    if(this->nextExpression_)
        this->nextExpression_->display(file);
    file << "</" << typeOperation << ">" << std::endl;
}


Relational::Relational(const std::string oprtSimbol, Node *prevExpression, Node *nextExpression)
{
    this->content_ = oprtSimbol;
    this->prevExpression_ = prevExpression;
    this->nextExpression_ = nextExpression;
}

void Relational::calculateType()
{
    this->prevExpression_->calculateType();
    this->nextExpression_->calculateType();

    if(this->prevExpression_->semanticType_ == VOID || this->nextExpression_->semanticType_ == VOID)
        semanticERROR("Functions \"void\" not allowed to use in expressions");

    if(this->prevExpression_->semanticType_ != this->nextExpression_->semanticType_)
        semanticERROR("Different operand types");
    else
        this->semanticType_ = this->prevExpression_->semanticType_;
}

void Relational::display(std::fstream & file)
{
    std::string typeOperation = "";

    if(this->content_ == "<")
        typeOperation = "LESS";
    else if(this->content_ == ">")
        typeOperation = "GREATER";
    else if(this->content_ == "<=")
        typeOperation = "LESS-OR-EQUAL";
    else if(this->content_ == "=>")
        typeOperation = "GREATER-OR-EQUAL";

    file << "<" << typeOperation << ">" << std::endl;
    if(this->prevExpression_)
        this->prevExpression_->display(file);
    if(this->nextExpression_)
        this->nextExpression_->display(file);
    file << "</" << typeOperation << ">" << std::endl;
}

VarList::VarList(std::vector<Node *> list)
{
    this->list_ = list;
}

void VarList::calculateType(unsigned int listSize)
{
    if (this->list_.size() != listSize)
        semanticERROR("Invalid parameters");

    for(unsigned int i = 0; i < this->list_.size(); i++)
    {
        this->list_[i]->calculateType();

        if (this->list_[i]->semanticType_ != INTEGER)
            semanticERROR("Not valid data type");
    }
}

void VarList::display(std::fstream & file)
{
    for(unsigned int i = 0; i < this->list_.size(); i++)
    {
        this->list_[i]->display(file);
    }
}

ParamList::ParamList(std::vector<std::pair<Type *, Identifier *> > list)
{
    this->list_ = list;
}

void ParamList::display(std::fstream & file)
{
    for(unsigned int i = 0; i < this->list_.size(); i++)
    {
        file << "<PARAM type=\""<< this->list_[i].first->content_ << "\">";
        this->list_[i].second->display(file);
        file << "</PARAM>" << std::endl;
    }
}

FuncDefinition::FuncDefinition(Node *type, Node *name, ParamList *params, Node * statement_)
{
    this->type_ = type;
    this->name_ = name;
    this->params_ = params;
    this->statement_ = statement_;
}

void FuncDefinition::calculateType()
{
    std::map<std::string, SemanticObjetc>::iterator iter;

    iter = symbolTab_.find(this->name_->content_);

    // TODO: Finish this

    if(iter != symbolTab_.end())
    {
        if (iter->second.objType == FUNCTION)
            semanticERROR("Funtion previously defined");

        if (iter->second.objType == VAR)
            semanticERROR("Var cannot be use as a function");

        if (iter->second.objType == PROTO_FUNCTION)
        {
            if (iter->second.parameterListSize != ((ParamList* )&this->params_)->list_.size())
            {

            }
        }
    }
    else
    {
        SemanticObjetc tempObj;

        tempObj.dataType = (this->type_->content_ == "int") ? INTEGER : VOID;
        tempObj.objType = FUNCTION;
        tempObj.scope = "global";
        tempObj.parameterListSize = this->params_->list_.size();

        symbolTab_.insert(std::make_pair<std::string, SemanticObjetc>(this->name_->content_, tempObj));
    }
}

void FuncDefinition::display(std::fstream & file)
{
    file << "<FUNC_DEFINITION type=\"" << this->type_->content_ << "\"" <<  " name=\"" << this->name_->content_ << "\">" << std::endl;

    file << "<PARAMS>\n";
    if(this->params_)
        this->params_->display(file);
    file << "</PARAMS>" << std::endl;

    file << "<STATEMENT>" << std::endl;
    if(this->statement_)
        this->statement_->display(file);
    file << "</STATEMENT>" << std::endl;

    file << "</FUNC_DEFINITION>" << std::endl;

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}

FuncDeclaration::FuncDeclaration(Node * type, Node * name, ParamList *params)
{
    this->type_ = type;
    this->name_ = name;
    this->params_ = params;
}

void FuncDeclaration::display(std::fstream & file)
{
    file << "<FUNC_DECLARATION type=\"" << this->type_->content_ << "\"" <<  " name=\"" << this->name_->content_ << "\">" << std::endl;

    file << "<PARAMS>\n";
    if(this->params_)
        this->params_->display(file);
    file << "</PARAMS>" << std::endl;

    file << "</FUNC_DECLARATION>" << std::endl;

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}

FuncCall::FuncCall(Node *name, VarList *params)
{
    this->name_ = name;
    this->params_ = params;
}

void FuncCall::display(std::fstream & file)
{
    file << "<FUNC_CALL name=\"" << this->name_->content_ << "\">" << std::endl;

    file << "<PARAMS>\n";
    if(this->params_)
        this->params_->display(file);
    file << "</PARAMS>" << std::endl;

    file << "</FUNC_CALL>" << std::endl;

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}

Assigment_Statement::Assigment_Statement(Node * id, Node * expression)
{
    this->id_ = id;
    this->expression_ = expression;
}

void Assigment_Statement::display(std::fstream & file)
{
    file << "<ASSIGMENT_STATEMENT var = \"" << this->id_->content_ << "\">" << std::endl;
    this->expression_->display(file);
    file << "</ASSIGMENT_STATEMENT>" << std::endl;

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}

VarDeclaration::VarDeclaration(Type * type, VarList *list)
{
    this->type_ = type;
    this->list_ = list;
}

void VarDeclaration::display(std::fstream & file)
{
    file << "<VAR_DEF type=\"" << this->type_->content_ << "\">" << std::endl;
    this->list_->display(file);
    file << "</VAR_DEF>" << std::endl;

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}

GlobalDeclaration::GlobalDeclaration(Type * type, VarList *list)
{
    this->type_ = type;
    this->list_ = list;
}

void GlobalDeclaration::display(std::fstream & file)
{
    file << "<GLOBAL_DECLARATION type=\"" << this->type_->content_ << "\">" << std::endl;
    this->list_->display(file);
    file << "</GLOBAL_DECLARATION>" << std::endl;

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}

Selection::Selection(std::string function, Node * exp, Node *statement, Node * elseStatement)
{
    this->exp_ = exp;
    this->content_ = function;
    this->statement_ = statement;
    this->elseStatement_ = elseStatement;
}

void Selection::display(std::fstream & file)
{
    if(this->content_ == "if")
    {
        file << "<SELECTION_STATEMENT type=\"if\">" << std::endl;
        //file << "<TYPE>" << "if" << "</TYPE>" << std::endl;
        file << "<EXPRESSION>\n";
        this->exp_->display(file);
        file << "</EXPRESSION>\n";

        if(this->statement_)
        {
            file << "<STATEMENT>\n";
            this->statement_->display(file);
            file << "</STATEMENT>\n";
        }

        if(this->elseStatement_)
            this->elseStatement_->display(file);

        file << "</SELECTION_STATEMENT>" << std::endl;

        if(this->nextStatement_)
            this->nextStatement_->display(file);
    }
    else
    {
        file << "<SELECTION_STATEMENT type=\"else\">" << std::endl;
        if(this->statement_)
        {
            file << "<STATEMENT>\n";
            this->statement_->display(file);
            file << "</STATEMENT>\n";
        }
        file << "</SELECTION_STATEMENT>" << std::endl;
    }
}

Iteration::Iteration(std::string type, Node * expr1, Node * expr2, Node * expr3, Node * statement)
{
    this->content_ = type;
    this->expr1_ = expr1;
    this->expr2_ = expr2;
    this->expr3_ = expr3;
    this->statement_ = statement;
}

void Iteration::display(std::fstream & file)
{
    file << "<ITERATION_STATEMENT type=\"" << this->content_ << "\">" << std::endl;

    if(this->content_ == "for")
    {
        file << "<EXPRESSION_1>\n";
        if(this->expr1_)
            this->expr1_->display(file);
        file << "</EXPRESSION_1>\n";

        file << "<EXPRESSION_2>\n";
        if(this->expr2_)
            this->expr2_->display(file);
        file << "</EXPRESSION_2>\n";

        file << "<EXPRESSION_3>\n";
        if(this->expr3_)
            this->expr3_->display(file);
        file << "</EXPRESSION_3>\n";

        if(this->statement_)
        {
            file << "<STATEMENT>\n";
            this->statement_->display(file);
            file << "</STATEMENT>\n";
        }
    }
    else if(this->content_ == "while")
    {        
        file << "<EXPRESSION>\n";
        if(this->expr1_)
            this->expr1_->display(file);
        file << "</EXPRESSION>\n";

        if(this->statement_)
        {
            file << "<STATEMENT>\n";
            this->statement_->display(file);
            file << "</STATEMENT>\n";
        }
    }
    else if(this->content_ == "do")
    {
        if(this->statement_)
        {
            file << "<STATEMENT>\n";
            this->statement_->display(file);
            file << "</STATEMENT>\n";
        }

        file << "<EXPRESSION>\n";
        if(this->expr1_)
            this->expr1_->display(file);
        file << "</EXPRESSION>\n";
    }

    file << "</ITERATION_STATEMENT>" << std::endl;

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}

Jump::Jump(std::string function, Node * exp)
{
    this->content_ = function;
    this->exp_ = exp;
}

void Jump::display(std::fstream & file)
{
    file << "<JUMP_STATEMENT type=\"" << this->content_ << "\">\n";

    if(this->content_ == "return")
    {
        if(this->exp_)
            this->exp_->display(file);
    }
    file << "</JUMP_STATEMENT>\n";

    if(this->nextStatement_)
        this->nextStatement_->display(file);
}


void semanticERROR(const std::string message)
{
    std::cout << "[SEMANTIC ERROR]: ";
    std::cout << message << std::endl;
    exit(0);
}

std::map<std::string, SemanticObjetc>::iterator findIdentifier(std::string identifier)
{
    std::map<std::string, SemanticObjetc>::iterator iter;

    for (iter = symbolTab_.end(); iter != symbolTab_.begin(); iter--)
    {
        if (iter->first == identifier)
            break;
    }

    return iter;
}


bool existInThisContext(std::string context)
{
    bool exist  = false;

    for (unsigned int i = context_.size(); i > 0; i--)
    {
        if (context == context_[i])
        {
            exist = true;
            break;
        }
    }

    return exist;
}
