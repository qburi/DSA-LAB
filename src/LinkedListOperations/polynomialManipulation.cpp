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

PolynomialNode* add(PolynomialNode* p1, PolynomialNode* p2) {
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


PolynomialNode* subtract(PolynomialNode* p1, PolynomialNode* p2) {
    PolynomialNode* p2Head = new PolynomialNode();
    PolynomialNode* p2Tail = p2Head;
    while (p2 != nullptr) {
        p2Tail->next = new PolynomialNode(p2->coefficient * -1, p2->exp, nullptr);
        p2Tail = p2Tail->next;
        p2 = p2->next;
    }
    PolynomialNode* result = add(p1, p2Head->next);
    deletePolynomial(p2Head);
    return result;
}

PolynomialNode* multiplyOneTerm(PolynomialNode* p1, PolynomialNode* p2) {
    // we perform p1 node multiplication on p2
    PolynomialNode* result = new PolynomialNode();
    while (p2 != nullptr) {
        PolynomialNode* newNode = new PolynomialNode(p1->coefficient * p2->coefficient, p1->exp + p2->exp, nullptr);
        result = add(result, newNode);
        deletePolynomial(newNode);
        p2 = p2->next;
    }
    return result;
}

PolynomialNode* multiply(PolynomialNode* p1, PolynomialNode* p2) {
    PolynomialNode* result = new PolynomialNode(0, 0, nullptr);

    while (p1 != nullptr) {
        PolynomialNode* oneTerm = multiplyOneTerm(p1, p2);
        result = add(result, oneTerm);
        deletePolynomial(oneTerm);
        p1 = p1->next;
    }

    return result;
}
int main() {
    PolynomialNode* p1 = new PolynomialNode(1, 1);
    p1->next = new PolynomialNode(2, 2);
    p1->next->next = new PolynomialNode(3, 3);

    PolynomialNode* p2 = new PolynomialNode(1, 1);
    p2->next = new PolynomialNode(2, 2);
    p2->next->next = new PolynomialNode(3, 4);

    // PolynomialNode* addition = addTwoPolynomials(p1, p2);
    PolynomialNode* multiplication = multiply(p1, p2);
    printPolynomial(multiplication);



    deletePolynomial(p1);
    deletePolynomial(p2);
    // deletePolynomial(addition);
    // deletePolynomial(subtraction);
    deletePolynomial(multiplication);
    return 0;
}