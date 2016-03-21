#ifndef LOGIA_ACTIVEOBJ_H
#define LOGIA_ACTIVEOBJ_H

#include "core_thread.h"
#include "logia_queue.h"



namespace logia
{
    typedef std::function<void()> _callback;


	class Activeobj
	{
	    
		public:
		    virtual ~Activeobj()
			{
			    send([this] {_done = true});
				_thread.stopApps();
			}

			void send(_callback message)
			{
			    _queue.push(message);
			}

			void start_activeobj()
			{
			    _thread.startApps(&run,this);
			}

			static Activeobj* create_self()
			{
			    Activeobj* active_ptr = new Activeobj;
				active_ptr.start_activeobj();
				return active_ptr;
			}
		private:
		    bool _done;
            logia::Queue<_callback> _queue;
			logia::Thread _thread;
		    Activeobj(): _done(false)
			{
			}

			Activeobj(const Activeobj&);
			Activeobj& operator=(const Activeobj&);

			void run()
			{
			    while(!_done)
				{
				    _callback function;
					_queue.pop_wait(function);
					function();

				}
			
			}




	
	}



}


#endif
