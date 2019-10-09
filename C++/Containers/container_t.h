#ifndef CONTAINERT_H
#define CONTAINERT_H

#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string>

using namespace std;

template<class T,class C> class  tContainer_t
{
	private:
		C m_cont;
		tContainer_t(const tContainer_t& c);
		tContainer_t& operator=(const tContainer_t& c);
		typedef typename C::iterator Iter_t;
		typedef typename C::const_iterator cIter_t;

	public:
		tContainer_t();
		bool isEmpty() const;
		size_t elementsNumber() const;
		void insertElement(T* t);
		T* getFirst() const;
		T* getLast() const;
		T* findElement(T& t) const;
		T* removeElement(T& t);
		void removeElements();
		void deleteElement(T& t);
		void deleteElements();
		T* operator[](size_t index) const;
		~tContainer_t();
};

template<class T> class Equal
{
	private:
		T m_t;

	public:
		Equal(T& t){ m_t=t; }
		bool operator()(T* t){ return m_t==*t; }
};

template<class T,class C> tContainer_t<T,C>::tContainer_t(){}

template<class T,class C> bool tContainer_t<T,C>::isEmpty() const{ return m_cont.empty(); } 

template<class T,class C> size_t tContainer_t<T,C>::elementsNumber() const{ return m_cont.size(); }

template<class T,class C> void tContainer_t<T,C>::insertElement(T* t){ m_cont.push_back(t); }

template<class T,class C> T* tContainer_t<T,C>::getFirst() const{ return *(m_cont.begin()); }

template<class T,class C> T* tContainer_t<T,C>::getLast() const{ return *(m_cont.rbegin()); }

template<class T,class C> T* tContainer_t<T,C>::findElement(T& t) const
{ 
	cIter_t it=(find_if(m_cont.begin(),m_cont.end(),Equal<T>(t))); 
	if(it==m_cont.end())
		return NULL;
	return *it;
}

template<class T,class C> T* tContainer_t<T,C>::removeElement(T& t)
{
	T* ret=NULL;
	Iter_t it=(find_if(m_cont.begin(),m_cont.end(),Equal<T>(t))); 
	if(it!=m_cont.end())
	{
		ret=*it;
		m_cont.erase(it);
	}
	return ret;
}

template<class T,class C> void tContainer_t<T,C>::removeElements()
{
	m_cont.erase(m_cont.begin(),m_cont.end());// or m_cont.clear();
}

template<class T,class C> void tContainer_t<T,C>::deleteElement(T& t)
{
	Iter_t it=(find_if(m_cont.begin(),m_cont.end(),Equal<T>(t))); 
	if(it!=m_cont.end())
	{
		delete *it;
		m_cont.erase(it);
	}
}

template<class T,class C> void tContainer_t<T,C>::deleteElements()
{
	for(Iter_t it=m_cont.begin();it!=m_cont.end();++it)
	{
		delete *it;
	}
	m_cont.erase(m_cont.begin(),m_cont.end());// or m_cont.clear();
}

template<class T,class C> T* tContainer_t<T,C>::operator[](size_t index) const
{
	if(index>=m_cont.size())
	{
		string s="IndexOutOfBounds!";
		throw(s);

	}
	/*if(typeid(C)==typeid(vector<T*>))
	{
		return ((vector<T*>)m_cont)[index];
	}*/
	cIter_t it;
	for(it=m_cont.begin();index>0;it++,index--);
	return *it;
}

template<class T,class C> tContainer_t<T,C>::~tContainer_t()
{
	if(!isEmpty())
		m_cont.erase(m_cont.begin(),m_cont.end());// or m_cont.clear();
}

#endif