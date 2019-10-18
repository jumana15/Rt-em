#ifndef MEETINGS_H
#define MEETINGS_H

#include <iostream>
#include <string>

using namespace std;

class Meeting
{
	private:
	    const float m_begin;
	    const float m_end;
	    const string m_subject;
	    Meeting& operator=(const Meeting& m);

	public:
		Meeting(const float b,const float e,const string s);
		Meeting(const Meeting& m);
		inline const float getBegin() const; 
		inline const float getEnd() const;
		inline const string getSubject() const;
		inline void printMeeting() const;
		~Meeting(); 
}; 

inline const float Meeting::getBegin() const { return m_begin; } 

inline const float Meeting::getEnd() const { return m_end; }

inline const string Meeting::getSubject() const { return m_subject; }

inline void Meeting::printMeeting() const {	cout<<"{Begin: "<<m_begin<<", End: "<<m_end<<", Subject: "<<m_subject<<"}"<<endl; }

#endif