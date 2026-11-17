#include <iostream>
using namespace std;
int numOps;
char opType[10];     // the symbol of each operation: + - * /
int opVal[10];       // the number of each operation
int stackOps[50];    // the operation stack (stores operation numbers)
int top = 0;         // how many operations are in the stack
int start, target, K, Mmax;
int found = 0;       // how many solutions we found
void push(int op) {
    stackOps[top] = op;
    top++;
}
void pop() {
    top--;
}
// print the whole sequence from the stack
void printSolution() {
    found++;
    cout << found << ") " << start;
    for (int i = 0; i < top; i++) {
        int op = stackOps[i];
        cout << " " << opType[op] << opVal[op];
    }
    cout << " = " << target << endl;
}
void solve(int value, int opsUsed) {
    // reached the target, print the sequence
    if (value == target && top > 0)
        printSolution();
    // no more operations allowed
    if (opsUsed == K) return;
    for (int i = 0; i < numOps; i++) {
        int next;
        if (opType[i] == '+') next = value + opVal[i];
        else if (opType[i] == '-') next = value - opVal[i];
        else if (opType[i] == '*') next = value * opVal[i];
        else {
            // division only if it divides exactly
            if (value % opVal[i] != 0) continue;
            next = value / opVal[i];
        }
        // prune: value can't be negative or go over the limit
        if (next < 0 || next > Mmax) continue;
        push(i);                    // choose the operation
        solve(next, opsUsed + 1);
        pop();                      // undo it (backtrack)
    }
}
int main() {
    cout << "Start value: ";
    cin >> start;
    cout << "Target value: ";
    cin >> target;
    cout << "Max operations K: ";
    cin >> K;
    cout << "Overflow limit Mmax: ";
    cin >> Mmax;
    cout << "How many operations? ";
    cin >> numOps;
    for (int i = 0; i < numOps; i++) {
        cout << "Enter operation " << i + 1 << " (symbol then number, like + 3): ";
        cin >> opType[i] >> opVal[i];
    }
    solve(start, 0);
    if (found == 0)
        cout << "No sequence found." << endl;
    return 0;
}