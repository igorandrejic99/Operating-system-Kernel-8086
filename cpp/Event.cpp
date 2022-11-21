#include "Event.h"
#include "KernelEv.h"
#include "PCB.h"
#include "Schedule.h"
#include "IVTEntry.h"

extern void dispatch();

Event::Event(IVTNo ivtNo){
#ifndef BCC_BLOCK_IGNORE
	LOCK
#endif
	myImpl = new KernelEv(ivtNo, this);
	IVTEntry::ivtEntries[ivtNo]->event = this;
#ifndef BCC_BLOCK_IGNORE
	UNLOCK
#endif
}

Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
#endif
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	UNLOCK
#endif
}

void Event::wait(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
#endif
	if (myImpl->pcb == PCB::running && myImpl->blocked == 0){
		myImpl->blocked = 1;
		myImpl->pcb->state = BLOCKED;
		dispatch();
	}
#ifndef BCC_BLOCK_IGNORE
	UNLOCK
#endif
}

void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
#endif
	if (myImpl->blocked == 1){
		myImpl->blocked = 0;
		myImpl->pcb->state = READY;
		Scheduler::put(myImpl->pcb);
	}
#ifndef BCC_BLOCK_IGNORE
	UNLOCK
#endif
}
