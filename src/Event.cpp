/*
 * Event.cpp
 *
 *  Created on: Aug 24, 2021
 *      Author: OS1
 */

#include "Event.h"
#include "KerEvent.h"

Event::Event(IVTNo ivtNo) {
	myImpl=new KerEvent(ivtNo);
}

Event::~Event() {
	delete myImpl;
}

void Event::wait() {
	myImpl->wait();
}

void Event::signal() {
	myImpl->signal();
}
