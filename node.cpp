#include <iostream>
#include "node.h"
template <class K,class V>
Node<K,V>::Node(K x,V y,Node*l,Node*r):cheie(x),val(y),st(l),dr(r)
{

};
template <class K,class V>
Node<K,V>::Node(Node&p):val(p.val),st(p.st),dr(p.dr)
{

}
template <class K,class V>
Node<K,V>::~Node(){
};
