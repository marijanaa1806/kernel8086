/*
 * KerEvent.cpp
 *
 *  Created on: Aug 24, 2021
 *      Author: OS1
 */

#include "KerEvent.h"
#include "IVTEntry.h"
#include "SCHEDULE.h"
#include "PCB.h"
#include <iostream.h>
#include <dos.h>

KerEvent::KerEvent(IVTNo ivtNo) {
	this->ivtNo=ivtNo;
	holder = PCB::running;
	happened=0; //dogadjaj se nije dogodio
	haveBlocked=0; //nema blokiranih niti na dogadjaju
	IVTEntry::table[ivtNo]->myEv=this;

}

KerEvent::~KerEvent() {

	if(IVTEntry::table[ivtNo]->myEv==this)
		{
			IVTEntry::table[ivtNo]->myEv = 0;
		}

}

void KerEvent::signal() {
	if(haveBlocked==1) //oslobodi jednu nit
	{
		releaseMe();
		dispatch();
	}
	else
	{
		happened=1;
		//dispatch();
	}


}

void KerEvent::wait() {
	if(holder==PCB::running)
	{
		if(happened==0) //jos uvek se nije dogodio blokiraj nit
		{
			//cout<<"blokiramo nit "<<holder->myThread->getId()<<endl;
			blockMe();
		}
		else happened=!happened; //dogadjaj se dogodio, reset

	}else return;
}

void KerEvent::blockMe() {
	haveBlocked=1;
	holder->status=blocked;
	dispatch();
}

void KerEvent::releaseMe() {
	haveBlocked=0;
	holder->status=ready;
	Scheduler::put(holder);
}
