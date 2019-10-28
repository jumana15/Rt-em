
#include <iostream>

#include "tokenizer.h"

string tokenizer::delimiters="()[]{}<>+-*/&, \n\t\v\f\r";

queue<string> tokenizer::tokenize(const string& line) const
{
	queue<string> q;
	size_t lastPos = 0;
   	size_t pos = line.find_first_of(delimiters, lastPos);
 	while ((string::npos != pos)&&(string::npos!=lastPos))
   	{
   		q.push(line.substr(lastPos,pos-lastPos));
   		if(!isspace(line[pos]))
   		{
   			q.push(line.substr(pos,1));
   		}
		lastPos = pos+1;
		pos = line.find_first_of(delimiters, lastPos);
   	}
   	return q;
}