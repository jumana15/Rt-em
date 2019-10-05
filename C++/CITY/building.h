#ifndef BUILDING_H
#define BUILDING_H

#include<stdio.h>
#include<vector>

using namespace std;

template<class B>
class Building_t
{
	private:
		B m_buildingID;

	public:
		Building_t();
		Building_t(const Building_t& b);
		Building_t<B>& operator=(const Building_t& b);
		inline void setBuidingID(const B buildingID);
		inline const B getBuildingID() const;
		~Building_t();
};

template<class B> 
Building_t<B>::Building_t(){}

template<class B> 
Building_t<B>::Building_t(const Building_t& b){ this->m_buildingID=b.getBuildingID(); }

/*template<class B> 
Building_t<B>& Building_t<B>::operator=(const Building_t& b)
{ 
	if(this!=&b)
		this->m_buildingID=b.getBuildingID(); 
	return *this;
}*/

template<class B> 
inline void Building_t<B>::setBuidingID(const B buildingID){ this->m_buildingID=buildingID; }

template<class B> 
inline const B Building_t<B>::getBuildingID() const{ return this->m_buildingID; }

template<class B> 
Building_t<B>::~Building_t(){}


#endif
