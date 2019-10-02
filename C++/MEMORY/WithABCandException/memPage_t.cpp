#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memManager_t.h"
#include "memPage_t.h"

memPage::memPage():memManager(),capacity(6)
{
	this->buffer=new char[this->capacity];
}

memPage::memPage(size_t capacity):memManager(),capacity(capacity)
{
	this->buffer=new char[this->capacity];
}

memPage::~memPage()
{
	delete[] buffer;
}

void memPage::setChar(size_t index,char c) 
{	
	if(index<this->capacity) 
		this->buffer[index]=c; 
}

bool memPage::read(void* buffer,size_t* k,size_t size)
{
	size_t cp=memManager::getCurrentPosition();
	size_t  as=memManager::getActualSize();
	for(*k=0;(cp<as)&&(*k<size);cp++,(*k)++)
	{
		((char*)buffer)[*k]=this->buffer[cp];	
	}
	try
	{
		memManager::setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	if(*k==size)
		return 1; 
	return 0;
}

bool memPage::read(void* buffer,size_t* k,size_t size,size_t position)
{
	size_t  as=memManager::getActualSize();
	for(*k=0;(position<as)&&(*k<size);position++,(*k)++)
	{
		((char*)buffer)[*k]=this->buffer[position];	
	}
	try
	{
		memManager::setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	if(*k==size)
		return 1; 
	return 0;
}

bool memPage::write(void* buffer,size_t* k,size_t size)
{
	size_t cp=memManager::getCurrentPosition();
	size_t as=memManager::getActualSize();
	for(*k=0;(cp<this->capacity)&&(*k<size);cp++,(*k)++)
	{
		this->buffer[cp]=((char*)buffer)[*k];	
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
	if((*k)==size)
		return 1; 
	return 0;
}

bool memPage::write(void* buffer,size_t* k,size_t size,size_t position)
{
	size_t cp=memManager::getCurrentPosition();
	size_t  as=memManager::getActualSize();
	if(position>as)
	{
		return 0;
	}
	for(*k=0;(position<this->capacity)&&(*k<size);position++,(*k)++)
	{
		this->buffer[position]=((char*)buffer)[*k];	
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
	if(*k==size)
		return 1; 
	return 0;
}

void memPage::print() const
{
	memManager::print();
	cout<<"Capacity= "<<this->capacity<<endl;
	for(int i=0;i<this->getActualSize();i++)
	{
		cout<<this->buffer[i]<<" ";
	}
	cout<<endl;
}