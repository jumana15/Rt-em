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
		
		size_t actualSize;
		size_t currentPosition;

	protected:

		virtual bool read(void* buffer,size_t* k,size_t size) const;
		virtual bool read(void* buffer,size_t* k,size_t size,size_t position) const;
		virtual bool write(void* buffer,size_t* k,size_t size);
		virtual bool write(void* buffer,size_t* k,size_t size,size_t position);
		void print() const;
		

	public:
		memManager();
		size_t setCurrentPosition(size_t currentPosition);
		inline size_t setActualSize(size_t actualSize);
		inline size_t getCurrentPosition() const;
		inline size_t getActualSize() const;
		inline bool isEmpty() const;
		virtual ~memManager()=0;

};

inline size_t memManager::getCurrentPosition() const { return this->currentPosition; }

inline size_t memManager::getActualSize() const { return this->actualSize; }

inline size_t memManager::setActualSize(size_t actualSize) 
{
	if(actualSize>this->actualSize) 
		this->actualSize=actualSize; 
}

inline bool memManager::isEmpty() const { return !(this->actualSize); }

#endif
