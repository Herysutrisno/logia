

#include "logia_time.h"
#include <cstdio>
#include <cassert>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <math.h>
int main(int argc, char* argv[]){
    struct timeval tv;
    int millisec=0;

	gettimeofday(&tv, NULL);

	millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
	if (millisec>=1000) { // Allow for rounding up to nearest second
        millisec -=1000;
	    tv.tv_sec++;
	}


    //comment	
    //comment2
	//comment3
	//comment4
	//comment5
	//comment6
    std::string str = logia::setFormatTime(logia::currentSystemTime(),"test time %Y-%m-%d %H:%M:%S");
    std::cout<<"time: "<<str<<":"<<millisec<<std::endl;   
 
    return 0;

}
