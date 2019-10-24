#include "bin.h"

binIO_t::binIO_t():virtIO_t(){}

binIO_t::binIO_t(const string name, const string mode):virtIO_t(name,mode){}

virtIO_t& binIO_t::operator>>(int& i)
{
	return fromFile<int>(i);
}

virtIO_t& binIO_t::operator<<(int i)
{
	return toFile<int>(i);
}

virtIO_t& binIO_t::operator>>(unsigned int& i)
{
	return fromFile<unsigned int>(i);
}

virtIO_t& binIO_t::operator<<(unsigned int i)
{
	return toFile<unsigned int>(i);
}

virtIO_t& binIO_t::operator>>(char& i)
{
	return fromFile<char>(i);
}

virtIO_t& binIO_t::operator<<(char i)
{
	return toFile<char>(i);
}

virtIO_t& binIO_t::operator>>(unsigned char& i)
{
	return fromFile<unsigned char>(i);
}

virtIO_t& binIO_t::operator<<(unsigned char i)
{
	return toFile<unsigned char>(i);
}

virtIO_t& binIO_t::operator>>(short& i)
{
	return fromFile<short>(i);
}

virtIO_t& binIO_t::operator<<(short i)
{
	return toFile<short>(i);
}

virtIO_t& binIO_t::operator>>(unsigned short& i)
{
	return fromFile<unsigned short>(i);
}

virtIO_t& binIO_t::operator<<(unsigned short i)
{
	return toFile<unsigned short>(i);
}

virtIO_t& binIO_t::operator>>(long& i)
{
	return fromFile<long>(i);
}

virtIO_t& binIO_t::operator<<(long i)
{
	return toFile<long>(i);
}

virtIO_t& binIO_t::operator>>(unsigned long& i)
{
	return fromFile<unsigned long>(i);
}

virtIO_t& binIO_t::operator<<(unsigned long i)
{
	return toFile<unsigned long>(i);
}

virtIO_t& binIO_t::operator>>(float& i)
{
	return fromFile<float>(i);
}

virtIO_t& binIO_t::operator<<(float i)
{
	return toFile<float>(i);
}

virtIO_t& binIO_t::operator>>(double& i)
{
	return fromFile<double>(i);
}

virtIO_t& binIO_t::operator<<(double i)
{
	return toFile<double>(i);
}

binIO_t& binIO_t::operator>>(void* buf)
{
	if(rCheck())
	{
		m_buffer=buf;
		m_flag=0;
		return *this;
	}
	string s="Can't Read From File!";
	throw(s);
}
		
binIO_t& binIO_t::operator<<(const void* buf)
{
	if(wCheck())
	{
		m_buffer=(void*)buf;
		m_flag=1;
		return *this;
	}
	string s="Can't Write On File!";
	throw(s);
}

void binIO_t::operator,(int len)
{
	if(m_flag)
	{
		fwrite(m_buffer,len,1,m_file);
	}
	else
	{
		fread(m_buffer,len,1,m_file);
	}
}

binIO_t::~binIO_t(){}