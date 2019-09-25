#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "private_t.h"
#include "bus_t.h"

int main()
{
	bool flag;
	private_t p1;
	private_t p2("715cc");
	private_t p3(p2);
	bus_t b1;
	bus_t b2("420cc");
	bus_t b3(b2);
	p1.print();
	p2.print();
	p3.print();
	b1.print();
	b2.print();
	b3.print();
	p1=p3;
	p1.print();
	flag=(b1==p2);
	cout<<"Bus==Private: "<<flag<<endl;
	flag=(b1==b2);
	cout<<"Bus==Bus: "<<flag<<endl;
	cout<<"p2<b2: "<<(p2<b2)<<endl;
	cout<<"b2<p2: "<<(b2<p2)<<endl;

	return 0;
}
