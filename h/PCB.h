#ifndef _pcb_h_
#define _pcb_h_

#include "Types.h"


class Thread;
class PCBList;

class PCB{
	private:
		Time timeSlice;
		StackSize stackSize;
		Stack *stack;
		Register sp;
		Register bp;
		Register ss;
		State state;
		ID id;
		Thread* myThread;
		PCBList* blocked;
		int semValue;

		static unsigned int idGenerator;
		static PCB* running;
		static PCBList* allPCB;

		friend class Thread;
		friend class Kernel;
		friend class PCBList;
		friend class Semaphore;
		friend class TimeList;
		friend class Idle;
		friend class KernelEv;
		friend class Event;
		friend int main(int argc, char**argv);

	public:
		PCB(StackSize stackSize_, Time timeSlice_, Thread* myThread_);
		~PCB();

		ID getId();
		Thread* getMyThread();
		static PCB* getRunning();
		static PCBList* getAllPCB();

		void createStack();

		static void wrapper();
};

#endif
