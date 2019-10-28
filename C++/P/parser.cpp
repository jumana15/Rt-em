#include<parser.h>

parser::parser()
{
	m_token=new tokenizer();
	m_analyzer=new analyzer();
	m_linesNumber=0;
}

bool parser::parse(const string& fileName)
{
	m_file(fileName.c_str()); 
	string line;
	if(m_file.is_open())
	{	
		queue<string> q;
		while(getline(m_file,line)>0)
		{
			q=m_token->tokenize(line);
			m_analyzer->analyzer(q,m_linesNumber);
			m_linesNumber++;
		}
		return 1;
	}
	string s="Can't Open File!"
	throw s;
	return 0;
}

void parser::closeFile()
{
	if(m_file)
	{
		m_file.close();
	}
}

parser::~parser()
{
	delete m_analyzer;
	delete m_token;
}