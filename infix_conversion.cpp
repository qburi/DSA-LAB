#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cmath> // For pow()
#include <cctype> // For isdigit()

using namespace std;

/**
 * @brief Determines the precedence of a mathematical operator.
 * @param op The operator character.
 * @return An integer representing the precedence level. Higher is more important.
 */
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
                ) {
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
            string number_str;
            while (i < postfix.length() && isdigit(postfix[i])) {
                number_str.push_back(postfix[i]);
                i++;
            }
            // i is now at the space after the number, loop will increment past it
            stk.push(stod(number_str)); // stod converts string to double
        }
        else if (string("+-*/^").find(token) != string::npos) {
            // Pop the two operands from the stack
            double firstPop = stk.top(); stk.pop();
            double secondPop = stk.top(); stk.pop();

            // Perform operation and push result back onto stack
            double res = getOperationResult(token, firstPop, secondPop);
            stk.push(res);
        }
        // we ignore spaces
    }
    // The final result is the last item on the stack
    return stk.top();
}


int main() {
    string infix;
    cout << "Enter an infix expression: " << endl;
    getline(cin, infix); // getline reads the entire line including spaces

    string postfix = getReversePolish(infix);
    if (postfix.empty()) {
        cout << "Invalid format found. Try again" << endl;
        return 0;
    }
    cout << "Postfix expression: " << postfix << endl;

    double result = evaluateReversePolish(postfix);
    cout << "Result: " << result << endl;

    return 0;
}