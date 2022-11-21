#ifndef _kernelev_h_
#define _kernelev_h_

#include "Types.h"

class PCB;
class Event;

class KernelEv{
	private:
		int blocked;
		PCB* pcb;
		IVTNo ivtNo;
		Event* myEvent;

		friend class Event;
	public:
		KernelEv(IVTNo ivtNo_, Event *myEvent_);
		~KernelEv();
		Event* getMyEvent();
};

#endif