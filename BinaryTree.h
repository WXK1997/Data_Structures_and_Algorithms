//
// Created by 12181 on 2017/12/2.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_BINARYTREE_H
#define DATA_STRUCTURES_AND_ALGORITHMS_BINARYTREE_H
#include <iostream>
using namespace std;

enum side{L, R};
template <class T>
class BinaryTree;
template <class T>
class BinaryTreeNode;

template <class T>
class BinaryTreeNode{
public:
    BinaryTreeNode(){l_child = r_child = NULL;}
    BinaryTreeNode(const T& e){data = e; l_child = r_child =NULL;}
    BinaryTreeNode(const T& e, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r){
        data = e; l_child = l; r_child = r;
    }
    T& Data(){return data;}
    BinaryTreeNode<T>* LeftChild(){return l_child;}
    BinaryTreeNode<T>* RightChild(){return r_child;}
    bool SetData(const T& data){data = data; return true;}
    bool SetLChild(const BinaryTreeNode<T> *l){l_child = l; return true;}
    bool SetRChild(const BinaryTreeNode<T> *r){r_child = r; return true;}
    BinaryTreeNode<T>* AddSon(const T& e, BinaryTreeNode<T> *father, side s){
        BinaryTreeNode<T> *newnode = new BinaryTreeNode<T>(e);
        if(s == L)
            father->l_child = newnode;
        else
            father->r_child = newnode;
        return newnode;
    }
    BinaryTreeNode<T>* AddSon(const T& e, side s){
        BinaryTreeNode<T> *newnode = new BinaryTreeNode<T>(e);
        if(s == L){
            if(this->l_child)
                throw "father already have a left son";
            this->l_child = newnode;}
        else{
            if(this->r_child)
                throw "father already have a right con";
            this->r_child = newnode;
        }
        return newnode;
    }
private:
    T data;
    BinaryTreeNode<T> *l_child,
            *r_child;
};
//
//template <class T>
//void Visit(BinaryTreeNode<T> *n){
//    cout<<n->l_child->data<<endl;
//}
template <class T>
class BinaryTree{
public:
    BinaryTree(BinaryTreeNode<T> *r = NULL){root = r;}
    ~BinaryTree(){}
    bool IsEmpty() const{return root == NULL;}
    BinaryTreeNode<T>* Root(){return root;}
    void MakeTree(const T& e, BinaryTree<T>& l_tree, BinaryTree<T>& r_tree);
    void BreakTree(T& e, BinaryTree<T>& l_tree, BinaryTree<T>& r_tree);
    void PreOrder(void(*Visit) (BinaryTreeNode<T> *u)){PreOrder(Visit, root);}
    void Inorder(void(*Visit) (BinaryTreeNode<T> *u)) {InOrder(Visit, root);}
    void PostOrder(void(*Visit) (BinaryTreeNode<T> *u)) {PostOrder(Visit, root);}
    void LevelOrder(void(*Visit) (BinaryTreeNode<T> *u));
    void PreOut(){PreOrder(&out, root);}
    void InOut(){InOrder(&out, root);}
    void PostOut(){PostOrder(&out, root);}
    int D0Nodes(){return D0Nodes(root);}
    int D1Nodes(){return D1Nodes(root);}
    int D2Nodes(){return D0Nodes(root)-1;}
    int Depth(){Depth(root);}
    BinaryTreeNode<T>& FindBlank(int i);
    int LeftLevel();
private:
    BinaryTreeNode<T> *root;
    int Depth(BinaryTreeNode<T> *t);
    int D0Nodes(BinaryTreeNode<T> *t);
    int D1Nodes(BinaryTreeNode<T> *t);
    static void out(BinaryTreeNode<T> *t){cout<<t->Data()<<" ";}
    void PreOrder(void (*Visit) (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
    void InOrder(void (*Visit) (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
    void PostOrder(void (*Visit) (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
};

template <class T>
void BinaryTree<T>::MakeTree(const T &e, BinaryTree<T> &l_tree, BinaryTree<T> &r_tree) {
    root = new BinaryTreeNode<T>(e, l_tree.root, r_tree.root);
    l_tree.root = NULL;
    r_tree.root = NULL;
    root->SetData(e);
}

template <class T>
void BinaryTree<T>::BreakTree(T &e, BinaryTree<T> &l_tree, BinaryTree<T> &r_tree) {
    Root(e);
    l_tree.root = root->LeftChild();
    r_tree.root = root->RightChild();
    delete(root);
    ///////can't visit root->l_child (friend?)
}

template <class T>
void BinaryTree<T>::PreOrder(void (*Visit)(BinaryTreeNode<T> *), BinaryTreeNode<T> *t) {
    if(t){
        Visit(t);
        PreOrder(Visit,t->LeftChild());
        PreOrder(Visit, t->RightChild());
    }
}
template <class T>
void BinaryTree<T>::InOrder(void (*Visit)(BinaryTreeNode<T> *), BinaryTreeNode<T> *t) {
    if(t){
        InOrder(Visit,t->LeftChild());
        Visit(t);
        InOrder(Visit, t->RightChild());
    }
}
template <class T>
void BinaryTree<T>::PostOrder(void (*Visit)(BinaryTreeNode<T> *), BinaryTreeNode<T> *t) {
    if(t){
        PostOrder(Visit,t->LeftChild());
        PostOrder(Visit, t->RightChild());
        Visit(t);
    }
}

template <class T>
int BinaryTree<T>::LeftLevel() {
    BinaryTreeNode<T> *p = root;
    int i = 0;
    while(p){
        p = p->LeftChild();
        i++;
    }
    return i;
}

template <class T>
BinaryTreeNode<T>& BinaryTree<T>::FindBlank(int level) {
    BinaryTreeNode<T> *p =  root;
    if(level > this->LeftLevel())
        throw "the input level to big";
    for(int i = 2; i<=level; ++i)
        p = p->LeftChild();
    return *p;
}

template <class T>
int BinaryTree<T>::Depth(BinaryTreeNode<T> *t) {
    if(!t)
        return 0;
    else{
        int l_d = Depth(t->LeftChild());
        int r_d = Depth(t->RightChild());
        int big_d = l_d>r_d? l_d:r_d;
        return big_d+1;
    }
}

template <class T>
int BinaryTree<T>::D0Nodes(BinaryTreeNode<T> *t) {
    if(!t)
        return 0;
    int count = 0;
    if(!(t->LeftChild() || t->RightChild()))
        count = 1;
    else
        count = 0;
    return count + D0Nodes(t->LeftChild()) + D0Nodes(t->RightChild());
}
template <class T>
int BinaryTree<T>::D1Nodes(BinaryTreeNode<T> *t) {
    if(!t)
        return 0;
    int count = 0;
    if((t->LeftChild() ==NULL) ^ (t->RightChild() ==  NULL))
        count = 1;
    else
        count = 0;
    return count + D1Nodes(t->LeftChild()) + D1Nodes(t->RightChild());
}
#endif //DUOXIANGSHIJIAJIANFA_BINARYTREE_H


