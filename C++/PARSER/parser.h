#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<vector>
#include<queue>

#include "analyzer.h"
#include "tokenizer.h"

using namespace std;

class parser
{
	private:
		tokenizer *m_token;
		analyzer *m_analyzer;
		size_t m_linesNumber;
		parser(const parser& p);
		parser& operator=(const parser& p);

	protected:

	public:
		parser();
		bool parse(const string& fileNames);
		~parser();

};

#endif