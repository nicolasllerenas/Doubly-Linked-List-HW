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
class DoublyLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int listSize = 0;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    T front() {
        return head->data;
    }
    T back() {
        return tail->data;
    }
    void push_front(T value) {
        auto *newNode = new Node<T>(value);
        if(!head) {head = tail = newNode;}
        else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        listSize++;
    }
    void push_back(T value) {
        auto *newNode = new Node<T>(value);
        if (!head) {head = tail = value;}
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }
    T pop_front() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }

        T value = head->data;
        Node<T>* temp = head;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        listSize--;
        return value;
    }
    T pop_back() {
        if (!tail) {
            throw std::out_of_range("List is empty");
        }

        T value = tail->data;
        Node<T>* temp = tail;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        listSize--;
        return value;
    }

    void insert(T value, int position) {
        if (position < 0 || position > listSize) {
            throw std::out_of_range("Invalid position");
        }

        Node<T>* newNode = new Node<T>(value);

        if (position == 0) {
            // Insertar al inicio
            if (!head) {
                head = tail = newNode;
            } else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        } else if (position == listSize) {
            // Insertar al final
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        } else {
            // Insertar en el medio
            Node<T>* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }

        listSize++;
    }

    void remove(int position) {
        if (position < 0 || position >= listSize) {
            throw std::out_of_range("Invalid position");
        }

        Node<T>* toDelete;

        if (position == 0) {
            // Eliminar el primero
            toDelete = head;
            if (head == tail) {
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
        } else if (position == listSize - 1) {
            // Eliminar el último
            toDelete = tail;
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            // Eliminar en el medio
            Node<T>* current = head;
            for (int i = 0; i < position; i++) {
                current = current->next;
            }
            toDelete = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete toDelete;
        listSize--;
    }

    T operator[](int position) {
        if (position < 0 || position >= listSize) {
            throw std::out_of_range("Invalid position");
        }

        Node<T>* current;

        if (position < listSize / 2) {
            current = head;
            for (int i = 0; i < position; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = listSize - 1; i > position; i--) {
                current = current->prev;
            }
        }

        return current->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        return listSize;
    }
    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        listSize = 0;
    }

    void reverse() {
        Node<T> *current = head;
        Node<T> *dummy;
        while (current) {
            dummy = current->prev;
            current->prev = current->next;
            current->next = dummy;
            current = current->prev;
        }
        if(dummy) {
            tail = head;
            head = dummy->prev;
        }
    }
};