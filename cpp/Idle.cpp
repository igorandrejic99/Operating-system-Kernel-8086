#include "Idle.h"
#include "Kernel.h"
#include "PCB.h"

Idle::Idle():Thread(){
	Kernel::setIdle(myPCB);
}

void Idle::start(){
	myPCB->createStack();
	myPCB->state = READY;
}


void Idle::run(){
	while(1){

	}
}
