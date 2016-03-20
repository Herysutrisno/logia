#ifndef CORE_MUTEX_H
#define CORE_MUTEX_H


#include <pthread.h>
#include "core_error.h"

namespace CORE
{

    class Mutex
	{
	    public:
		    inline Mutex()
			{
			    int success = 0;
				success = pthread_mutexattr_init(&_mutex_attr);
				posix_assert(success);

				success = pthread_mutexattr_settype(&_mutex_attr,PTHREAD_MUTEX_RECURSIVE);
				posix_assert(success);

				success = pthread_mutex_init(&_mutex, &_mutex_attr);
				posix_assert(success);
			
			}
			/*##
            when you call free/delete heap object or stack, take care carefully _mutex status.
			call try_clutch() to ensure the _mutex not in locked,do not destroy _mutex while in locked.
			makesure try_clutch() return true before call Mutex distructor,either heap or stack.
			##*/
			inline ~Mutex()
			{
				int success = 0;
				success = pthread_mutex_destroy(&_mutex);
                posix_assert(success);

				success = pthread_mutexattr_destroy(&_mutex_attr);
				posix_assert(success);			
			}

			inline void clutch()
			{
                int success = 0;
				success = pthread_mutex_lock(&_mutex);
				posix_assert(success);
			
			}

			inline void release()
			{
                int success = 0;
				success = pthread_mutex_unlock(&_mutex);
				posix_assert(success);
			
			}
            /*##
            if Device or resource is busy, return false
			else if success = 0, return true
			else call abort assertion
			##*/
			inline bool try_clutch()
			{
			    int success = 0;
				success = pthread_mutex_trylock(&_mutex);
                if(success == EBUSY)
				    return false;
				posix_assert(success);
				return true;
			
			}

			inline const pthread_mutex_t* get_mutex() const
			{
			    return &_mutex;
			}

		private:
		    pthread_mutex_t _mutex;
			pthread_mutexattr_t _mutex_attr;

			Mutex(const Mutex&);
			const Mutex& operator=(const Mutex&);
		
	};
}
#endif
