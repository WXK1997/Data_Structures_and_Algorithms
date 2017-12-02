//
// Created by 12181 on 2017/12/2.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_CHAINNODE_H
#define DATA_STRUCTURES_AND_ALGORITHMS_CHAINNODE_H
#include <iostream>

using  namespace std;

class OutOfBounds{
public:
    OutOfBounds(){};
};

template <class T>
class Chain;
template <class T>
class ChainNode;
template <class T>
class ChainIterator;


template <class T>
class ChainIterator{
public:
    T *Initialize(const Chain<T>& c){
        location = c.first;
        if(location) return &location->data;
        return 0;
    }
    T *Next(){
        if(!location) return 0;
        location = location->link;
        if(location) return &location->data;
        return 0;
    }
private:
    ChainNode<T> *location;
};

template <class  T>
class ChainNode {
    friend ChainIterator<T>;
    friend Chain<T>;
private:
    T data;
    ChainNode<T> *link;
};
template <class T>
class Chain{
    friend ChainIterator<T>;
public:
    Chain(const T &x);
    Chain();
    ~Chain();
    bool IsEmpty() const {return length == 0;}
    int Length() const { return  length;}
    ChainNode<T>& GetFirst () const {return first;}
    Find(int k, T& x) const;
    int Search(const T& x) const;//homework 18
    Chain<T>& Delete(int k, T& x);
    Chain<T>& Insert(int k, const T&x);
    void OutPut(ostream& out) const;
    Chain<T>& Erase();
    Chain<T>& Append(const T& x);
    Chain<T>& Reverse();
    void Loop(){last->link = first;}
    void NotLoop(){last->link = 0;}
    Chain<T>& OrderInsert(const T&x);
    Chain<T>& Sum(const Chain<T>& x);
private:
    ChainNode<T> *first;
    ChainNode<T> *last;
    int length;
};

template <class T>
Chain<T>::Chain(const T &x) {
    first = new ChainNode<T>;
    first->data = x;
    first->link = first;
    last = 0;
    length = 0;
}

template <class T>
Chain<T>::Chain(){
    first = new ChainNode<T>;
    first->link = first;
    last = 0;
    length = 0;
};

template <class T>
Chain<T>::~Chain() {
    ChainNode<T> *next = first;
    for(int i = 0; i < length+1; ++i){
        next = first->link;
        delete first;
        first = next;
    }
}

template <class T>
Chain<T>::Find(int k, T &x) const {
    if(k<=0 || k>length)
        throw OutOfBounds();
    ChainNode<T> *current = first;
    for(int i = 0; i<k; ++i)
        current = current->link;
    x = current->data;
}

template <class T>
int Chain<T>::Search(const T &x) const {
    ChainNode<T> *current = first->link;
    first->data = x;
    int cnt = 1;
    while(current->data != x)
        cnt++;
    current = current->link;
    if(current == first)
        return 0;
    return cnt;
}

template <class T>
Chain<T>& Chain<T>::Delete(int k, T &x) {
    if(k<1 || k>length)
        throw OutOfBounds();
    ChainNode<T> *current = first;
    for(int i = 0; i < k-1; ++i){
        current = current->link;
    }
    ChainNode<T> *temp = current->link;
    current->link = temp->link;
    x = temp->data;
    delete temp;
    if(k == length)
        last = current;
    length--;
    return *this;
}

template <class T>
Chain<T>& Chain<T>::Insert(int k, const T &x) {
    if(length == 0){
        ChainNode<T> *i = new ChainNode<T>;
        first->link = i;
        i->data = x;
        i->link = first;
        length = 1;
        last = i;
        return *this;
    }
    if(k<1 || k>length)
        throw OutOfBounds();
    ChainNode<T> *current = first;
    for(int i = 0; i < k-1; ++i)
        current = current->link;
    ChainNode<T> *n = new ChainNode<T>;
    n->link = current->link;
    current->link = n;
    n->data = x;
    length++;
    return *this;
}

template <class T>
Chain<T>& Chain<T>::Erase() {
    ChainNode<T> *current, *next;
    current = first->link;
    for(int i = 0; i < length; ++i){
        next = current->link;
        delete current;
        current = next;
    }
    first->link = first;
    length = 0;
    last = 0;
    return *this;
}

template <class T>
Chain<T>& Chain<T>::Append(const T &x) {
    ChainNode<T> *n = new ChainNode<T>;
    n->link = first;
    n->data = x;
    if(length != 0)
        last->link = n;
    else{
        first->link = n;
    }
    last = n;
    length ++;
}

template <class T>
void Chain<T>::OutPut(ostream &out) const {
    ChainNode<T> *current =  first;
    for(int i = 0; i <length; ++i){
        current = current->link;
        out<<current->data<<", ";
    }
}

template <class T>
ostream& operator<<(ostream& out, const Chain<T>& x){
    x.OutPut(out);
    return  out;
}

template <class T>
Chain<T>& Chain<T>::Reverse() {
    ChainNode<T> *temp = first->link;
    ChainNode<T> *temp2;
    ChainNode<T> *current;
    first->link = first;
    for(int i = 0; i < length; ++i){
        current = temp;
        temp = temp->link;
        temp2 = first->link;
        first->link = current;
        current->link = temp2;
    }
    return *this;
}

template <class T>
Chain<T>& Chain<T>::OrderInsert(const T &x) {
    ChainNode<T> *current = first->link;
    int index = 1;
    if(length == 0){
        Insert(1, x);
        return *this;
    }
    while(current->data < x && index <length+1){
        index ++;
        current = current->link;
    }
    if(index > length){
        Append(x);
        return  *this;
    }
    if(current->data == x){
        current->data = current->data + x;
        return *this;
    }
    Insert(index, x);
    return *this;
}

template <class T>
Chain<T>& Chain<T>::Sum(const Chain<T> &x) {
    ChainIterator<T> it1, it2;
    T *p1, *p2;
    Chain<T> *ret;
    ret = new Chain<T>;
    T temp;
    it1.Initialize(*this);
    it2.Initialize(x);
    p1 = it1.Next();
    p2 = it2.Next();
    int l1 = this->Length();
    int l2 = x.Length();
    int i = 1;
    int j = 1;
    while(i<=l1 || j<=l2){
        if(*p1 < *p2){
            ret->Append(*p1);
            p1 = it1.Next();
            i++;
        }
        else if(*p1 == *p2){
            temp = *p1 + *p2;
            ret->Append(temp);
            p1 = it1.Next();
            p2 = it2.Next();
            i++;
            j++;
        }
        else{
            ret->Append(*p2);
            p2 = it2.Next();
            j++;
        }
    }

    return *ret;
}

#endif //DATA_STRUCTURES_AND_ALGORITHMS_CHAINNODE_H
