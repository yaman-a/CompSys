#include "CompilerParser.h"


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->currI = this->tokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if (have("keyword","class")){
        next();
        
        if(current()->getType() == "identifier" || current()->getValue() == "Main" || current()->getValue() == "main"){
            prev();
            ParseTree* ans = compileClass();
            return ans;
        } else {
            throw ParseException();
        }
    }
    throw ParseException();
    return nullptr;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* ans = new ParseTree("class","");
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    
    if (!have("symbol", "{")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    while (currI != tokens.end() && !have("symbol", "}")){
        if (have("keyword", "function") || have("keyword", "method") || have("keyword", "constructor")){
            ans->addChild(compileSubroutine());
        } else if (have("keyword", "static") || have("keyword", "field")){
            ans->addChild(compileClassVarDec());
        } else {
            throw ParseException();
        }

        next();
    }


    if (!have("symbol", "}")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    return ans;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* ans = new ParseTree("classVarDec","");
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && !(current()->getType() == "identifier")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    if (!(current()->getType() == "identifier")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();

    while (currI != tokens.end() && have("symbol", ",")){
        ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
        if (!(current()->getType() == "identifier")){
            throw ParseException();
            return NULL;
        }
        ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
    }

    if (!have("symbol", ";")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return ans;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
     ParseTree* ans = new ParseTree("subroutine","");
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    if (current()->getType() != "keyword" && current()->getType() != "identifier"){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    next();
    if (current()->getType() != "identifier"){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    
    if (!have("symbol", "(")){
        // cout << "8" << endl;
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    next();
    if (!have("symbol", ")")){
        ans->addChild(compileParameterList());
    }
    
    if (!have("symbol", ")")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    
    next();
    if (!have("symbol", "{")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(compileSubroutineBody());

    return ans;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* ans = new ParseTree("parameterList","");

    if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && current()->getType() != "identifier"){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    
    
    if (current()->getType() != "identifier"){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    
    if (!have("symbol", ",")){
        return ans;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    while (currI != tokens.end() && !have("symbol", ")")){
        if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && current()->getType() != "identifier"){
            throw ParseException();
            return NULL;
        }
        ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
        
        
        if (current()->getType() != "identifier"){
            throw ParseException();
            return NULL;
        }
        ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();

        
        if (have("symbol", ",") ){
            ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
            next();
            if (have("symbol", ")")){
                throw ParseException();
            }
        }
        
    }
    return ans;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* ans = new ParseTree("subroutineBody","");
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
    while (currI != tokens.end() && !have("symbol", "}")){
        if (have("keyword", "var")){
            ans->addChild(compileVarDec());
            next();
            continue;
        }
        ans->addChild(compileStatements());
    }
    if (!have("symbol", "}")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    return ans;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* ans = new ParseTree("varDec","");
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    
    next();
    if (!have("keyword", "int") && !have("keyword", "char") && !have("keyword", "boolean") && current()->getType() != "identifier"){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();
    if (!(current()->getType() == "identifier")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    next();

    while (currI != tokens.end() && have("symbol", ",")){
        ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
        if (!(current()->getType() == "identifier")){
            throw ParseException();
            return NULL;
        }
        ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
    }

    if (!have("symbol", ";")){
        throw ParseException();
        return NULL;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return ans;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* ans = new ParseTree("ifStatement","");

    if (!have("keyword", "if")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("symbol", "(")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    ans->addChild(compileExpression());

    if (!have("symbol", ")")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("symbol", "{")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    ans->addChild(compileStatements());
    
    if (!have("symbol", "}")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("keyword", "else")){
        return ans;
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (!have("symbol", "{")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();
        
    

    ans->addChild(compileStatements());

    if (!have("symbol", "}")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return ans;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* ans = new ParseTree("doStatement", "");
    if (!have("keyword", "do")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    ans->addChild(compileExpression());

    if (!have("symbol", ";")){
        throw ParseException();
    }
    ans->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return ans;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    return NULL;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}

void CompilerParser::prev(){
    if (currI != tokens.begin()) {
        --currI;
    } else {
        throw ParseException(); 
    }
}