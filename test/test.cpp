/*
 * test.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: gio
 */

#include "../context_util/util.h"
#include <iostream>

const char* SIMPLE_TEMPO = "Simple_Tempo";


int main(int argc, char **argv) {

	//Simple Timer - execute function every 400 millis
	TempoMap::createTimer("timer1", []()->void{
		std::cout<<"test timer simple 500"<<std::endl;
	}, 500);

	TempoMap::createTimer("timer2", []()->void{
			std::cout<<"test timer 1500"<<std::endl;
		}, 1500, 5000);


	int cont=0;
	while(true)  {

		if(TempoMap::getElapsedMill(SIMPLE_TEMPO) >= 1000)  {

			std::cout<<"hello"<<std::endl; //hello will be printed each second
			cont++;
			TempoMap::updateStart(SIMPLE_TEMPO);
		}




	}


}
