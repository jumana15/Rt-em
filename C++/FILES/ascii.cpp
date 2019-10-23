#include "ascii.h"

asciiIO_t::asciiIO_t():virtIO_t(){}

asciiIO_t::asciiIO_t(const string name, const string mode):virtIO_t(name,mode){}

virtual virtIO_t& asciiIO_t::operator>>(int& i)
{
	toFile<int>(i,"%d");
}

virtual virtIO_t& asciiIO_t::operator<<(int i)
{
	fromFile<int>(i,"%d");
	cout<<i<<endl;
}
/*
virtual virtIO_t& asciiIO_t::operator>>(unsigned int& i)
{

}
virtual virtIO_t& asciiIO_t::operator<<(unsigned int i)
{

}
virtual virtIO_t& asciiIO_t::operator>>(char& i);
virtual virtIO_t& asciiIO_t::operator<<(char i);
virtual virtIO_t& asciiIO_t::operator>>(unsigned char& i);
virtual virtIO_t& asciiIO_t::operator<<(unsigned char i);
virtual virtIO_t& asciiIO_t::operator>>(short& i);
virtual virtIO_t& asciiIO_t::operator<<(short i);
virtual virtIO_t& asciiIO_t::operator>>(unsigned short& i);
virtual virtIO_t& asciiIO_t::operator<<(unsigned short i);
virtual virtIO_t& asciiIO_t::operator>>(long& i);
virtual virtIO_t& asciiIO_t::operator<<(long i);
virtual virtIO_t& asciiIO_t::operator>>(unsigned long& i);
virtual virtIO_t& asciiIO_t::operator<<(unsigned long i);
virtual virtIO_t& asciiIO_t::operator>>(float& i);
virtual virtIO_t& asciiIO_t::operator<<(float i);
virtual virtIO_t& asciiIO_t::operator>>(double& i);
virtual virtIO_t& asciiIO_t::operator<<(double i);
*/

asciiIO_t::~asciiIO_t() {}
