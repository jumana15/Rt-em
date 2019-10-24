#ifndef BIN_H
#define BIN_H

#include "vir.h"

class binIO_t:public virtIO_t
{
	private:
		binIO_t(const binIO_t& b);
		binIO_t& operator=(const binIO_t& b);
		bool m_flag;//0-read, 1-write
		void* m_buffer;

	public:
		binIO_t();
		binIO_t(const string name, const string mode);
		template <class T> binIO_t& toFile(T t);
		template <class T> binIO_t& fromFile(T& t);
		virtual virtIO_t& operator>>(int& i);
		virtual virtIO_t& operator<<(int i);
		virtual virtIO_t& operator>>(unsigned int& i);
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
		virtual virtIO_t& operator<<(double i);
		binIO_t& operator>>(void* Buf);
		binIO_t& operator<<(const void* Buf);
		void operator,(int len); 
		~binIO_t(); 

};

template <class T> binIO_t& binIO_t::toFile(T t)
{
	if(wCheck())
	{
		if(fwrite(&t,sizeof(T),1,m_file)<=0)
		{
			m_status= writeErr_e;
		}
		return *this;
	}
	else
	{
		string s="Can't Write On File!";
		throw(s);
	}
}

template <class T> binIO_t& binIO_t::fromFile(T& t)
{
	if(rCheck())
	{
		if(fread(&t,sizeof(T),1,m_file)<=0)
		{
			m_status=readErr_e;
		}
		return *this;
	}
	else
	{
		string s="Can't Read From File!";
		throw(s);
	}
	//(*this)>>(&t),sizeof(T);
}

#endif
