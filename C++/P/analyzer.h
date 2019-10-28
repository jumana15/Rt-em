#ifndef ANALYZER_H
#define ANALYZER_H

#include <string> 
#include <vector>

using namespace std;

class analyzer
{
	private:
		analyzer(const analyzer& a);
		analyzer& operator=(const analyzer& a);

	protected:
		bool mainFlag;
		bool ifFlag;
		string varType;
		int braces;//()
		int curlyBraces;//{}
		int sqareBrackets;//[]
		int angleBrackets;//<>
		static vector<string> legalTypes;
		static vector<string> keyWords;
		static vector<string> operators;
		static vector<string> symbolTable;

	public:
		analyzer();
		void analyzer(queue<string>& q,size_t lineNumber) const;
		~analyzer();
};


#endif

