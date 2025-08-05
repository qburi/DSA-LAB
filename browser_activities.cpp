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

int main() {
    Browser browser("google.com");

    browser.goToPage("bing.com");
    browser.goToPage("youtube.com");
    browser.goToPage("vtop.vit.ac.in");

    std::cout << browser.getCurrentPage() << "\n";
    browser.moveBackToPage();
    std::cout << browser.getCurrentPage() << "\n";
    browser.moveBackToPage();
    std::cout << browser.getCurrentPage() << "\n";
    browser.moveForwardToPage();
    std::cout << browser.getCurrentPage() << "\n";
    browser.goToPage("web.whatsapp.com");
    std::cout << browser.getCurrentPage() << "\n";
    browser.moveForwardToPage(); // No effect
    return 0;
}