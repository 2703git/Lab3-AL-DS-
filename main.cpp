#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};
Node* createNode(int value) {
    Node* node = new Node;
    node->data = value;
    node->next = nullptr;
    return node;
}
//Lab A - linked list traversal
//Problem 1 A
void printList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    Node* temp= head;
    while (temp->next != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << temp->data << endl;
    return;
}
//Problem 2 A
bool searchValue(Node* head, int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
//Problem 3 A
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}
//Lab B - linked list insertion
//Problem 1 B
void insertBeginning(Node* &head, int value) {
    Node* newNode = createNode(value);
    newNode->next = head;
    head = newNode;
}
//Problem 2 B
void insertEnd(Node* &head, int value) {
    Node* newNode = createNode(value);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}
//Problem 3 B
void insertAtPosition(Node* &head, int value, int k) {
    if (k<=0) {
        cout<<"Wrong input"<<endl;
    return;
    }
    if (k==1) {
        insertBeginning(head, value);
        return;
    }
    Node* temp = head;
    for (int i=0; i<k-1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout<<"Wrong input"<<endl;
        return;
    }
    Node* newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
}
//Lab C - linked list deletion
//Problem 1 C
void deleteBeginning(Node* &head) {
    Node* temp = head;
    head = head->next;
    delete temp;
}
//Problem 2 C
void deleteEnd(Node* &head) {

}





int main() {
    //Node* head = nullptr; //Example for empty list
    Node* head = createNode(10);    //example for: 10 20 30
    head->next = createNode(20);
    head->next->next = createNode(30);
    // cout<<"Problem 1 A"<<endl;
    // cout<<"Org list: ";
    // printList(head);
    // cout<<"\nProblem 2 A"<<endl;
    // cout<<"Search 20: ";
    // if (searchValue(head, 20)) {
    //     cout<<"Found"<<endl;
    // }else {
    //     cout<<"Not Found"<<endl;
    // }
    // cout<<"\nProblem 3 A"<<endl;
    // cout<<"Number of nodes: "<<countNodes(head)<<endl;
    // cout<<"\nProblem 1 B:  "<<endl;
    // insertBeginning(head, 5);
    // cout<<"Insert 5: \nNew node: ";
    // printList(head);
    // cout<<"\nProblem 2 B: "<<endl;
    // insertEnd(head, 40);
    // cout<<"Insert 40: \nNew node: ";
    // printList(head);
    // cout<<"\nProblem 3 B: "<<endl;
    // insertAtPosition(head, 15, 2);
    // cout<<"Insert 15: \nNew node: ";
    // printList(head);
    // cout<<"\nProblem 1 C"<<endl;
    // deleteBeginning(head);
    // cout<<"New list: ";
    // printList(head);
    cout<<"\nProblem 2 C"<<endl;
    

}
