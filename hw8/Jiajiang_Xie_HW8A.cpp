/*
* Author: Jiajiang Xie
*/
#include <iostream>
#include <memory.h>
using namespace std;

class Person {
private:
    uint32_t len;
    char* name;
public:
    Person(const char n[]) : len(strlen(n)), name(new char[len]) {
        cout << "Person constructor\n";\

        memcpy(name, n, len);
    }
    Person(const Person& orig) : len(strlen(orig.name)){
        cout << "copying Person\n";
        name = new char[len];
        memcpy(name, orig.name, len);
    }
    ~Person() {
        cout << "Destructor\n";
        delete [] name;
    }
};

template <typename T>
class GrowArray{
private:
    uint32_t len;
    uint32_t capacity;
    T* data;
    void* operator new(size_t sz, T* place){
        return place;
    }
    void checkGrow(){
        if(len >= capacity) {
            capacity *= 2;
            T *old = data;
            data = (T*)new char[capacity];
            memcpy(data, old, capacity);
            delete [] old;
        }
    }
public:
    GrowArray(uint32_t capacity) : len(0), capacity(capacity), data((T*)new char[sizeof(T)*capacity]){}
    ~GrowArray(){
        for(int i = 0; i<len; i++){
            data[i].~T();
        }
        delete [] (char*)data;
    }
    GrowArray(const GrowArray& orig): len(orig.len), capacity(orig.capacity),data((T*)new char[sizeof(T)*orig.len]){
        memccpy(data, orig.data, sizeof(T)*orig.len);
    }
    GrowArray& operator =(GrowArray copy){
        data = copy.data;
        capacity = copy.capacity;
        swap(data, copy.data);
        return *this;
    }
    GrowArray(GrowArray&& orig) : len(orig.len), capacity(orig.capacity), data(orig.data){
        orig.data = nullptr;
    }
    void add(T person){
        checkGrow();
        new(&data[len++]) T(person);
    }
};


int main() {
    GrowArray<Person> list(1000000); // should not call constructor for Person!
    list.add(Person("Test")); // Should call the constructor once and the copy once
    /*
        Destructor should be called twice for person (once for the temp, and once for
        the object in the array. If the optimizer somehow can do it, it could be only once.
        But most important, you must not call the destructor 1000000 times!
    */
}

