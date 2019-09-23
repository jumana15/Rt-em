#ifndef STRINGT_H
#define STRINGT_H
#include <iostream>
#include<stdlib.h>

using namespace std;

class String
{
	public:
		String();
		String(const char* str);
		String(const String& str);
		String& operator=(const String& str);
		size_t length() const;
		void setString(const char* str);
		const char* getString() const;
		int compare(const String& str);
		void print() const;
		void upperCase();
		void lowerCase();
		void prependString(const String& str);
		void prependChar(const char* str);
		String& operator+=(const String& str);
		String& operator+=(const char* str);
		int operator<(const String& str) const;
		int operator>(const String& str) const;
		int operator<=(const String& str) const;
		int operator>=(const String& str) const;
		int operator==(const String& str) const;
		int operator!=(const String& str) const;
		int contain(const String& str) const;
		char& operator[](size_t index);
		char operator[](size_t index) const;
		~String();
	private:
		char* str;
		size_t len;

};

ostream& operator<<(ostream& os,const String& str);
istream& operator>>(istream& is,String& str);

#endif




