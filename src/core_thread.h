#ifndef CORE_THREAD_H
#define CORE_THREAD_H

#include <pthread.h>

namespace core
{
    typedef void (fptr)(void*);
    class Thread
	{   
	    public:
		    inline Thread()
			    :_internal_thd(0),
				 _argument(0)
		    {
			}
	        
			void startApps(fptr* internal_thd, void* arg);

			void stopApps();

			void setPriority(int priority, int scheduling_policy);
            
            fptr* _internal_thd;
			
			void* _argument;

		private:
		    
			pthread_t  _mainthread;
			Thread(const Thread&);
			const Thread &operator=(const Thread&);	
	};
}


#endif
