#include "IVTEntry.h"
#include "Event.h"
#include "Types.h"
#include <dos.h>
#include <iostream.h>
IVTEntry* IVTEntry::ivtEntries[256]={0};

IVTEntry::IVTEntry(InterruptPointer newRoutine_, IVTNo ivtNo_){
#ifndef BCC_BLOCK_IGNORE
	LOCK
#endif
	newRoutine = newRoutine_;
	ivtNo = ivtNo_;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRoutine);
#endif
	ivtEntries[ivtNo] = this;
	event = 0;
#ifndef BCC_BLOCK_IGNORE
	UNLOCK
#endif
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	setvect(ivtNo, oldRoutine);
#endif
	event = 0;
	ivtEntries[ivtNo] = 0;
	oldRoutine();
#ifndef BCC_BLOCK_IGNORE
	UNLOCK
#endif
}

void IVTEntry::callSignal(){
	if (event)
		event->signal();
}

void IVTEntry::callOldRoutine(){
	if (oldRoutine)
		oldRoutine();
}
