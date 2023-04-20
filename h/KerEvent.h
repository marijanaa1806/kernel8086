/*
 * KerEvent.h
 *
 *  Created on: Aug 24, 2021
 *      Author: OS1
 */

#ifndef KEREVENT_H_
#define KEREVENT_H_
#include "PCB.h"
#include "IVTEntry.h"
#include "Event.h"

typedef unsigned char IVTNo;

class KerEvent {
public:
	KerEvent(IVTNo ivtNo);
	~KerEvent();
	void signal();
	void wait();
	void blockMe();
	void releaseMe();
private:
	int happened;
	int haveBlocked;
	IVTNo ivtNo;
	PCB* holder;

};

#endif /* KEREVENT_H_ */
