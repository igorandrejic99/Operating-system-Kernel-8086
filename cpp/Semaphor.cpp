#include "Semaphor.h"
#include "KernelSe.h"
#include "PCB.h"
#include "List.h"
#include "TimeList.h"
#include "Types.h"
#include "Schedule.h"
#include "Thread.h"

Semaphore::Semaphore(int init){
	myImpl = new KernelSem(init);
}

Semaphore::~Semaphore(){
	delete myImpl;
	myImpl=0;
}

int Semaphore::val()const{
	return myImpl->value;
}

int Semaphore::wait(Time maxTimeToWait){
#ifndef BCC_BLOCK_IGNORE
	LOCK
#endif
	if (maxTimeToWait == 0){
		myImpl->value--;
		if (myImpl->value < 0){
			PCB::running->state = BLOCKED;
			myImpl->blocked->add(PCB::running);
			dispatch();
		}
	}
	else if (maxTimeToWait > 0){
		myImpl->value--;
		if (myImpl->value < 0){
			PCB::running->state = BLOCKED;
			myImpl->timeList->add(PCB::running, maxTimeToWait);
			dispatch();
		}
	}
#ifndef BCC_BLOCK_IGNORE
	UNLOCK
#endif
	return PCB::running->semValue;
}

int Semaphore::signal(int n){
	if (n == 0){
		myImpl->value++;
		if (myImpl->value <= 0){
			PCB* pcb = myImpl->blocked->removeFirst();
			if (pcb == 0)
				pcb = myImpl->timeList->removeFirst();
			pcb->state = READY;
			pcb->semValue = 1;
			Scheduler::put(pcb);
		}
		return n;
	}
	else if (n > 0){
		int numOfUnblocked = 0;
		while (numOfUnblocked < n){
			myImpl->value++;
			if (myImpl->value <= 0){
				numOfUnblocked++;
				PCB* pcb = myImpl->blocked->removeFirst();
				if (pcb == 0)
					pcb = myImpl->timeList->removeFirst();
				pcb->state = READY;
				pcb->semValue = 1;
				Scheduler::put(pcb);
			}
			else {
				myImpl->value+= n - numOfUnblocked - 1;
				break;
			}
		}
		return numOfUnblocked;
	}
	else 
		return n;
}
