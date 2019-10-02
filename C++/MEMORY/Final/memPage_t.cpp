#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memManager_t.h"
#include "memPage_t.h"

size_t memPage::m_capacity=6;

memPage::memPage():memManager()
{
	this->m_buffer=new char[this->m_capacity];
}

memPage::~memPage()
{
	delete[] m_buffer;
}

size_t memPage::read(void* buffer,size_t size)
{
	size_t k=0;
	size_t cp=getCurrentPosition();
	size_t as=getActualSize();
	try
	{
		setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	for(k=0;(cp<as)&&(k<size);cp++,(k)++)
	{
		((char*)buffer)[k]=this->m_buffer[cp];	
	}
	try
	{
		setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	return k;
}

size_t memPage::read(void* buffer,size_t size,size_t position)
{
	size_t k;
	size_t as=getActualSize();
	try
	{
		setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	for(k=0;(position<as)&&(k<size);position++,(k)++)
	{
		((char*)buffer)[k]=this->m_buffer[position];	
	}
	try
	{
		setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
	}
	return k;
}

size_t memPage::write(const void* buffer,size_t size)
{
	size_t k;
	size_t cp=getCurrentPosition();
	size_t as=getActualSize();
	try
	{
		setCurrentPosition(cp);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	for(k=0;(cp<this->m_capacity)&&(k<size);cp++,(k)++)
	{
		this->m_buffer[cp]=((char*)buffer)[k];	
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
	return k;
}

size_t memPage::write(const void* buffer,size_t size,size_t position)
{
	size_t k;
	size_t cp=getCurrentPosition();
	size_t  as=getActualSize();
	try
	{
		setCurrentPosition(position);
	} 
	catch(...)
	{
		cout<<"An Exception occurred!"<<endl;
		return 0;
	}
	for(k=0;(position<this->m_capacity)&&(k<size);position++,(k)++)
	{
		this->m_buffer[position]=((char*)buffer)[k];	
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
	return k;
}

void memPage::print() const
{
	memManager::print();
	cout<<"Capacity= "<<this->m_capacity<<endl;
	for(int i=0;i<this->getActualSize();i++)
	{
		cout<<this->m_buffer[i]<<" ";
	}
	cout<<endl;
}