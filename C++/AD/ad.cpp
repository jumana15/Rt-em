#include "ad.h"

AD::AD() {}

bool AD::insertMeeting(Meeting* m)
{
	if(!m)
		return 0;
	if(m_meetingList.empty())
	{
		m_meetingList[m->getBegin()]=m;
		return 1;
	}
	if(m_meetingList.rbegin()->second->getEnd()<=m->getBegin())
	{
		m_meetingList[m->getBegin()]=m;
		return 1;
	}
	Iter_t it=m_meetingList.begin();
	if(it->first>=m->getEnd())
	{
		m_meetingList[m->getBegin()]=m;
		return 1;
	}
	for(;it!=m_meetingList.end();it++)
	{
		if(it->first>=m->getBegin())
		{
			break;
		}
	}
	if((it->first>=m->getEnd()))
	{	
		it--;
		if(it->second->getEnd()<=m->getBegin())
		{
			m_meetingList[m->getBegin()]=m;
			return 1;
		}
	}
	return 0;
}

Meeting* AD::removeMeeting(const float b)
{
	Meeting* m;
	cIter_t it=m_meetingList.find(b);
	if(it!=m_meetingList.end())
	{
		m=it->second;
		m_meetingList.erase(it->first);
		return m;
	}
	return NULL;
}

Meeting* const AD::findMeeting(const float b) const
{
	cIter_t it=m_meetingList.find(b);
	if(it!=m_meetingList.end())
	{
		return it->second;
	}
	return NULL;
}

void AD::cleanAD()
{
	/*for(Iter_t it=m_meetingList.begin();it!=m_meetingList.end();it++)
	{
		delete it->second;
	}*/
	m_meetingList.clear();

}

void AD::printMap() const
{
	cout<<"Map:"<<endl;
	for(cIter_t it=m_meetingList.begin();it!=m_meetingList.end();it++)
	{
		cout<<"Key: "<<it->first<<"\tValue: ";
		it->second->printMeeting();
	}
}
AD::~AD()
{
	/*for(Iter_t it=m_meetingList.begin();it!=m_meetingList.end();it++)
	{
		delete it->second;
	}*/
	m_meetingList.clear();
}
