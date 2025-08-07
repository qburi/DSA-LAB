#include <bits/stdc++.h>

using namespace std;


template <typename A>
class Stack {
public:
    int SIZE;
    A* stk;
    int ptr = -1;

    Stack(int n) {
        SIZE = n;
        stk = new A[SIZE];
    }

    Stack () {
        SIZE = 1000;
        stk = new A[SIZE];
        ptr = -1;
    }

    ~Stack() {
        delete[] stk;
    }

    void push(A x) {
        if (isFull()) {
            cout << "Stack Overflow" << endl;
        } else {
            stk[++ptr] = x;
        }
    }

    void pop() {
        if (isEmpty()) cout << "Underflow" << endl;
        else ptr--;
    }

    A peek() {
        if (isEmpty()) return A();
        return stk[ptr];
    }

    bool isEmpty() {
        return ptr == -1;
    }

    bool isFull() {
        return ptr == SIZE - 1;
    }
};

class Browser {
    Stack<string> backStack;
    Stack<string> forwardStack;
    string currPage;
public:
    Browser(string firstPage) : currPage(firstPage) {}

    string getCurrentPage() {
        return ! currPage.empty() ? currPage : "No current page available";
    }

    void goToPage(const string& page) {
        backStack.push(currPage);
        currPage = page;
        while (! forwardStack.isEmpty()) forwardStack.pop();
    }

    void moveForwardToPage() {
        if (forwardStack.isEmpty()) {
            cout << "Forward Stack is empty. Can't move forward." << endl;
            return;
        }
        backStack.push(currPage);
        currPage = forwardStack.peek(); forwardStack.pop();
    }

    void moveBackToPage() {
        if (backStack.isEmpty()) {
            cout << "Back Stack is empty. Can't move back." << endl;
            return;
        }
        forwardStack.push(currPage);
        currPage = backStack.peek(); backStack.pop();
    }
};
int main() {
    cout << "--- Test Case 5: Emptying Stacks Completely ---" << endl;
    Browser browser("Start.com");
    browser.goToPage("Middle.com");
    browser.goToPage("End.com");

    cout << "Current Page: " << browser.getCurrentPage() << endl; // End.com

    cout << "Moving all the way back..." << endl;
    browser.moveBackToPage(); // -> Middle.com
    cout << "Current Page: " << browser.getCurrentPage() << endl;
    browser.moveBackToPage(); // -> Start.com
    cout << "Current Page: " << browser.getCurrentPage() << endl;

    // Back stack should now be empty.
    browser.moveBackToPage(); // Should print "Back Stack is empty."

    cout << "Moving all the way forward..." << endl;
    browser.moveForwardToPage(); // -> Middle.com
    cout << "Current Page: " << browser.getCurrentPage() << endl;
    browser.moveForwardToPage(); // -> End.com
    cout << "Current Page: " << browser.getCurrentPage() << endl;

    // Forward stack should now be empty.
    browser.moveForwardToPage(); // Should print "Forward Stack is empty."
    return 0;
}

