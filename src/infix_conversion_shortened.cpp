#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Stack {
public:
    int ptr;
    T* stk;
    int SIZE;
    Stack() {
        SIZE = 1000;
        ptr = -1;
        stk = new T[SIZE];
    }

    Stack(int SIZE) {
        this->SIZE = SIZE;
        ptr = -1;
        stk = new T[SIZE];
    }

    ~Stack() {
        delete[] stk;
    }

    void push(T x) {
        if (isFull()) {
            cout << "Stack Overflow." << endl;
            return;
        }
        stk[++ptr] = x;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return;
        }
        ptr--;
    }

    bool isFull() {
        return ptr == SIZE - 1;
    }

    bool isEmpty() {
        return ptr == -1;
    }

    T peek() {
        if (isEmpty()) {
            cout << "Stack is empty. Can't peek" << endl;
            return T();
        }
        return stk[ptr];
    }

    int size() {
        return ptr + 1;
    }
};


int getOperatorPrecedence(char op) {
    unordered_map<char, int> opMap{
        {'^', 3},
        {'/', 2},
        {'*', 2},
        {'-', 1},
        {'+', 1}
    };
    if (opMap.count(op)) {
        return opMap[op];
    }
    return 0; // incorrect infix expression
}

double getOperationResult(char token, double first, double second) {
    if (token == '+') return first + second;
    if (token == '-') return first - second;
    if (token == '*') return first * second;
    if (token == '/') return first / second;
    if (token == '^') return pow(first, second);
    return INT_MIN;
}

string getReversePolish(const string& infix) {
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

            i--; // we don't know how to handle infix[i] -> leave it for the next iteration
            postfix.append(number);
            postfix.push_back(' ');
        }
        else if (token == '(') {
            stk.push('(');
        }
        else if (token == ')') {
            while (! stk.isEmpty() && stk.peek() != '(') {
                postfix.push_back(stk.peek());
                postfix.push_back(' '); // pad with space
                stk.pop();
            }
            if (! stk.isEmpty() && stk.peek() == '(') {
                stk.pop();
            }
            else {
                cout << "Invalid infix found.";
                return "";
            }
        }
        else {
            // operator confirmed
            // we have to push the operator to the stack
            while (! stk.isEmpty() && stk.peek() != '('
                && (
                    getOperatorPrecedence(stk.peek()) >= getOperatorPrecedence(token) && token != '^'
                    )) {
                postfix.push_back(stk.peek());
                postfix.push_back(' ');
                stk.pop();

            }
            stk.push(token);
        }
    }
    while (! stk.isEmpty()) {
        postfix.push_back(stk.peek());
        postfix.push_back(' ');
        stk.pop();
    }
    return postfix;
}


double getReversePolishResult(string postfix) {
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
            // ignore space
            stk.push(stod(number));
        }
        else if (string("*-+/^").find(token) != string::npos) {
            double firstPop = stk.peek(); stk.pop();
            double secondPop = stk.peek(); stk.pop();
            double result = getOperationResult(token, secondPop, firstPop);
            stk.push(result);
        }
    }
    if (stk.size() > 1) {
        cout << "Error in postfix expression";
        return INT_MIN;
    }
    return stk.peek();
}


string getPolishNotation(const string& infixMain) {
    string prefix;
    string infix = infixMain;
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

            i--; // we don't know how to handle infix[i] -> leave it for the next iteration
            reverse(number.begin(), number.end());
            prefix.append(number);
            prefix.push_back(' ');
        }
        else if (token == ')') {
            stk.push(')');
        }
        else if (token == '(') {
            while (!stk.isEmpty() && stk.peek() != ')') {
                prefix.push_back(stk.peek());
                prefix.push_back(' '); // pad with space
                stk.pop();
            }
            if (!stk.isEmpty() && stk.peek() == ')') {
                stk.pop();
            }
            else {
                cout << "Invalid infix found.";
                return "";
            }
        }
        else {
            // operator confirmed
            // we have to push the operator to the stack
            while (!stk.isEmpty() && stk.peek() != ')'
                && (
                    (
                        getOperatorPrecedence(stk.peek()) > getOperatorPrecedence(token)
                    ) ||
                    (
                        getOperatorPrecedence(stk.peek()) == getOperatorPrecedence(token) && token == '^'
                    )
                    )) {
                prefix.push_back(stk.peek());
                prefix.push_back(' ');
                stk.pop();

            }
            stk.push(token);
        }
    }
    while (!stk.isEmpty()) {
        prefix.push_back(stk.peek());
        prefix.push_back(' ');
        stk.pop();
    }

    string result;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char token = prefix[i];
        if (isdigit(token)) {
            string number;
            while (i >= 0 && isdigit(prefix[i])) {
                number.push_back(prefix[i]);
                i--;
            }
            // currently i points to space which we omit
            reverse(number.begin(), number.end());
            result.append(number);
            result.push_back(' ');
        }
        else if (string("*^/+-").find(token) != string::npos) {
            result.push_back(token);
            result.push_back(' ');
        }
    }

    return result;
}

double evaluatePolish(string prefix) {
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
            // i points to space which we ignore
            reverse(number.begin(), number.end());
            stk.push(stod(number));
        }
        else {
            // operator confirmed
            double firstPop = stk.peek(); stk.pop();
            double secondPop = stk.peek(); stk.pop();
            double operationResult = getOperationResult(token, firstPop, secondPop);
            stk.push(operationResult);
        }

    }

    if (stk.size() > 1) {
        cout << "Invalid prefix" << endl;
        return INT_MIN;
    }
    return stk.peek();
}

int main() {
    string infix = "75 / 5 * 2 - 4 ^ 2 / 2";
    string prefix = getPolishNotation(infix);
    cout << prefix << endl;
    cout << evaluatePolish(prefix) << endl;

    cout << endl;
    cout << "postfix: ";
    string postfix = getReversePolish(infix);
    cout << postfix << endl;
    cout << getReversePolishResult(postfix) << endl;
    return 0;
}