
// **********************************************
// Author: Angel Jimenez
// **********************************************
// Email: Ajl890889702@csu.fullerton.edu
// **********************************************
// main.cpp: A hand built lexer that takes in an
// A2 language program written in a text file and
// produces tokens to be used in Syntax Analysis.
// **********************************************

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <regex>
using namespace std;

FILE * file;
char nextChar;
char lexeme[100];
char lexemeLength = 0;
int lexCode;
int lineCount=1;
/*Punctuation DFA Functions*/
void stateOnePuncDFA(char c);
void stateTwoPuncDFA(char c);

/*KeyWord DFA Functions*/
void stateOneKeyWordDFA(char c);
void stateTwoKeyWordDFA(char c);
void stateThreeKeyWordDFA(char c);
void stateFourKeyWordDFA(char c);
void stateFiveKeyWordDFA(char c);
void stateSixKeyWordDFA(char c);

/*RegEx DFA Functions*/
void stateOneRegex(char c);
void stateTwoRegex(char c);
void stateThreeRegex(char c);
void terminateStateRegex();
int getRegexCode(string lex);

/* General Functions */
void addChar(char c);
void terminateState();
int getCode(string s);

/* Regex Codes */
#define COMMENT 1
#define ID 2
#define INT 3
#define FLOAT 4
#define STRING 5

/* Key Words */
#define KWDPROG 10      // "prog"
#define KWDMAIN 11      // "main"
#define KWDFCN 12       // "fcn"
#define KWDCLASS 13     // "class"
#define KWDFLOAT 15     // "float"
#define KWDINT 16       // "int"
#define KWDSTRING 17    // "string"
#define KWDIF 18        // "if"
#define KWDELSEIF 19    // "elseif"
#define KWDELSE 20      // "else"
#define KWDWHILE 21     // "while"
#define KWDINPUT 22     // "input"
#define KWDPRINT 23     // "print"
#define KWDNEW 24       // "new"
#define KWDRETURN 25    // "return"

/* Paired Delimiters */
#define ANGLE1 31       // '<'
#define ANGLE2 32       // '>'
#define BRACE1 33       // '{'
#define BRACE2 34       // '}'
#define BRACKET1 35     // '['
#define BRACKET2 36     // ']'
#define PARENS1 37      // '('
#define PARENS2 38      // ')'

/* Other Punctuation */
#define COMMA 6         // ","
#define SEMI 7          // ";"
#define ASTER 41        // '*'
#define CARET 42        // '^'
#define COLON 43        // ':'
#define DOT 44          // '.'
#define EQUAL 45        // '='
#define MINUS 46        // '-'
#define PLUS 47         // '+'
#define SLASH 48        // '/'

/* Multi-char Operators */
#define OPARROW 51      // '->'
#define OPEQ 52         // '=='
#define OPNE 53         // '!='
#define OPLE 54         // '<='
#define OPGE 55         // '>='
#define OPSHL 56        // '<<'
#define OPSHR 57        // '>>'

/* Miscellaeous */
#define ERROR  99       // Unknown token
#define eof 0           // End-of-Input

int main() {
    
    file = fopen("program.txt", "r");
    if (file == nullptr) { perror("Error opening file."); }
    do {
        nextChar = getc(file);
        if(ispunct(nextChar) && nextChar != '"'){
            stateOnePuncDFA(nextChar);
        }
        else if(isalpha(nextChar)){
            stateOneKeyWordDFA(nextChar);
            
        } else {
            stateOneRegex(nextChar);
        }
        
    } while (nextChar != EOF);
    
    cout << "(Tok: id= " << eof << " line = " << lineCount << " str= \"\")" << endl;
    return 0;
}

/****************************************/
/****** PUNCTUATION DFA FUNCTIONS *******/
/****************************************/

