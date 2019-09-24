#ifndef STRINGT_H
#define STRINGT_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class String
{
	public:
		String();
		String(const char* str);
		String(const String& str);
		String& operator=(const String& str);
		inline size_t length() const;
		void setString(const char* str);
		inline const char* getString() const;
		int compare(const String& str);
		inline void print() const;
		void upperCase();
		void lowerCase();
		void prepend(const String& str);
		void prepend(const char* str);
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
		static bool setCaseSensitive(bool b);
		inline static bool getCaseSensitive();
		size_t setCapacity(size_t size);
		inline size_t getCapacity() const;
		size_t firstOccurrenceCharacter(char c);
		size_t lastOccurrenceCharacter(char c);
		String operator()(int start, int len) const;
		inline static size_t getNumOfStrings();
		~String();
	private:
		char* str;
		size_t len;
		size_t capacity;
		static size_t dCapacity;
		static bool caseSens;
		static size_t numOfStrings;
};

ostream& operator<<(ostream& os,const String& str);
istream& operator>>(istream& is,String& str);
inline size_t String::length() const{ return this->len;}
inline const char* String::getString() const{ return this->str;}
inline void String::print() const{ printf("s: %s - %lu\n",this->str,this->len);}
inline bool String::getCaseSensitive(){ return caseSens;}
inline size_t String::getCapacity() const{ return this->capacity;}
inline size_t String::getNumOfStrings(){ return numOfStrings; }

#endif