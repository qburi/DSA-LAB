#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cmath> // For pow()
#include <cctype> // For isdigit()
#include <algorithm>

using namespace std;

int operatorPrecedence(char op) {
    unordered_map<char, int> opMap;
    opMap['^'] = 3;
    opMap['*'] = 2;
    opMap['/'] = 2;
    opMap['+'] = 1;
    opMap['-'] = 1;
    // Returns 0 if op is not found (e.g., for parentheses), which works for the logic.
    if (opMap.count(op)) {
        return opMap[op];
    }
    return 0;
}

string getReversePolish(const string& infix) {
    string postFix;
    stack<char> stk;

    for (int i = 0; i < infix.length(); i++) {
        char token = infix[i];

        // skip spaces
        if (isspace(token)) continue;

        if (isdigit(token)) {
            string number;
            while (i < infix.length() && isdigit(infix[i])) {
                number.push_back(infix[i]);
                i++;
            }

            // We currently don't know how infix[i] should be handled. If we don't decrement it, we will skip infix[i]
            i--; // Decrement i to offset the for-loop's increment

            postFix.append(number);
            postFix.push_back(' '); // Add space delimiter after the number
        }
        else if (token == '(') {
            stk.push(token);
        }
        else if (token == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postFix.push_back(stk.top());
                postFix.push_back(' ');
                stk.pop();
            }
            if (!stk.empty()) {
                stk.pop(); // Pop the opening parenthesis '('
            }
            else {
                cerr << "Mismatched parenthesis found" << endl;
                return ""; // we will handle this case in main function
            }
        }
        else if (string("+-*/^").find(token) != string::npos) {
            while (
                ! stk.empty() &&
                stk.top() != '(' &&
                (
                    // Pop if operator on stack has higher precedence
                    operatorPrecedence(stk.top()) > operatorPrecedence(token) ||
                    // OR if they have equal precedence AND the token is left-associative
                    (operatorPrecedence(stk.top()) == operatorPrecedence(token) && token != '^')
                )
                ){
                postFix.push_back(stk.top());
                postFix.push_back(' '); // add delimiter
                stk.pop();
            }
            stk.push(token);
        }
    }

    // Pop any remaining operators from the stack to the output string
    while (!stk.empty()) {
        postFix.push_back(stk.top());
        postFix.push_back(' ');
        stk.pop();
    }

    return postFix;
}

double getOperationResult(char op, double first, double second) {
    if (op == '+')
        return first + second;
    if (op == '-')
        return first - second;
    if (op == '*')
        return first * second;
    if (op == '/') {
        // Handle division by zero
        if (second == 0) {
            cerr << "Error: Division by zero." << endl;
            return 0;
        }
        return first / second;
    }
    if (op == '^')
        return pow(first, second);
    return 0.0;
}

double evaluateReversePolish(string postfix) {
    stack<double> stk;

    for (int i = 0; i < postfix.length(); ++i) {
        char token = postfix[i];

        // If the token is a digit, parse the full number
        if (isdigit(token)) {
            string number;
            while (i < postfix.length() && isdigit(postfix[i])) {
                number.push_back(postfix[i]);
                i++;
            }
            // i is now at the space after the number, loop will increment past it
            stk.push(stod(number)); // stod converts string to double
        }
        else if (string("+-*/^").find(token) != string::npos) {
            // Pop the two operands from the stack
            double firstPop = stk.top(); stk.pop();
            double secondPop = stk.top(); stk.pop();
            // Perform operation and push result back onto stack
            double res = getOperationResult(token, secondPop, firstPop);
            stk.push(res);
        }
        // we ignore spaces
    }

    if (stk.size() > 1) {
        cout << "Invalid format found. Try again" << endl;
        return INT_MIN;
    }

    // The final result is the last item on the stack
    return stk.top();
}

