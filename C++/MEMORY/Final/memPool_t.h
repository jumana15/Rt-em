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
		size_t m_pagesNumber;
		vector<memPage*> m_v;
		void operator=(const memPool& mp);
		memPool(const memPool& mp);
		inline size_t getDefaultSize() const;
		
	protected:


	public:
		memPool();
		virtual size_t read(void* buffer,size_t size);
		virtual size_t read(void* buffer,size_t size,size_t position);
		virtual size_t write(const void* buffer,size_t size);
		virtual size_t write(const void* buffer,size_t size,size_t position);
		void print() const;
		virtual ~memPool();
};

inline size_t memPool::getDefaultSize() const { return m_v[0]->getCapacity(); }

#endif