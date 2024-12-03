#include <iostream>
using namespace std;

class polynode {
    friend class polylist;
    int co;
    int ex;
    polynode *next;
};

class polylist {
    polynode *first;
    polynode *last;

public:
    polylist();
    ~polylist();
    void enter_in_last(int c, int e);
    void disply() const; // Mark as const since it doesn't modify the object.
    polylist add(const polylist &b) const; // Mark as const since it doesn't modify `this`.
};

polylist::polylist() {
    first = last = nullptr;
}

polylist::~polylist() {
    polynode *temp;
    while (first) {
        temp = first;
        first = first->next;
        delete temp;
    }
}

void polylist::enter_in_last(int c, int e) {
    polynode *curptr = new polynode;
    curptr->co = c;
    curptr->ex = e;
    curptr->next = nullptr;
    if (first == nullptr) {
        first = curptr;
    } else {
        last->next = curptr;
    }
    last = curptr;
}

void polylist::disply() const {
    polynode *curptr = first;
    if (!curptr) {
        cout << "0" << endl; // Print 0 if the list is empty.
        return;
    }

    bool isFirst = true;
    while (curptr) {
        if (!isFirst && curptr->co > 0)
            cout << "+"; // Add '+' for positive terms after the first term.

        if (curptr->ex == 0)
            cout << curptr->co; // Constant term.
        else if (curptr->ex == 1)
            cout << curptr->co << "x"; // Linear term.
        else
            cout << curptr->co << "x^" << curptr->ex; // General term.

        isFirst = false;
        curptr = curptr->next;
    }
    cout << endl;
}

polylist polylist::add(const polylist &b) const {
    polylist result;
    polynode *curA = first;
    polynode *curB = b.first;

    while (curA && curB) {
        if (curA->ex == curB->ex) {
            int sum = curA->co + curB->co;
            if (sum != 0)
                result.enter_in_last(sum, curA->ex);
            curA = curA->next;
            curB = curB->next;
        } else if (curA->ex < curB->ex) {
            result.enter_in_last(curA->co, curA->ex);
            curA = curA->next;
        } else {
            result.enter_in_last(curB->co, curB->ex);
            curB = curB->next;
        }
    }

    // Add remaining terms from `this`.
    while (curA) {
        result.enter_in_last(curA->co, curA->ex);
        curA = curA->next;
    }

    // Add remaining terms from `b`.
    while (curB) {
        result.enter_in_last(curB->co, curB->ex);
        curB = curB->next;
    }

    return result;
}
int main() {
    polylist a, b, result;
    int ca, ea, cb, eb, n, m;
    cout<<"++++++++++For adding tow Sparse polynomials: +++++++++"<<"\n";
    cout << "Please enter the number of terms for polynomial A: ";
    cin >> n;
    cout << "Enter the coefficient and exponent of each term (starting with the lowest exponent): ";
    for (int i = 0; i < n; i++) {
        cin >> ca >> ea;
        a.enter_in_last(ca, ea);
    }

    cout << "Please enter the number of terms for polynomial B: ";
    cin >> m;
    cout << "Enter the coefficient and exponent of each term (starting with the lowest exponent): ";
    for (int i = 0; i < m; i++) {
        cin >> cb >> eb;
        b.enter_in_last(cb, eb);
    }

    // Add the two polynomials.
    result = a.add(b);

    cout << "The resulting polynomial after addition is: ";
    result.disply();

    return 0;
}

