/*
 * KSem.h
 *
 *  Created on: May 23, 2021
 *      Author: OS1
 */

#ifndef KSEM_H_
#define KSEM_H_
#include "Thread.h"
#include "Semaphor.h"

class Red;
class Sems;

class KSem {
public:
	KSem(Semaphor* s,int i);
	int val()const;
	int wait (Time maxTimeToWait);
	void signal();
	Red* blockedThr;
	void block();
	void unblock();
	Semaphor* mySem;
	void incSem();
	~KSem();
private:
	int value;


};

#endif /* KSEM_H_ */
