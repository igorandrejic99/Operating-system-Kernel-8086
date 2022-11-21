#include "Kernel.h"
#include "PCB.h"
#include "Types.h"
#include "KernelSe.h"
#include <dos.h>
#include "Schedule.h"
#include "SemList.h"

Register sp_;
Register bp_;
Register ss_;

unsigned int Kernel::counter = 0;

PCB* Kernel::idlePCB = 0;

void Kernel::setIdle(PCB* idlePCB_){
	idlePCB = idlePCB_;
}

void interrupt Kernel::contextSwitch(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		mov sp_, sp
		mov bp_, bp 
		mov ss_, ss
	}
#endif
	PCB::running->sp = sp_;
	PCB::running->bp = bp_;
	PCB::running->ss = ss_;

	if (PCB::running->state == RUNNING && PCB::running != idlePCB){
		PCB::running->state = READY;
		Scheduler::put(PCB::running);
	}

	PCB::running = Scheduler::get();
	if (PCB::running == 0){
		PCB::running = idlePCB;
	}
	PCB::running->state = RUNNING;
	counter = PCB::running->timeSlice;

	sp_ = PCB::running->sp;
	bp_ = PCB::running->bp;
	ss_ = PCB::running->ss;
#ifndef BCC_BLOCK_IGNORE
	asm{
		mov sp, sp_
		mov bp, bp_
		mov ss, ss_
	}
#endif
}

void interrupt Kernel::timer(...){
	counter--;
	KernelSem::allSems->update();
#ifndef BCC_BLOCK_IGNORE
	asm int 0x60
#endif
	if (counter == 0)
		contextSwitch();
}

void Kernel::initTimer(){
#ifndef BCC_BLOCK_IGNORE
	setvect(0x60, getvect(0x08));
	setvect(0x08, Kernel::timer);
#endif
}

void Kernel::restoreTimer(){
#ifndef BCC_BLOCK_IGNORE
	setvect(0x08, getvect(0x60));
#endif
}
