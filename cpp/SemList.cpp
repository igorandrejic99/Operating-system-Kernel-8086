#include "SemList.h"
#include "KernelSe.h"
#include "TimeList.h"

SemList::SemList(){
	first = last = 0;
}

SemList::~SemList(){
	while(first){
			Elem* temp=first;
			first=first->next;
			temp->next=0;
			temp->kernelSem=0;
			delete temp;
		}
		first=last=0;
}

KernelSem* SemList::getFirst(){
	if (first)
		return first->kernelSem;
	else
		return 0;
}

KernelSem* SemList::get(KernelSem* kernelSem){
	Elem* temp=first;
		while(temp){
			if(temp->kernelSem==kernelSem) return temp->kernelSem;
			else temp=temp->next;
		}
		return 0;
}

void SemList::add(KernelSem* kernelSem){
	Elem* newElem=new Elem(kernelSem);
		if(first==0){
			first=newElem;
		}
		else{
			last->next=newElem;
		}
		last=newElem;
}

void SemList::removeFirst(){
	if(first==0) last=0;
	else{
		Elem* temp=first;
		first=first->next;
		delete temp;
		if(first==0){
			first = last = 0;
		}
	}
}

void SemList::remove(KernelSem* kernelSem){
	if(first->kernelSem==kernelSem){
			Elem* temp=first;
			first=first->next;
			if (first == 0)
				last = 0;
			delete temp;
			return;
		}
		else{
			Elem* temp=first->next;
			Elem* temp1=first;
			while(temp){
				if(temp->kernelSem==kernelSem){
					if(temp==last){
						last=temp1;
					}
					temp1->next=temp->next;
					delete temp;
					return;
				}
				temp=temp->next;
				temp1=temp1->next;
			}
			return;
		}
}

void SemList::update(){
	Elem* temp = first;
	while (temp){
		temp->kernelSem->getTimeList()->update();
		temp=temp->next;
	}
}
