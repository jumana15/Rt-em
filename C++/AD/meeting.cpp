#include "meeting.h"


Meeting::Meeting(const float b,const float e,const string s):m_begin(b),m_end(e),m_subject(s)
{
	if(!((b>=0)&&(b<24)&&(e>b)&&(e<24)))
	{
		string ex="IllegalInput!";
		throw(ex);
	}
}

Meeting::Meeting(const Meeting& m):m_begin(m.getBegin()),m_end(m.getEnd()),m_subject(m.getSubject()){}


Meeting::~Meeting() {}
