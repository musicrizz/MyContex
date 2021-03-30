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

	//Simple Timer - execute function every 400 millis
	TempoMap::createTimer("asdasd", []()->void{
		std::cout<<"test timer simple 400"<<std::endl;
	}, 400);

	TempoMap::createTimer("qqqq", []()->void{
			std::cout<<"test timer 1500"<<std::endl;
		}, 1500, 5000);


	int cont=0;
	while(true)  {

		if(TempoMap::getElapsedMill(SIMPLE_TIMER) >= 1000)  {

			std::cout<<"hello"<<std::endl; //hello will be printed each second
			cont++;
			TempoMap::updateStart(SIMPLE_TIMER);
		}




	}


}
