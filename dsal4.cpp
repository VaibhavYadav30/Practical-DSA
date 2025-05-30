#include <iostream>
#include <climits>
using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int data){
        left = NULL;
        right = NULL;
        this->data = data;
    }
};

class Tree{
public:
    TreeNode *root;

    Tree(){
        root = NULL;
    }

    void insert(TreeNode *root, TreeNode *node);
    TreeNode *create();
    void PrintInorder(TreeNode *root);
    void search(TreeNode *root, int key);
    int longestPath(TreeNode *root);
    int MinInTree(TreeNode *root);
    void Mirror(TreeNode *root);

    int Max(int a, int b);
    int Min(int a, int b);
};

int Tree::Max(int a, int b)
{
    int max = (a > b) ? a : b;
    return max;
}

int Tree::Min(int a, int b)
{
    int min = (a < b) ? a : b;
    return min;
}

void Tree::insert(TreeNode *root, TreeNode *node)
{
    if (root == NULL)
    {
        return;
    }

    if (root->data > node->data)
    {
        if (root->left == NULL)
            root->left = node;
        else
        {
            insert(root->left, node);
            return;
        }
    }
    else
    {
        if (root->right == NULL)
            root->right = node;
        else
        {
            insert(root->right, node);
            return;
        }
    }
}

TreeNode* Tree::create()
{
    char ch;
    ch = 'y';
    do
    {
        cout << "Enter the data for the node: " << endl;
        int newdata;
        cin >> newdata;
        TreeNode *newNode = new TreeNode(newdata);

        if (root == NULL)
            root = newNode;

        else
        {
            insert(root, newNode);
        }

        cout << "Do you want to continue?(y|n) :  ";
        cin >> ch;
    } while (ch != 'n');

    return this->root;
}

void Tree::PrintInorder(TreeNode *root)
{
    if (root == NULL)
        return;

    PrintInorder(root->left);
    cout << root->data << " ";
    PrintInorder(root->right);
}

void Tree::search(TreeNode *root, int key)
{
    if (root == NULL)
    {
        cout << "key is not present\n";
        return;
    }

    if (key < root->data) search(root->left, key);
    else if (key > root->data)  search(root->right, key);
    else{
        cout << "key is present\n";
        return;
    }
}

int Tree::longestPath(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int leftPath = longestPath(root->left);
    int rightPath = longestPath(root->right);

    return Max(leftPath, rightPath) + 1;
}

int Tree::MinInTree(TreeNode *root)
{
    if (root == NULL)
        return INT_MAX;

    int smallestInLeft = MinInTree(root->left);
    int smallestInRight = MinInTree(root->right);

    return Min(root->data, Min(smallestInLeft, smallestInRight));
}

void Tree::Mirror(TreeNode *root)
{
    if (root == NULL)
        return;

    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    Mirror(root->left);
    Mirror(root->right);
}

int main()
{

    char ch;
    cout << "\nChoose : \n1. Create a tree \n2. Display Tree \n3. Search a value \n4. To find the number of nodes in the Longest Path \n5. To find Node with Minimum data \n6. To Mirror the Tree \n7 To stop \n";
    cin >> ch;
    TreeNode *root;
    Tree Mytree;
    while (ch != '7')
    {

        if (ch == '1')
        {
            root = Mytree.create();
        }
        else if (ch == '2')
        {
            Mytree.PrintInorder(root);
        }
        else if (ch == '3')
        {
            cout << "Enter the key that want to find in the Tree\n";
            int key;
            cin >> key;
            Mytree.search(root, key);
        }
        else if (ch == '4')
        {
            cout << Mytree.longestPath(root);
        }
        else if (ch == '5')
        {
            cout << Mytree.MinInTree(root);
        }
        else if (ch == '6')
        {
            Mytree.Mirror(root);
            Mytree.PrintInorder(root);
        }
        cout << "\nChoose : \n1. Create a tree \n2. Display Tree \n3. Search a value \n4. To find the number of nodes in the Longest Path \n5. To find Node with Minimum data \n6. To Mirror the Tree \n7 To stop \n";
        cin >> ch;
    }
    cout << "Thank You!!";
}

