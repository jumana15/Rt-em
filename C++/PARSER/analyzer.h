#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class analyzer
{
	private:
		analyzer(const analyzer& a);
		analyzer& operator=(const analyzer& a);

	protected:
		bool mainFlag;
		bool ifFlag;
		bool varType;
		int plusNum;
		int minNum;
		int braces;//()
		int curlyBraces;//{}
		int sqareBrackets;//[]
		int angleBrackets;//<>
		static vector<string> legalTypes;
		static vector<string> keyWords;
		static vector<string> operators;
		vector<string> vTable;

	public:
		analyzer();
		void analyze(queue<string>& q,size_t lineNumber);
		/*bool isMain(string& s) const;
		bool isType(string& s) const;
		bool isKeyWord(string& s) const;
		bool isOperator(string& s) const;
		bool isVar(string& s) const;*/
		~analyzer();
};


#endif

