#ifndef _types_h_
#define _types_h_

typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
typedef unsigned int Stack;
typedef unsigned int Register;
typedef unsigned char IVTNo;
typedef int ID;
typedef enum State{NEW, READY, RUNNING, BLOCKED, FINISHED};
typedef void interrupt (*InterruptPointer)(...);

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2; // default = 2*55ms

#define LOCK asm{pushf;cli;}
#define UNLOCK asm popf;

#endif
