#include "KernelSe.h"
#include "List.h"
#include "TimeList.h"
#include "Kernel.h"
#include "SemList.h"

SemList* KernelSem::allSems = new SemList();

KernelSem::KernelSem(int value_){
	value = value_;
	blocked = new PCBList();
	timeList = new TimeList();
	allSems->add(this);
}

KernelSem::~KernelSem(){
	delete blocked;
	delete timeList;
}

TimeList* KernelSem::getTimeList(){
	return timeList;
}
