#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <iostream>
#include "stringt.h"

size_t String::dCapacity=64;
bool String::caseSens=1;
size_t String::numOfStrings=0;

String::String()
{
	setCapacity(this->dCapacity);
	this->str=new char[this->capacity];
	this->str[0]='\0';
	this->len=0;
	this->numOfStrings++;
}

String::String(const char* str)
{
	this->len=(strlen(str));
	setCapacity(this->len+1);
	this->str=new char[this->capacity];
	strcpy(this->str,str);
	this->numOfStrings++;
}

String::String(const String& str)
{
	this->len=str.length();
	setCapacity(this->len+1);
	this->str=new char[this->capacity];
	strcpy(this->str,(char*)(str.getString()));
	this->numOfStrings++;
}

String& String::operator=(const String& str)
{
	if(this!= &str)
	{
		this->len=str.length();
		if(this->capacity<str.length()+1)
		{
			delete[] this->str;
			setCapacity(this->len+1);
			this->str=new char[this->capacity];
		}
		strcpy(this->str,(char*)(str.getString()));
	}
	return *this;
}

void String::setString(const char* str)
{
	this->len=strlen(str);
	if(this->capacity<this->len+1)
	{
		delete[] this->str;
		setCapacity(this->len+1);
		this->str=new char[this->capacity];
	}
	strcpy(this->str,(char*)str);
}

int String::compare(const String& str)
{	
	int x;
	if(caseSens)
		x=strcmp(this->str,(char*)(str.getString()));
	else
		x=strcasecmp(this->str,(char*)(str.getString()));
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

String::~String()
{
	delete[] this->str;
	this->numOfStrings--;
}

void String::upperCase()
{
	for(int i=0;i<this->len;i++)
		this->str[i]=toupper(this->str[i]);
}

void String::lowerCase()
{
	for(int i=0;i<this->len;i++)
		this->str[i]=tolower(this->str[i]);
}

void String::prepend(const String& str)
{
	char* newS= new char[this->len+str.length()+1];
	strcpy(newS,(char*)str.getString()); 
	strcat(newS,this->str);
	String::setString(newS);
	delete[] newS;
}

void String::prepend(const char* str)
{
	char* newS= new char[this->len+strlen(str)+1];
	strcpy(newS,str); 
	strcat(newS,this->str);
	String::setString(newS);
	delete[] newS;
}

String& String::operator+=(const String& str)
{
	char* newS= new char[this->len+str.length()+1];
	strcpy(newS,this->str); 
	strcat(newS,(char*)str.getString());
	String::setString(newS);
	delete[] newS;
	return *this;
}

String& String::operator+=(const char* str)
{
	char* newS= new char[this->len+strlen(str)+1];
	strcpy(newS,this->str); 
	strcat(newS,str);
	String::setString(newS);
	delete[] newS;
	return *this;
}

int String::operator<(const String& str) const
{
	if(caseSens)
		return(strcmp(this->str,(char*)str.getString())<0);
	else
		return(strcasecmp(this->str,(char*)str.getString())<0);
}

int String::operator>(const String& str) const
{
	if(this->caseSens)
		return(strcmp(this->str,(char*)str.getString())>0);
	else
		return(strcasecmp(this->str,(char*)str.getString())>0);
}

int String::operator<=(const String& str) const
{
	if(this->caseSens)
		return(strcmp(this->str,(char*)str.getString())<=0);
	else
		return(strcasecmp(this->str,(char*)str.getString())<=0);
}

int String::operator>=(const String& str) const
{
	if(this->caseSens)
		return(strcmp(this->str,(char*)str.getString())>=0);
	else
		return(strcasecmp(this->str,(char*)str.getString())>=0);
}

int String::operator==(const String& str) const
{
	if(this->caseSens)
		return(strcmp(this->str,(char*)str.getString())==0);
	else
		return(strcasecmp(this->str,(char*)str.getString())==0);
}

int String::operator!=(const String& str) const
{
	if(this->caseSens)
		return(strcmp(this->str,(char*)str.getString())!=0);
	else
		return(strcasecmp(this->str,(char*)str.getString())!=0);
}

int String::contain(const String& str) const
{
	if(this->caseSens)
		return strstr(this->str,(char*)str.getString())==0?0:1;
	else
	{
		String s1(this->str),s2((char*)str.getString());
		s1.lowerCase();
		s2.lowerCase();
		return strstr((char*)s1.getString(),(char*)s2.getString())==0?0:1;
	}
}

bool String::setCaseSensitive(bool b) 
{
	bool x=caseSens;
	caseSens=b;
	return x;
}

size_t String::setCapacity(size_t size)
{
	size_t prevSize=this->capacity;
	size_t s=64;
	while(s<size)
		s*=2;
	this->capacity=s;
	return prevSize;
}

size_t String::firstOccurrenceCharacter(char c)
{
	size_t index;
	for(index=0;index<this->len;index++)
	{
		if(this->str[index]==c)
		{
			return index;
		}
	}
	return index;
}

size_t String::lastOccurrenceCharacter(char c)
{
	size_t index;
	for(index=this->len-1;index>=0;index--)
	{
		if(this->str[index]==c)
		{
			return index;
		}
	}
	return index;
}

String String::operator()(int start, int len) const
{
	char* s;
	if(len>0)
		s=new char[len+1];
	else
		s=new char[1];
	if((start<0)||(len<0)||(start>=this->len)||((start+len)>=this->len))
	{
		s[0]='\0';
	}
	else
	{
		strncpy(s,(this->str)+start,len);
		s[len]='\0';
	}
	String st(s);
	return st;
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
	os <<"String: "<<(char*)str.getString()<<".\tLength: "<<str.length()<<".\tCapacity: "<<str.getCapacity()<<"."<<endl;
	return os;
}

istream& operator>>(istream& is,String& str)
{
	char s[20];
	is >>s;
	str.setString(s);
	return is;
}
