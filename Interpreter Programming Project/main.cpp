//
//  main.cpp
//  Interpreter Programming Project
//
//  Created by Scott English on 3/25/17.
//  Copyright © 2017 Scott English. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

bool isWhitespace(char input);
std::string get();
bool B();
bool IT();
bool IT_Tail();
bool OT();
bool OT_Tail();
bool AT();
bool AT_Tail();
bool L();
bool A();
int count=0;
std::string output,expression="";
int main(int argc, char *argv[]) {
    std::cin >> expression;
    if(B()){
        std::cout << "Correct syntax\n";
    }
    else{
        std::cout << "Incorrect syntax\n";
    }
    return 0;
}
std::string get(){
    if(!(isWhitespace(expression[count]))){
        output=expression[count];
    }else{
        return output;
    }
    count++;
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
    std::string lex="";
    std::cout << "In B "<< lex<<"\n";
    if(IT()){
        lex=get();
        std::cout <<lex<<"\n";
        if(lex=="."){
            std::cout << "<"<<lex<<">"<<".\n";
            return true;

        }else{
            return false;
        }
    }else{
        return false;
    }

}
bool IT(){
    std::cout << "In IT "<<"\n";

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
    std::string lex="";
    lex=get();
    std::cout << "In IT_Tail "<< lex<<"\n";
    if(lex=="-"){
        lex+=get();
        if(lex=="->"){
            if(OT()){
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
    }
    else{
        return false;
    }
}
bool OT(){
    std::cout << "In OT "<<"\n";
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
    std::string lex="";
    lex=get();
    std::cout << "In OT_Tail "<< lex<<"\n";
    if(lex=="v"){
        if(AT()){
            if(OT_Tail()){
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
}
bool AT(){
    std::cout << "In AT "<<"\n";
    if(L()){
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
    std::string lex="";
    lex=get();
    std::cout << "In AT_Tail "<< lex<<"\n";
    if(lex=="^"){
        if(L()){
            if(AT_Tail()){
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
}
bool L(){
    int counter=0;
    std::string lex="";
    std::cout << "In L "<< lex<<"\n";
    counter=count;
    lex=get();
    count=counter;
    if(A()){
        return true;
    }
    else if(lex=="~"){
        if(L()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
bool A(){
    std::string lex="";
    lex=get();
    std::cout << "In A "<< lex<<"\n";
    if(lex =="T"|| lex =="F"){
        return true;
    }else if(lex=="("){
        return true;
    }else{
        return false;
    }
}



