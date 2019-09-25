#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "car_t.h"
#include "private_t.h"

private_t::private_t():car_t()
{
	car_t::setGear(1);
	car_t::setName("PRIVATE");
	this->accelerate=10;
	this->reduceSpeed=10;
}
private_t::private_t(const string capacity):car_t(capacity)
{
	car_t::setGear(1);
	car_t::setName("PRIVATE");
	this->accelerate=10;
	this->reduceSpeed=10;
}
private_t::private_t(const private_t& car):car_t(car)
{
	car_t::setGear(1);
	this->accelerate=car.getAccelerate();
	this->reduceSpeed=car.getReduceSpeed();
}
void private_t::print() const
{
	cout<<"Accelerate: "<<this->accelerate<<"\tReduce Speed: "<<this->reduceSpeed<<"\t";
	car_t::print();
}
/*private_t& private_t::operator=(const private_t& car)
{
	car_t::operator=(car);
	this->accelerate=car.getAccelerate();
	this->reduceSpeed=car.getReduceSpeed();
}*/
private_t::~private_t(){}


