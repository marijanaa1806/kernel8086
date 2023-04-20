/*
 * Sys.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: OS1
 */

#include "PCB.h"
#include <iostream.h>
#include <dos.h>
#include "Red.h"
#include "SCHEDULE.H"
#include "IThr.h"
#include "Sys.h"
extern void tick();
 unsigned tsp;
 unsigned tss;
 unsigned tbp;
unsigned oldTimerOFF, oldTimerSEG;
volatile int onDemand = 0;
volatile int cnt =20;
 Red* timeBlocked=new Red();
 volatile int time0;//promenljiva koju setujemo kad budimo nit zbog tajmera
 IThr* Idle;

void interrupt timer() {
	if (!onDemand)
		{
			cnt--;
			tick();
			timeBlocked->decTime();
			while(timeBlocked && timeBlocked->headTime() == 0){
						time0=1; //uzima se prvi pcb i stavlja u scheduler
						timeBlocked->unblock();
					}
			time0=0;
		}
			if (cnt == 0|| onDemand) {
#ifndef BCC_BLOCK_IGNORE
				asm {
					// cuva sp
					mov tsp, sp
					mov tss, ss
					mov tbp,bp
				}
#endif
				PCB::running->sp = tsp;
				PCB::running->ss = tss;
				PCB::running->bp=tbp;

				  if (PCB::running->status==ready && PCB::running!=Idle->getMyPcb()) {
				    Scheduler::put(PCB::running);
				  }
				  	  PCB* oldr=PCB::running;
				// cout<<"stara raning je "<<PCB::running->myThread->getId()<<endl;
				PCB::running= Scheduler::get();	// Scheduler

				if(PCB::running==0)
				{
					PCB::running=Idle->getMyPcb();
					//cout<<"usli smo u idle\n";
				}
				//cout<<"nova raning je "<<PCB::running->myThread->getId()<<endl;
			/*	unsigned tmp;
#ifndef BCC_BLOCK_IGNORE
				asm {
				    pushf
				    pop tmp
				}
#endif
				if(PCB::running!=Idle->getMyPcb())cout << "bit i je "<<tmp<<endl;*/
				tsp = PCB::running->sp;
				tss = PCB::running->ss;
				tbp = PCB::running->bp;
				cnt = PCB::running->timeSlice;
#ifndef BCC_BLOCK_IGNORE
				asm {
					mov sp, tsp   // restore sp
					mov ss, tss
					mov bp,tbp
				}
			}
#endif
			if(!onDemand)
			{
#ifndef BCC_BLOCK_IGNORE
						asm int 60h
			        #endif
			}

			onDemand = 0;
}

void restore() {
	//cout<<"restoreee\n";
#ifndef BCC_BLOCK_IGNORE
	asm {

			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}
#endif
	delete Idle;
	delete timeBlocked;

}

void inic() {
	//cout<<"iniiit\n";
#ifndef BCC_BLOCK_IGNORE
	asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax // upisujemo 0 u es preko ax

			// pamtimo staru rutinu
			mov ax, word ptr es:0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			//nova rutina
			mov word ptr es:0022h, seg timer
			mov word ptr es:0020h, offset timer

			//stara rutina
			mov ax, oldTimerSEG
			mov word ptr es:0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}
#endif
	Idle=new IThr();
	Idle->start();
}
