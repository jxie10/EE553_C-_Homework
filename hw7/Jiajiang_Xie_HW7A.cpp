/*
	Author: Jiajiang Xie
 */
#include <iostream>
using namespace std;

class LinkedList2 {
private:
    class Node { // LinkedList2::Node
    public:
        int val;
        Node* next;
        Node(int v, Node* n) : val(v), next(n){}
    };
    Node* head;
    Node* tail;
public:
    LinkedList2() : head(nullptr), tail(head){}
    ~LinkedList2(){
        Node* q;
        for(Node* p = head; p != nullptr; p = q){
            q = p->next;
            delete p;
        }
    }
    LinkedList2(const LinkedList2& orig){
        if (orig.head == nullptr) {
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new Node(orig.head->val, nullptr);
        Node *p = orig.head->next;
        if (p == nullptr) {
            tail = head;
            return;
        }
        tail = head;
        for (; p != nullptr; p = p->next, tail = tail->next) {
            tail->next = new Node(p->val, nullptr);
        }
    }
    LinkedList2& operator =(LinkedList2 copy){
        swap(head, copy.head);
        swap(tail,copy.tail);
        return *this;
    }
    // move constructor
    LinkedList2(LinkedList2&& orig) : head(orig.head), tail(orig.tail){ // steal orig data while it's dying (nice)
        orig.head = nullptr;
        orig.tail = nullptr;
    }
    void addStart(int v){
        head = new Node(v,head);
        if(head->next == nullptr){
            tail = head;
        }
    }
    void addEnd(int v){
        if(head == nullptr){
            addStart(v);
            return;
        }
        tail->next = new Node(v, nullptr);
        tail = tail->next;
    }
    void removeStart(){
        if(head == nullptr){
            return;
        }
        Node* temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
    }
    void removeEnd(){
        if(tail == nullptr){
            return;
        }
        Node* p = head;
        for(; p->next != tail; p = p->next);
        tail = p;
        p = tail->next;
        tail->next = nullptr;
        delete p;
    }
    friend ostream&operator <<(ostream& s, const LinkedList2& l){
        for(Node* p = l.head; p!= nullptr; p=p->next){
            s << p->val << ' ';
        }
        return s;
    }
};
/**
  head --> nullptr

  head --> [ val=3 next= nullptr  ]

  head -->  [val=1 next= ---->  [ val=3 next= nullptr  ]



 */
int main() {
    LinkedList2 a;
    a.addStart(3); // 3 is the first element in the list
    a.addStart(1); // 1 3
    a.addStart(4); // 4 1 3
    for (int i = 1; i <= 5; i++)
        a.addEnd(i);
    a.removeStart();
    a.removeEnd();
    cout << a << '\n'; // print out the list, separated by spaces or commas

    LinkedList2 b = a;
    cout << b << '\n';

    LinkedList2 c;
    c.addStart(5);
    c = b; // wipe out c, copy in b
    cout << c << '\n';
}

