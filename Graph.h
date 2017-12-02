//
// Created by 12181 on 2017/12/2.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_GRAPH_H
#define DATA_STRUCTURES_AND_ALGORITHMS_GRAPH_H
#include <iostream>
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

void BadInput(){};
void OutOfBounds(){};

template <class T>
class AdjacencyWGraph<T>;

template <class T>
class AdjacencyWDigraph{
    friend  AdjacencyWGraph<T>;
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
AdjacencyWDigraph::AdjacencyWDigraph(int Vertices, T noEdge) {
    n = Vertices;
    e = 0;
    NoEdge = noEdge;
    Make2DArray(a, n+1, n+1);
    for(int i=0; i<=n; ++i)
        for(int j=0; j<=n; ++j)
            a[i][j] = NoEdge;
}
template <class T>
bool AdjacencyWDigraph::Exist(int i, int j) const {
    if(i<1 || j<1 || i>n || j >n || i==j ) throw OutOfBounds();
    if(a[i][j] == NoEdge) return false;
    return true;
}
template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph::Add(int i, int j, const T &w) {
    if(i<1 || j<1 || i>n || j >n || i==j ) throw OutOfBounds();
    if(a[i][j]!= NoEdge) throw BadInput();
    a[i][j] = w;
    return *this;
}
template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph::Delete(int i, int j) {
    if(i<1 || j<1 || i>n || j>n ) throw OutOfBounds();
    if(a[i][j]==NoEdge) throw BadInput();
    a[i][j] = NoEdge;
    e--;
    return *this;
}
template <class T>
int AdjacencyWDigraph::InDegree(int i) const {
    if(i<1 || i>n) throw OutOfBounds();
    int sum = 0;
    for(int j=1; j<=n; ++j){
        if(a[j][i]!=NoEdge) ++j;
    }
    return sum;
}
template <class T>
int AdjacencyWDigraph::OutDegree(int i) const {
    if(i<1 || i>n) throw OutOfBounds();
    int sum =0;
    for(int j=1; j<=n; ++j){
        if(a[i][j] != NoEdge) ++sum;
    }
    return sum;
}

template <class T>
class AdjacencyWGraph:public AdjacencyWDigraph<T>{
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

#endif //GRAPH_GRAPH_H
