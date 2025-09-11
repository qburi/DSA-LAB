#include <bits/stdc++.h>

using namespace std;

struct PolynomialNode {
    int exp;
    int coefficient;
    PolynomialNode* next;
    PolynomialNode(int coefficient, int exp, PolynomialNode* next) : exp(exp), coefficient(coefficient), next(next) {}
    PolynomialNode(int coefficient, int exp) : exp(exp), coefficient(coefficient), next(nullptr) {}
    PolynomialNode() : exp(0), coefficient(0), next(nullptr) {}
};

void printPolynomial(PolynomialNode* head) {
    while (head != nullptr) {
        if (head->next != nullptr)
            cout << head->coefficient << "x^" << head->exp << " + ";
        else cout << head->coefficient << "x^" << head->exp << " ";
        head = head->next;
    }
    cout << endl;
}

void deletePolynomial(PolynomialNode*& node) {
    while (node != nullptr) {
        PolynomialNode* temp = node;
        node = node->next;
        delete temp;
    }
    node = nullptr;
}

PolynomialNode* addTwoPolynomials(PolynomialNode* p1, PolynomialNode* p2) {
    PolynomialNode* ans = new PolynomialNode();
    PolynomialNode* tail = ans;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->exp == p2->exp) {
            int sum_coeff = p1->coefficient + p2->coefficient;
            // Only create a new node if the resulting coefficient is not zero
            if (sum_coeff != 0) {
                tail->next = new PolynomialNode(sum_coeff, p1->exp);
                tail = tail->next;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exp < p2->exp) {
            tail->next = new PolynomialNode(p1->coefficient, p1->exp);
            tail = tail->next;
            p1 = p1->next;
        }
        else if  (p2->exp < p1->exp) {
            tail->next = new PolynomialNode(p2->coefficient, p2->exp);
            tail = tail->next;
            p2 = p2->next;
        }

    }

    while (p1 != nullptr) {
        tail->next = new PolynomialNode(p1->coefficient, p1->exp);
        tail = tail->next;
        p1 = p1->next;
    }
    while (p2 != nullptr) {
        tail->next = new PolynomialNode(p2->coefficient, p2->exp);
        tail = tail->next;
        p2 = p2->next;

    }
    return ans->next;
}

int main() {
    PolynomialNode* p1 = new PolynomialNode(1, 1);
    p1->next = new PolynomialNode(2, 2);
    p1->next->next = new PolynomialNode(3, 3);

    PolynomialNode* p2 = new PolynomialNode(1, 1);
    p2->next = new PolynomialNode(2, 2);
    p2->next->next = new PolynomialNode(3, 3);

    PolynomialNode* addition = addTwoPolynomials(p1, p2);
    printPolynomial(addition);



    deletePolynomial(p1);
    deletePolynomial(p2);
    deletePolynomial(addition);
    return 0;
}