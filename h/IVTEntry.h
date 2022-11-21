#ifndef _ivtentry_h_
#define _ivtentry_h_

#include "Types.h"

class Event;

class IVTEntry{
	private:
		IVTNo ivtNo;
		Event* event;
		InterruptPointer oldRoutine;
		InterruptPointer newRoutine;
		static IVTEntry *ivtEntries[256];

		friend class Event;
		friend class KernelEv;

	public:
		IVTEntry(InterruptPointer newRoutine_, IVTNo ivtNo_);
		~IVTEntry();
		void callSignal();
		void callOldRoutine();
};

#endif