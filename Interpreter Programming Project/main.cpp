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
#include <string>
#include <iostream>
#include <stack>

// Function Declerations //
bool isWhiteSpace(char input);
std::string GetChar();
std::string SpecialGetChar();
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
/* 
 Main calls std::getline which takes all input from console until it encounters '\0' and returns the value to expression.
 It calls B() and decides whether the syntax is correct or not.
 If the syntax is correct, we pop the value off of the top of the stack to determine the value of the semantics.
*/
int main(int argc, char *argv[]) {
    std::getline(std::cin, expression);
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
/* 
GetChar() takes the global variable and moves through each character as count is incremented throghout the program.
If a whitespace is encountered, count is incremented and getChar() is called once more to "walk over" the whitespace until we have found the next character in the input.
*/
std::string GetChar(){
    std::string output;
    if(!(isWhiteSpace(expression[count]))){
        output=expression[count];
    }else{
        count++;
        output=GetChar();
    }
    return output;
}
/*
 SpecialGetChar() takes the global variable expression and obtains the character at the spot specified by count, specifically for the check of '->'.
 If a whitespace is encountered, output is returned.
 */
std::string SpecialGetChar(){
    std::string output;
    if(!(isWhiteSpace(expression[count]))){
        output=expression[count];
    }else{
        return output;
    }
    return output;
}
/*
isWhiteSpace() is given a character and determines if the character is a whitespace which is defined by   ' ','\n','\r','\t'.
*/
bool isWhiteSpace(char input){
    if(input==' '||input=='\n'||input=='\r'||input=='\t'){
        return true;
    }
    else{
        return false;
    }
}
/*
B() is a non-terminal function that calls it's non-terminal functions to obtain whether the value is syntactically correct.
Syntax       Selection Set
<B>::= <IT>. {∼, T, F,(}
*/
bool B(){
    std::string lex;
    if(IT()){
        lex=GetChar();
        if(lex=="."){
            return true;

        }else{
            std::cout<< "Expecting '.' but got "<<lex<<"\n";
            return false;
        }
    }else{
        return false;
    }

}
/*
IT() is a non-terminal function that calls it's non-terminal functions to obtain whether the value is syntactically correct.
Syntax                Selection Set
<IT>::= <OT><IT_Tail> {∼, T, F,(}
*/
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
/*
IT_Tail() is a non-terminal function that calls it's non-terminal functions to obtain whether the value is syntactically correct and after establishing we have a terminal function, determining its semantic value.
IT_Tail() has a specific property to it that requires the use of a different means of getting characters called SpecialGetChar().
When getting characters is done, we only get one character at a time, to catch for the off chance that -> does not have any white space between the '-','>', we must check for whitespace after we call SpecialGetChar() to catch the error case where there is a space between '-','>'.
If there is a space between '-','>', we return false signifying an Incorrect syntax.
Syntax                       Selection Set
<IT_Tail>::= -><OT><IT_Tail> {->}
         ::= ε               {.,)}
*/
bool IT_Tail(){
    std::string lex,first,second,output;
    lex=GetChar();
    if(lex=="-"){
        count++;
        lex=SpecialGetChar();
        if(lex==""){
            std::cout<< "Expecting '>' but got "<<lex<<"\n";
            return false;
        }
        else if(lex==">"){
            count++;
            if(OT()){
                second=mystack.top();
                mystack.pop();
                first=mystack.top();
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
            std::cout<< "Expecting '>' but got "<<lex<<"\n";
            return false;
        }
    }else if(lex=="."||lex==")"){
        return true;
    }else{
        std::cout<< "Expecting '-' but got "<<lex<<"\n";
        return false;
    }
}
/*
 OT() is a non-terminal function that calls it's non-terminal functions to obtain whether the value is syntactically correct.
 Syntax                 Selection Set
 <OT>::= <AT><OT_Tail>  {∼, T, F,(}
*/
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
/*
OT_Tail() is a non-terminal function that calls it's non-terminal functions to obtain whether the value is syntactically correct and after establishing we have a terminal function, determining its semantic value.
Syntax                      Selection Set
<OT_Tail>::= V<AT><OT_Tail> {V}
         ::= ε              {− >, .,)}
*/
bool OT_Tail(){
    std::string lex,FirstChar,SecondChar;
    lex=GetChar();
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
        std::cout<< "Expecting 'v' but got "<<lex<<"\n";
        return false;
    }
}
/*
AT() is a non-terminal function that calls it's non-terminal functions to obtain whether the value is syntactically correct.
Syntax                Selection Set
<AT>::= <L><AT_Tail>  {∼, T, F,(}
*/
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
/*
AT_Tail() is a non-terminal function that calls it's non-terminal functions to obtain whether the value is syntactically correct and after establishing we have a terminal function, determining its semantic value.
Syntax                      Selection Set
<AT_Tail>::= ^<L><AT_Tail>  {^}
         ::= ε              {∨, − >, .,)}
*/
bool AT_Tail(){
    std::string lex,FirstChar,SecondChar;
    lex=GetChar();
    if(lex=="^"){
        count++;
        if(L()){
            count++;
            SecondChar=mystack.top();
            mystack.pop();
            FirstChar=mystack.top();
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
        std::cout<< "Expecting '^' but got "<<lex<<"\n";
        return false;
    }
}
/*
L() is a non-terminal function that calls it's non-terminal or terminal functions to obtain whether the value is syntactically or semanticaly correct.
 Syntax        Selection Set
 <L>::= <A>    {T, F,(}
    ::= ~<L>   {~}
 */
bool L(){
    std::string lex,output;
    lex=GetChar();
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
        std::cout<< "Expecting 'T,F,(,~' but got "<<lex<<"\n";
        return false;
    }
}
/*
 A() is a terminal function that determines if the terminal value we have recieved is defined by our language.
 Syntax        Selection Set
 <A>::= T      {T}
    ::= F      {F}
    ::=(<IT>)  {(}
 */
bool A(){
    std::string lex;
    lex=GetChar();
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
