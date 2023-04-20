/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 24, 2021
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "KerEvent.h"
#include <dos.h>
#include <iostream.h>
IVTEntry* IVTEntry::table[256]={0};
IVTEntry* IVTEntry::getEntry(IVTNo entry) {
	return table[entry];
}

IVTEntry::IVTEntry(IVTNo ivtno, interruptPointer newRoutine) {
	this->ivtNo=ivtno;
	table[this->ivtNo] = this;
	myEv = 0;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRoutine);
#endif

}

IVTEntry::~IVTEntry() {
	table[ivtNo] = 0;
	#ifndef BCC_BLOCK_IGNORE
		setvect(ivtNo, oldRoutine);
	#endif

}

void IVTEntry::signalK() {
	if(myEv)
		{
			myEv->signal();
		}
}

void IVTEntry::callR() {
	if(oldRoutine)
		{
			(*oldRoutine)();
		}

}