void stateOnePuncDFA(char c){
    //printf("entering state 1 PUNC with: %c \n", c);
    if(c == '!' || c == '<' || c == '>' || c == '='){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == '=' || nextChar == '<' || nextChar == '>'){
            stateTwoPuncDFA(nextChar);
        }
        else {
            terminateState();
            stateOnePuncDFA(nextChar);
        }
    }
    //Non-problematic characters
    if(c == ',' || c == ';' || c == '*' || c == '^' || c == ':' || c == '.'|| c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')'){
        addChar(c);
        terminateState();
    }
    //Regex-problematic characters
    else if( c == '/'){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == '/'){
            stateTwoRegex(nextChar);
        }
    }
    else if(c == '+' || c == '-'){
        addChar(c);
        nextChar = getc(file);
        if(isdigit(nextChar)){
            stateTwoRegex(nextChar);
        }
        else {
            terminateState();
        }
    }
    else if(c == '\n'){
        lineCount++;
    }
}
void stateTwoPuncDFA(char c){
    //printf("entering state 2 PUNC with: %c \n", c);
    if ( c == '=' || c == '<' || c == '>'){
        addChar(c);
        terminateState();
    }
}

/****************************************/
/******** KEYWORD DFA FUNCTIONS *********/
/****************************************/
void stateOneKeyWordDFA(char c){
    //printf("entering state 1 KEYWD with: %c \n", c);
    
    //Non-Problematic characters
    if(c == 'c' || c == 'e' || c == 'm'  || c == 'n' || c == 'p' || c == 'r' || c == 's' || c == 'w' ){
        addChar(c);
        stateTwoKeyWordDFA(nextChar = getc(file));
    }
    //Problem characters
    else if(c == 'f' || c == 'i'){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == 'a' || nextChar == 'c' || nextChar == 'e' || nextChar == 'f' || nextChar == 'l' || nextChar == 'n' ){
            stateTwoKeyWordDFA(nextChar);
        }
    }
    //If not a keyword, save as identifier
    else if(c == '_' || isalpha(nextChar)){
        addChar(c);
        nextChar = getc(file);
        while((nextChar == '_') || isalpha(nextChar)){
            addChar((nextChar));
            nextChar = getc(file);
        }
        stateTwoRegex(nextChar);
    }
    else if(c == '\n'){
        lineCount++;
    }
}

void stateTwoKeyWordDFA(char c){
    //printf("entering state 2 KEYWD with: %c \n", c);
    
    //Non-Problematic characters
    if(c == 'a' || c == 'c' || c == 'h' || c == 'r' || c == 't'){
        addChar(c);
        stateThreeKeyWordDFA(nextChar = getc(file));
    }
    //Problematic characters
    else if(c == 'e'|| c == 'l' || c == 'n' ){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == 'a' || nextChar == 'n' || nextChar == 'o' || nextChar == 'p' || nextChar == 's' || nextChar == 't' || nextChar  == 'w'){
            stateThreeKeyWordDFA(nextChar);
        }
        else {
            lexemeLength = 0;
        }
    }
    //Terminating character
    else if (c == 'f'){
        addChar(c);
        terminateState();
    }
    //If not a keyword, save as identifier
    else if(c == '_' || isalpha(nextChar)){
        addChar(c);
        nextChar = getc(file);
        while((nextChar == '_') || isalpha(nextChar)){
            addChar((nextChar));
            nextChar = getc(file);
        }
        stateTwoRegex(nextChar);
    }
    
}

void stateThreeKeyWordDFA(char c){
    //printf("entering state 3 KEYWD with: %c \n", c);
    
    //Special case for 'input' and 'int'
    if(c == 't'){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == 'u'){
            stateFourKeyWordDFA(nextChar);
        }
        else {
            terminateState();
            stateOneKeyWordDFA(nextChar);
        }
    }
    //Non-Problematic characters
    else if( c == 'a' || c == 'o' || c == 'p' || c == 'r' || c == 's' || c == 'u' ){
        addChar(c);
        stateFourKeyWordDFA(nextChar = getc(file));
    }
    //Problematic character
    else if (c == 'i'){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == 'e' || nextChar == 'l' || nextChar == 'n' || nextChar == 'u'){
            stateFourKeyWordDFA(nextChar);
        }
        else {
            lexemeLength = 0;
        }
    }
    //Terminating characters
    else if ( c == 'n' || c == 'w'){
        addChar(c);
        terminateState();
    }
}

