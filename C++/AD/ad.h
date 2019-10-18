#ifndef AD_H
#define AD_H

#include <typeinfo>
#include <algorithm>
#include <map>
#include "meeting.h"

class AD
{
	private:
    	typedef typename map<float,Meeting*>::iterator Iter_t;
    	typedef typename map<float,Meeting*>::const_iterator cIter_t;
    	map<float,Meeting*> m_meetingList;
    	AD(const AD& ad);
    	AD& operator=(const AD& ad);

    public:
    	AD();
    	bool insertMeeting(Meeting* m);
    	Meeting* removeMeeting(const float b);
    	Meeting* const findMeeting(const float b) const;
    	void cleanAD();
    	void printMap() const;
    	virtual ~AD();
}; 

#endif