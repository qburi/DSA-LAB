#include <bits/stdc++.h>

using namespace std;


class Browser {
    stack<string> backStack;
    stack<string> forwardStack;
    string currPage;
public:
    Browser(string firstPage) : currPage(firstPage) {}

    string getCurrentPage() {
        return ! currPage.empty() ? currPage : "No current page available";
    }

    void goToPage(const string& page) {
        backStack.push(currPage);
        currPage = page;
        while (! forwardStack.empty()) forwardStack.pop();
    }

    void moveForwardToPage() {
        if (forwardStack.empty()) {
            cout << "Forward Stack is empty. Can't move forward." << endl;
            return;
        }
        backStack.push(currPage);
        currPage = forwardStack.top(); forwardStack.pop();
    }

    void moveBackToPage() {
        if (backStack.empty()) {
            cout << "Back Stack is empty. Can't move back." << endl;
            return;
        }
        forwardStack.push(currPage);
        currPage = backStack.top(); backStack.pop();
    }
};

// --- Test Case 5: Emptying Stacks Completely ---
// This test involves navigating and then using the back button until the
// original page is reached and the back stack is empty.
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
