#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memPool_t.h"

using namespace std;

memPool::memPool():memManager()
{
	memPage* pg= new memPage();
	(this->m_v).insert((this->m_v).end(),pg);	
	this->m_pagesNumber=1;
}

memPool::~memPool()
{         
    for(size_t i=0;i<m_v.size();i++)
    {
    	delete m_v[i];
    }
}

size_t memPool::read(void* buffer,size_t size)
{
	size_t k,z=0;
	size_t as=getActualSize();
	size_t cp=getCurrentPosition();
	size_t m_dCapacity=m_v[0]->getCapacity();
	try
	{
		setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	if(as-cp<size)
	{
		size=as-cp;
	}
	while((size>0)&&(cp<as))
	{
		k=m_v[cp/m_dCapacity]->read(buffer,size,cp%m_dCapacity);
		buffer=((char*)buffer)+(k);
		size-=(k);
		cp+=(k);
		z+=(k);
	}
	try
	{
		setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	return z;
}

size_t memPool::read(void* buffer,size_t size,size_t position)
{
	size_t as=getActualSize();
	size_t k,z=0;
	size_t m_dCapacity=m_v[0]->getCapacity();
	try
	{
		setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	if(as-position<size)
	{
		size=as-position;
	}
	while((size>0)&&(position<as))
	{
		k=m_v[position/m_dCapacity]->read(buffer,size,position%m_dCapacity);
		buffer=((char*)buffer)+(k);
		size-=(k);
		position+=(k);
		z+=(k);
	}
	try
	{
		setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	return z;
}

size_t memPool::write(const void* buffer,size_t size)
{
	size_t cp=getCurrentPosition();
	size_t as=getActualSize();
	size_t m_currentCapacity=(m_v[0]->getCapacity())*(this->m_pagesNumber);
	size_t k,z=0;
	size_t m_dCapacity=m_v[0]->getCapacity();
	try
	{
		setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	while(size>0)
	{
		if(cp==m_currentCapacity)
		{
			memPage* pg= new memPage();
			this->m_v.insert(this->m_v.end(),pg);	
			this->m_pagesNumber++;
			m_currentCapacity+=m_dCapacity;
		}
		k=m_v[cp/m_dCapacity]->write(buffer,size,cp%m_dCapacity);
		buffer=((char*)buffer)+(k);
		size-=(k);
		cp+=(k);
		z+=(k);
	}
	if(cp>as)
	{
		setActualSize(cp);
	}
	try
	{
		setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	return z;
}

size_t memPool::write(const void* buffer,size_t size,size_t position)
{
	size_t as=getActualSize();
	size_t m_currentCapacity=(m_v[0]->getCapacity())*(this->m_pagesNumber);
	size_t k,z=0;
	size_t m_dCapacity=m_v[0]->getCapacity();
	try
	{
		setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	while(size>0)
	{
		if(position==m_currentCapacity)
		{
			memPage* pg= new memPage();
			this->m_v.insert(this->m_v.end(),pg);	
			this->m_pagesNumber++;
			m_currentCapacity+=m_dCapacity;
		}
		k=m_v[position/m_dCapacity]->write(buffer,size,position%m_dCapacity);
		buffer=((char*)buffer)+(k);
		size-=(k);
		position+=(k);
		z+=(k);
	}
	if(position>as)
	{
		setActualSize(position);
	}
	try
	{
		setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	return z;
}

void memPool::print() const
{
	size_t m_currentCapacity=(m_v[0]->getCapacity())*(this->m_pagesNumber);
	memManager::print();
	cout<<"Pages Number= "<<this->m_pagesNumber<<endl;		
	cout<<"Current Capacity= "<<m_currentCapacity<<endl;
	for(int i=0;i<this->m_pagesNumber;i++)
	{
		cout<<"Page "<<i<<": "<<endl;
		m_v[i]->print();
	}
}