//
//  main.cpp
//  Interpreter Programming Project
//
//  Created by Scott English on 3/25/17.
//  Copyright © 2017 Scott English. All rights reserved.
//
//
/* The input to this program is through the console/command line by simply inputing the string to be checked */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stack>

// Function Declerations //
bool isWhitespace(char input);
std::string getChar();
bool B();
bool IT();
bool IT_Tail();
bool OT();
bool OT_Tail();
bool AT();
bool AT_Tail();
bool L();
bool A();

/* 

Global Variables:
* count is used to contain the character index of the input string. count is incremented after each character contained within the set {~,.,-,>,(,T,F} is munch'd.
* expression is used to capture the input in main and allow getChar() to access the character needed per each call
* mystack is used to contain the characters that have been munch'd for there semantic evaluations.

*/

int count=0;
std::string expression="";
std::stack<std::string> mystack;

// Function Definitions //
int main(int argc, char *argv[]) {
    std::cin >> expression;
    if(B()){
        std::cout << "Correct syntax\n";
        std::cout<<mystack.top()<<"\n";
        mystack.pop();
    }
    else{
        std::cout << "Incorrect syntax\n";
    }
    return 0;
}
std::string getChar(){
    std::string output;
    if(!(isWhitespace(expression[count]))){
        output=expression[count];
    }else{
        return output;
    }
    return output;
}
bool isWhitespace(char input){
    if(input==' '){
        return true;
    }
    else{
        return false;
    }
}
bool B(){
    std::string lex;
    if(IT()){
        lex=getChar();
        if(lex=="."){
            return true;

        }else{
            return false;
        }
    }else{
        return false;
    }

}
bool IT(){
    if(OT()){
        if(IT_Tail()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
bool IT_Tail(){
    std::string lex,first,second,output;
    lex=getChar();
    if(lex=="-"){
        count++;
        lex=getChar();
        if(lex==">"){
            count++;
            if(OT()){
                first=mystack.top();
                mystack.pop();
                second=mystack.top();
                mystack.pop();
                if(first=="T"&&second=="F"){
                    mystack.push("F");
                }
                else{
                    mystack.push("T");
                }
                if(IT_Tail()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else if(lex=="."||lex==")"){
        return true;
    }else{
        return false;
    }
}
bool OT(){
    if(AT()){
        if(OT_Tail()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
bool OT_Tail(){
    std::string lex,FirstChar,SecondChar;
    lex=getChar();
    if(lex=="v"){
        count++;
        if(AT()){
            SecondChar=mystack.top();
            mystack.pop();
            FirstChar=mystack.top();
            mystack.pop();
            if(FirstChar=="T" && SecondChar=="T"){
                mystack.push("T");
            }else{
                mystack.push("F");
            }
            if(OT_Tail()){
                return true;
            }else{
                return true;
            }
        }else{
            return false;
        }
    }else if(lex=="-"||lex=="."||lex==")"){
        return true;
    }else{
        return false;
    }
}
bool AT(){
    if(L()){
        count++;
        if(AT_Tail()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
bool AT_Tail(){
    std::string lex,FirstChar,SecondChar;
    lex=getChar();
    if(lex=="^"){
        count++;
        if(L()){
            count++;
            FirstChar=mystack.top();
            mystack.pop();
            SecondChar=mystack.top();
            mystack.pop();
            if(FirstChar=="T" && SecondChar=="T"){
                mystack.push("T");
            }else{
                mystack.push("F");
            }
            if(AT_Tail()){
                return true;
            }else{
                return true;
            }
        }else{
            return false;
        }
    }else if(lex=="v"||lex=="-"||lex=="."||lex==")"){
        return true;
    }else{
        return false;
    }
}
bool L(){
    std::string lex,output;
    lex=getChar();
    if(A()){
        return true;
    }
    else if(lex=="~"){
        count++;
        if(L()){
            output=mystack.top();
            mystack.pop();
            if(output=="T"){
                mystack.push("F");
            }else{
                mystack.push("T");
            }
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
bool A(){
    std::string lex;
    lex=getChar();
    if((lex=="T")|| (lex=="F")){
        mystack.push(lex);
        return true;
    }else if(lex=="("){
        count++;
        if(IT()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
