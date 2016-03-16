#ifndef LOGIA_TIME_H
#define LOGIA_TIME_H

#include <ctime>
#include <string>
#include <stdint.h>


namespace logia
{

	//typedef const std::chrono::time_point<std::chrono:system_clock>   _system_time;
//	uint64_t      _millisecond;
//	uint64_t      _microseconds;

    

	std::time_t  currentSystemTime();
	tm localTime(const std::time_t& time);

	std::string setFormatTime(const std::time_t &set_time, const std::string &time_format);

}

#endif








