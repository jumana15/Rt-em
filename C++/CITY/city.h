#ifndef CITY_H
#define CITY_H

#include<stdio.h>
#include"building.h"
#include "street.h"

template<class C,class S,class B> 
class City_t
{
	private:
		C m_cityID;
		vector<Street_t<S,B>*> m_streetsVec;
	public:
		City_t();
		City_t(const City_t& c);
		City_t<C,S,B>& operator=(const City_t& c);
		inline void setCityID(const C& cityID);
		inline const C& getCityID() const;
		void AddStreet(const Street_t<S,B>* s);
		const Street_t<S,B>* getStreet(int index) const;
		const vector<Street_t<S,B>*> getVec() const;
		~City_t();
};

template<class C,class S,class B>
City_t<C,S,B>::City_t(){}

template<class C,class S,class B>
City_t<C,S,B>::City_t(const City_t& c)
{
	vector<Street_t<S,B>*> v=c.getVec(); 
	this->m_cityID=c.getCityID();
	for(int i=0;i<v.size();i++)
	{
		m_streetsVec.AddStreet(v[i]);
	}
}

template<class C,class S,class B>
inline void City_t<C,S,B>::setCityID(const C& cityID){ this->m_cityID=cityID; }

template<class C,class S,class B>
inline const C& City_t<C,S,B>::getCityID() const{ return this->m_cityID; }

template<class C,class S,class B>
void City_t<C,S,B>::AddStreet(const Street_t<S,B>* s){ m_streetsVec.push_back((Street_t<S,B>*)s); }

template<class C,class S,class B> 
const Street_t<S,B>* City_t<C,S,B>::getStreet(int index) const
{
	if(index>=m_streetsVec.size())
	{
		throw("IndexOutOfBounds!");
	}
	return m_streetsVec[index];
}

template<class C,class S,class B> 
const vector<Street_t<S,B>*> City_t<C,S,B>::getVec() const{ return m_streetsVec; }

template<class C,class S,class B>
City_t<C,S,B>::~City_t()
{
	for(int i=0;i<m_streetsVec.size();i++)
		{
			delete m_streetsVec[i];
		}
		m_streetsVec.clear();
}

/*template<class C,class S,class B>
City_t& City_t<C,S,B>::operator=(const City_t& c)
{
	if(this!=&c)
	{
		vector<Street_t<S,B>*> v=c.getVec(); 
		Street_t<S,B>* s;
		for(int i=0;i<m_streetsVec.size();i++)
		{
			delete m_streetsVec[i];
		}
		m_streetsVec.clear();
		this->m_cityID=c.getCityID();
		for(int i=0;i<v.size();i++)
		{
			s=new Street_t<S,B>;
			*s=*v[i];
			m_streetsVec.AddStreet(s);
		}
	}
	return *this;
}*/
#endif