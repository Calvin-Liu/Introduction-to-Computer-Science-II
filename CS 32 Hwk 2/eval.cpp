//
//  File.cpp
//  CS 32 Hwk 2
//
//  Created by Calvin Liu on 2/3/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <cctype>

using namespace std;

int precedence(char x)
{
    switch(x)
    {
        case '!':
            return 3;
            break;
        case '&':
            return 2;
            break;
        case '|':
            return 1;
            break;
    }
    return -1;
}

// Evaluates a boolean expression
// Precondition: infix is an infix boolean expression consisting of
//   the digits 0 through 9, the operators |, &, and !, and parentheses,
//   with embedded blanks allowed for readability.
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression, result is set to the value of the expression (where
//   each digit k represents element k of the values array), and
//   the function returns zero.  If infix is not a syntactically
//   valid expression, the function returns 1.  (In that case,
//   postfix may or may not be changed, but result must be unchanged.)

int evaluate(const string& infix, const bool values[], string& postfix, bool& result)
{
    string nospaceinfix = "";
    for(int k = 0; k < infix.size(); k++)
    {
        char c = infix[k];
        if(c != ' ')
        {
            nospaceinfix += c;
        }
    }
    if(nospaceinfix == "")
    {
        return 1;
    }
    
    for(int j = 0; j < nospaceinfix.size(); j++)
    {
        char ch = nospaceinfix[j];
        if(nospaceinfix[0] == '&' || nospaceinfix[0] == '|')
        {
            return 1;
        }
        if(nospaceinfix[nospaceinfix.size()-1] == '&' || nospaceinfix[nospaceinfix.size()-1] == '|')
        {
            return 1;
        }
        //Operator is at the end or the beginning? WRONG
        if(ch == '&' || ch == '|')
        {
            if(!isdigit(nospaceinfix[j-1]))
            {
                return 1;
            }
        }
        //Operator, Operator? WRONG
        if(nospaceinfix[nospaceinfix.size()-1] == '!')
        {
            return 1;
        }
        //'!' at the end? WRONG
        if(isdigit(ch))
        {
            if(isdigit(nospaceinfix[j-1]))
            {
                return 1;
            }
        }
        if(ch == '(')
        {
            for(int i = j; i < nospaceinfix.size(); i++)
            {
                if(nospaceinfix[i] != ')')              //3&6(
                {                                   //(3!5&6
                    if(i == nospaceinfix.size())
                    {
                        return 1;
                    }
                }
            }
        }
    }
//////////////////////////////DONE CHECKING TO SEE IF IT IS VALID/////////////////////
    
    postfix = "";
    stack <char> stackOfChar;       //initialize the stack to be empty
    for(int k = 0; k < nospaceinfix.size(); k++)
    {
        switch(nospaceinfix[k])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                postfix += nospaceinfix[k];
                break;
            case '(':
                stackOfChar.push(nospaceinfix[k]);
                break;
            case ')':
                if(postfix.empty())
                {
                    return 1;
                }
                while(stackOfChar.top() != '(')
                {
                    postfix += stackOfChar.top();
                    stackOfChar.pop();
                    if(stackOfChar.empty())
                    {
                        return 1;
                    }
                }
                stackOfChar.pop();
                break;
            case '!':
                stackOfChar.push(nospaceinfix[k]);
                break; //just added
            case '&':
            case '|':
                while(!stackOfChar.empty() && stackOfChar.top() != '(' && (precedence(nospaceinfix[k]) <= precedence(stackOfChar.top())))
                {
                    postfix += stackOfChar.top();
                    stackOfChar.pop();
                }
                stackOfChar.push(nospaceinfix[k]);
                break;
        }
    }
    while(!stackOfChar.empty())
    {
        if(stackOfChar.top() == '(')
        {
            return 1;
        }
        postfix += stackOfChar.top();
        stackOfChar.pop();
    }
    
  //////////////////////////////EVALUATION///////////////////////////////////
    stack <bool> stackOfBool;
    for(int k = 0; k < postfix.size();k++)
    {
        if(isdigit(postfix[k]))
        {
            int number = postfix[k] - '0';
            stackOfBool.push(values[number]);
        }
        else
        {
            if(stackOfBool.empty())
            {
                return 1;
            }
            
            bool thisResult;
            if(postfix[k] == '!')
            {
                if(stackOfBool.size() < 1)
                {
                    return 1;
                }
                bool exclamation = stackOfBool.top();
                stackOfBool.pop();
                thisResult = !exclamation;
            }
            
            if(postfix[k] == '&')
            {
                if(stackOfBool.size() < 2)
                {
                    return 1;
                }
                bool operand2 = stackOfBool.top();
                stackOfBool.pop();
                bool operand1 = stackOfBool.top();
                stackOfBool.pop();
                thisResult = operand1 && operand2;
            }
            
            if(postfix[k] == '|')
            {
                if(stackOfBool.size() < 2)
                {
                    return 1;
                }
                bool operand2 = stackOfBool.top();
                stackOfBool.pop();
                bool operand1 = stackOfBool.top();
                stackOfBool.pop();
                thisResult = operand1 || operand2;
            }
            stackOfBool.push(thisResult);
        }
    }
    if(stackOfBool.size() != 1)
    {
        return 1;
    }
    result = stackOfBool.top();
    return 0;
}

/*
int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
           &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("(()))))))", ba, pf, answer) == 1);
    assert(evaluate(")))((((", ba, pf, answer) == 1);
    assert(evaluate("((((((((())", ba, pf, answer) == 1);
    assert(evaluate("*", ba, pf, answer) == 1);
    assert(evaluate("X", ba, pf, answer) == 1);
    assert(evaluate("&", ba, pf, answer) == 1);
    assert(evaluate("!", ba, pf, answer) == 1);
    assert(evaluate("34", ba, pf, answer) == 1);
    assert(evaluate("!5&6&9", ba, pf, answer) == 0);
    assert(evaluate("(1)", ba, pf, answer) == 0);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("3&|4", ba, pf, answer) == 1);
    assert(evaluate("(3&|4", ba, pf, answer) == 1);
    assert(evaluate("3&|)4)", ba, pf, answer) == 1);
    assert(evaluate("3&|4", ba, pf, answer) == 1);
    assert(evaluate("!!!!!!4", ba, pf, answer) == 0);
    assert(evaluate("!!!!!", ba, pf, answer) == 1);
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}
*/