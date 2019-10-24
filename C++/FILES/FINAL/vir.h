#ifndef VIR_H
#define VIR_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <linux/limits.h>

using namespace std;

enum status {ok_e,cant_open_file_e,bad_access_e,writeErr_e,readErr_e};

class virtIO_t
{
	private:
		virtIO_t(const virtIO_t& vir);
		virtIO_t& operator=(const virtIO_t& vir);

	protected:
		FILE* m_file;
		string m_name;
		string m_mode;
		size_t m_position;
		enum status m_status;
		inline void setStatus(status st);
		inline bool rCheck();
		inline bool wCheck();

	public:
		virtIO_t();
		virtIO_t(const string name, const string mode);
		bool openFile(const string name,const string mode);
		void closeFile();
		const char* getPath() const;
		inline const string getAccess() const;
		const size_t getLength() const;
		inline const size_t getPosition() const;
		bool setPosition(size_t pos);
		inline const int getStatus() const;
		virtual virtIO_t& operator>>(int& i)=0;
		virtual virtIO_t& operator<<(int i)=0;
		virtual virtIO_t& operator>>(unsigned int& i)=0;
		virtual virtIO_t& operator<<(unsigned int i)=0;
		virtual virtIO_t& operator>>(char& i)=0;
		virtual virtIO_t& operator<<(char i)=0;
		virtual virtIO_t& operator>>(unsigned char& i)=0;
		virtual virtIO_t& operator<<(unsigned char i)=0;
		virtual virtIO_t& operator>>(short& i)=0;
		virtual virtIO_t& operator<<(short i)=0;
		virtual virtIO_t& operator>>(unsigned short& i)=0;
		virtual virtIO_t& operator<<(unsigned short i)=0;
		virtual virtIO_t& operator>>(long& i)=0;
		virtual virtIO_t& operator<<(long i)=0;
		virtual virtIO_t& operator>>(unsigned long& i)=0;
		virtual virtIO_t& operator<<(unsigned long i)=0;
		virtual virtIO_t& operator>>(float& i)=0;
		virtual virtIO_t& operator<<(float i)=0;
		virtual virtIO_t& operator>>(double& i)=0;
		virtual virtIO_t& operator<<(double i)=0;
		virtual ~virtIO_t();

};

inline const string virtIO_t::getAccess() const { return m_mode; }

inline const size_t virtIO_t::getPosition() const 
{ 
	if(m_file)
		return ftell(m_file);
	return 0;
}

inline const int virtIO_t::getStatus() const { return m_status; }

inline void virtIO_t::setStatus(status st) { m_status=st; }

inline bool virtIO_t::rCheck()
{
	if((!m_file)||((m_mode!="r")&&(m_mode!="r+")))
	{
		m_status=bad_access_e;
		return 0;
	}
	return 1;
}

inline bool virtIO_t::wCheck()
{
	if((!m_file)||((m_mode!="w")&&(m_mode!="w+")))
	{
		m_status= bad_access_e;
		return 0;
	}
	return 1;
}

#endif