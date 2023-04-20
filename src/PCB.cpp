/*
 * PCB.cpp
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#include "PCB.h"
#include "Thread.h"
#include <dos.h>
#include <iostream.h>
#include "SCHEDULE.H"
PCB* PCB::running=0;
#include "Red.h"
extern IThr* Idle;

Red* redNiti=new Red();

void PCB::start() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
		this->status = ready;
		make();
		Scheduler::put(this);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif

}

void PCB::waitToComplete() {
/*#ifndef BCC_BLOCK_IGNORE
	lock
#endif*/
	if(this->status == finished ||
				this == PCB::running ||
				this->myThread == Idle ) {
/*#ifndef BCC_BLOCK_IGNORE
	unlock
#endif*/
			return;
		}
		PCB::running->status=blocked; //running mora da ceka da se pozvana nit zavrsi
		myThread->getMyPcb()->waitingCompl->addProc(PCB::running); //running se dodaje u red niti koje cekaju na zavrsetak
		dispatch(); //predaje se procesor drugoj niti

/*#ifndef BCC_BLOCK_IGNORE
	unlock
#endif*/

}

void PCB::wrapper() {
	if(PCB::running->myThread)
	{
		PCB::running->myThread->run();
	}
	PCB::running->status=finished;
	int m=PCB::running->myThread->getId();//nit je zavrsila
	int n=PCB::running->waitingCompl->numOfThreads;

	while(n>0) {

		PCB* temp=PCB::running->waitingCompl->top();
		if(temp==0)break;
		temp->status=ready;
		Scheduler::put(temp);
		n--;

	}
	dispatch();//nit zavrsila predaje drugoj niti procesor
}

PCB::PCB(Thread* t, StackSize ss, Time ts) {

	myThread=t;
	timeSlice=ts;
	stackSize=ss;
	if (ss > maxStackSize)
		stackSize = maxStackSize;
	stackSize /= sizeof(unsigned);
	bp=sp;
	waitingCompl=new Red();

}


void PCB::make() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
#ifndef BCC_BLOCK_IGNORE
	this->stack = new unsigned[stackSize];
	stack[stackSize - 1] = 0x200;
	stack[stackSize-2]= FP_SEG(PCB::wrapper);
	stack[stackSize-3]= FP_OFF(PCB::wrapper);
	this->ss = FP_SEG(stack + stackSize - 12);
	this->sp=this->bp = FP_OFF(stack + stackSize - 12);
#endif

#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

PCB::~PCB() {
	if (myThread) redNiti->removeProc(this->myThread->getId()); //brisu se sve niti
	if(stack) delete[] stack;
	if(waitingCompl) delete waitingCompl; //mozda moze da ako ima jos koje cekaju da se odblokiraju
	// TODO Auto-generated destructor stub
}

