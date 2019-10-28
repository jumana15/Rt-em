#include "tokenizer.h"

string tokenizer::delimiters=" \n\t\v\f\r()[]{}<>+-*/&,";

queue<string> tokenizer::tokenize(const string& line) const
{
	queue<string> q;
	//tokens.clear();
	size_t lastPos = line.find_first_not_of(delimiters, 0);
   	size_t pos = line.find_first_of(delimiters, lastPos);
 	while ((string::npos != pos)||(string::npos!=lastPos))
   	{
	// Found a token, add it to the vector.
		q.push(line.substr(lastPos, pos - lastPos));
	// Skip delimiters.  Note the "not_of"
		lastPos = line.find_first_not_of(delimiters, pos);
	// Find next "non-delimiter"
		pos = line.find_first_of(delimiters, lastPos);
   	}
   	return q;
}