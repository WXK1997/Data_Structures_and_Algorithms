//
// Created by 12181 on 2017/12/2.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_HUFFMAN_H
#define DATA_STRUCTURES_AND_ALGORITHMS_HUFFMAN_H
#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include <vector>
#include <algorithm>

using  namespace std;


template <class T>
class Huffman{
    friend bool smaller(Huffman<char>*, Huffman<char>*);
public:

    Huffman(T d, int f=0){data = d, freq = f;l_child=NULL; r_child=NULL;}
    Huffman(Huffman<T> *l, Huffman<T> *r, int f){freq = f; l_child = l; r_child = r;}
    ~Huffman(){};
    T Data(){return data;}
    int Freq(){return freq;}
    void PreOrder(bool side, vector<bool> code){
        PreOrder(this, side, code);
    }
private:
    void PreOrder(Huffman<char> *t, bool side, vector<bool>& parent_code){
        t->code = new vector<bool>(parent_code);
        t->code->push_back(side);
        PreOrder(t->l_child, 1, *t->code);
        PreOrder(t->r_child, 0, *t->code);
    }
    int freq;
    T data;
    Huffman<T> *l_child;
    Huffman<T> *r_child;
    vector<bool> *code;
};

bool smaller(Huffman<char> *a, Huffman<char> *b){
    return (a->freq) < (b->freq);
}

bool bigger(Huffman<char> *a, Huffman<char> *b){
    return (a->Freq()) > (b->Freq());
}

void read_file(int fre_count[128]){
    for(int i = 0; i<128; ++i)
        fre_count[i] = 0;
    ifstream file("D://test.txt", ios::binary);
    char ch;
    while(file.read(&ch, 1)){
//        cout<<ch<<endl;
        fre_count[ch]++;
    }
//    for(int i = 0; i< 128; ++i){
//        if(fre_count[i]){
//            cout<<"------------------"<<endl;
//            printf("i is %d %c fre is %d\n", i, i, fre_count[i]);
//        }
//    }
}

Huffman<char>& make_haff_tree(int fre_count[128]){
    int cnt = 0;
    int a = 0;
    int b = a+1;
    vector<Huffman<char>* >  vt;
    for(char i=0; i^0x7f; ++i){
        if(fre_count[i]){
            Huffman<char> *temp = new Huffman<char>(i, fre_count[i]);
            vt.push_back(temp);
        }
    }
    std::sort(vt.begin(), vt.end(), smaller);
//    for(int i=0; i<vt.size(); ++i){
//        cout<<vt[i]->Data()<<endl;
//        cout<<vt[i]->Freq()<<endl;
//        cout<<"-----------------"<<endl;
//    }
    while(vt.size()>1){
        Huffman<char> *t1 = vt[0], *t2 = vt[1], *new_node;
        vt.erase(vt.begin());
        vt.erase(vt.begin());
        new_node = new Huffman<char>(t1, t2, t1->Freq()+t2->Freq());
        vector<Huffman<char>* >::iterator it = vt.begin();
        while(smaller(*it, new_node) && it != vt.end())
            ++it;
        if(! *it)
            vt.push_back(new_node);
        vt.insert(it, new_node);
    }
    vector<bool> code;
    vt[0]->PreOrder( 1, code);
//        for(int i=0; i<vt.size(); ++i){
//        cout<<vt[i]->Data()<<endl;
//        cout<<vt[i]->Freq()<<endl;
//        cout<<"-----------------"<<endl;
//    }
    return *vt[0];
}

void haff_encode(Huffman<char> & t){
    bool code[64];
}
#endif //DUOXIANGSHIJIAJIANFA_HAFFMAN_H