void stateFourKeyWordDFA(char c){
    //printf("entering state 4 KEYWD with: %c \n", c);
    
    //Special case for 'else'/'elseif' & 'main'/'print'
    if(c == 'e' || c == 'n'){
        addChar(c);
        nextChar = getc(file);
        if( nextChar == 'i' || nextChar == 't'){
            stateFiveKeyWordDFA(nextChar);
        }
        else {
            terminateState();
            stateOneKeyWordDFA(nextChar);
        }
    }
    //Non-problematic characters
    else if(c == 'a' || c == 'i' || c == 'l' || c == 's' ){
        addChar(c);
        stateFiveKeyWordDFA(nextChar = getc(file));
    }
    //Problematic character
    else if(c == 'u'){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == 'r' || nextChar == 't'){
            stateFiveKeyWordDFA(nextChar);
        }
    }
    //Terminating characters
    else if(c == 'g' || c == 'r'){
        addChar(c);
        terminateState();
    }
}

void stateFiveKeyWordDFA(char c){
    //printf("entering state 5 KEYWD with: %c \n", c);
    //Non-problematic characters
    if(c == 'i' || c == 'n' || c == 'r'){
        addChar(c);
        stateSixKeyWordDFA(nextChar = getc(file));
        
    }
    //Terminating characters
    else if(c == 'e' || c == 's' || c == 't'){
        addChar(c);
        terminateState();
    }
}

void stateSixKeyWordDFA(char c){
    //printf("entering state 6 KEYWD with: %c \n", c);
    //Terminating characters
    if( c == 'f' ||  c == 'g' || c == 'n'){
        addChar(c);
        terminateState();
    }
}

/****************************************/
/****** REGEX    DFA    FUNCTIONS *******/
/****************************************/

void stateOneRegex(char c){
    //printf("entering state 1 RegEx with: %c \n", c);
    if( c == '/'){
        addChar(c);
        nextChar = getc(file);
        if(nextChar == '/'){
            stateTwoRegex(nextChar);
        }
    }
    else if(c =='"'){
        addChar(c);
        nextChar = getc(file);
        while(nextChar != '"' || nextChar == '\xff'){
            addChar(nextChar);
            nextChar = getc(file);
        }
        addChar(nextChar);
        stateTwoRegex(nextChar);
    }
    else if(isdigit(c) || c == '+' || c == '-'){
        addChar(c);
        nextChar = getc(file);
        if(isdigit(nextChar) || nextChar == '.'){
            stateTwoRegex(nextChar);
        }
        else {
            terminateStateRegex();
        }
    }
    else if(c == '_' || isalpha(nextChar)){
        addChar(c);
        nextChar = getc(file);
        while((nextChar == '_') || isalpha(nextChar)){
            addChar((nextChar));
            nextChar = getc(file);
        }
        stateTwoRegex(nextChar);
    }
    else if(c == '\n'){
        lineCount++;
    }
}

void stateTwoRegex(char c){
    //printf("entering state 2 RegEx with: %c \n", c);
    if(c=='/'){
        addChar(c);
        nextChar = getc(file);
        while(nextChar != '\n' || nextChar == '\xff'){
            addChar(nextChar);
            nextChar = getc(file);
        }
        stateThreeRegex(nextChar);
    }
    else if(isdigit(c) || c == '.'){
        addChar(c);
        nextChar = getc(file);
        while (isdigit(nextChar)) {
            addChar(nextChar);
            nextChar = getc(file);
        }
        terminateStateRegex();
    }
    else if(c == '\n' || c == '"' || ' '){
        terminateStateRegex();
    }
    stateOnePuncDFA(nextChar);
}

void stateThreeRegex(char c){
    //printf("entering state 3 RegEx with: %c \n", c);
    if(c == '\n'){
        terminateStateRegex();
    }
    else if(c == '.'){
        addChar(c);
        nextChar = getc(file);
        while (isdigit(nextChar)) {
            addChar(nextChar);
            nextChar = getc(file);
        }
        terminateStateRegex();
    }
    else if(!isdigit(c)){
        terminateStateRegex();
    }
}

