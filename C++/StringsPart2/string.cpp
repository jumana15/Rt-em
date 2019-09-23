#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <iostream>
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

void String::upperCase()
{
	//strcpy(this->str,strupr(this->str));
	//this->len=strlen(this->str);
	for(int i=0;i<this->len;i++)
		this->str[i]=toupper(this->str[i]);
}

void String::lowerCase()
{
	//strcpy(this->str,strlwr(this->str));
	//this->len=strlen(this->str);
	for(int i=0;i<this->len;i++)
		this->str[i]=tolower(this->str[i]);
}

void String::prepend(const String& str)
{
	char* newS= new char[this->len+str.length()+1];
	strcpy(newS,(char*)str.getString()); 
	strcat(newS,this->str);
	String nS(newS);
	*this=nS;
}

void String::prepend(const char* str)
{
	char* newS= new char[this->len+strlen(str)+1];
	strcpy(newS,str); 
	strcat(newS,this->str);
	String nS(newS);
	*this=nS;
}

String& String::operator+=(const String& str)
{
	char* newS= new char[this->len+str.length()+1];
	strcpy(newS,this->str); 
	strcat(newS,(char*)str.getString());
	String nS(newS);
	*this=nS;
	return *this;
}

String& String::operator+=(const char* str)
{
	char* newS= new char[this->len+strlen(str)+1];
	strcpy(newS,this->str); 
	strcat(newS,str);
	String nS(newS);
	*this=nS;
	return *this;
}

int String::operator<(const String& str) const
{
	return(strcmp(this->str,(char*)str.getString())<0);
}

int String::operator>(const String& str) const
{
	return(strcmp(this->str,(char*)str.getString())>0);
}

int String::operator<=(const String& str) const
{
	return(strcmp(this->str,(char*)str.getString())<=0);
}

int String::operator>=(const String& str) const
{
	return(strcmp(this->str,(char*)str.getString())>=0);
}

int String::operator==(const String& str) const
{
	return(strcmp(this->str,(char*)str.getString())==0);
}

int String::operator!=(const String& str) const
{
	return(strcmp(this->str,(char*)str.getString())!=0);
}

int String::contain(const String& str) const
{
	return strstr(this->str,(char*)str.getString())==0?0:1;
}

char& String::operator[](size_t index) 
{ 
    if (index>=this->len) 
    { 
        cout << "Array index out of bound, exiting\n"; 
        exit(0); 
    } 
    return this->str[index]; 
} 

char String::operator[](size_t index) const
{ 
    if (index>=this->len) 
    { 
        cout << "Array index out of bound, exiting\n"; 
        return '\0'; 
    } 
    return this->str[index]; 
} 

ostream& operator<<(ostream& os,const String& str)
{
	os <<"String: "<<(char*)str.getString()<<".\tLength: "<<str.length()<<".\n";
	return os;
}

istream& operator>>(istream& is,String& str)
{
	char s[20];
	is >>s;
	str.setString(s);
	return is;
}
