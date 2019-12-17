/*
	Author: Jiajiang Xie
 */
#include <iostream>
using namespace std;

class DLinkedList {
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
public:
    DLinkedList() : head(nullptr), tail(head){}
    ~DLinkedList(){
        Node* q;
        for(Node* p = head; p != nullptr; p = q){
            q = p->next;
            delete p;
        }
    }
    DLinkedList(const DLinkedList& orig){
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
    DLinkedList& operator =(DLinkedList copy){
        swap(head, copy.head);
        swap(tail,copy.tail);
        return *this;
    }
    DLinkedList(DLinkedList&& orig) : head(orig.head), tail(orig.tail){
        orig.head = nullptr;
        orig.tail = nullptr;
    }
    void walk(){
        if(head == nullptr){
            cout << "The list is empty" << '\n';
            return;
        }
        for(Node* p = head; p != nullptr; p = p->next){
            cout << p->val << ' ';
        }
        cout << '\n';
    }
    Node* search(int v){
        if(head == nullptr){
            cout << "The list is empty" << '\n';
            return nullptr;
        }
        for(Node* p = head; p != nullptr; p = p->next){
            if(v == p->val){
                return p;
            }
        }
        cout << "Can not find " << v << '\n';
    }
    void addStart(int v){
        if(head == nullptr){
            head = new Node(v, nullptr, nullptr);
            tail = head;
            return;
        }
        head = new Node(v, nullptr, head);
    }
    void addEnd(int v){
        if(tail == nullptr){
            addStart(v);
            return;
        }
        tail->next = new Node(v, tail, nullptr);
        tail = tail->next;
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
    void removeEnd(){
        if(tail == nullptr){
            return;
        }
        if(tail->before == nullptr){
            Node* temp = tail;
            tail = tail->before;
            temp->next = nullptr;
            delete temp;
            return;
        }
        Node* temp = tail;
        tail = tail->before;
        tail->next = nullptr;
        temp->before = nullptr;
        delete temp;
    }
    void addAfterpos(int v, Node* pos){
        if(head == nullptr){
            return;
        }
        if(pos->next == nullptr){
            addEnd(v);
            return;
        }
        Node* temp = pos->next;
        pos->next = new Node(v,pos,temp);
        temp->before = pos->next;
    }
    void addBeforepos(int v, Node* pos){
        if(head == nullptr){
            return;
        }
        if(pos->next == nullptr){
            addEnd(v);
            return;
        }
        Node* temp = pos->before;
        temp->next = new Node(v,temp,pos);
        pos->before = temp->next;
    }
    void removePos(Node* pos){
        if(head == nullptr){
            return;
        }
        for(Node* p = head; p != pos; p = p->next){
            if(p->next == nullptr){
                cout << "No node to delete" << '\n';
                return;
            }
        }
        if(pos == tail){
            removeEnd();
            return;
        }
        if(pos == head){
            removeStart();
            return;
        }
        pos->before->next = pos->next;
        delete pos;
    }
    friend ostream&operator <<(ostream& s, const DLinkedList& l){
        for(Node* p = l.head; p!= nullptr; p=p->next){
            s << p->val << ' ';
        }
        return s;
    }
};

int main() {
    DLinkedList a;
    a.addStart(3);
    a.removeStart();
    a.walk();
}

