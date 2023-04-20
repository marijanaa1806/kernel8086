/*
 * Semaphor.cpp
 *
 *  Created on: May 23, 2021
 *      Author: OS1
 */

#include "Semaphor.h"
#include "KSem.h"


Semaphor::Semaphor(int init) {
	myImpl=new KSem(this,init);

}

Semaphor::~Semaphor() {
	if(myImpl)delete myImpl;
}

int Semaphor::wait(Time maxTimeToWait) {
	return myImpl->wait(maxTimeToWait);
}

void Semaphor::signal() {
	if(myImpl)myImpl->signal();
}

int Semaphor::val() const {
	return myImpl->val();

}
