#ifndef _SemList_h_
#define _SemList_h_

#include "KernelSe.h";

class SemList{
	private:
		struct Elem{
			KernelSem* kernelSem;
			Elem* next;
			Elem(KernelSem* kernelSem_,Elem* n=0):kernelSem(kernelSem_),next(n){}
		};

	Elem* first;
	Elem* last;

	public:
		SemList();
		~SemList();

		KernelSem* getFirst();
		KernelSem* get(KernelSem* kernelSem);



		void add(KernelSem* kernelSem);
		void removeFirst();
		void remove(KernelSem* kernelSem);
		void update();
};
#endif
