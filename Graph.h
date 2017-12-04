//
// Created by 12181 on 2017/12/2.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_GRAPH_H
#define DATA_STRUCTURES_AND_ALGORITHMS_GRAPH_H
#include <iostream>
#include "ChainNode.h"
#include "NativeExceptions.h"
using  namespace std;


template <class T>
void Make2DArray(T **&x, int rows, int cols){
    x = new T *[rows];
    for(int i=0; i<rows; ++i)
        x[i] = new T[cols];
}

template <class T>
void Delete2DArray(T **&x, int rows){
    for(int i=0; i<rows; ++i)
        delete [ ] x[i];
    delete [] x;
    x = 0;
}


template <class T>
class AdjacencyWGraph;

template <class T>
class AdjacencyWDigraph{
    template<class U>
    friend class AdjacencyWGraph;
public:
    AdjacencyWDigraph(int Vertices = 10, T noEdge = 0);
    ~AdjacencyWDigraph(){Delete2DArray(a, n+1);}//TODO why n+1? --because count freom 1?
    bool Exist(int i, int j) const;
    int Edges() const {return e;}
    int Vertices() const {return n;}
    AdjacencyWDigraph<T>& Add(int i, int j, const T& w);
    AdjacencyWDigraph<T>& Delete(int i, int j);
    int OutDegree(int i) const;
    int InDegree(int i) const;
private:
    T NoEdge;//the symbol of no edge
    int n;//count of nodes
    int e;//count of edges
    T **a;//matrix
};
template <class T>
AdjacencyWDigraph<T>::AdjacencyWDigraph(int Vertices, T noEdge) {
    n = Vertices;
    e = 0;
    NoEdge = noEdge;
    Make2DArray(a, n+1, n+1);
    for(int i=0; i<=n; ++i)
        for(int j=0; j<=n; ++j)
            a[i][j] = NoEdge;
}
template <class T>
bool AdjacencyWDigraph<T>::Exist(int i, int j) const {
    if(i<1 || j<1 || i>n || j >n || i==j ) throw OutOfBounds();
    if(a[i][j] == NoEdge) return false;
    return true;
}
template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Add(int i, int j, const T &w) {
    if(i<1 || j<1 || i>n || j >n || i==j ) throw OutOfBounds();
    if(a[i][j]!= NoEdge) throw BadInput();
    a[i][j] = w;
    return *this;
}
template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Delete(int i, int j) {
    if(i<1 || j<1 || i>n || j>n ) throw OutOfBounds();
    if(a[i][j]==NoEdge) throw BadInput();
    a[i][j] = NoEdge;
    e--;
    return *this;
}
template <class T>
int AdjacencyWDigraph<T>::InDegree(int i) const {
    if(i<1 || i>n) throw OutOfBounds();
    int sum = 0;
    for(int j=1; j<=n; ++j){
        if(a[j][i]!=NoEdge) ++j;
    }
    return sum;
}
template <class T>
int AdjacencyWDigraph<T>::OutDegree(int i) const {
    if(i<1 || i>n) throw OutOfBounds();
    int sum =0;
    for(int j=1; j<=n; ++j){
        if(a[i][j] != NoEdge) ++sum;
    }
    return sum;
}

template <class T>
class AdjacencyWGraph:public AdjacencyWDigraph<T>{
    using AdjacencyWDigraph<T>::a;
    using AdjacencyWDigraph<T>::NoEdge;
    using AdjacencyWDigraph<T>::OutDegree;
public:
    AdjacencyWGraph(int Vertices = 10, T noEdge = 0): AdjacencyWDigraph<T>(Vertices, noEdge){}
    AdjacencyWGraph<T>& Add(int i, int j, const T &w){
        AdjacencyWDigraph<T>::Add(i, j, w);
        a[j][i] = w;
        return *this;
    }
    AdjacencyWGraph<T>& Delete(int i, int j){
        AdjacencyWDigraph<T>::Delete(i, j);
        a[j][i] = NoEdge;
        return *this;
    }
    int Degree(int i) const {return OutDegree(i);}
};

class AdjacencyGraph:public AdjacencyWGraph<int>{
public:
    AdjacencyGraph(int Vertices):AdjacencyWGraph<int>(Vertices, 0){}
    AdjacencyGraph& Add(int i, int j){
        AdjacencyWGraph<int>::Add(i, j, 1);
        return *this;
    }
    AdjacencyGraph& Delete(int i, int j){
        AdjacencyWGraph<int>::Delete(i, j);
        return *this;
    }
    void Input();6+
};


template <class T>
class LinkedBase{
    friend class LinkedDigraph;
    friend class LinkedGraph;
    template <class U> friend class LinkedWDigraph;
    template <class U> friend class LinkedWGraph;
public:
    LinkedBase(int Vertices = 10){
        n = Vertices;
        e = 0;
        h = new Chain<T> [n+1];
    }
    ~LinkedBase(){delete [] h;}
    int Edges()const{return e;}
    int Vertices()const{return n;}
    int OutDegree(int i)const{
        if(i<1 || i>n) throw OutOfBounds();
        return h[i].Length();
    }
protected:
    int n;//the number of vertices
    int e;//the number of edges
    Chain<T> *h;//the head of the chain
};
template <class T>
class GraphNode{
    template <class U> friend class LinkedWDigrap;
    template <class U> friend class LinkedWGraph;
    friend Chain<T>;
public:
    int operator !=(GraphNode<T> y)const{return vertex != y.vertex;}
    void Output(ostream& out)const{out<<vertex<<" "<<weight<<" ";}
private:
    int vertex;
    T weight;
};
template <class T>
ostream& operator<<(ostream& out, GraphNode<T> x){
    x.Output(out);
    return out;
}

