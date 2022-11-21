#include "PCB.h"
#include "Thread.h"
#include "List.h"
#include <dos.h>
#include "Schedule.h"

unsigned int PCB::idGenerator = 0;
PCB* PCB::running = 0;

PCBList* PCB::allPCB = new PCBList();

PCB::PCB(StackSize stackSize_, Time timeSlice_, Thread* myThread_){
	stackSize = stackSize_;
	timeSlice = timeSlice_;
	myThread = myThread_;
	state = NEW;
	id = idGenerator++;
	blocked = new PCBList();
	allPCB->add(this);
	semValue = 1;
}

PCB::~PCB(){
	myThread = 0;
	allPCB->remove(this);
	delete blocked;
	delete stack;
	blocked = 0;
	stack = 0;
}

void PCB::createStack(){
#ifndef BCC_BLOCK_IGNORE
	stackSize = stackSize / sizeof(StackSize);
	stack = new Stack[stackSize];
	stack[stackSize - 1] = 0x0200;
	stack[stackSize - 2] = FP_SEG(wrapper);
	stack[stackSize - 3] = FP_OFF(wrapper);
	sp = bp = FP_OFF(stack + stackSize - 12);
	ss = FP_SEG(stack + stackSize - 12);
#endif
}

void PCB::wrapper(){
	running->myThread->run();
	allPCB->remove(running);
	running->state = FINISHED;
	PCB *pcb = PCB::running->blocked->removeFirst();
	while(pcb != 0){
		pcb->state = READY;
		Scheduler::put(pcb);
		pcb = PCB::running->blocked->removeFirst();
	}
	dispatch();
}

PCB* PCB::getRunning(){
	return running;
}

ID PCB::getId(){
	return id;
}

PCBList* PCB::getAllPCB(){
	return allPCB;
}

Thread* PCB::getMyThread(){
	return myThread;
}
