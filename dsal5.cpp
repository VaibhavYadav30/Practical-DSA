#include <iostream>
#include <cstring> // Use <cstring> instead of <string.h>
using namespace std;

struct node {
    char data;
    node *left, *right;
};

class tree {
    char prefix[20];

public:
    node *top;
    tree() { top = nullptr; }
    void expression(char[]);
    void preorder(node *);
    void inorder(node *);
    void non_rec_postorder(node *);
    void del(node *&);
};

// Stack implementation for expression tree
class stack1 {
    node *data[30];
    int top;

public:
    stack1() { top = -1; }

    bool empty() { return (top == -1); }

    void push(node *p) { data[++top] = p; }

    node *pop() { return (empty() ? nullptr : data[top--]); }
};

// Function to construct expression tree from prefix expression
void tree::expression(char prefix[]) {
    stack1 s;
    node *t1, *t2;
    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) {
        top = new node;
        top->left = nullptr;
        top->right = nullptr;
        top->data = prefix[i];

        if (isalpha(prefix[i])) {  // If operand, push into stack
            s.push(top);
        } else if (prefix[i] == '+' || prefix[i] == '*' || prefix[i] == '-' || prefix[i] == '/') {  // If operator
            t1 = s.pop();
            t2 = s.pop();
            top->left = t1;
            top->right = t2;
            s.push(top);
        }
    }
    top = s.pop(); // Final root node
}

// Preorder Traversal
void tree::preorder(node *root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Inorder Traversal
void tree::inorder(node *root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Non-recursive postorder traversal
void tree::non_rec_postorder(node *top) {
    if (!top) return;

    stack1 s1, s2;
    node *T = top;
    cout << "\nPostorder Traversal: ";

    s1.push(T);
    while (!s1.empty()) {
        T = s1.pop();
        s2.push(T);
        if (T->left) s1.push(T->left);
        if (T->right) s1.push(T->right);
    }

    while (!s2.empty()) {
        top = s2.pop();
        cout << top->data << " ";
    }
    cout << endl;
}

// Function to delete the tree
void tree::del(node *&node) {
    if (!node) return;

    del(node->left);
    del(node->right);
    
    cout << "Deleting node: " << node->data << endl;
    delete node;
    node = nullptr;
}

int main() {
    tree t;
    int choice;
    char expr[20];
    
    do {
        cout << "\nMenu:";
        cout << "\n1. Enter Prefix Expression";
        cout << "\n2. Construct Expression Tree";
        cout << "\n3. Display Tree (Preorder & Inorder)";
        cout << "\n4. Postorder Traversal";
        cout << "\n5. Delete Tree";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter prefix Expression: ";
                cin >> expr;
                break;
            case 2:
                t.expression(expr);
                cout << "Expression tree constructed successfully!" << endl;
                break;
            case 3:
                if (t.top) {
                    cout << "\nPreorder traversal: ";
                    t.preorder(t.top);
                    cout << "\nInorder traversal: ";
                    t.inorder(t.top);
                    cout << endl;
                } else {
                    cout << "Tree does not exist!" << endl;
                }
                break;
            case 4:
                t.non_rec_postorder(t.top);
                break;
            case 5:
                t.del(t.top);
                if (!t.top)
                    cout << "Tree deleted successfully!" << endl;
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}


