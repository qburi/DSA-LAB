#include <bits/stdc++.h>


using namespace std;

template<typename T>
class Stack {
public:
    int ptr;
    T *arr;
    int SIZE;

    Stack() {
        SIZE = 100;
        arr = new T[SIZE];
        ptr = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool isEmpty() {
        return ptr == -1;
    }

    bool isFull() {
        return ptr == SIZE - 1;
    }

    int size() {
        return ptr + 1;
    }

    void push(T x) {
        if (isFull()) {
            cout << "Cannot push" << endl;
            return;
        }
        arr[++ptr] = x;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Cannot pop" << endl;
            return;
        }
        ptr--;
    }

    T peek() {
        if (isEmpty()) {
            cout << "Cannot peek" << endl;
            return T();
        }
        return arr[ptr];
    }
};


int getOperatorPrecedence(char op) {
    unordered_map<char, int> opMap{
        {'^', 3},
        {'/', 2},
        {'*', 2},
        {'+', 1},
        {'-', 1}
    };
    if (opMap.count(op)) {
        return opMap[op];
    }
    return 0; // incorrect infix
}


double getOperationResult(char token, double first, double second) {
    if (token == '^') return pow(first, second);
    if (token == '/') return first / second;
    if (token == '*') return first * second;
    if (token == '+') return first + second;
    if (token == '-') return first - second;
    return 0;
}

string getReversePolish(const string &infix) {
    string postfix;
    Stack<char> stk;

    for (int i = 0; i < infix.length(); i++) {
        char token = infix[i];
        if (isspace(token)) continue;
        if (isdigit(token)) {
            string number;
            while (i < infix.length() && isdigit(infix[i])) {
                number.push_back(infix[i]);
                i++;
            }
            i--; // we don't know how to handl the next character;
            postfix.append(number);
            postfix.push_back(' ');
        }
        else if (token == '(') {
            stk.push(token);
        }
        else if (token == ')') {
            while (! stk.isEmpty() && stk.peek() != '(') {
                postfix.push_back(stk.peek());
                postfix.push_back(' ');
                stk.pop();
            }
            if (! stk.isEmpty() && stk.peek() == '(') {
                stk.pop();
            }
            else {
                cout << "Incorrect infix" << endl;
                return "";
            }
        }
        else if (string("*/^-+").find(token) != string::npos) {
            while (! stk.isEmpty() && stk.peek() != '(' && getOperatorPrecedence(stk.peek()) >= getOperatorPrecedence(token) && token != '^') {
                postfix.push_back(stk.peek());
                postfix.push_back(' ');
                stk.pop();
            }
            stk.push(token);
        }
    }

    while (! stk.isEmpty()) {
        postfix.push_back(stk.peek()); stk.pop();
        postfix.push_back(' ');
    }

    return postfix;
}


double evaluateReversePolish(string postfix) {
    Stack<double> stk;
    for (int i = 0; i < postfix.length(); i++) {
        char token = postfix[i];
        if (isspace(token)) continue;
        if (isdigit(token)) {
            string number;
            while (i < postfix.length() && isdigit(postfix[i])) {
                number.push_back(postfix[i]);
                i++;
            }
            // we know i is a space and we ignore it
            stk.push(stod(number));
        }
        else {
            // operator confirmed
            double firstPop = stk.peek(); stk.pop();
            double secondPop = stk.peek(); stk.pop();
            double result = getOperationResult(token, secondPop, firstPop);
            stk.push(result);
        }
    }
    if (stk.size() > 1) {
        cout << "Error in postfix" << endl;
        return INT_MIN;
    }
    return stk.peek();
}

string getPolishExpression(string infix) {
    string prefix;
    reverse(infix.begin(), infix.end());
    Stack<char> stk;

    for (int i = 0; i < infix.length(); i++) {
        char token = infix[i];
        if (isspace(token)) continue;
        if (isdigit(token)) {
            string number;
            while (i < infix.length() && isdigit(infix[i])) {
                number.push_back(infix[i]);
                i++;
            }
            i--; // we don't know how to handle the next character;
            prefix.append(number);
            prefix.push_back(' ');
        }
        else if (token == ')') {
            stk.push(token);
        }
        else if (token == '(') {
            while (! stk.isEmpty() && stk.peek() != ')') {
                prefix.push_back(stk.peek());
                prefix.push_back(' ');
                stk.pop();
            }
            if (! stk.isEmpty() && stk.peek() == ')') {
                stk.pop();
            }
            else {
                cout << "Incorrect infix" << endl;
                return "";
            }
        }
        else if (string("*/^-+").find(token) != string::npos) {
            while (! stk.isEmpty() && stk.peek() != ')' && (
                (getOperatorPrecedence(stk.peek()) > getOperatorPrecedence(token) && token != '^')
                    || (token == '^' && getOperatorPrecedence(stk.peek()) == getOperatorPrecedence(token))
                    )
            ) {
                prefix.push_back(stk.peek());
                prefix.push_back(' ');
                stk.pop();
            }
            stk.push(token);
        }
    }

    while (! stk.isEmpty()) {
        prefix.push_back(stk.peek()); stk.pop();
        prefix.push_back(' ');
    }

    reverse(prefix.begin(), prefix.end());

    return prefix;
}


double evaluatePolishExpression(string prefix) {
    Stack<double> stk;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        char token = prefix[i];
        if (isspace(token)) continue;
        if (isdigit(token)) {
            string number;
            while (i >= 0 && isdigit(prefix[i])) {
                number.push_back(prefix[i]);
                i--;
            }
            // we won't increment the value of i because we know it's a space
            reverse(number.begin(), number.end());
            stk.push(stod(number));
        }
        else {
            double firstPop = stk.peek(); stk.pop();
            double secondPop = stk.peek(); stk.pop();
            double result = getOperationResult(token, firstPop, secondPop);
            stk.push(result);
        }
    }

    if (stk.size() > 1) {
        cout << "Invalid infix lmao" << endl;
        return INT_MIN;
    }
    return stk.peek();
}



int main() {
    string infix = "( ( 60 - 15 ) / ( 3 + 2^2 ) ) * 4";
    string postfix = getReversePolish(infix);
    cout << postfix << endl;
    double postfixEvaluation = evaluateReversePolish(postfix);
    cout << postfixEvaluation << endl;
    cout << "Prefix: ";
    string prefix = getPolishExpression(infix);
    cout << prefix << endl;
    cout << evaluatePolishExpression(prefix) << endl;
    return 0;
}
