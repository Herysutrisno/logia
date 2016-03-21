#include "logia_activeobj.h"
#include "core_error.h"

namespace logia
{
    ActiveObj::ActiveObj()
	   : _done(false)
	{
	}

	ActiveObj::~ActiveObj()
	{
	     while(!_que_callback.is_empty())
	     {
	         logia::CallBack*  callback;
             _que_callback.pop_wait(callback);

		     delete callback;
		     callback = NULL;
	   }
   	   _thread.stopApps();
	}

    void ActiveObj::is_send(CallBack* callback_msg)
	{
	    return _que_callback.push(callback_msg);
	}

    void ActiveObj::run()
	{
	    while(!_done)
		{
		    if(_que_callback.is_empty())
			{
			   _thread.yield();        
			}
			else
			{
			    logia::CallBack* callback_msg;
				_que_callback.pop_wait(callback_msg);
                (*callback_msg)();//execute functor
			}
		}
	
	}

	void ActiveObj::run_thread(void* args)
	{
	    
	    ActiveObj* ptr_active = 0;
		ptr_active = static_cast<ActiveObj*>(args);
        heap_assert(0 != ptr_active);
        ptr_active->run();
		ptr_active->get_thread()->thread_exit();
	}

    core::Thread* ActiveObj::get_thread()
	{
	    return &_thread;   
	}

    logia::ActiveObj* ActiveObj::create_activeobj()
	{
        ActiveObj* ptr_active = new ActiveObj();
        ptr_active->_thread.startApps(run_thread, ptr_active);

		return ptr_active;
	}


}



