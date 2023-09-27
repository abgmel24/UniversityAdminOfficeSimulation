#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>
using namespace std;

template <class T>
class TListNode {
    public:
        T data;
        TListNode<T> *next;

        TListNode() {}
        TListNode(T d) {
            data = d;
            next = NULL;
        }
        ~TListNode() {
            delete next;
        }

};

#endif