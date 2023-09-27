#ifndef DLL_H
#define DLL_H

#include "TListDoubleNode.h"
using namespace std;

template <class T>
class TDoublyLinkedList {
    private:
        TDoubleListNode<T> *head;
        TDoubleListNode<T> *tail;
        unsigned int size;

    public:
        TDoublyLinkedList() {
            size = 0;
            head = NULL;
            tail = NULL;
        }
        
        ~TDoublyLinkedList() {
            //TODO
            TDoubleListNode<T> *curr = head;

            while(curr) {
                // cout << "Data: " << curr->data << " at " << &curr << endl;
                TDoubleListNode<T> *temp = curr;
                // cout << "next: " << curr->next << endl;
                curr = curr->next;
                // cout << "switched to: " << &curr << endl;
                curr->prev= NULL;

                delete temp;
            }

            delete tail;

        }

        void insertFront(T data) {
            TDoubleListNode<T> *node = new TDoubleListNode<T>(data);

            if(isEmpty()) {
                tail = node;
            } else {
                node->next = head;
                head->prev = node;
            }
            head = node;
            size++;
        }

        void insertBack(T data) {
            TDoubleListNode<T> *node = new TDoubleListNode<T>(data);

            if(isEmpty()) {
                head = node;
            } else {
                tail->next = node;
                node->prev = tail;
            }            
            tail = node;
            size++;
        }

        T removeFront() {
            if(isEmpty()) {
                throw std::runtime_error("Cannot remove from an empty DLL");
            }

            TDoubleListNode<T> *temp = head;

            if(head->next == NULL) {
                tail = NULL;
            } else {
                head->next->prev = NULL;
            }

            head = head->next;
            
            T d = temp->data;
            temp->next = NULL;

            size--;
            delete temp;

            return d;
        }

        T removeBack() {
            if(isEmpty()) {
                throw std::runtime_error("Cannot remove from an empty DLL");
            }

            TDoubleListNode<T> *temp = tail;

            if(tail->prev == NULL) {
                head = NULL;
            } else {
                tail->prev->next = NULL;
            }

            tail = tail->prev;

            T d = temp->data;
            temp->prev = NULL;

            size--;
            delete temp;
            return d;
        }

        T removeNode(T val) {
            if(isEmpty()) {
                throw std::runtime_error("Cannot remove from an empty DLL");
            }

            TDoubleListNode<T> *curr = head;

            while(curr->data != val) {
                curr = curr->next;

                if(curr == NULL) {
                    return -1;
                }
            }

            if(curr == head) {
                head = curr->next;
                head->prev = NULL;
            } else if(curr == tail) {
                tail = curr->prev;
                tail->next = NULL;
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            T d = curr->data;
            curr->next = NULL;
            curr->prev = NULL;

            size--;
            delete curr;
            return d;
        }

        T get(int index) {
            if(index < 0 || index > size)
                return NULL;
            
            int i = 0;
            TDoubleListNode<T> *curr = head;
            while(i < index) {
                curr = curr->next;
                i++;
            }
            
            return curr->data;
        }
        
        int find(T val) {
            int index = -1;

            TDoubleListNode<T> *curr = head;
            while(curr != NULL) {
                index++;

                if(curr->data == val) {
                    return index;
                }

                curr = curr->next;
            }
            
            return -1;
        }

        bool isEmpty() {
            return size == 0;
        }

        unsigned int getSize() {
            return size;
        }

        void printList() {
            TDoubleListNode<T> *curr = head;
            cout << "List: ";
            while(curr != NULL) {
                cout << curr->data << " ";
                curr = curr->next;
            }
            cout << endl;
        }
};

#endif