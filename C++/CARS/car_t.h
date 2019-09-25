#ifndef CART_H
#define CART_H

#include <iostream>
#include <stdlib.h>
#include  <string>

using namespace std;

class car_t
{
	private:
		string name;
		bool gear; //standard=0 - automatic=1
		string capacity; 
		static size_t IDcounter;
		const size_t id;

	protected:
		~car_t();
		inline const string getName() const;
		void setName(string name);
		inline bool getGear() const;
		inline void setGear(bool b);
		inline const string getCapacity() const;
		void setCapacity(string capacity);
		inline const size_t getID() const;
		void print() const;

	public:
		car_t();
		car_t(const string capacity);
		car_t(const car_t& car);
		car_t& operator=(const car_t& car);
		bool operator<(const car_t& car) const;
		bool operator==(const car_t& car) const;

};

inline const string car_t::getName() const{ return this->name; }
		
inline bool car_t::getGear() const{ return this->gear; }

inline void car_t::setGear(bool b){ this->gear=b; }

inline const string car_t::getCapacity() const { return this->capacity; }
	
inline const size_t car_t::getID() const{ return this->id; }

#endif