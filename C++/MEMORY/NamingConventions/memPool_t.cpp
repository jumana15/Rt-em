#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memPool_t.h"

using namespace std;

memPool::memPool():memManager(),m_dCapacity(6),m_currentCapacity(6)
{
	memPage* pg= new memPage(this->m_dCapacity);
	(this->m_v).insert((this->m_v).end(),pg);	
	this->m_pagesNumber=1;
}

memPool::memPool(size_t capacity):memManager(),m_dCapacity(capacity),m_currentCapacity(capacity)
{
	memPage* pg= new memPage(this->m_dCapacity);
	this->m_v.insert(this->m_v.end(),pg);	
	this->m_pagesNumber=1;
}

memPool::~memPool()
{         
    for(size_t i=0;i<m_v.size();i++)
    {
    	delete m_v[i];
    }
}

bool memPool::read(void* buffer,size_t* k,size_t size)
{
	size_t as=memManager::getActualSize();
	size_t cp=memManager::getCurrentPosition();
	size_t z=0;
	bool flag=1;
	if(cp>=as)
		return 0;
	while((size>0)&&(cp<as))
	{
		if(as-cp<size)
		{
			size=as-cp;
			flag=0;
		}
		m_v[cp/this->m_dCapacity]->read(buffer,k,size,cp%this->m_dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		cp+=(*k);
		z+=(*k);
	}
	try
	{
		memManager::setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	(*k)=z;
	return flag;
}

bool memPool::read(void* buffer,size_t* k,size_t size,size_t position)
{
	size_t as=memManager::getActualSize();
	size_t z=0;
	bool flag=1;
	if(position>=as)
		return 0;
	while((size>0)&&(position<as))
	{
		if(as-position<size)
		{
			size=as-position;
			flag=0;
		}
		m_v[position/this->m_dCapacity]->read(buffer,k,size,position%this->m_dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		position+=(*k);
		z+=(*k);
	}
	try
	{
		memManager::setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	(*k)=z;
	return flag;
}

bool memPool::write(void* buffer,size_t* k,size_t size)
{
	size_t cp=memManager::getCurrentPosition();
	size_t as=memManager::getActualSize();
	size_t z=0;
	while(size>0)
	{
		if(cp>=this->m_currentCapacity)
		{
			memPage* pg= new memPage(this->m_dCapacity);
			this->m_v.insert(this->m_v.end(),pg);	
			this->m_pagesNumber++;
			this->m_currentCapacity+=this->m_dCapacity;
		}
		m_v[cp/this->m_dCapacity]->write(buffer,k,size,cp%this->m_dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		cp+=(*k);
		z+=(*k);
	}
	if(cp>as)
	{
		memManager::setActualSize(cp);
	}
	try
	{
		memManager::setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	(*k)=z;
	return 1;
}

bool memPool::write(void* buffer,size_t* k,size_t size,size_t position)
{
	size_t as=memManager::getActualSize();
	size_t z=0;
	if(position>as)
	{
		return 0;
	}
	while(size>0)
	{
		if(position>=this->m_currentCapacity)
		{
			memPage* pg= new memPage(this->m_dCapacity);
			this->m_v.insert(this->m_v.end(),pg);	
			this->m_pagesNumber++;
			this->m_currentCapacity+=this->m_dCapacity;
		}
		m_v[position/this->m_dCapacity]->write(buffer,k,size,position%this->m_dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		position+=(*k);
		z+=(*k);
	}
	if(position>as)
	{
		memManager::setActualSize(position);
	}
	try
	{
		memManager::setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	(*k)=z;
	return 1;
}

void memPool::print() const
{
	memManager::print();
	cout<<"Pages Number= "<<this->m_pagesNumber<<endl;		
	cout<<"Current Capacity= "<<this->m_currentCapacity<<endl;
	for(int i=0;i<this->m_pagesNumber;i++)
	{
		cout<<"Page "<<i<<": "<<endl;
		m_v[i]->print();
	}
}