void terminateStateRegex(){
    string lex = lexeme;
    
    lexCode = getRegexCode(lex);
    if(lexCode == INT){
        cout << "(Tok: id= " << lexCode << " line = " << lineCount << "" << " str= \"" << lex << "\" int= "<< lex << ")" << endl;
    }
    else if(lexCode == FLOAT){
        cout << "(Tok: id= " << lexCode << " line = " << lineCount << " str= \"" << lex << "\" float= "<< lex << ")" << endl;
    }
    else if (lexCode == STRING){
        cout << "(Tok: id= " << lexCode << " line = " << lineCount << " str= " << lex << ")" << endl;
    }
    else if(lexCode != COMMENT){
        cout << "(Tok: id= " << lexCode << " line = " << lineCount << " str= \"" << lex << "\")" << endl;
    }
    memset(&lexeme, 0, 100);
    lexemeLength = 0;
}

int getRegexCode(string lex){
    regex id("['_'*|[a-zA-Z0-9]*");
    regex integer("(-|\\+)?[0-9]+");
    regex flt("((-|\\+)?[0-9]+\\.)?[0-9]+");
    regex string("\".*\"");
    
    if(regex_match(lex, integer)){
        return INT;
    }
    else if(regex_match(lex, flt)){
        return FLOAT;
        
    }
    else if(regex_match(lex, id)){
        return ID;
    }
    else if(regex_match(lex, string)){
        return STRING;
    }
    else {
        return COMMENT;
    }
}
/****************************************/
/********** GENERAL FUNCTIONS ***********/
/****************************************/

void addChar(char c){
    lexeme[lexemeLength++] = c;
}
void terminateState(){
    string lex = lexeme;
    
    lexCode = getCode(lex);
    if(lexCode != ERROR){
        cout << "(Tok: id= " << lexCode << " line = " << lineCount << " str= \"" << lex << "\")" << endl;
    }
    memset(&lexeme, 0, 100);
    lexemeLength = 0;
}

int getCode(string lex){
    
    if(lex == "prog"){
        return KWDPROG;
    }
    else if(lex == "main"){
        return KWDMAIN;
    }
    else if(lex == "fcn"){
        return KWDFCN;
    }
    else if(lex == "class"){
        return KWDCLASS;
    }
    else if(lex == "float"){
        return KWDFLOAT;
    }
    else if(lex == "int"){
        return KWDINT;
    }
    else if(lex == "string"){
        return KWDSTRING;
    }
    else if(lex == "if"){
        return KWDIF;
    }
    else if(lex == "elseif"){
        return KWDELSEIF;
    }
    else if(lex == "else"){
        return KWDELSE;
    }
    else if(lex == "while"){
        return KWDWHILE;
    }
    else if(lex == "input"){
        return KWDINPUT;
    }
    else if(lex == "print"){
        return KWDPRINT;
    }
    else if(lex == "new"){
        return KWDNEW;
    }
    else if(lex == "return"){
        return KWDRETURN;
    }
    else if(lex == ","){
        return COMMA;
    }
    else if(lex == ";"){
        return SEMI;
    }
    else if(lex == "<"){
        return ANGLE1;
    }
    else if(lex == ">"){
        return ANGLE2;
    }
    else if(lex == "{"){
        return BRACE1;
    }
    else if(lex == "}"){
        return BRACE2;
    }
    else if(lex == "["){
        return BRACKET1;
    }
    else if(lex == "]"){
        return BRACKET2;
    }
    else if(lex == "("){
        return PARENS1;
    }
    else if(lex == ")"){
        return PARENS2;
    }
    else if(lex == "*"){
        return ASTER;
    }
    else if(lex == "^"){
        return CARET;
    }
    else if(lex == ":"){
        return COLON;
    }
    else if(lex == "."){
        return DOT;
    }
    else if(lex == "="){
        return EQUAL;
    }
    else if(lex == "-"){
        return MINUS;
    }
    else if(lex == "+"){
        return PLUS;
    }
    else if(lex == "/"){
        return SLASH;
    }
    else if(lex == "->"){
        return OPARROW;
    }
    else if (lex == "=="){
        return OPEQ;
    }
    else if(lex == "!="){
        return OPNE;
    }
    else if(lex == "<="){
        return OPLE;
    }
    else if(lex == ">="){
        return OPGE;
    }
    else if(lex == "<<"){
        return OPSHL;
    }
    else if(lex == ">>"){
        return OPSHR;
    }
    else{
        return ERROR;
    }
}










