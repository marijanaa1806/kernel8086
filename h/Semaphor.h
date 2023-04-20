/*
 * Semaphor.h
 *
 *  Created on: May 23, 2021
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_
class KSem;
typedef unsigned int Time;
class Semaphor {
public:
 Semaphor (int init=1);
virtual ~Semaphor ();
 virtual int wait (Time maxTimeToWait);
 virtual void signal();
 int ID;
 int val () const; // Returns the current value of the semaphore
private:
 KSem* myImpl;
};

#endif /* SEMAPHOR_H_ */
