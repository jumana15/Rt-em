#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "stringt.h"

String::String()
{
	this->str=new char[15];
	str[0]='\0';
	this->len=0;
}
String::String(const char* str)
{
	this->len=strlen(str);
	this->str=new char[this->len+1];
	strcpy(this->str,str);
}
String::String(const String& str)
{
	this->len=str.length();
	this->str=new char[this->len+1];
	strcpy(this->str,(char*)(str.getString()));
}
String& String::operator=(const String& str)
{
	if(this!= &str)
	{
		delete[] this->str;
		this->len=str.length();
		this->str=new char[this->len+1];
		strcpy(this->str,(char*)(str.getString()));
	}
}
size_t String::length() const
{
	return this->len;
}
void String::setString(const char* str)
{
	delete[] this->str;
	this->len=strlen(str);
	this->str=new char[this->len+1];
	strcpy(this->str,(char*)str);
}
const char* String::getString() const
{
	return this->str;
}
int String::compare(const String& str)
{
	int x=strcmp(this->str,(char*)(str.getString()));
	if(x==0)
	{
		return 0;
	}
	if(x<0)
	{
		return 1;
	}
	return 2;

}
void String::print() const
{
	printf("s: %s - %lu\n",this->str,this->len);
}
String::~String()
{
	delete[] this->str;
}

