#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class parser
{
	private:
		//queue<string> m_tokens;
		//vector<string> m_tokens;
		tokenizer *m_token;
		analyzer *m_analyzer;
		ifstream m_file;
		size_t m_linesNumber;
		parser(const parser& p);
		parser& operator=(const parser& p);

	protected:

	public:
		parser();
		bool parse(const string& fileNames);
		void closeFile();
		/*void readFile();
		string& getLine();
		void cleanParser();*/
		~parser();

};

#endif