#include <iostream>
#include "Dictionar.h"
#include <assert.h>
#include <queue>
using namespace std;
template <class K,class V>
Dictionar<K,V>::Dictionar()
{
    root=NULL;
    nr=0;
}
template <class K,class V>
unsigned Dictionar<K,V>::nivel(Node<K,V>*p)
{
    unsigned r,l;
    if(p==NULL)
    {
		return 0;
	}
    r=nivel(p->dr);
    l=nivel(p->st);
	if(l>r)
    {
		return l+1;
	}
	return r+1;
}
template <class K,class V>
Node<K,V>* Dictionar<K,V>::rot_st(Node<K,V>*p)
{
    Node<K,V>*t=p->dr;
    Node<K,V>*t2=t->st;
    t->st=p;
    p->dr=t2;
    return t;
}
template <class K,class V>
Node<K,V>* Dictionar<K,V>::rot_dr(Node<K,V>*p)
{
    Node<K,V>*t=p->st;
    Node<K,V>*t2=t->dr;
    t->dr=p;
    p->st=t2;
    return t;
}
template <class K,class V>
unsigned Dictionar<K,V>::getdif(Node<K,V>*p)
{
    if(p==NULL)
        return 0;
    return nivel(p->st)-nivel(p->dr);
}
template <class K,class V>
Node<K,V>* Dictionar<K,V>::InsertieR(Node<K,V>*p,K x,V y)
{
    assert(x!=NULL);
    if(p==NULL)
        {
            nr++;
            p=new Node<K,V>(x,y);
            return p;
        }
	if(y<p->cheie)
        p->st=insertieR(p->st,x);
    else
        if(y>p->cheie)
            p->dr=insertieR(p->dr,x);
        else
            {
                p->val=y;
                return p;
            };
    if(getDif(p)>1 && x<p->st->cheie)
        return rot_dr(p);
    if(getDif(p)>1 && x>p->st->cheie)
        {p->st=rot_st(p->st);
        return rot_dr(p);}
    if(getDif(p)<-1 && x>p->dr->cheie)
        return rot_st(p);
    if(getDif(p)<-1 && x<p->dr->cheie)
        {p->dr=rot_dr(p->dr);
        return rot_st(p);}
    return p;
}
template <class K,class V>
void Dictionar<K,V>::Insertie(K x,V y)
{
    root=insertieR(root,x,y);
}
template <class K,class V>
Dictionar<K,V>::Dictionar(Dictionar<K,V>& Dex)
{
    root=NULL;
    nr=0;
    Node<K,V>** s=new Node<K,V>*[Dex.nr];
    int nrs=0;
    s[nrs]=Dex.root;
    nrs++;
    while(nrs>0)
    {
        Node<K,V>*p=s[nrs-1];
        nrs--;
        Insertie(p->cheie,p->val);
        if(p->dr!=NULL)
        {
            s[nrs+1]=p->dr;
            nrs++;
		}
		if (p->st!=NULL)
        {
			s[nrs]=p->st;
            nrs++;
		}
    }
    delete[] s;
    nr=Dex.nr;
}
template <class K,class V>
Node<K,V>* Dictionar<K,V>::cautare(K x)
{
	if (root==NULL)
    {
		return 0;
	}
	Node<K,V>** s=new Node<K,V>*[nr];
	unsigned dim=0;
	Node<K,V>* p=root;
	if(p->cheie==x)
        return p;
    else
        while (p!=NULL || dim>0)
        {
            if(p->cheie==x)
                break;
            if (p!=NULL)
            {
                s[dim]=p;
                dim++;
                p=p->st;
            }
            else
            {
                p=s[dim-1];
                dim--;
                p=p->dr;

            }
        }
        delete[] s;
	return p;
}
template <class K,class V>
void Dictionar<K,V>::el(K x)
{
	Node<K,V>*p=root;
	Node<K,V>*t=root;
	bool gasit=false;
	while(!gasit && p!=NULL)
    {
		if(p->cheie==x)
        {
			gasit=true;
		}
		else
            if (x<p->cheie)
            {
                t=p;
                p=p->st;
            }
            else
            {
                t=p;
                p=p->dr;
            }
	}
	if(!gasit)
	{
		return;
	}
	if(p->dr==NULL && p->st==NULL)
	{
		if(t->dr==p)
		{
			t->dr=NULL;
		}
		else
		{
			t->st=NULL;
		}
		delete p;
        if(getDif(p)>1 && x<p->st->cheie)
            return rot_dr(p);
        if(getDif(p)>1 && x>p->st->cheie)
            {p->st=rot_st(p->st);
            return rot_dr(p);}
        if(getDif(p)<-1 && x>p->dr->cheie)
            return rot_st(p);
        if(getDif(p)<-1 && x<p->dr->cheie)
            {p->dr=rot_dr(p->dr);
            return rot_st(p);}
	}
	else
        if (p->st!=NULL && p->dr==NULL)
        {
            if(t->dr==p)
            {
                t->dr=p->st;
            }
            else
            {
                t->st=p->st;
            }
            delete p;
            if(getDif(p)>1 && x<p->st->cheie)
                return rot_dr(p);
            if(getDif(p)>1 && x>p->st->cheie)
                {p->st=rot_st(p->st);
                return rot_dr(p);}
            if(getDif(p)<-1 && x>p->dr->cheie)
                return rot_st(p);
            if(getDif(p)<-1 && x<p->dr->cheie)
                {p->dr=rot_dr(p->dr);
                return rot_st(p);}
        }
        else
            if(p->st==NULL && p->dr!=NULL)
            {
                if (t->dr==p)
                {
                    t->dr=p->dr;
                }
                else
                {
                    t->st=p->dr;
                }
                delete p;
                if(getDif(p)>1 && x<p->st->val)
                    return rot_dr(p);
                if(getDif(p)>1 && x>p->st->val)
                    {p->st=rot_st(p->st);
                    return rot_dr(p);}
                if(getDif(p)<-1 && x>p->dr->val)
                    return rot_st(p);
                if(getDif(p)<-1 && x<p->dr->val)
                    {p->dr=rot_dr(p->dr);
                    return rot_st(p);}
            }
            else
            {
                Node<K,V>*succesor=p->dr;
                t=p;
                while (succesor->st!=NULL)
                {
                    t=succesor;
                    succesor=succesor->st;
                }
                p->val=succesor->val;
                delete succesor;
                if (t==p)
                {
                    t->dr=NULL;
                }
                else
                {
                    t->st=NULL;
                }
            }
	nr--;
}
template <class K,class V>
void Dictionar<K,V>::eliminare(Dictionar<K,V> Dex)
{
	if (Dex.root==NULL)
    {
		return NULL;
	}
	queue<Node<K,V>* > coada;
	coada.push(root);
	Node<K,V>*p;
	while(!coada.empty())
    {
        p=coada.front();
        coada.pop();
        if(p->st)
            coada.push(p->st);
        if(p->dr)
            coada.push(p->dr);
        delete p;
    }
    root=NULL;
}
template <class K,class V>
int* Dictionar<K,V>::inordine() const
{
	if (root==NULL)
    {
		return 0;
	}
	int*v=new int[nr];
	int n=0;
	Node<K,V>** s=new Node<K,V>*[nr];
	unsigned dim=0;
	Node<K,V>* p=root;
	while (p!=NULL || dim>0)
    {
        if (p!=NULL)
        {
            s[dim]=p;
            dim++;
            p=p->st;
		}
		else
        {
			p=s[dim-1];
			v[n]=p->val;
            n++;
			dim--;
			p=p->dr;
		}
	}
	for(int i=0;i<n;i++)
        cout<<v[i]<<' ';
    delete[] s;
	return v;
}
template <class K,class V>
Dictionar<K,V>::~Dictionar()
{

}
template <class K,class V>
V Dictionar<K,V>::operator[](K x)
{
    Node<K,V>*p=cautare(x);
    return p.val;
}
template <class K,class V>
ostream& operator<<(ostream& out, const Dictionar<K,V>&Dex)
{
    Dex.inordine();
    return out;
}
