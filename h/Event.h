#ifndef _event_h_
#define _event_h_

#include "Types.h"
#include "IVTEntry.h"

class KernelEv;

class Event {
	public:
 		Event (IVTNo ivtNo);
 		~Event ();
 		void wait ();
	protected:
 		friend class KernelEv;
 		friend class IVTEntry;
 		void signal(); // can call KernelEv
	private:
 		KernelEv* myImpl;
};

#define PREPAREENTRY(numOfEntry, callOld);\
void interrupt inter##numOfEntry(...);\
IVTEntry ivtEntry##numOfEntry(inter##numOfEntry, numOfEntry);\
void interrupt inter##numOfEntry(...){\
	ivtEntry##numOfEntry.callSignal();\
	if (callOld == 1)\
		ivtEntry##numOfEntry.callOldRoutine();\
	dispatch();\
}


#endif