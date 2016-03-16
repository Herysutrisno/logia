#include "logia_time.h"
#include <cassert>
#include <cstdio>
namespace logia
{
    std::string getStrTime(const struct tm* c_time, const char* c_time_format)
	{
	    const size_t size = 1024;
		char buffer[size];

		size_t success  = std::strftime(buffer,size,c_time_format,c_time);
		if(!success)
		{
		    assert((0 != success) && "strftime fails with illegal formatting");
			return c_time_format;	
		}

		return buffer;
	}

    std::time_t  currentSystemTime()
	{
        std::time_t current_time;
		time(&current_time);
		return current_time;
	}
    
    tm localTime(const std::time_t& time)
	{
	    struct tm local_time;
		tm* success = localtime_r(&time, &local_time);
		if(!success)
		{   
		    assert((0 != success) && "localtime_r fails with illegal time set");
		    return local_time;
		}
	
	    return local_time;
	}

    std::string setFormatTime(const std::time_t &set_time, const std::string &time_format)
	{
        struct tm form_time = localTime(set_time);

	    return logia::getStrTime(&form_time, time_format.c_str());
	}

}
