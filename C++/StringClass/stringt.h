#ifndef STRINGT_H
#define STRINGT_H
#include<stdlib.h>

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
		~String();
	private:
		char* str;
		size_t len;

};

#endif
