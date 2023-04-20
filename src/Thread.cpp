/*
 * Thread.cpp
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#include "Thread.h"
ID Thread::poslID=9;
#include "SCHEDULE.H"
#include "PCB.h"
#include "Sys.h"
#include <iostream.h>

#include "Red.h"

extern volatile int onDemand;
extern void interrupt timer();
extern Red* redNiti;
Thread::~Thread() {
	// TODO Auto-generated destructor stub

	if(myPCB)
		delete myPCB;
	myPCB=0;
}

ID Thread::getId() {
	return this->id;
}

ID Thread::getRunningId() {
 return PCB::running->myThread->id;
}

Thread* Thread::getThreadById(ID id) {
	return redNiti->getThread(id);
}

PCB* Thread::getMyPcb() {
	return this->myPCB;
}

Thread::Thread(StackSize stackSize, Time timeSlice) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	id=poslID++;
	myPCB=new PCB(this,stackSize,timeSlice);
	//cout<<this->getId()<<" nit se stvorila"<<endl;
	if(id>=0)redNiti->addProc(myPCB);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif

}


void Thread::start() {

	this->myPCB->start();

}

void Thread::waitToComplete() {
	myPCB->waitToComplete();

}

void interrupt dispatch() {

#ifndef BCC_BLOCK_IGNORE
	asm { cli }
#endif
   onDemand = 1;
	timer();
#ifndef BCC_BLOCK_IGNORE
	asm { sti }
#endif


}
