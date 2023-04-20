/*
 * Main.cpp
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */

#include "Main.h"
#include "Red.h"
#include "PCB.h"
#include "SCHEDULE.h"
#include "Thread.h"
#include "Semaphor.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>




int syncPrintf(const char *format, ...)  {
	int res;
	va_list args;
	va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	return res;
}

extern void inic();
extern void restore();

StackSize mainSize = 4096;
Time mainTime = 2;


PCB* mainThread = new PCB(0,mainSize,mainTime);



extern int userMain(int argc, char * argv[]);



int main(int argc, char * argv[]) {
	inic();
	mainThread->status=ready;
	PCB::running = mainThread;
	int retval = 0;
	retval = userMain(argc,argv);
	PCB::running=mainThread;
	restore();
	return retval;
}