class LinkedDigraph:public LinkedBase<int>{
public:
    explicit LinkedDigraph(int Vertices = 10):LinkedBase<int>(Vertices){}
    bool Exist(int i, int j)const;
    LinkedDigraph& Add(int i, int j);
    LinkedDigraph& Delete(int i, int j);
    int InDegree(int i)const;
protected:
    LinkedDigraph& AddNoCheck(int i, int j);
};
bool LinkedDigraph::Exist(int i, int j) const {
    if(i<1 || i>n) throw OutOfBounds();
    return h[i].Search(j);
}
LinkedDigraph& LinkedDigraph::Add(int i, int j) {
    if(i<1 || j<1 || i>n || j >n  ) throw OutOfBounds();
    if(Exist(i, j) || i==j) throw BadInput();
    return AddNoCheck(i, j);
}
LinkedDigraph& LinkedDigraph::Delete(int i, int j) {
    if(i<1 || j<1 || i>n || j >n || i==j ) throw OutOfBounds();
    h[i].Delete(j);
    --e;
    return *this;
}
LinkedDigraph& LinkedDigraph::AddNoCheck(int i, int j) {
    h[i].Insert(0, j);
    ++e;
    return *this;
}
int LinkedDigraph::InDegree(int i) const {
    if(i<1 || i>n  ) throw OutOfBounds();
    int sum =0;
    for(int j=0; j<=n; ++j)
        if(h[j].Search(i)) ++sum;
    return sum;
}

class LinkedGraph:public LinkedDigraph{
public:
    LinkedGraph(int Vertices = 10):LinkedDigraph(Vertices){}
    LinkedGraph& Add(int i, int j);
    LinkedGraph& Delete(int i, int j);
    int Degree(int i)const{return InDegree(i);}
protected:
    LinkedGraph& AddNoCheck(int i, int j);
};
LinkedGraph& LinkedGraph::Add(int i, int j) {
    if(i<1 || j<1 || i>n || j >n ) throw OutOfBounds();
    if(i==j || Exist(i, j)) throw BadInput();
    return AddNoCheck(i, j);
}
LinkedGraph& LinkedGraph::AddNoCheck(int i, int j) {
    h[i].Insert(0, j);
    try{h[j].Insert(0, i);}
    catch(...){h[i].Delete(j); throw;}
    ++e;
    return *this;
}
LinkedGraph& LinkedGraph::Delete(int i, int j) {
    LinkedDigraph::Delete(i, j);
    ++e;
    LinkedDigraph::Delete(j, i);
    return *this;
}

template <class T>
class LinkedWDigraph:LinkedBase<GraphNode<T> >{
    using LinkedBase<GraphNode<T> >::e;
    using LinkedBase<GraphNode<T> >::n;
    using LinkedBase<GraphNode<T> >::h;
public:
    LinkedWDigraph(int Vertices = 10):LinkedBase<GraphNode<T> >(Vertices){}
    bool Exist(int i, int j) const;
    LinkedWDigraph<T>& Add(int i, int j, const T& w);
    LinkedWDigraph<T>& Delete(int i, int j);
    int InDegree(int i)const;
protected:
    LinkedWDigraph<T>& AddNoCheck(int i, int j, const T& w);
};
template <class T>
bool LinkedWDigraph<T>::Exist(int i, int j) const {
    if(i<1 || j<1 || i>n || j >n ) throw OutOfBounds();
    GraphNode<T> x;
    x.vertex = j;
    return h[i].Search(x);
}
template <class T>
LinkedWDigraph<T>& LinkedWDigraph<T>::Add(int i, int j, const T &w) {
    if(i<1 || j<1 || i>n || j >n ) throw OutOfBounds();
    if(i==j || Exist(i, j)) throw BadInput();
    return AddNoCheck(i, j, w);
}
template <class T>
LinkedWDigraph<T>& LinkedWDigraph<T>::AddNoCheck(int i, int j, const T &w) {
    GraphNode<T> x;
    x.vertex = j;
    x.weight = w;
    h[i].Insert(0, x);
    return *this;
}
template <class T>
LinkedWDigraph<T>& LinkedWDigraph<T>::Delete(int i, int j) {
    if(i<1 || j<1 || i>n || j >n ) throw OutOfBounds();
    if(i==j || Exist(i, j)) throw BadInput();
    GraphNode<T> x;
    x.vertex = j;
    h[i].Delete(x);
    --e;
    return *this;
}
template <class T>
int LinkedWDigraph<T>::InDegree(int i) const {
    if(i<1 ||  i>n  ) throw OutOfBounds();
    int sum = 0;
    GraphNode<T> x;
    x.vertex = i;
    for(int i=0; i<n; ++i)
        if(h[i].Search(x)) ++sum;
    return sum;
}
#endif //GRAPH_GRAPH_H
