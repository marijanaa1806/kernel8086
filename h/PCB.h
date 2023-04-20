/*
 * PCB.h
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"


#define lock asm{\
	pushf;\
	cli;\
}
#define unlock asm popf

enum Status{finished,blocked,ready};
class Red;
class PCB {
public:
	unsigned* stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	Status status;
	Thread* myThread;
	static PCB* running;
	StackSize stackSize;
	Time timeSlice;
	//static Red* redNiti;
	Red* waitingCompl;
	void start();
	void waitToComplete();
	static void wrapper();
	PCB(Thread* t,StackSize ss,Time ts);
	PCB(StackSize s,Time t);
	void make();
	int signaled;
	virtual ~PCB();

};

#endif /* PCB_H_ */
