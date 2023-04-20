/*
 * Event.h
 *
 *  Created on: Aug 24, 2021
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
typedef unsigned char IVTNo;
#define lock asm{\
	pushf;\
	cli;\
}
#define unlock asm popf

class KerEvent;


class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();
	void wait ();
protected:
	friend class KerEvent;
	void signal();
private:
	KerEvent* myImpl;
};

#define PREPAREENTRY(ivtNo, call)\
	void interrupt interrupt##ivtNo(...);\
	IVTEntry newEntry##ivtNo(ivtNo, interrupt##ivtNo);\
	void interrupt interrupt##ivtNo(...){\
		newEntry##ivtNo.signalK();\
		if(call) newEntry##ivtNo.callR();\
}\

#endif /* EVENT_H_ */
