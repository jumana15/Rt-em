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
	for(*k=0;(cp<as)&&(*k<size);cp++,(*k)++)
	{
		((char*)buffer)[*k]=(this->v[cp/this->dCapacity])->getChar(cp%this->dCapacity);	
	}
	memManager::setCurrentPosition(cp);
	if(*k==size)
		return 1; 
	return 0;
}

bool memPool::read(void* buffer,size_t* k,size_t size,size_t position)
{
	size_t as=memManager::getActualSize();
	if(position>=as)
		return 0;
	for(*k=0;(position<as)&&((*k)<size);position++,(*k)++)
	{
		((char*)buffer)[*k]=(this->v[position/this->dCapacity])->getChar(position%this->dCapacity);		
	}
	memManager::setCurrentPosition(position);
	if(*k==size)
		return 1; 
	return 0;
}

bool memPool::write(void* buffer,size_t* k,size_t size)
{
	size_t cp=memManager::getCurrentPosition();
	size_t as=memManager::getActualSize();
	for(*k=0;*k<size;cp++,(*k)++)
	{
		if(cp>=this->currentCapacity)
		{
			memPage* m=this->v[(cp-1)/this->dCapacity];
			m->setActualSize(m->getCapacity());
			m->setCurrentPosition(m->getCapacity());
			memPage* pg= new memPage(this->dCapacity);
			this->v.insert(this->v.end(),pg);	
			this->pagesNumber++;
			this->currentCapacity+=this->dCapacity;
		}
		(this->v[cp/this->dCapacity])->setChar(cp%this->dCapacity,((char*)buffer)[*k]);	
		/*size_t z=this->v[cp/this->dCapacity]->getCpacity()-(cp%this->dCapacity);
		if(z<size)
		{
			v[cp/this->dCapacity]->write(buffer,k,z,cp%this->dCapacity);
			if(v[cp/this->dCapacity]==v.end())
			{
				memPage* pg= new memPage(this->dCapacity);
				this->v.insert(this->v.end(),pg);	
				this->pagesNumber++;
				this->currentCapacity+=this->dCapacity;
			}
			v[cp/this->dCapacity+1]->write((void*)((char*)buffer+z),k,size-z);
		}
		else
		{
			v[cp/this->dCapacity]->write(buffer,k,size,cp%this->dCapacity);
		}*/
	}
	memManager::setCurrentPosition(cp);
	if(cp>as)
	{
			memManager::setActualSize(cp);
	}
	if(cp%this->dCapacity==0)
	{
		this->v[(cp-1)/this->dCapacity]->setActualSize(this->dCapacity);
		this->v[(cp-1)/this->dCapacity]->setCurrentPosition(this->dCapacity);
	}
	else
	{
		if(this->v[cp/this->dCapacity]->getActualSize()<cp%this->dCapacity)
			this->v[cp/this->dCapacity]->setActualSize(cp%this->dCapacity);
		this->v[cp/this->dCapacity]->setCurrentPosition(cp%this->dCapacity);
	}
	if(*k==size)
		return 1;
	return 0;
}

bool memPool::write(void* buffer,size_t* k,size_t size,size_t position)
{
	size_t cp=memManager::getCurrentPosition();
	size_t as=memManager::getActualSize();
	if(position>as)
	{
		return 0;
	}
	for(*k=0;(*k)<size;position++,(*k)++)
	{
		if(position>=this->currentCapacity)
		{
			memPage* m=this->v[(position-1)/this->dCapacity];
			m->setActualSize(m->getCapacity());
			m->setCurrentPosition(m->getCapacity());
			memPage* pg= new memPage(this->dCapacity);
			this->v.insert(this->v.end(),pg);	
			this->pagesNumber++;
			this->currentCapacity+=this->dCapacity;
		}
		(this->v[position/this->dCapacity])->setChar(position%this->dCapacity,((char*)buffer)[*k]);	
	}
	memManager::setCurrentPosition(position);
	if(position>as)
	{
			memManager::setActualSize(position);
	}
	if(position%this->dCapacity==0)
	{
		this->v[(position-1)/this->dCapacity]->setActualSize(this->dCapacity);
		this->v[(position-1)/this->dCapacity]->setCurrentPosition(this->dCapacity);
	}
	else
	{
		if(this->v[position/this->dCapacity]->getActualSize()<position%this->dCapacity)
			this->v[position/this->dCapacity]->setActualSize(position%this->dCapacity);
		this->v[position/this->dCapacity]->setCurrentPosition(position%this->dCapacity);
	}
	if(*k==size)
		return 1;
	return 0;
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