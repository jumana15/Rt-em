#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "car_t.h"
#include "bus_t.h"

bus_t::bus_t():car_t()
{
	car_t::setGear(0);
	car_t::setName("BUS");
	this->seatsNumber=0;
	this->lineNumber="000";
}
bus_t::bus_t(const string capacity):car_t(capacity)
{
	car_t::setGear(0);
	car_t::setName("BUS");
	this->seatsNumber=0;
	this->lineNumber="000";
}
bus_t::bus_t(const bus_t& car):car_t(car)
{
	car_t::setGear(0);
	this->seatsNumber=0;
	this->lineNumber="000";
}
void bus_t::print() const
{
	cout<<"Seats Number: "<<this->seatsNumber<<"\tLine Number: "<<this->lineNumber<<"\t";
	car_t::print();
}
bus_t::~bus_t(){}
