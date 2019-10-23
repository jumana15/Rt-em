#ifndef ASCII_H
#define ASCII_H

#include "vir.h"

class asciiIO_t:public virtIO_t
{
	private:
		asciiIO_t(const asciiIO_t& asc);
		asciiIO_t& operator=(const asciiIO_t& asc);

	public:
		asciiIO_t();
		asciiIO_t(const string name, const string mode);
		template <calss T> void toFile(T t,const string fr);
		template <calss T> void fromFile(T& t,const string fr);
		virtual virtIO_t& operator>>(int& i);
		virtual virtIO_t& operator<<(int i);
		/*virtual virtIO_t& operator>>(unsigned int& i);
		virtual virtIO_t& operator<<(unsigned int i);
		virtual virtIO_t& operator>>(char& i);
		virtual virtIO_t& operator<<(char i);
		virtual virtIO_t& operator>>(unsigned char& i);
		virtual virtIO_t& operator<<(unsigned char i);
		virtual virtIO_t& operator>>(short& i);
		virtual virtIO_t& operator<<(short i);
		virtual virtIO_t& operator>>(unsigned short& i);
		virtual virtIO_t& operator<<(unsigned short i);
		virtual virtIO_t& operator>>(long& i);
		virtual virtIO_t& operator<<(long i);
		virtual virtIO_t& operator>>(unsigned long& i);
		virtual virtIO_t& operator<<(unsigned long i);
		virtual virtIO_t& operator>>(float& i);
		virtual virtIO_t& operator<<(float i);
		virtual virtIO_t& operator>>(double& i);
		virtual virtIO_t& operator<<(double i);*/
		~asciiIO_t();
};

template <calss T> void asciiIO_t::toFile(T t,const string fr)
{
	if(wCheck())
	{
		if(fprintf(m_file,fr,t)<=0)
		{
			m_status= writeErr_e;
		}
	}
	else
	{
		string s="Can't Write On File!";
		throw(s);
	}
}
template <calss T> void asciiIO_t::fromFile(T& t,const string fr)
{
	if(rCheck())
	{
		if(fscanf(m_file,fr,t)<=0)
		{
			m_status=readErr_e;
		}
	}
	else
	{
		string s="Can't Read From File!";
		throw(s);
	}
}

#endif