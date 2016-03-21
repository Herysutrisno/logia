#include "core_thread.h"

#include "core_error.h"
#include <signal.h>
#include <unistd.h>
namespace core
{
extern "C"
{
    static void* thread_routine(void* args)
	{
	    /*###
        block all SIGNALS in thread
		###*/
	    int success;
	    sigset_t signal_set;
		success = sigfillset(&signal_set);
        core_errno(success == 0);
		success = pthread_sigmask(SIG_BLOCK, &signal_set, 0);
        posix_assert(success);

		core::Thread* self = (core::Thread*)args;
		self->_internal_thd(self->_argument);
        
		return 0;
	}
}
	void Thread::startApps(fptr* internal_thd, void* arg)
	{
	    _internal_thd = internal_thd;
		_argument = arg;
		int success;
		success = pthread_create(&_mainthread, 0, thread_routine, this);
		posix_assert(success);
	
	}

	void Thread::stopApps()
	{
	    int success;
		success = pthread_join(_mainthread, 0);
		posix_assert(success);
	
	}

	void Thread::yield()
	{
	    int success;
		success = pthread_yield();
		posix_assert(success);
	
	}

	void Thread::thread_exit()
	{
	    pthread_exit(NULL);
	}


    void Thread::setPriority(int priority, int scheduling_policy)
    {
        #if defined _POSIX_THREAD_PRIORITY_SCHEDULING && _POSIX_THREAD_PRIORITY_SCHEDULING >= 0
		    int policy = 0;
			struct sched_param param;

	    #if _POSIX_THREAD_PRIORITY_SCHEDULING == 0 && defined _SC_THREAD_PRIORITY_SCHEDULING
		    if (sysconf(_SC_THREAD_PRIORITY_SCHEDULING) < 0) 
			    return;
			
		#endif

		int success;
		success = pthread_getschedparam(_mainthread, &policy, &param);
		posix_assert(success);

		if(priority != -1)
		    param.sched_priority = priority;
		
		if(scheduling_policy != -1)
		    policy = scheduling_policy;

		success = pthread_setschedparam(_mainthread, policy, &param);
		posix_assert(success);

		#endif
		   
	
	}

}

