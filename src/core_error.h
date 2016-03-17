
#ifndef	CORE_ERROR_H
#define CORE_ERROR_H
/*
email direct to me if anyone counter any error
author: HerySutrisno
email:galaksi101@yahoo.co.id
*/

#include <string.h>                                                                                           
#include <stdlib.h>                                                                                           
#include <stdio.h> 
#include <errno.h>
#include <netdb.h>

//Use exit(EXIT_FAILURE) if you want to exit normally and have 
//an error code that you may be able to test from the shell. 
//Use abort if you want to flag a critical error and generate a core dump.
// (1,0) is true, (0,0) is false, (0,1) is false, (1,1) is true 
#if defined __GNUC__
#define likely(expr) __builtin_expect ((expr), 1)
#define unlikely(expr) __builtin_expect ((expr), 0)
#else
#define likely(expr) (expr)
#define unlikely(expr) (expr)
#endif

#ifdef  NODEBUG
    #define core_assert(expr) \
	    do{ \
		    (void)(expr); \
		  }while(0)

	#define core_errno(expr) \
	    do{ \
		    (void)(expr); \
		  }while(0)
     
	#define posix_assert(expr) \
	    do{ \
		    (void)(expr); \
		  }while(0)

    #define gai_assert(expr) \
	    do{ \
		    (void)(expr); \
		  }while(0)
    
    #define heap_assert(expr) \
	    do{ \
		    (void)(expr); \
		  }while(0)

#else
	//common errors checking equivalent std::assert
	//return expr 0(error),not 0 is success
    #define core_assert(expr) \
	    do{ \
		    if(unlikely(!expr)){ \
			    fprintf(stderr,"Assertion failed: %s (%s:line %d)\n",#expr, \
				__FILE__,__LINE__); \
			    abort(); \
			} \
		}while(0)
   
   //errno-style checking return last errors no
   //return 0(error),not 0 is success
   #define core_errno(expr) \
       do{ \
	       if(unlikely(!expr)){ \
		       const char* errstr = strerror(errno); \
			   fprintf(stderr,"%s (%s:line %d)\n",errstr, \
			   __FILE__,__LINE__); \
			   abort(); \
		   } \
		}while(0)
    
	//POSIX errors checking
	//return expr 0(success) 1-n(error)
	#define posix_assert(expr) \
	    do{ \
		    if(unlikely(expr)){ \
			    const char* errstr = strerror(expr); \
                fprintf(stderr,"%s (%s:line %d)\n",errstr, \
			    __FILE__,__LINE__); \
			    abort(); \
			} \
		}while(0)

    //function shall return a text string describing 
	//an error value for the getaddrinfo() and getnameinfo()
	//return expr 0(success) -1-->(-n)(error)
	#define gai_assert(expr) \
        do{ \
		    if(unlikely(expr)){ \
			    const char* errstr = gai_strerror(expr); \
                fprintf(stderr,"%s (%s:line %d)\n",errstr, \
			    __FILE__,__LINE__); \
			    abort(); \
			} \
		}while(0)

	//memory allocation errors checking
	//return expr 0(error), not 0 is success
	#define heap_assert(expr) \
        do{ \
		    if(unlikely(!expr)){ \
                fprintf(stderr,"FATAL ERROR: OUT OF MEMORY ALLOC  (%s:line %d)\n",\
			    __FILE__,__LINE__); \
			    abort(); \
			} \
		}while(0)

#endif

#endif
