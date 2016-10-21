//
//  Parser.h
//  A1_parser
//
//  Created by Angel on 10/15/16.
//  Copyright © 2016 Angel Jimenez. All rights reserved.
//

#ifndef Parser_h
#define Parser_h

#include "Rule.h"
#include "Symbol.h"
#include <vector>

#define PGM 0
#define SLIST 1 // can lead to "Stmt semi Slist" | "eps"
#define STMT 2 // can lead to "id equal STMT'" | "S_Out"
#define STMT_ 3 // can lead to "E" | "kwdinput"
#define S_OUT 4
#define ELIST 5 // can lead to "E Elist" | "eps"
#define ELIST2 6
#define E 7
#define E_ 8
#define T 9
#define T_ 10
#define F 11 // can lead to "Fatom | paren1 E paren2"
#define FATOM 12 // can lead to "id | int | string| float"
#define OPADD 13 // can lead to "plus | minus"
#define OPMUL 14 // can lead to "aster | slash | caret"
#define EPS 1000

class Parser{
public:
    Rule rules[24];
    int mtx[17][20] = {
        {pgm1},
        {0,0,EPS,0,slist2,0,0,slist2},
        {0,0,0,0,stmt3,0,0,stmt4},
        {0,0,0,0,stmt_5,0,stmt_6,0,0,stmt_5,0,stmt_5,stmt_5,stmt_5},
        {0,0,0,0,0,0,0,s_out7},
        {0,0,0,0,elist8,0,0,0,0,elist8,EPS,elist8,elist8,elist8},
        {0,0,0,0,0,0,0,0,elist2_9,0,EPS},
        {0,0,0,0,e10,0,0,0,0,e10,0,e10,e10,e10},
        {0,0,0,EPS,0,0,0,0,EPS,0,EPS,0,0,0,e_11,e_11},
        {0,0,0,0,t12,0,0,0,0,t12,0,t12,t12,t12},
        {0,0,0,EPS,0,0,0,0,EPS,0,EPS,0,0,0,EPS,EPS,t_13,t_13,t_13},
        {0,0,0,0,f14,0,0,0,0,f15,0,f14,f14,f14},
        {0,0,0,0,fatom16,0,0,0,0,0,0,fatom17,fatom18,fatom19},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,opadd20,opadd21},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,opmul22,opmul23,opmul24}
    };
    enum Lhs { pgm1, slist2, stmt3, stmt4, stmt_5,    stmt_6,
        s_out7,  elist8, elist2_9,      e10,    e_11,       t12,
        t_13,     f14,      f15,  fatom16, fatom17,   fatom18,
        fatom19, opadd20,  opadd21,  opmul22, opmul23,   opmul24
    };
    
    vector<Symbol> input;
    vector<Symbol> stack;
    
    Parser(vector<Symbol> input_){
        input = input_;
        //reverse(input.begin(),input.end());
    }
    ~Parser(){
        
    }
    void buildRules(){
        
        
        /* RULES BUILT BY HAND TO REDUCE ERRORS */
        
        cout << "Building rules...!\n";
        
        /* RULE 1 */
        
        Symbol lhs1 = Symbol(0, "", "Pgm", false);
        Symbol rhs1[4] = {
            Symbol(KWDPROG, "prog", "", true),
            Symbol(BRACE1, "{", "", true),
            Symbol(SLIST, "", "Slist", false),
            Symbol(BRACE2, "}", "", true)
        };
        rules[0] = Rule(PGM, lhs1, rhs1, 4);
        
        
        /* RULE 2 */
        Symbol lhs2 = Symbol(1, "", "Slist", false);
        Symbol rhs2[3] = {
            Symbol(STMT,"","Stmt", false),
            Symbol(SEMI, ";", "", true),
            Symbol(SLIST,"","Slist", false)
        };
        
        rules[1] = Rule(SLIST, lhs2, rhs2, 3);
        
        /* RULE 3 */
        
        Symbol lhs3 = Symbol(2, "", "Stmt", false);
        Symbol rhs3[3] = {
            Symbol(ID, "id","", true),
            Symbol(EQUAL, "=","", true),
            Symbol(STMT_, "","Stmt_", false)};
        rules[2] = Rule(STMT, lhs3, rhs3, 3);
        
        /* RULE 4 */
        
        Symbol lhs4 = Symbol(3, "", "Stmt", false);
        Symbol rhs4[1] = {
            Symbol(S_OUT, "","S_Out", false)
        };
        rules[3] = Rule(STMT, lhs4, rhs4, 1);
        
        /* RULE 5 */
        
        Symbol lhs5 = Symbol(4, "", "Stmt_", false);
        Symbol rhs5[1] = {
            Symbol(E, "","E", false)
        };
        rules[4] = Rule(STMT_, lhs5, rhs5, 1);
        
        /* RULE 6 */
        
        Symbol lhs6 = Symbol(5, "", "Stmt_", false);
        Symbol rhs6[1] = {
            Symbol(KWDINPUT, "kwdinput","", true)
        };
        rules[5] = Rule(STMT_, lhs6, rhs6, 1);
        
        
        /* RULE 7 */
        
        Symbol lhs7 = Symbol(6, "", "S_Out", false);
        Symbol rhs7[4] = {
            Symbol(KWDPRINT, "kwdprint", "", true),
            Symbol(PAREN1, "(", "", true),
            Symbol(ELIST, "", "Elist", false),
            Symbol(PAREN2, ")", "", true),
        };
        rules[6] = Rule(STMT_, lhs7, rhs7, 4);
        
        /* RULE 8 */
        
        Symbol lhs8 = Symbol(7, "", "Elist", false);
        Symbol rhs8[2] = {
            Symbol(E, "", "E", false),
            Symbol(ELIST2, "", "Elist2", false)
        };
        rules[7] = Rule(ELIST, lhs8, rhs8, 2);
        
        /* RULE 9 */
        
        Symbol lhs9 = Symbol(8, "", "Elist2", false);
        Symbol rhs9[2] = {
            Symbol(COMMA, ",", "", true),
            Symbol(ELIST, "", "Elist", false)
        };
        rules[8] = Rule(ELIST2, lhs9, rhs9, 2);
        
        /* RULE 10 */
        
        Symbol lhs10 = Symbol(9, "", "E", false);
        Symbol rhs10[2] = {
            Symbol(T, "", "T", false),
            Symbol(E_, "", "E_", false)
        };
        rules[9] = Rule(E, lhs10, rhs10, 2);
        
        /* RULE 11 */
        
        Symbol lhs11 = Symbol(10, "", "E_", false);
        Symbol rhs11[3] = {
            Symbol(OPADD, "", "Opadd", false),
            Symbol(T, "", "T", false),
            Symbol(E_, "", "E_", false),
        };
        rules[10] = Rule(E_, lhs11, rhs11, 3);
        
        /* RULE 12 */
        
        Symbol lhs12 = Symbol(11, "", "T", false);
        Symbol rhs12[2] = {
            Symbol(F, "", "F", false),
            Symbol(T_, "", "T_", false)
        };
        rules[11] = Rule(T, lhs12, rhs12, 2);
        
        /* RULE 13 */
        
        Symbol lhs13 = Symbol(12, "", "T_", false);
        Symbol rhs13[3] = {
            Symbol(OPMUL, "", "Opmul", false),
            Symbol(F, "", "F", false),
            Symbol(T_, "", "T_", false),
        };
        rules[12] = Rule(T_, lhs13, rhs13, 3);
        
        /* RULE 14 */
        
        Symbol lhs14 = Symbol(13, "", "F", false);
        Symbol rhs14[1] = {
            Symbol(FATOM, "","Fatom", false)
        };
        rules[13] = Rule(STMT_, lhs14, rhs14, 1);
        
        
        /* RULE 15 */
        
        Symbol lhs15 = Symbol(14, "", "F", false);
        Symbol rhs15[3] = {
            Symbol(PAREN1, "(", "", true),
            Symbol(E, "", "E", false),
            Symbol(PAREN2, ")", "", true)
        };
        rules[14] = Rule(T_, lhs15, rhs15, 3);
        
        /* RULE 16 */
        
        Symbol lhs16 = Symbol(15, "", "Fatom", false);
        Symbol rhs16[1] = {
            Symbol(ID, "id","", true)
        };
        rules[15] = Rule(FATOM, lhs16, rhs16, 1);
        
        /* RULE 17 */
        
        Symbol lhs17 = Symbol(16, "", "Fatom", false);
        Symbol rhs17[1] = {
            Symbol(INT, "int","", true)
        };
        rules[16] = Rule(FATOM, lhs17, rhs17, 1);
        
        /* RULE 18 */
        
        Symbol lhs18 = Symbol(17, "", "Fatom", false);
        Symbol rhs18[1] = {
            Symbol(FLOAT, "float","", true)
        };
        rules[17] = Rule(FATOM, lhs18, rhs18, 1);
        
        /* RULE 19 */
        
        Symbol lhs19 = Symbol(18, "", "Fatom", false);
        Symbol rhs19[1] = {
            Symbol(STRING, "string","", true)
        };
        rules[18] = Rule(FATOM, lhs19, rhs19, 1);
        
        /* RULE 20 */
        
        Symbol lhs20 = Symbol(29, "", "Opadd", false);
        Symbol rhs20[1] = {
            Symbol(PLUS, "plus","", true)
        };
        rules[19] = Rule(OPADD, lhs20, rhs20, 1);
        
        /* RULE 21 */
        
        Symbol lhs21 = Symbol(20, "", "Opadd", false);
        Symbol rhs21[1] = {
            Symbol(MINUS, "minus","", true)
        };
        rules[20] = Rule(OPADD, lhs21, rhs21, 1);
        
        /* RULE 22 */
        
        Symbol lhs22 = Symbol(21, "", "Opmul", false);
        Symbol rhs22[1] = {
            Symbol(ASTER, "aster","", true)
        };
        rules[21] = Rule(OPMUL, lhs22, rhs22, 1);
        
        /* RULE 23 */
        
        Symbol lhs23 = Symbol(22, "", "Opmul", false);
        Symbol rhs23[1] = {
            Symbol(SLASH, "slash","", true)
        };
        rules[22] = Rule(OPMUL, lhs23, rhs23, 1);
        
        /* RULE 24 */
        
        Symbol lhs24 = Symbol(23, "", "Opmul", false);
        Symbol rhs24[1] = {
            Symbol(CARET, "caret","", true)
        };
        rules[23] = Rule(OPMUL, lhs24, rhs24, 1);
        
        /* print rules
         
         for(int i = 0; i < 24; i++){
         rules[i].print();
         }*/
        
        cout << "Rules built successfully.." << endl;
        
    }
    void buildStream(){
        
        input.push_back(Symbol(eof,"$","", true));
        input.push_back(Symbol(BRACE2,"}","", true));
        input.push_back(Symbol(SEMI,";","", true));
        input.push_back(Symbol(PAREN2,")","", true));
        input.push_back(Symbol(INT,"int","", true));
        input.push_back(Symbol(COMMA,",","", true));
        input.push_back(Symbol(STRING,"string","", true));
        input.push_back(Symbol(COMMA,",","", true));
        input.push_back(Symbol(INT,"int","", true));
        input.push_back(Symbol(COMMA,",","", true));
        input.push_back(Symbol(STRING,"string","", true));
        input.push_back(Symbol(COMMA,",","", true));
        input.push_back(Symbol(STRING,"string","", true));
        input.push_back(Symbol(PAREN1,"(","", true));
        input.push_back(Symbol(KWDPRINT,"print","", true));
        input.push_back(Symbol(BRACE1,"{","", true));
        input.push_back(Symbol(KWDPROG,"prog","", true));
        
        cout << "Input stack built successfully...\n";
    }
    
    void printStack(const vector<Symbol>& stack ){
        vector<Symbol>::iterator it;
        for(auto& i : stack){
            if(i.terminal) cout << i.lexeme << " ";
            else cout << i.identifier;
        }
        cout << endl;
    }
    void printHelper(vector<Symbol> input, vector<Symbol> stack){
        printStack(input);
        printStack(stack);
    }
    void pushRevRHS(Symbol s[], int size){
        for( int i = size-1; i >=
            0; i-- ){
            stack.push_back(s[i]);
        }
    }
    void start(){
        buildRules();
        //buildStream();
        Symbol eof_ = Symbol(eof,"$", "", true);
        //push eof
        stack.push_back(eof_);
        stack.push_back(rules[0].lhs); // push "Pgm"
        printHelper(input, stack);
        
        while(stack.back().code != eof){
            if(mtx[stack.back().code][input.back().mtxCode] == EPS){
                stack.pop_back();
            }
            
            else if(!stack.back().terminal){
                Symbol tmp = stack.back();
                stack.pop_back();
                pushRevRHS(rules[mtx[tmp.code][input.back().mtxCode]].rhs, rules[mtx[tmp.code][input.back().mtxCode]].size);
            }
            else if(stack.back().code == input.back().code){
                stack.pop_back();
                input.pop_back();
            }
            else if(mtx[stack.back().code][input.back().mtxCode] == 0){
                if(input.back().terminal) cout << "Syntax error at: " << input.back().identifier << " Error code: " << input.back().code << endl;
                else cout << "Syntax error at: " << input.back().lexeme << " Error code: " << input.back().code << endl;
                
                break;
            }
            printHelper(input, stack);
        }
    }
};
#endif /* Parser_h */
