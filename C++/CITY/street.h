#ifndef STREET_H
#define STREET_H

#include<stdio.h>
#include<vector>
#include "building.h"

template<class S,class B> 
class Street_t
{
	private:
		S m_steetID;
		vector<Building_t<B>*> m_buildingsVec;

	public:
		Street_t();
		Street_t(const Street_t& s);
		Street_t<S,B>& operator=(const Street_t& s);
		inline void setStreetID(const S& streetID);
		inline const S& getStreetID() const;
		void AddBuilding2Street(const Building_t<B>* b);
		const Building_t<B>* getBuilding(int index) const;
		const vector<Building_t<B>*> getVec() const;
		~Street_t();
};

template<class S,class B> 
Street_t<S,B>::Street_t(){}

template<class S,class B> 
Street_t<S,B>::Street_t(const Street_t& s)
{
	vector<Building_t<B>*> v=s.getVec(); 
	this->m_steetID=s.getStreetID();
	for(int i=0;i<v.size();i++)
	{
		m_buildingsVec.AddBuilding2Street(v[i]);
	}
}

/*template<class S,class B> 
Street_t<S,B>& Street_t<S,B>::operator=(const Street_t<S,B>& s)
{
	if(this!=&s)
	{
		vector<Building_t<B>*> v=s.getVec();
		Building_t<B>* b;
		for(int i=0;i<m_buildingsVec.size();i++)
		{
			delete m_buildingsVec[i];
		} 
		m_buildingsVec.clear();
		this->m_steetID=s.getStreetID();
		for(int i=0;i<v.size();i++)
		{
			b=new Building_t<B>;
			*b=*v[i];
			m_buildingsVec.AddBuilding2Street(b);
		}
		return *this;
}*/

template<class S,class B> inline void Street_t<S,B>::setStreetID(const S& streetID){ this->m_steetID=streetID; }

template<class S,class B> 
inline const S& Street_t<S,B>::getStreetID() const { return this->m_steetID; }

template<class S,class B> 
void Street_t<S,B>::AddBuilding2Street(const Building_t<B>* b){ m_buildingsVec.push_back((Building_t<B>*)b); }

template<class S,class B> 
const Building_t<B>* Street_t<S,B>::getBuilding(int index) const
{
	if(index>=m_buildingsVec.size())
	{
		throw("IndexOutOfBounds!");
	}
	return m_buildingsVec[index];
}

template<class S,class B> 
const vector<Building_t<B>*> Street_t<S,B>::getVec() const { return m_buildingsVec; }

template<class S,class B> 
Street_t<S,B>::~Street_t()
{
	/*for(int i=0;i<m_buildingsVec.size();i++)
	{
		delete m_buildingsVec[i];
	}
	m_buildingsVec.clear();*/
}

#endif