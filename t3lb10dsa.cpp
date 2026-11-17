#include <iostream>
using namespace std;
// one microservice in the BST
struct Node {
    int serviceID;
    int cost;
    Node* left;
    Node* right;
};
int B;   // target budget
//bst insert
Node* insert(Node* root, int id, int cost) {
    if (root == NULL) {
        Node* n = new Node;
        n->serviceID = id;
        n->cost = cost;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    if (cost < root->cost)
        root->left = insert(root->left, id, cost);
    else
        root->right = insert(root->right, id, cost);
    return root;
}
//PART A
Node* path[50];     // the current path (works like a stack)
int pathSize = 0;
int foundA = 0;
void findPaths(Node* node) {
    if (node == NULL) return;
    // push: add this node to the path
    path[pathSize] = node;
    pathSize++;
    // check every path that ends at this node (start from any node above it)
    int sum = 0;
    for (int i = pathSize - 1; i >= 0; i--) {
        sum += path[i]->cost;
        if (sum == B) {
            foundA++;
            cout << foundA << ") ";
            for (int j = i; j < pathSize; j++) {
                cout << path[j]->serviceID << "(" << path[j]->cost << ")";
                if (j < pathSize - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
    findPaths(node->left);
    findPaths(node->right);
    // pop: remove this node (backtrack)
    pathSize--;
}
//PART B
int sortedID[50];     // nodes in increasing cost order
int sortedCost[50];
int total = 0;
int chosen[50];       // positions of the nodes we picked
int chosenSize = 0;
int foundB = 0;
// inorder on a BST gives the costs from smallest to largest
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    sortedID[total] = root->serviceID;
    sortedCost[total] = root->cost;
    total++;
    inorder(root->right);
}
void subsets(int start, int sum) {
    // found a subset with the exact budget
    if (sum == B && chosenSize > 0) {
        foundB++;
        cout << foundB << ") ";
        for (int i = 0; i < chosenSize; i++)
            cout << sortedID[chosen[i]] << "(" << sortedCost[chosen[i]] << ") ";
        cout << endl;
    }
    for (int i = start; i < total; i++) {
        // prune: costs are sorted, so everything after this is even bigger
        if (sum + sortedCost[i] > B) break;17
        
        chosen[chosenSize] = i;      // choose
        chosenSize++;
        subsets(i + 1, sum + sortedCost[i]);
        chosenSize--;                // un-choose (backtrack)
    }
}
int main() {
    int n;
    Node* root = NULL;
    cout << "How many microservices? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int id, cost;
        cout << "Enter serviceID and monthlyCost " << i + 1 << ": ";
        cin >> id >> cost;
        root = insert(root, id, cost);
    }
    cout << "Target budget B: ";
    cin >> B;
    cout << endl << "Part A: downward paths with sum " << B << endl;
    findPaths(root);
    if (foundA == 0) cout << "No path found." << endl;
    cout << endl << "Part B: subsets with sum " << B << endl;
    inorder(root);
    subsets(0, 0);
    if (foundB == 0) cout << "No subset found." << endl;
    return 0;
}