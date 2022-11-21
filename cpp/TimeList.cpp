#include "TimeList.h"
#include "PCB.h"
#include "Schedule.h"

TimeList::TimeList(){
	first=0;
	last=0;
}

TimeList::~TimeList(){
	while(first){
		Elem *temp=first;
		first=first->next;
		temp->next=0;
		temp->pcb=0;
		delete temp;
	}
	first=last=0;
}

void TimeList::add(PCB* pcb, int time){
	if(first==0){
		first=new Elem(pcb, time);
		last=first;
	}
	else{
		Elem* temp=first;
		Elem* previous=0;
		int total=temp->time;
		while((temp)&&(total<time)){
			previous=temp;
			temp=temp->next;
			if(temp!=0){
				total+=temp->time;
			}
		}
		if(previous==0){//pre prvog
			Elem* elem=new Elem(pcb, time);
			elem->next=first;
			first->time=first->time-time;
			first=elem;
		}
		else if(temp==0){//nakon poslednjeg
			Elem* elem=new Elem(pcb, time);
			elem=previous->next;
			elem->time=elem->time-total;
			last=elem;
		}
		else {//negde izmedju
			Elem* elem=new Elem(pcb, time);
			elem->next=temp;
			previous->next=elem;
			int x=temp->time;
			temp->time=total-elem->time;
			elem->time=elem->time-(total-x);
		}
	}
}

PCB* TimeList::removeFirst(){
	if(first==0) return 0;
	PCB* pcb = first->pcb;
	Elem* temp=first;
	first=first->next;
	if(first!=0){
		first->time+=temp->time;
	}
	temp->next=0;
	temp->pcb=0;
	delete temp;
	if(first==0){
		first = last = 0;
	}
	return pcb;
}

PCB* TimeList::getFirst(){
	if(first==0) return 0;
	else return first->pcb;
}

PCB* TimeList::removeLast(){
	if(last==0) return 0;
	Elem* temp=last;
	PCB* pcb=last->pcb;
	Elem* temp1=first;
	if(first!=last){//ako ima vise elemenata
		while(temp1->next!=last){
			temp1=temp1->next;
		}
	}
	else {//ako ima samo 1 element u listi
		first=last=0;
		temp->next=0;
		temp->pcb=0;
		delete temp;
		return pcb;
	}
	last=temp1;
	temp->next=0;
	temp->pcb=0;
	delete temp;
	return pcb;
}

PCB* TimeList::getLast(){
	if(last==0) return 0;
	else return last->pcb;
}

void TimeList::update(){
	if (first)
		first->time--;
	while(first && first->time == 0){
		first->pcb->state = READY;
		first->pcb->semValue = 0;
		Scheduler::put(first->pcb);
		removeFirst();
	}
}