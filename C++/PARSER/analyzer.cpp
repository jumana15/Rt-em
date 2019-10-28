#include "analyzer.h"

string legalT[]={"char","short","int","long","float","double","void"};
string keyW[]={"if","else","for","while","class","private","public","protected","main","const","virtual"};
string op[]={"++","--","==”","->","=","+","-","*","&","<<",">>"};
vector<string> analyzer::legalTypes(legalT,legalT+7);
vector<string> analyzer::keyWords(keyW,keyW+11);
vector<string> analyzer::operators(op,op+11);

analyzer::analyzer()
{
	mainFlag=0;
	ifFlag=0;
	varType=0;
	plusNum=0;
	minNum=0;
	braces=0;
	curlyBraces=0;
	sqareBrackets=0;
	angleBrackets=0;

}

void analyzer::analyze(queue<string>& q,size_t lineNumber)
{	
	string str;
	int flag=1;
	varType=0;
	while(!q.empty())
	{
		str=q.front();
		q.pop();
		if(!str.compare(""))
		{
			continue;
		}
		//cout<<"str= "<<str<<endl;
		if(!mainFlag)
		{
			if((str).compare("main"))
			{
				if(flag)
				{
					cout<<"line: "<<lineNumber<<" error,illegal - declaration before 'main'."<<endl;
					flag=0;		
				}
			}
			else
			{
				mainFlag=1;
			}
		}
		if(find(legalTypes.begin(),legalTypes.end(),str)!=legalTypes.end())
		{
			if(varType)
			{
				cout<<"line "<<lineNumber<<" error, multiple type."<<endl;
				varType=0;
			}
			else
			{
				varType=1;
			}
			continue;
		}
		if(find(keyWords.begin(),keyWords.end(),str)!=keyWords.end())
		{
			if((!(str).compare("else"))&&(!ifFlag))
			{
				cout<<"line "<<lineNumber<<" error, “else” without “if”."<<endl;
			}
			if(!(str).compare("if"))
			{
				ifFlag=1;
			}
			if((!(str).compare("virtual"))&&(varType))
			{
				cout<<"line "<<lineNumber<<" error invalid variable declaration."<<endl;
			}
			continue;
		}
		if((find(operators.begin(),operators.end(),str)!=operators.end()))
		{
			if(!(str).compare("+"))
			{
				plusNum++;
				if(plusNum==3)
				{
					cout<<"line "<<lineNumber<<" error, no operator +++."<<endl;
					plusNum=0;
				}
			}
			if(!(str).compare("-"))
			{
				minNum++;
				if(minNum==3)
				{
					cout<<"line "<<lineNumber<<" error, no operator ---."<<endl;
					minNum=0;
				}
			}
			continue;
		}
		if(find(vTable.begin(),vTable.end(),str)!=vTable.end())
		{
			if(varType)
			{
				cout<<"line "<<lineNumber<<" error, variable '"<<str<<"' already declared."<<endl;
			}
			continue;
		}
		if(!(str).compare("("))
		{
			braces++;
			continue;
		}
		if(!(str).compare(")"))
		{
			braces--;
			if(braces<0)
				cout<<"line "<<lineNumber<<" error, “)” without “(“."<<endl;
			continue;
		}
		if(!(str).compare("{"))
		{
			curlyBraces++;
			continue;
		}
		if(!(str).compare("}"))
		{
			curlyBraces--;
			if(curlyBraces<0)
				cout<<"line "<<lineNumber<<" error, “}” without “{“."<<endl;
			continue;
		}
		if(!(str).compare("["))
		{
			sqareBrackets++;
			continue;
		}
		if(!(str).compare("]"))
		{
			sqareBrackets--;
			if(sqareBrackets<0)
				cout<<"line "<<lineNumber<<" error, “]” without “[“."<<endl;
			continue;
		}
		if(!(str).compare("<"))
		{
			angleBrackets++;
			continue;
		}
		if(!(str).compare(">"))
		{
			angleBrackets--;
			if(angleBrackets<0)
				cout<<"line "<<lineNumber<<" error, “>” without “<“."<<endl;
			continue;
		}
		if(!varType)
		{
			cout<<"line "<<lineNumber<<" error, '"<<str<<"' is'not declared."<<endl;	
		}
		else
		{
			if((('a'<=str[0])&&(str[0]<='z'))||(('A'<=str[0])&&(str[0]<='Z'))||(str[0]=='_'))
			{
				vTable.push_back(str);
				varType=0;
			}
			else
			{
				cout<<"line "<<lineNumber<<" error,"<<str<<" illegal variable name."<<endl;
			}
		}
	} 
}

/*bool analyzer::isType(string& s) const
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
	return (find(symbolTable.begin(),symbolTable.end(),s)!=symbolTable.end());
}*/

analyzer::~analyzer()
{
	if(sqareBrackets)
	{
		//cout<<sqareBrackets<<endl;
		cout<<"error – 1 '[' not closed."<<endl;
	}
	if(curlyBraces)
	{
		//cout<<curlyBraces<<endl;
		cout<<"error – 2 '{' not closed."<<endl;
	}
	if(braces)
	{
		//cout<<braces<<endl;
		cout<<"error – 3 '(' not closed."<<endl;
	}
	if(angleBrackets)
	{
		//cout<<angleBrackets<<endl;
		cout<<"error – 4 '<' not closed."<<endl;
	}
	vTable.clear();
}
