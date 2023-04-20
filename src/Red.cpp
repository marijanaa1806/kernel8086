/*
 * Red.cpp
 *
 *  Created on: May 19, 2021
 *      Author: OS1
 */

#include "Red.h"
#include "SCHEDULE.H"
#include <iostream.h>
extern Red* timeBlocked;
//PCB* awaken=0;
extern volatile int time0; //u unblock
Red::Red() {
	head=0;
	tail=0;
	topSem=0;
	numOfThreads=0;
	numOfBlocked=0;


}

Red::~Red() {
	while(head) {
			El* old = head;
			head = head->next;
			delete old;
		}
	head=0;
	tail=0;

	// TODO Auto-generated destructor stub
}

void Red::addProc(PCB* pcb) {
	El* novi=new El(pcb);
		if(head==0)
		{
			head=novi;
			tail=head;
		}
		else
		{
			tail->next=novi;
			tail=tail->next;
		}
		numOfThreads++;

}

void Red::removeProc(ID id) {

	El* previous = 0;
	El* current = head;
	while(current->pcb->myThread->getId() != id && current) {
			previous = current;
			current = current->next;
	}
	if(current) {
			if(previous)
				previous->next = current->next;
			else
				head = head->next;
			if(current == tail)
				tail = previous;
		}
	numOfThreads--;
	delete current;

}

PCB* Red::top() {
	if(head) {
		El* curr= head;
		head = head->next;
		numOfThreads--;
		if(!head) tail = 0;
		PCB* result = curr->pcb;
		topSem=curr->mySem;
		delete curr;
		return result;
	}
	return 0;
}

Thread* Red::topThread() {
	return head->pcb->myThread;
}

Thread* Red::getThread(ID id) {
	El* curr=head;
	while(curr!=0)
	{
		if(curr->pcb->myThread->getId()==id)return curr->pcb->myThread;
		curr=curr->next;
	}
	return 0;
}

void Red::decTime() {
	El* curr=head;
	while(curr!=0)
	{
		curr->time=curr->time-1;
		curr=curr->next;
	}
}

void Red::addProc(PCB* pcb, Time t,KSem* sem) {

	El* novi = new El(pcb, t,sem);
	if (!head){
		head = novi;
		tail = novi;
	}
	else {
		El* curr = head;
		El* prev = 0;
		while(curr!= 0 && novi->time >= curr->time) {
			prev = curr;
			curr = curr->next;
		}
		if (prev == 0){
			novi->next = head;
			head = novi;
		}
		else if(curr == 0) {
			tail->next = novi;
			tail = novi;
		}
		else{
			novi->next = prev->next;
			prev->next = novi;
		}
	}
}
void Red::unblock() {
	if(time0)
	{
		PCB* p=timeOut();
		p->signaled=0;
		p->status=ready;
		Scheduler::put(p);
	}else
	{
		PCB* p=top();
		p->signaled=1;
		p->status=ready;
		timeBlocked->removeProc(p->myThread->getId());
		Scheduler::put(p);
	}
	topSem=0;

}

PCB* Red::timeOut() {
	if(head->time==0 && head) //proveri uslov...
	{
		PCB* p=top();
		if(topSem){
		topSem->blockedThr->removeProc(p->myThread->getId());
		topSem->incSem();

		}
		//cout<<"vrednost timeout semafora je  "<<topSem->val()<<endl;
		/*if(topSem->val()==0)
		{
			cout<<"lista niti blokiranih na sem"<<endl;
			topSem->blockedThr->printList();
			cout<<endl;
			cout<<"uspavane "<<endl;
			timeBlocked->printList();
			cout<<endl;
		}*/
		return p;
	}else return 0;
}

Time Red::headTime() {
	return head->time;
}

void Red::printList() {
	El*curr=head;
	while(curr)
	{
		cout<<"nit je "<<curr->pcb->myThread->getId()<<" a status je "<<curr->pcb->status<<"\n";
		curr=curr->next;
	}
}


