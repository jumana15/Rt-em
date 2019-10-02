#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "memManager_t.h"

using namespace std;

memManager::memManager():m_actualSize(0),m_currentPosition(0){}

bool memManager::read(void* buffer,size_t* k,size_t size) const { return 0; } 

bool memManager::read(void* buffer,size_t* k,size_t size,size_t position) const { return 0; }

bool memManager::write(void* buffer,size_t* k,size_t size) { return 0; }

bool memManager::write(void* buffer,size_t* k,size_t size,size_t position) { return 0; }

memManager::~memManager(){}

size_t memManager::setCurrentPosition(size_t currentPosition) 
{ 
	int flag=-1;
	if(currentPosition<=memManager::getActualSize())
	{
		this->m_currentPosition=currentPosition; 
	}
	else
	{
		throw(flag);
	}
}
		
void memManager::print() const
{
	cout<<"Actual Size= "<<this->m_actualSize<<endl;
	cout<<"Current Position= "<<this->m_currentPosition<<endl;
}