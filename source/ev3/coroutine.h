/**
 *  \file coroutine.h
 *  \brief Coroutines in C.
 *  \author Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright The MIT License
 *
 *  Coroutine mechanics, implemented using the C language extensions "Labels as Values",
 *  "Statements and Declarations in Expressions" and "Locally Declared Labels".
 *  Based on Simon Tatham "Coroutines in C".
 */

/**
 *  \defgroup coro
 *
 *  \code
 *  CORO_CONTEXT( A );
 *  CORO_CONTEXT( B );
 *
 *  CORO_DEFINE( A )
 *  {
 *      CORO_BEGIN();
 *      for ( ; ; ) {
 *          // ...
 *          CORO_YIELD();
 *      }
 *      CORO_END();
 *  }
 *
 *  CORO_DEFINE( B )
 *  {
 *      CORO_LOCAL int b;
 *
 *      CORO_BEGIN();
 *      for ( ; ; ) {
 *          // ...
 *          CORO_WAIT( cond );
 *      }
 *      CORO_END();
 *  }
 *
 *  int main( void )
 *  {
 *      for ( ; ; ) {
 *          CORO_CALL( A );
 *          CORO_CALL( B );
 *      }
 *      return 0;
 *  }
 *  \endcode
 *
 *  Any local variables which need to be persistent across a coroutine switching
 *  must be declared static (CORO_LOCAL).
 *
 *  \{
 */

#ifndef COROUTINE_H
#define COROUTINE_H

typedef void * co_t;
typedef unsigned int semaphore_t;

enum {
	CO_READY,
	CO_WAIT,
	CO_YIELD,
	CO_END,
	CO_SKIP,
};

/**
 *  \brief Define the coroutine context (a pointer to label).
 *  \param name Coroutine name.
 */
#define CORO_CONTEXT( name ) \
	co_t co_##name

#define CORO_CONTEXT_INIT( name ) ({ \
	co_##name = NULL; \
})

/**
 *  \brief Declare the local variable that preserves a value across a coroutine switching.
 */
#define CORO_LOCAL  static

/**
 *  \brief Define the coroutine.
 *  \param name Coroutine name.
 */
#define CORO_DEFINE( name ) \
	int coro_##name( co_t *co_p )

/**
 *  \brief The coroutine beginning.
 *  \param initial The initial operation, executed whenever enter in the coroutine.
 */
#define CORO_BEGIN( initial ) ({ \
	initial; \
	if ( *co_p ) goto **co_p; \
})

/**
 *  \brief The coroutine end.
 *  \param final The final operation, executed whenever exit from the coroutine.
 *  \hideinitializer
 */
#define CORO_END( final ) ({ \
	__label__ L; \
	*co_p = &&L; \
L: \
	final; \
	return CO_END; \
})

/**
 *  \brief Switching to the next coroutine.
 *  \param final Final operation.
 */
#define CORO_YIELD( final ) ({ \
	__label__ L; \
	*co_p = &&L; \
	final; \
	return CO_YIELD; \
L:; \
})

/**
 *  \brief Waiting for the condition is true.
 *  \param cond Condition.
 *  \param ... Final operation.
 */
#define CORO_WAIT( cond, ... ) ({ \
	__label__ L; \
	*co_p = &&L; \
L: \
	if (!( cond )) { \
		__VA_ARGS__;  /* final */ \
		return CO_WAIT; \
	} \
})

/**
 *  \brief Restart the coroutine.
 *  \param final Final operation.
 */
#define CORO_RESTART( final ) ({ \
	*co_p = NULL; \
	final; \
	return CO_YIELD; \
})

/**
 *  \brief Quit the coroutine.
 *  \param final Final operation.
 */
#define CORO_QUIT( final )  CORO_END( final )

/**
 *  \brief Call the coroutine.
 *  \param name Coroutine name.
 */
#define CORO_CALL( name ) \
	coro_##name( &co_##name )

/**
 *  \brief Checking the coroutine is not completed.
 *  \param coro Result of the coroutine call.
 *  \return Alive flag.
 */
#define CORO_ALIVE( coro ) (( coro ) < CO_END )

/**
 *  \brief Start and waiting for the child coroutine is completed.
 *  \param coro Child coroutine.
 *  \param ... Final operation.
 */
#define CORO_WAIT_CORO( coro, ... ) \
	CORO_WAIT( !CORO_ALIVE( coro ), ## __VA_ARGS__ )

/**
 *  \brief Initialize the semaphore.
 *  \param name Semaphore name.
 *  \param val Semaphore capacity.
 */
#define SEMAPHORE_INIT( name, val ) ({ \
	name = val; \
})

/**
 *  \brief Waiting and acquire the semaphore.
 *  \param name Semaphore name.
 *  \param ... Final operation.
 */
#define SEMAPHORE_ACQUIRE( name, ... ) ({ \
	CORO_WAIT(( name > 0 ), ## __VA_ARGS__ ); \
	--name; \
})

/**
 *  \brief Release the semaphore.
 *  \param name Semaphore name.
 */
#define SEMAPHORE_RELEASE( name ) ({ \
	++name; \
})

/** \} */

#endif /* COROUTINE_H */