string getReversePolishForPolish(const string& infix) {
    string postFix;
    stack<char> stk;

    for (int i = 0; i < infix.length(); i++) {
        char token = infix[i];

        // skip spaces
        if (isspace(token)) continue;

        if (isdigit(token)) {
            string number;
            while (i < infix.length() && isdigit(infix[i])) {
                number.push_back(infix[i]);
                i++;
            }

            // We currently don't know how infix[i] should be handled. If we don't decrement it, we will skip infix[i]
            i--; // Decrement i to offset the for-loop's increment

            postFix.append(number);
            postFix.push_back(' '); // Add space delimiter after the number
        }
        else if (token == '(') {
            stk.push(token);
        }
        else if (token == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postFix.push_back(stk.top());
                postFix.push_back(' ');
                stk.pop();
            }
            if (!stk.empty()) {
                stk.pop(); // Pop the opening parenthesis '('
            }
            else {
                cerr << "Mismatched parenthesis found" << endl;
                return ""; // we will handle this case in main function
            }
        }
        else if (string("+-*/^").find(token) != string::npos) {
            while (
                ! stk.empty() &&
                stk.top() != '(' &&
                operatorPrecedence(stk.top()) >= operatorPrecedence(token)
                ){
                postFix.push_back(stk.top());
                postFix.push_back(' '); // add delimiter
                stk.pop();
            }
            stk.push(token);
        }
    }

    // Pop any remaining operators from the stack to the output string
    while (!stk.empty()) {
        postFix.push_back(stk.top());
        postFix.push_back(' ');
        stk.pop();
    }

    return postFix;
}

string getPolishExpression(const string& infix) {
    string prefix = infix;

    for (int i = 0; i < infix.length(); i++) {
        if (prefix[i] == '(') prefix[i] = ')';
        else if (prefix[i] == ')') prefix[i] = '(';
    }
    reverse(prefix.begin(), prefix.end());
    prefix = getReversePolishForPolish(prefix); // the only difference from the original function is that we remove
                                                // the right associativity of ^ for reversing.
    reverse(prefix.begin(), prefix.end());
    return prefix;
}

double evaluatePolishExpression(const string& prefix) {
    stack<double> stk;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        char token = prefix[i];
        if (isdigit(token)) {
            string number;
            while (i >= 0 && isdigit(prefix[i])) {
                number.push_back(prefix[i]);
                i--;
            }
            // we have definitely encountered a space here - since we added spaces explicitly in our prefix expression
            // therefore, it's safe to not decrement i
            reverse(number.begin(), number.end()); // single we are parsing right to left
            stk.push(stod(number));
        }
        else if (string("+*-/^").find(token) != string::npos) {
            double firstPop = stk.top(); stk.pop();
            double secondPop = stk.top(); stk.pop();
            stk.push(getOperationResult(token, firstPop, secondPop));
        }
        // ignore the spaces
    }

    if (stk.size() > 1) {
        cout << "Invalid format found. Try again" << endl;
        return INT_MIN;
    }

    return stk.top();
}


int main() {
    string infix;
    cout << "Enter an infix expression: " << endl;
    getline(cin, infix); // getline reads the entire line including spaces

    cout << "Enter one of the following options (1/2)" << endl;
    cout << "1. Convert to Polish Notation and evaluate" << endl;
    cout << "2. Convert to Reverse Polish Notation and evaluate" << endl;
    char option;
    cin >> option;
    double result;

    if (option == '1') {
        string prefix = getPolishExpression(infix);
        if (prefix.empty()) {
            cout << "Invalid format found. Try again" << endl;
            return 0;
        }
        cout << "Polish Notation expression: " << prefix << endl;
        result = evaluatePolishExpression(prefix);
        cout << "Result from Polish Notation expression: " << result << endl;
    }
    else if (option == '2') {
        string postfix = getReversePolish(infix);
        if (postfix.empty()) {
            cout << "Invalid format found. Try again" << endl;
            return 0;
        }
        cout << "Reverse Polish Notation expression: " << postfix << endl;

        result = evaluateReversePolish(postfix);
        cout << "Result from Reverse Polish Notation: " << result << endl;
    }
    else {
        cout << "Invalid option. Try again" << endl;
    }
    return 0;
}