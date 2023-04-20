/*
 * Red.h
 *
 *  Created on: May 19, 2021
 *      Author: OS1
 */

#ifndef RED_H_
#define RED_H_
#include "PCB.h"
#include "KSem.h"
class Red {
public:
	Red();
	 ~Red();
	int numOfThreads;
	int numOfBlocked;
	void addProc(PCB* pcb); //neuredjena lista
	void removeProc(ID id); //neuredjena lista
	PCB* top(); //prvi element iz neuredjene liste
	Thread* topThread();
	Thread* getThread(ID id);
	void decTime();
	void addProc(PCB* pcb,Time t,KSem* sem); //dodaje u uredjenu listu
	void unblock();
	KSem* topSem; //da znamo na kom je semaforu uspavana nit da je izbacimo iz liste blokiranih, koristi se u top i timeout
	PCB* timeOut(); //vraca prvi element iz uredjene liste
	Time headTime();
	void printList();

private:
	struct El
	{
		PCB* pcb;
		El* next;
		Time time;
		KSem* mySem;
		El(PCB* p)
		{
			pcb=p;
			next=0;
			time=pcb->timeSlice;
			mySem=0;
		}
		El(PCB* pc,Time t,KSem* sem)
		{
			pcb=pc;
			time=t;
			next=0;
			mySem=sem;
		}
	};
	El* head,*tail;

};

#endif /* RED_H_ */
