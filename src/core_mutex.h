#ifndef CORE_MUTEX_H
#define CORE_MUTEX_H


#include <pthread.h>
#include <time.h>
#include "core_error.h"

#define CLOCK_REALTIME 0
//int clock_gettime(int clock_id, timespec* ts);
namespace core
{

    class Mutex
	{
	    public:
		    inline Mutex()
			{
			    int success;
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
				int success;
				success = pthread_mutex_destroy(&_mutex);
                posix_assert(success);

				success = pthread_mutexattr_destroy(&_mutex_attr);
				posix_assert(success);			
			}

			inline void clutch()
			{
                int success;
				success = pthread_mutex_lock(&_mutex);
				posix_assert(success);
			
			}

			inline void release()
			{
                int success;
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
			    int success;
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

			inline void condition_init()
			{
			    int success;
				success = pthread_cond_init(&_cond, 0);
				posix_assert(success);
			
			}

			inline void condition_signal()
			{
			    int success;
				success = pthread_cond_signal(&_cond);
				posix_assert(success);
			}

			inline void condition_destroy()
			{
			    int success;
				success = pthread_cond_destroy(&_cond);
				posix_assert(success);
			
			}

			inline int wait(int timeout)
			{
			    int success;
				if(timeout != -1)
				{
				    struct timespec time;
					clock_gettime(CLOCK_REALTIME, &time);

					time.tv_sec += timeout / 1000;
					time.tv_nsec += (timeout % 1000) * 1000000;

					if(time.tv_nsec > 1E9)
					{
					    time.tv_sec++;
						time.tv_nsec -= 1E9;
					}
					success = pthread_cond_timedwait(&_cond, &_mutex, &time);
				}
				else
				{
				    success = pthread_cond_wait(&_cond, &_mutex);
				
				}

				if(success == 0)
				    return 0;

				if(success == ETIMEDOUT)
				{
				    errno = EAGAIN;
				}

				posix_assert(success);
				return -1;
			}

			inline void broadcast()
			{
			    int success;
				success = pthread_cond_broadcast(&_cond);
				posix_assert(success);
			}

		private:
		    pthread_mutex_t _mutex;
			pthread_mutexattr_t _mutex_attr;
			pthread_cond_t _cond;


			Mutex(const Mutex&);
			const Mutex& operator=(const Mutex&);
		
	};
}
#endif
