/*
 * IThr.h
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#ifndef ITHR_H_
#define ITHR_H_

#include "Thread.h"

class IThr: public Thread {
public:
	IThr();
	virtual void run();
	void start();
	friend class PCB;
};

#endif /* ITHR_H_ */
