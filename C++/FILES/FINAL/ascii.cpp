#include "ascii.h"

asciiIO_t::asciiIO_t():virtIO_t(){}

asciiIO_t::asciiIO_t(const string name, const string mode):virtIO_t(name,mode){}

virtIO_t& asciiIO_t::operator>>(int& i)
{
	return fromFile<int>(i,"%d");
}

virtIO_t& asciiIO_t::operator<<(int i)
{
	return toFile<int>(i,"%d");
}

virtIO_t& asciiIO_t::operator>>(unsigned int& i)
{
	return fromFile<unsigned int>(i,"%u");
}

virtIO_t& asciiIO_t::operator<<(unsigned int i)
{
	return toFile<unsigned int>(i,"%u");
}

virtIO_t& asciiIO_t::operator>>(char& i)
{
	return fromFile<char>(i,"%c");
}

virtIO_t& asciiIO_t::operator<<(char i)
{
	return toFile<char>(i,"%c");
}

virtIO_t& asciiIO_t::operator>>(unsigned char& i)
{
	return fromFile<unsigned char>(i,"%c");
}

virtIO_t& asciiIO_t::operator<<(unsigned char i)
{
	return toFile<unsigned char>(i,"%c");
}

virtIO_t& asciiIO_t::operator>>(short& i)
{
	return fromFile<short>(i,"%d");
}

virtIO_t& asciiIO_t::operator<<(short i)
{
	return toFile<short>(i,"%d");
}

virtIO_t& asciiIO_t::operator>>(unsigned short& i)
{
	return fromFile<unsigned short>(i,"%hu");
}

virtIO_t& asciiIO_t::operator<<(unsigned short i)
{
	return toFile<unsigned short>(i,"%hu");
}

virtIO_t& asciiIO_t::operator>>(long& i)
{
	return fromFile<long>(i,"%ld");
}

virtIO_t& asciiIO_t::operator<<(long i)
{
	return toFile<long>(i,"%ld");
}

virtIO_t& asciiIO_t::operator>>(unsigned long& i)
{
	return fromFile<unsigned long>(i,"%lu");
}

virtIO_t& asciiIO_t::operator<<(unsigned long i)
{
	return toFile<unsigned long>(i,"%lu");
}

virtIO_t& asciiIO_t::operator>>(float& i)
{
	return fromFile<float>(i,"%f");
}

virtIO_t& asciiIO_t::operator<<(float i)
{
	return toFile<float>(i,"%f");
}

virtIO_t& asciiIO_t::operator>>(double& i)
{
	return fromFile<double>(i,"%lf");
}

virtIO_t& asciiIO_t::operator<<(double i)
{
	return toFile<double>(i,"%lf");
}

asciiIO_t::~asciiIO_t() {}