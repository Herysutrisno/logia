

#include "logia_time.h"
#include <cstdio>
#include <cassert>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include "core_error.h"
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
    std::string str = logia::setFormatTime(logia::currentSystemTime(),"test time %Y-%m-%d %H:%M:%S");
    std::cout<<"time: "<<str<<":"<<millisec<<std::endl;   

    
	//test assertion error
	//int var_error = -1;
	//core_assert(var_error);
	
	//FILE* pfile;
	//pfile = fopen("unexist.ent","r");
	//if(pfile == NULL)
        //core_errno(NULL);

    //error option return  can be 1-n,if 0 mean is success 
    //posix_assert(var_error);   

    //error option return from -1->(-n),if 0 is success 
    //gai_assert(var_error);
	
	//error if 0, if not 0 is success
    //heap_assert(var_error);
    printf("success no error\n");  
    return 0;

}
