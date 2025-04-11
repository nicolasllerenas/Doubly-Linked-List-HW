#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;


    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyList {
private:
    Node<T> *head;
    Node<T> *tail;

    DoublyList() : head(nullptr), tail(nullptr) {}

    T front() {return head;}
    T back() {return tail;}
    void push_front(T value) {
        auto *newNode = new Node<T>(value);
        if(!head) {head = tail = newNode;}
        else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }

    }
    void push_back(T value) {
        auto *newNode = new Node<T>(value);
        if (!head) {head = tail = value;}
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
};