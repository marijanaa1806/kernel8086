/*
 * KSem.cpp
 *
 *  Created on: May 23, 2021
 *      Author: OS1
 */

#include "KSem.h"
#include "Red.h"

#include "PCB.h"
#include "SCHEDULE.H"
#include <iostream.h>

extern volatile int time0;
extern Red* timeBlocked;

KSem::KSem(Semaphor* s,int i) {
	mySem=s;
	value=i;
	blockedThr=new Red();
}

int KSem::val() const {
	return value;
}

int KSem::wait(Time maxTimeToWait) {
	if(--value<0)
	{
		block();
		if(maxTimeToWait>0)
			{
				timeBlocked->addProc(PCB::running,maxTimeToWait,this);
			}
		dispatch();
		if(PCB::running->signaled)return 1; //odblokirana signalom
		else return 0; //odblokirana sa timer
	}
	else return 1; //nit se nije blokirala

}

void KSem::signal() {
/*#ifndef BCC_BLOCK_IGNORE
	lock
#endif*/
	if(value++<0) //bilo je value++
	{

		unblock();
/*#ifndef BCC_BLOCK_IGNORE
			unlock
#endif*/
	}
	else
	{
/*#ifndef BCC_BLOCK_IGNORE
			unlock
#endif*/
	}

}

void KSem::block() {

	PCB::running->status=blocked;
	blockedThr->addProc(PCB::running);

}

void KSem::unblock() {

	blockedThr->unblock();

}

void KSem::incSem() {
	this->value=this->value+1;
}

KSem::~KSem() {
	if(blockedThr)delete blockedThr;
	mySem=0;
	blockedThr=0;

}


