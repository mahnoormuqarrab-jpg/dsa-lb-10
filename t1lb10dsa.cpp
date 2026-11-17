#include <iostream>
#include <queue>
using namespace std;
// one container in the linked list
struct Node {
    int id;
    int weight;
    Node* next;
};
int numTrucks;
int space[50];          // space left in each truck
int assignedTruck[50];  // assignedTruck[i] = truck that container i is in
queue<int> trucks;      // the queue of trucks (we store truck numbers)
// pos = position of the current container in the list (0, 1, 2, ...)
bool load(Node* cur, int pos, int weightLeft, int spaceLeft) {
    // no containers left, so everything is loaded
    if (cur == NULL) return true;
    // prune: not enough total space for the remaining containers
    if (weightLeft > spaceLeft) return false;
    // try every truck in the queue, one by one
    for (int i = 0; i < numTrucks; i++) {
        int t = trucks.front();
        trucks.pop();
        trucks.push(t);          // send it to the back, so the queue keeps all trucks
        // prune: container doesn't fit in this truck
        if (space[t] < cur->weight) continue;
        // put the container in the truck
        space[t] -= cur->weight;
        assignedTruck[pos] = t;
        if (load(cur->next, pos + 1, weightLeft - cur->weight, spaceLeft - cur->weight))
            return true;
        // didn't work, take it back out (backtrack)
        space[t] += cur->weight;
    }
    return false;
}
int main() {
    int n, W;
    cout << "How many containers? ";
    cin >> n;
    // build the linked list
    Node* head = NULL;
    Node* tail = NULL;
    int totalWeight = 0;
    for (int i = 0; i < n; i++) {
        Node* c = new Node;
        cout << "Enter id and weight of container " << i + 1 << ": ";
        cin >> c->id >> c->weight;
        c->next = NULL;
        totalWeight += c->weight;
        if (head == NULL) head = c;
        else tail->next = c;
        tail = c;
    }
    cout << "How many trucks? ";
    cin >> numTrucks;
    cout << "Capacity of each truck: ";
    cin >> W;
    // trucks arrive in the queue
    for (int i = 0; i < numTrucks; i++) {
        trucks.push(i);
        space[i] = W;
    }
    if (load(head, 0, totalWeight, numTrucks * W)) {
        // for each truck, go through the list and print its containers
        for (int t = 0; t < numTrucks; t++) {
            cout << "Truck " << t + 1 << ": ";
            Node* p = head;
            int pos = 0;
            while (p != NULL) {
                if (assignedTruck[pos] == t)
                    cout << p->id << " ";
                p = p->next;
                pos++;
            }
            cout << endl;
        }
    } else {
        cout << "Insufficient truck capacity." << endl;
    }
    return 0;
}