#include "tokenizer.h"
#include <iostream>
#include <fstream>


int main()
{
	tokenizer t;
	string line;
	queue<string> q;
	ifstream m_file("p.txt");
	int counter=1;
	while(getline(m_file,line)>0)
	{
		q=t.tokenize(line);	
		cout<<"\n"<<counter++<<endl;
		while(!q.empty())
		{
			
			cout<<q.front()<<" ";
			q.pop();
		}
	}

	return 0;
}
