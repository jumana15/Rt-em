#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memPool_t.h"

using namespace std;

memPool::memPool():memManager(),dCapacity(6),currentCapacity(6)
{
	memPage* pg= new memPage(this->dCapacity);
	(this->v).insert((this->v).end(),pg);	
	this->pagesNumber=1;
}

memPool::memPool(size_t capacity):memManager(),dCapacity(capacity),currentCapacity(capacity)
{
	memPage* pg= new memPage(this->dCapacity);
	this->v.insert(this->v.end(),pg);	
	this->pagesNumber=1;
}

memPool::~memPool()
{         
    for(size_t i=0;i<v.size();i++)
    {
    	delete v[i];
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
		v[cp/this->dCapacity]->read(buffer,k,size,cp%this->dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		cp+=(*k);
		z+=(*k);
	}
	memManager::setCurrentPosition(cp);
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
		v[position/this->dCapacity]->read(buffer,k,size,position%this->dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		position+=(*k);
		z+=(*k);
	}
	memManager::setCurrentPosition(position);
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
		if(cp>=this->currentCapacity)
		{
			memPage* pg= new memPage(this->dCapacity);
			this->v.insert(this->v.end(),pg);	
			this->pagesNumber++;
			this->currentCapacity+=this->dCapacity;
		}
		v[cp/this->dCapacity]->write(buffer,k,size,cp%this->dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		cp+=(*k);
		z+=(*k);
	}
	memManager::setCurrentPosition(cp);
	if(cp>as)
	{
			memManager::setActualSize(cp);
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
		if(position>=this->currentCapacity)
		{
			memPage* pg= new memPage(this->dCapacity);
			this->v.insert(this->v.end(),pg);	
			this->pagesNumber++;
			this->currentCapacity+=this->dCapacity;
		}
		v[position/this->dCapacity]->write(buffer,k,size,position%this->dCapacity);
		buffer=((char*)buffer)+(*k);
		size-=(*k);
		position+=(*k);
		z+=(*k);
	}
	memManager::setCurrentPosition(position);
	if(position>as)
	{
			memManager::setActualSize(position);
	}
	(*k)=z;
	return 1;
}

void memPool::print() const
{
	memManager::print();
	cout<<"Pages Number= "<<this->pagesNumber<<endl;		
	cout<<"Current Capacity= "<<this->currentCapacity<<endl;
	for(int i=0;i<this->pagesNumber;i++)
	{
		cout<<"Page "<<i<<": "<<endl;
		v[i]->print();
	}
}