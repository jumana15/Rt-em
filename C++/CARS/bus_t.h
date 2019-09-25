#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <stdlib.h>
#include  <string>
#include "car_t.h"

class bus_t: public car_t
{
	private:
		int seatsNumber;
		string lineNumber;

	protected:

	public:
		bus_t();
		bus_t(const string capacity);
		bus_t(const bus_t& car);
		inline int getSeatsNumber();
		inline void setSeatsNumber(int seatsNumber);
		inline string getLineNumber();
		inline void setLineNumber(string lineNumber);
		void print() const;
		~bus_t();

};

inline int bus_t::getSeatsNumber() { return this->seatsNumber; }

inline void bus_t::setSeatsNumber(int seatsNumber) { this->seatsNumber=seatsNumber; }

inline string bus_t::getLineNumber() { return this->lineNumber; }

inline void bus_t::setLineNumber(string lineNumber) { this->lineNumber=lineNumber; }

#endif

