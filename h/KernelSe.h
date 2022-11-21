#ifndef _kernelse_h_
#define _kernelse_h_

class PCBList;
class TimeList;
class SemList;

class KernelSem{
	private:
		int value;
		PCBList* blocked;
		TimeList* timeList;
		static SemList* allSems;

		friend class Semaphore;
		friend class Kernel;
	public:
		KernelSem(int value_);
		~KernelSem();
		TimeList* getTimeList();
};

#endif
