#ifndef TLISTNODE_H
#define TLISTNODE_H

#include <iostream>
#include <exception>

template <class T>
class TDoubleListNode {
    public:
        TDoubleListNode<T> *next;
        TDoubleListNode<T> *prev;
        T data;

        TDoubleListNode() {}

        TDoubleListNode(T d) {
            data = d;
            next = NULL;
            prev = NULL;
        }

        ~TDoubleListNode() {
            delete next;
            delete prev;
        }
};

#endif