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
		static size_t m_capacity;
		char* m_buffer;
		void operator=(const memPage& mp);
		memPage(const memPage& mp);

	protected:

	public:
		memPage();
		virtual size_t read(void* buffer,size_t size);
		virtual size_t read(void* buffer,size_t size,size_t position);
		virtual size_t write(const void* buffer,size_t size);
		virtual size_t write(const void* buffer,size_t size,size_t position);
		inline size_t getCapacity() const;
		//inline void setCapacity(size_t capacity);
		void print() const;
		inline bool isFull() const;
		virtual ~memPage();

};

inline size_t memPage::getCapacity() const { return this->m_capacity; }

//inline void memPage::setCapacity(size_t capacity) { this->m_capacity=capacity; }

inline bool memPage::isFull() const { return this->m_capacity==memManager::getActualSize(); }

#endif