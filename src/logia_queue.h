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
			    _mutex.clutch();
				if(_queue.empty())
				    return false;
				popped_item = _queue.front();	
                _queue.pop_front();
				_mutex.release();
				return true;
			}

			void pop_wait(Type& popped_item)
			{
			     _mutex.clutch();
				 if(_queue.empty())
                     _mutex.wait(-1);
                 popped_item = _queue.front();
			     _queue.pop_front();
				 _mutex.release();
			}

			bool is_empty()
			{     
			    _mutex.clutch();
				bool empty=_queue.empty();
				_mutex.release();
				return empty;
			}

            unsigned size()
			{
			    _mutex.clutch();
				unsigned size = _queue.size();
				_mutex.release();
				return size;			
			}

			void set_max_size(int max_size)
			{
			    _max_queue_size = max_size;   
			}

			bool is_queue_full()
			{   
			    _mutex.clutch();
			    bool full =  (_queue_size >= _max_queue_size);
                _mutex.release();
			    return full;	
			}

			bool is_queue_max()
			{   
			    _mutex.clutch();
			    bool max = (this->size() >= _queue.max_size());
                _mutex.release();
		        return max;		
			}


		private:
            std::deque<Type> _queue;
            core::Mutex _mutex;
			Queue(const Queue&);
			int _queue_size;
			int _max_queue_size;
			Queue &operator=(const Queue&);

	
	};

}
#endif
