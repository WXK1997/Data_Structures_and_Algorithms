//
// Created by 12181 on 2017/12/2.
//TODO

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_BINARYARRAY_H
#define DATA_STRUCTURES_AND_ALGORITHMS_BINARYARRAY_H
#include <iostream>
using namespace std;

struct chunk{
    bool data[256];
    struct chunk *next=NULL;
};


class BinaryArray{
public:
    BinaryArray(){chunk_cnt = 1; index = 0; data = new struct chunk;}
    ~BinaryArray(){}
    void Append(const bool& bit);
    void Pop(bool& bit);
    void OutPut();
private:
    bool& Next();
    int chunk_cnt;
    unsigned char index;
    struct chunk *data;
};

void BinaryArray::Append(const bool &bit) {
    if(index ^ 0xff){
        ++index;
        struct chunk *current=data;
        for(int i=0; i<chunk_cnt-1; ++i)
            current = current->next;
        current->data[index] = bit;
    }
    else{
        ++index;
        ++chunk_cnt;
        struct chunk *current=data;
        for(int i=0; i<chunk_cnt-1; ++i)
            current = current->next;
        current->next = new struct chunk();
        current->data[index] = bit;
    }

}

void BinaryArray::Pop(bool &bit) {
    struct chunk *current=data;
    for(int i=0; i<chunk_cnt-1; ++i)
        current = current->next;
    bit = current->data[index];
    --index;
    if(index ^ 0xff){
        --chunk_cnt;
        current = data;
        for(int i=0; i<chunk_cnt-1; ++i)
            current =  current->next;
        free(current->next);
    }
}

void BinaryArray::OutPut() {
    struct chunk *current=data;
    while(current->next){
        int *p =(int *)current->data;
        for(int i=0; i<8; ++i){
            printf(" %x ", *p);
            ++p;
        }
        current = current->next;
    }
    int *p = (int *) current->data;
    for(int i=0; i<(index/32); ++i)
        printf(" %x ", *(p+i));
}
#endif //DUOXIANGSHIJIAJIANFA_BINARYARRAY_H
