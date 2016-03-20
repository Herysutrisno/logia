   VR_DESC
#ifndef    LOGIA_QUEUE_H
#define	   LOGIA_QUEUE_H

#include <queue>
#include <exception>

#include "core_mutex.h"
#include "core_error.h"


namespace logia
{
    template<class Type>
	class Queue
	{
	    public:
            Queue()
			{
			}

			void push(Type item)
			{
		        _mutex.clutch();
			    
				_queue.push(item);	
				
				_mutex.release();

			}



		private:
            std::queue<Type> _queue;
            core::Mutex _mutex;
			Queue(const Queue&);
			const &operator=(const Queue&);
	
	
	};




}




#endif
