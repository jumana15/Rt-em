#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "car_t.h"

using namespace std;

size_t car_t::IDcounter=0;

car_t::car_t():id(IDcounter++),capacity("0cc"){}
car_t::car_t(const string capacity):id(IDcounter++),capacity(capacity){}
car_t::car_t(const car_t& car):id(IDcounter++),name(car.getName()),capacity(car.getCapacity()){}
car_t& car_t::operator=(const car_t& car)
{
	if(this!= &car)
	{
		car_t::setCapacity((string)car.getCapacity());
	}
	return *this;
}
car_t::~car_t(){}
void car_t::setName(string name)
{
	this->name=name;
}
void car_t::setCapacity(string capacity)
{
	this->capacity=capacity;
}
int StoI(string str)
{
	int num=0;
	for(int i=0;i<str.length()-2;i++)
	{
		num*=10;
		num+=str[i]-'0';
	}
	return num;
}
bool car_t::operator<(const car_t& car) const
{
	size_t sz1,sz2;
	return StoI(this->capacity)<StoI((string)car.getCapacity());
}
bool car_t::operator==(const car_t& car) const
{
	return !((this->name).compare((string)car.getName()));
}
void car_t::print() const
{
	cout<<"Name: "<<this->name<<"\tCapacity= "<<this->capacity<<"\tID: "<<this->id<<"\tGear: "<<this->gear<<endl;
}
		
		