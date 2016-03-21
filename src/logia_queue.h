   VR_DESC
#ifndef    LOGIA_QUEUE_H
#define	   LOGIA_QUEUE_H

#include <deque>
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
			    _mutex.condition_init();
			}

			~Queue()
			{
			   _mutex.condition_destroy(); 
			}

			void push(Type item)
			{
		        _mutex.clutch();
				_queue.push_back(item);	
				_mutex.condition_signal(); 
				_mutex.release();

			}

			bool pop(Type& popped_item)
			{
			    _mutex_clutch();
				if(_queue.empty())
				    return false;
				popped_item = _queue.front();	
                _queue.pop_front();
				_mutex.release();
				return true;
			}

			void pop_wait(Type& popped_item)
			{
			     _mutex_clutch();
				 if(_queue.empty())
                     _mutex.wait(-1);
                 popped_item = _queue.front();
			     _queue.pop_front();
				 _mutex.release();
			}

			bool empty()const
			{     
			    _mutex_clutch();
				bool empty=_queue.empty();
				_mutex.release();
				return empty;
			}

            unsigned size()const
			{
			    _mutex_clutch();
				unsigned size = _queue.size();
				_mutex_release();
				return size;			
			}



		private:
            std::deque<Type> _queue;
            core::Mutex _mutex;
			Queue(const Queue&);
			const &operator=(const Queue&);
	
	
	};

}
#endif
