#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <queue>
#include<string>

using namespace std;


class tokenizer
{
	private:
		static string delimiters;
		static string single;
		tokenizer(const tokenizer& t);
		tokenizer& operator=(const tokenizer& t);

	public:
		tokenizer(){};
		queue<string> tokenize(const string& line) const;
		~tokenizer(){};
};
#endif