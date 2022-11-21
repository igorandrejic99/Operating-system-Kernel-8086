#ifndef _list_h_
#define _list_h_
#include "PCB.h"

class PCBList{
	private:
		struct Elem{
			PCB* pcb;
			Elem* next;
			Elem(PCB* pcb_, Elem* n=0):pcb(pcb_),next(n){}
			~Elem(){pcb=0; next=0;}
		};

		Elem* first;
		Elem* last;

	public:
		PCBList();
		~PCBList();

		void add(PCB* pcb_);
		PCB* remove(PCB* pcb_);
		PCB* get(PCB* pcb_);
		PCB* removeFirst();
		PCB* getFirst();
		PCB* getById(ID id_);
};
#endif
