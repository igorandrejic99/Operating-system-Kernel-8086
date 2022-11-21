#ifndef _TimeList_H_
#define _TimeList_H_
#include "PCB.h"

class TimeList {
private:
		struct Elem{
			PCB* pcb;
			int time;
			Elem* next;
			Elem(PCB* pcb_, int t,Elem* n=0):pcb(pcb_),next(n),time(t){}
			~Elem(){pcb=0; next=0;}
		};

		Elem* first;
		Elem* last;
public:
		TimeList();
		~TimeList();

		void add(PCB* pcb, int time);
		PCB* removeFirst();
		PCB* getFirst();
		PCB* removeLast();
		PCB* getLast();
		void update();
};
#endif
