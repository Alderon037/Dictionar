#ifndef NODE_H
#define NODE_H
#include <utility>
template <class K,class V>
class Node
{
    V val;
    K cheie;
    int h;
    Node *st,*dr;
public:
    Node(K x=0,V y=0,Node*l=NULL,Node*r=NULL);
    Node(Node&);
    ~Node();
    friend class Dictionar;
};

#endif // NODE_H
