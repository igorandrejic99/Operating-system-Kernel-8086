 #include "Thread.h"
#include "PCB.h"
#include "Kernel.h"
#include "List.h"
#include "Schedule.h"

Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB = new PCB(stackSize, timeSlice, this);
}

Thread::~Thread(){
	delete myPCB;
	myPCB = 0;
}

void Thread::waitToComplete(){
	if (myPCB->state != FINISHED && myPCB->state != NEW && myPCB != PCB::running){
		PCB::running->state = BLOCKED;
		myPCB->blocked->add(PCB::running);
		dispatch();
	}
}

void Thread::start(){
	myPCB->createStack();
	myPCB->state = READY;
	Scheduler::put(myPCB);
}

void dispatch(){
	Kernel::contextSwitch();
}

ID Thread::getRunningId(){
	PCB::getRunning()->getId();
}

Thread* Thread::getThreadById(ID id){
	PCB* pcb=PCB::getAllPCB()->getById(id);
	if(pcb==0) return 0;
	else return pcb->getMyThread();
}
