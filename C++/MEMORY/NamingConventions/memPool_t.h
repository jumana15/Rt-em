#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <iostream>
#include <stdlib.h>
#include  <string>
#include <vector>
#include "memManager_t.h"
#include "memPage_t.h"

using namespace std;

class memPool : public memManager
{
	private:
		size_t m_dCapacity;
		size_t m_currentCapacity;
		size_t m_pagesNumber;
		vector<memPage*> m_v;
		memPool& operator=(const memPool& mp);
	protected:


	public:
		memPool();
		memPool(size_t capacity);
		virtual bool read(void* buffer,size_t* k,size_t size);
		virtual bool read(void* buffer,size_t* k,size_t size,size_t position);
		virtual bool write(void* buffer,size_t* k,size_t size);
		virtual bool write(void* buffer,size_t* k,size_t size,size_t position);
		inline size_t getDefaultSize() const;
		inline void setDefaultSize(size_t dCapacity);
		inline size_t getPagesActualSize() const;
		void print() const;
		virtual ~memPool();
};

inline size_t memPool::getDefaultSize() const { return this->m_dCapacity; }

inline void memPool::setDefaultSize(size_t dCapacity) { this->m_dCapacity=dCapacity; }

inline size_t memPool::getPagesActualSize() const { return memManager::getActualSize(); }

#endif