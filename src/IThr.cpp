/*
 * IThr.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#include "IThr.h"
#include <iostream.h>
#include "PCB.h"
#include "Sys.h"

IThr::IThr() : Thread(256, 1) {

}

void IThr::run() {

	while(1);
}

void IThr::start() {

	myPCB->status = ready;
	myPCB->make();

}
