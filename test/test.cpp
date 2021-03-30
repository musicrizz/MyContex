/*
 * test.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: gio
 */

#include "../context_util/util.h"
#include <iostream>

const char* SIMPLE_TIMER = "Simple_Timer";


int main(int argc, char **argv) {

	TempoMap::createTimer("asdasd", []()->void{
		std::cout<<"test timer"<<std::endl;
	}, 400);

	while(true)  {
		if(TempoMap::getElapsedMill(SIMPLE_TIMER) >= 1000)  {

			std::cout<<"hello"<<std::endl; //hello will be printed each second

			TempoMap::updateStart(SIMPLE_TIMER);
		}
	}

}
