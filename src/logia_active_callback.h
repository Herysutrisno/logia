#ifndef LOGIA_ACTIVE_CALLBACK_H
#define LOGIA_ACTIVE_CALLBACK_H

namespace logia
{

    struct CallBack
	{
	    virtual void operator()() = 0;
        virtual ~CallBack(){}
	
	};

	template<class Type, class Param>
    class ActiveCallBack: public CallBack
	{
	    public:
            ActiveCallBack(Type* object, void(Type::*fptr)(Param), Param& param)
			    :_object(object),
				 _fptr(fptr),
				 _param(param)
			{
			}
		    
			virtual ~ActiveCallBack()
			{
			}

			virtual void operator()()
			{
			    (_object->*_fptr)(_param);
			}
	
	    private:
		    typedef void(Type::*Fptr)(Param);
		    Type* _object;
			Fptr _fptr;
			Param _param;
	};

    /*##
     * partial template specialization
     *##*/
    template<class Type>
    class ActiveCallBack<Type, void>: public CallBack
	{
	    public:
		    ActiveCallBack(Type* object, void(Type::*fptr)())
			    :_object(object),
				 _fptr(fptr)
            {
			}

			virtual ~ActiveCallBack()
			{
			}

			virtual void operator()()
			{
			    (_object->*_fptr)();   
			}

	    private:
		    typedef void(Type::*Fptr)();
			Type* _object;
			Fptr _fptr;
		
	};

    template<class Type>
	CallBack* bind_ftr(Type* object, void (Type::*fptr)(void))
	{
	   // CallBack* functor = new ActiveCallBack<Type,void>(object, fptr);	
	   //return std::auto_ptr<CallBack>(functor);
        return  (new ActiveCallBack<Type,void>(object, fptr));
	}

	template<class Type, class Param>
    CallBack* bind_ftr(Type* object, void (Type::*fptr)(void), Param& param)
	{
	   // CallBack* functor =  new ActiveCallBack<Type, Param> (object, fptr, param);
		//return std::auto_ptr<CallBack>(functor);	
		return (new ActiveCallBack<Type, Param> (object, fptr, param));

	}


}
#endif
