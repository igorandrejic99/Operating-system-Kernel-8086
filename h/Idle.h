/*
 * Idle.h
 *
 *  Created on: Dec 23, 2019
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h"

class Idle:public Thread{
public:
		Idle();
		void run();
		void start();
};
#endif
