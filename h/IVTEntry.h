/*
 * IVTEntry.h
 *
 *  Created on: Aug 24, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "Event.h"

typedef void interrupt (*interruptPointer)(...);
class KerEvent;
class IVTEntry {
public:
	static IVTEntry* table[256];
	static IVTEntry* getEntry(IVTNo entry);
	IVTEntry(IVTNo ivtno,interruptPointer newRoutine);
	~IVTEntry();
	KerEvent* myEv;
	void signalK();
	void callR();
	IVTNo ivtNo;
	friend class KerEvent;
	interruptPointer oldRoutine;
};

#endif /* IVTENTRY_H_ */
