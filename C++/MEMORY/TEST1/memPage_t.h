#ifndef MEMPAGE_H
#define MEMPAGE_H

#include <iostream>
#include <stdlib.h>
#include  <string>
#include <vector>
#include "memManager_t.h"

using namespace std;

class memPage : public memManager
{
	private:
		size_t capacity;
		char* buffer;
		//inline size_t setCapacity(size_t capacity);
		memPage& operator=(const memPage& mp);

	protected:

	public:
		memPage();
		memPage(size_t capacity);
		virtual bool read(void* buffer,size_t* k,size_t size);
		virtual bool read(void* buffer,size_t* k,size_t size,size_t position);
		virtual bool write(void* buffer,size_t* k,size_t size);
		virtual bool write(void* buffer,size_t* k,size_t size,size_t position);
		inline size_t getCapacity() const;
		inline void setCapacity(size_t capacity);
		inline size_t getChar(size_t index) const;
		void setChar(size_t index,char c);
		void print() const;
		inline bool isFull() const;
		virtual ~memPage();

};

inline size_t memPage::getCapacity() const { return this->capacity; }

inline void memPage::setCapacity(size_t capacity) { this->capacity=capacity; }

inline size_t memPage::getChar(size_t index) const { return this->buffer[index]; }

inline bool memPage::isFull() const { return this->capacity==memManager::getActualSize(); }

#endif