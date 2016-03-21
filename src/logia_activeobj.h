#ifndef LOGIA_ACTIVEOBJ_H
#define LOGIA_ACTIVEOBJ_H


#include "core_thread.h"
#include "logia_queue.h"
#include "logia_active_callback.h"


namespace logia
{
    typedef logia::Queue<logia::CallBack*> QueueCallback; 
	class ActiveObj
	{
	    
		public:
		    virtual ~ActiveObj();
			void is_send(CallBack* callback_msg);
			static logia::ActiveObj* create_activeobj();
            
		private:
		   	QueueCallback _que_callback;
			core::Thread _thread;
            bool _done;
            void run();
			static void run_thread(void* args);

		    ActiveObj();
			void is_done()
			{
			    _done = true;
			}

			ActiveObj(const ActiveObj&);
			ActiveObj& operator=(const ActiveObj&);
			core::Thread* get_thread(); 

	};

}


#endif
