/*
	Author: Jiajiang Xie
 */
#include <iostream>
using namespace std;

class DLinkedListStack {
private:
    class Node {
    public:
        int val;
        Node* before;
        Node* next;
        Node(int v, Node* b, Node* n) : val(v), before(b), next(n){}
    };
    Node* head;
    Node* tail;
    void addStart(int v){
        if(head == nullptr){
            head = new Node(v, nullptr, nullptr);
            tail = head;
            return;
        }
        head = new Node(v, nullptr, head);
    }
    void removeStart(){
        if(head == nullptr){
            return;
        }
        if(head->next == nullptr){
            Node* temp = head;
            head = head->next;
            temp->next = nullptr;
            delete temp;
            return;
        }
        Node* temp = head;
        head = head->next;
        head->before = nullptr;
        temp->next = nullptr;
        delete temp;
    }
public:
    DLinkedListStack() : head(nullptr), tail(head){}
    ~DLinkedListStack(){
        Node* q;
        for(Node* p = head; p != nullptr; p = q){
            q = p->next;
            delete p;
        }
    }
    DLinkedListStack(const DLinkedListStack& orig){
        if (orig.head == nullptr) {
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new Node(orig.head->val, nullptr, nullptr);
        Node *p = orig.head->next;
        if (p == nullptr) {
            tail = head;
            return;
        }
        tail = head;
        for (; p != nullptr; p = p->next, tail = tail->next) {
            tail->next = new Node(p->val, p->before, nullptr);
        }
    }
    DLinkedListStack& operator =(DLinkedListStack copy){
        swap(head, copy.head);
        swap(tail,copy.tail);
        return *this;
    }
    DLinkedListStack(DLinkedListStack&& orig) : head(orig.head), tail(orig.tail){
        orig.head = nullptr;
        orig.tail = nullptr;
    }
    bool isEmpty(){
        return head == nullptr;
    }
    void push(int v){
        addStart(v);
    }
    int pop(){
        if(isEmpty()){
            cout << "The stack is empty" << '\n';
            return 0;
        }
        int temp = head->val;
        removeStart();
        return temp;
    }
    int size(){
        int i=0;
        for(Node* p = head; p != nullptr; p = p->next){
            i++;
        }
        return i * sizeof(int);
    }
    int top(){
        return head->val;
    }
};

int main() {
    DLinkedListStack a;
    a.push(1);
    cout << a.size() <<'\n';
    cout << a.top() << '\n';
    cout << a.pop() << '\n';
    cout << a.pop() <<'\n';
    cout << a.pop() <<'\n';
}

