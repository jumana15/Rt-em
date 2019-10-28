#include "analyzer.h"

vector<string> analyzer::legalTypes={“char”,“short”,“int”,“long”,“float”,“double”,“void”};
vector<string> analyzer::keyWords={“if”,“else”,“for”,“while”,“class”,“private”,“public”,“protected”,“main”,“const”,“virtual”};
vector<string> analyzer::operators={“++”,“--“,“==”,“->”,“=”,“+”,“-“,“*”,“&”,“<<”,“>>”};

analyzer::analyzer()
{
	mainFlag=0;
	ifFlag=0;
	braces=0;
	curlyBraces=0;
	sqareBrackets=0;
	angleBrackets=0;
}

void analyzer::analyzer(queue<string>& q,size_t lineNumber) const
{
	queue<sting>::iterator iter=q.begin();
	for(;iter!=q.end();iter++)
	{
		if(!isMain(*iter))
		{
			if(!mainFlag)
			{
				cout<<"line <<"lineNumber"<<:  error, illegal - declaration before 'main'"<<endl;
				continue;			
			}
		}
		else
		{
			mainFlag=1;
			continue;
		}
		if(isType(*iter))
		{
			it++;

		}
		if(isKeyWord(*iter))
		{

		}
		if(isOperator(*iter))
		{

		}
		if(isVar(*iter))
		{

		}
		if(!(*iter).compare("("))
		{
			braces++;
		}
		if(!(*iter).compare(")"))
		{
			braces--;
			if(braces<0)
				cout<<"line <<"lineNumber"<<  - error, “)” without “(“"<<endl;
		}
		if(!(*iter).compare("{"))
		{
			curlyBraces++;
		}
		if(!(*iter).compare("}"))
		{
			curlyBraces--;
			if(curlyBraces<0)
				cout<<"line <<"lineNumber"<<  - error, “}” without “{“"<<endl;
		}
		if(!(*iter).compare("["))
		{
			sqareBrackets++;
		}
		if(!(*iter).compare("]"))
		{
			sqareBrackets--;
			if(sqareBrackets<0)
				cout<<"line <<"lineNumber"<<  - error, “]” without “[“"<<endl;
		}
		if(!(*iter).compare("<"))
		{
			angleBrackets++;
		}
		if(!(*iter).compare(">"))
		{
			angleBrackets--;
			if(angleBrackets<0)
				cout<<"line <<"lineNumber"<<  - error, “>” without “<“"<<endl;
		}

	} 
}

bool analyzer::isType(string& s) const
{
	return (find(legalTypes.begin(),legalTypes.end(),s)!=legalTypes.end());
}

bool analyzer::isKeyWord(string& s) const
{
	return (find(keyWords.begin(),keyWords.end(),s)!=keyWords.end());
}

bool analyzer::isOperator(string& s) const
{
	return (find(operators.begin(),operators.end(),s)!=operators.end());
}

bool analyzer::isVar(string& s) const
{
	return (find(var.begin(),var.end(),s)!=var.end());
}

analyzer::~analyzer()
{
	if(sqareBrackets)
	{
		cout<<"error – 1 '[' not closed."<<endl;
	}
	if(curlyBraces)
	{
		cout<<"error – 2 '{' not closed."<<endl;
	}
	if(braces)
	{
		cout<<"error – 3 '(' not closed."<<endl;
	}
	if(angleBrackets)
	{
		cout<<"error – 4 '<' not closed."<<endl;
	}

}