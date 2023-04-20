/*
 * Thread.h
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
const StackSize maxStackSize = 65535L;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
#include <dos.h>

class Red;

class PCB;
class Thread {
public:
	virtual ~Thread();
	void start();
	void waitToComplete();
	ID getId();
	static ID poslID;
	static ID getRunningId();
	static Thread * getThreadById(ID id);
	PCB* getMyPcb();

protected:
	friend class PCB;
	friend class IThr;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice=defaultTimeSlice);
	virtual void run() {}
	ID id;
private:
	PCB* myPCB;


};
void interrupt dispatch();
#endif /* THREAD_H_ */
