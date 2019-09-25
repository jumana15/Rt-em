#ifndef PRIVATE_H
#define PRIVATE_H

#include <iostream>
#include <stdlib.h>
#include  <string>
#include "car_t.h"

class private_t: public car_t
{
	private:
		int accelerate;
		int reduceSpeed; 

	protected:

	public:
		private_t();
		private_t(const string capacity);
		private_t(const private_t& car);
		inline int getAccelerate() const;
		inline void setAccelerate(int a);
		inline int getReduceSpeed() const;
		inline void setReduceSpeed(int r);
		void print() const;
		~private_t();
};

inline int private_t::getAccelerate() const { return this->accelerate; }

inline void private_t::setAccelerate(int a) { this->accelerate=a; }

inline int private_t::getReduceSpeed() const {return this->reduceSpeed; }

inline void private_t::setReduceSpeed(int r) { this->reduceSpeed=r; }

#endif