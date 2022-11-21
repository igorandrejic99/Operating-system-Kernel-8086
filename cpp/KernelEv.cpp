#include "KernelEv.h"
#include "PCB.h"
#include "IVTEntry.h"
#include "Schedule.h"

KernelEv::KernelEv(IVTNo ivtNo_, Event *myEvent_){
	ivtNo = ivtNo_;
	myEvent = myEvent_;
	blocked = 0;
	pcb = PCB::running;
}

KernelEv::~KernelEv(){
	if (blocked == 1){
		blocked = 0;
		pcb->state = READY;
		Scheduler::put(pcb);
	}
	IVTEntry::ivtEntries[ivtNo]->event = 0;
}

Event* KernelEv::getMyEvent(){
	return myEvent;
}
