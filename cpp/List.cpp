#include "list.h"

PCBList::PCBList(){
	first=0;
	last=0;
}

PCBList::~PCBList(){
	while(first){
		Elem* temp=first;
		first=first->next;
		temp->next=0;
		temp->pcb=0;
		delete temp;
	}
	first=last=0;
}

void PCBList::add(PCB* pcb_){
	Elem* newElem=new Elem(pcb_);
	if(first==0){
		first=newElem;
	}
	else{
		last->next=newElem;
	}
	last=newElem;
}

PCB* PCBList::remove(PCB* pcb_){
	if(first->pcb==pcb_){
		Elem* temp=first;
		first=first->next;
		if (first == 0)
			last = 0;
		PCB* pcb = temp->pcb;
		delete temp;
		return pcb;
	}
	else{
		Elem* temp=first->next;
		Elem* temp1=first;
		while(temp){
			if(temp->pcb==pcb_){
				if(temp==last){
					last=temp1;
				}
				temp1->next=temp->next;
				PCB* pcb = temp->pcb;
				delete temp;
				return pcb;
			}
			temp=temp->next;
			temp1=temp1->next;
		}
		return 0;
	}
}

PCB* PCBList::get(PCB* pcb_){
	Elem* temp=first;
	while(temp){
		if(temp->pcb==pcb_) return temp->pcb;
		else temp=temp->next;
	}
	return 0;
}

PCB* PCBList::removeFirst(){
	if(first==0) return 0;
	PCB* pcb = first->pcb;
	Elem* temp=first;
	first=first->next;
	delete temp;
	if(first==0){
		first = last = 0;
	}
	return pcb;
}

PCB* PCBList::getFirst(){
	return first->pcb;
}

PCB* PCBList::getById(ID id_){
	Elem* temp=first;
	while(temp){
		if(temp->pcb->id==id_) return temp->pcb;
		temp=temp->next;
	}
	return 0;
}
