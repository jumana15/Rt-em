#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include <iostream>
#include <stdlib.h>
#include  <string>
#include <vector>

using namespace std;

class memManager
{
	private:
		
		size_t m_actualSize;
		size_t m_currentPosition;
		void operator=(const memManager& mp){};
		memManager(const memManager& mp){};

	protected:
		void print() const;

	public:
		memManager();
		virtual size_t read(void* buffer,size_t size)=0;
		virtual size_t read(void* buffer,size_t size,size_t position)=0;
		virtual size_t write(const void* buffer,size_t size)=0;
		virtual size_t write(const void* buffer,size_t size,size_t position)=0;
		size_t setCurrentPosition(size_t currentPosition);
		inline size_t setActualSize(size_t actualSize);
		inline size_t getCurrentPosition() const;
		inline size_t getActualSize() const;
		inline bool isEmpty() const;
		virtual ~memManager()=0;

};

inline size_t memManager::getCurrentPosition() const { return this->m_currentPosition; }

inline size_t memManager::getActualSize() const { return this->m_actualSize; }

inline size_t memManager::setActualSize(size_t actualSize) 
{
	if(actualSize>this->m_actualSize) 
		this->m_actualSize=actualSize; 
}

inline bool memManager::isEmpty() const { return !(this->m_actualSize); }

#endif
