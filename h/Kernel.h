#ifndef _kernel_h_
#define _kernel_h_

class PCB;

class Kernel{
	private:
		static unsigned int counter;
		static PCB* idlePCB;
	public:
		static void interrupt contextSwitch();
		static void interrupt timer(...);
		static void initTimer();
		static void restoreTimer();
		static void setIdle(PCB* idlePCB_);
};

#endif
