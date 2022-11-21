#include <iostream.h>
#include "PCB.h"
#include "Kernel.h"
#include "Idle.h"

extern int userMain(int argc, char**argv);

PCB* mainPCB; // Stek za mainPCB je vec napravljen
Thread* idleThread;

int main(int argc, char**argv){
	mainPCB = new PCB(4096, 2, 0);
	mainPCB->state = RUNNING;
	idleThread = new Idle();
	idleThread->start();
	PCB::running = mainPCB;
	Kernel::initTimer();
	userMain(argc, argv);
	Kernel::restoreTimer();
	return 0;
}