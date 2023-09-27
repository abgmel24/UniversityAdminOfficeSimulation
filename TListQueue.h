#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "TListSingleNode.h"

template <class T>
class TListQueue {
    private:
        TListNode<T> *front;
        TListNode<T> *rear;
        int numElements;

    public:
        TListQueue() {
            front = NULL;
            rear = NULL;
            numElements = 0;
        }
        ~TListQueue() {
            TListNode<T> *curr = front;
            while(curr) {
                TListNode<T> *temp = curr;
                curr = curr->next;
                delete temp;
            }
            delete curr;
            delete front;
            delete rear;
        }

        void push(T data) {
            TListNode<T> *temp = new TListNode<T>(data);

            if(numElements == 0) {
                front = temp;
                rear = front;
                numElements++;
                return;
            }
            
            rear->next = temp;
            rear = rear->next;
            numElements++;
        }

        T pop() {
            if(numElements == 0) {
                throw runtime_error("Cannot remove from an empty queue");
            }
            
            T temp = front->data;
            if(numElements == 1) {
                front = NULL;
                rear = NULL;
                numElements--;
                return temp;
            }

            front = front->next;
            numElements--;
            return temp;
        }

        T peek() {
            return front->data;
        }

        int size() {
            return numElements;
        }
        bool isEmpty() {
            return front == NULL;
        }

};

#endif