#ifndef DICTIONAR_H
#define DICTIONAR_H
#include "node.h"
using namespace std;
template <class K,class V>
class Dictionar
{
    Node<K,V>*root;
    int nr;
public:
    Dictionar();
    Dictionar(Dictionar<K,V>&);
    ~Dictionar();
    void Insertie(K,V);
    unsigned nivel(Node<K,V>*);
    unsigned getdif(Node<K,V>*);
    Node<K,V>* InsertieR(Node<K,V>*,K,V);
    Node<K,V>* rot_st(Node<K,V>*);
    Node<K,V>* rot_dr(Node<K,V>*);
    Node<K,V>* cautare(K);
    void el(K);
    void eliminare(Dictionar<K,V>);
    int* inordine() const;
    V operator[](K);
    Dictionar<K,V> operator=(const Dictionar<K,V>&);
    friend ostream& operator<<(ostream&, const Dictionar<K,V>&);

};

#endif // DICTIONAR_H
