/**
 *  \file coroutine.h
 *  \brief Coroutines in C.
 *  \author Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright The MIT License
 *
 *  Coroutine mechanics, implemented using the C language extension "Labels as Values".
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
 *          CORO_WAIT( cond, );
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
 *  Any local variables that need to be persistent across a coroutine switching
 *  must be declared static.
 *  If you need two CORO_YIELD on the same source line or into the macros,
 *  you should use CORO_YIELD_NAMED.
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

#define __concat_1( h, t )  h##t
#define __concat( h, t )  __concat_1( h, t )

#define CORO_LABEL  __concat( L__, __LINE__ )

#define CORO_LABEL_NAMED( name )  __concat( L__##name##_, __LINE__ )

/**
 *  \brief Define the coroutine context (a pointer to label).
 *  \param name Coroutine name.
 */
#define CORO_CONTEXT( name )  co_t co_##name

#define CORO_CONTEXT_INIT( name )  co_##name = NULL

/**
 *  \brief Define the coroutine.
 *  \param name Coroutine name.
 */
#define CORO_DEFINE( name )  int coro_##name( co_t *co_p )

/**
 *  \brief Declare the local variable that preserves a value across a coroutine switching.
 */
#define CORO_LOCAL  static

/**
 *  \brief The coroutine beginning.
 *  \param initial The initial operation, executed whenever enter in the coroutine.
 */
#define CORO_BEGIN( initial ) \
	initial; \
	if ( *co_p ) goto **co_p;

/**
 *  \brief The coroutine end.
 *  \param final The final operation, executed whenever exit from the coroutine.
 *  \hideinitializer
 */
#define CORO_END( final ) \
	*co_p = &&CORO_LABEL; \
CORO_LABEL: \
	final; \
	return CO_END;

/**
 *  \brief Switching to the next coroutine.
 *  \param final Final operation.
 */
#define CORO_YIELD( final ) \
	do { \
		*co_p = &&CORO_LABEL; \
		final; \
		return CO_YIELD; \
CORO_LABEL:; \
	} while ( 0 )

/**
 *  \brief Switching to the next coroutine (with a named label).
 *  \param n Label name.
 *  \param final Final operation.
 */
#define CORO_YIELD_NAMED( name, final ) \
	do { \
		*co_p = &&CORO_LABEL_NAMED( name ); \
		final; \
		return CO_YIELD; \
CORO_LABEL_NAMED( name ):; \
	} while ( 0 )

/**
 *  \brief Waiting for the condition is true.
 *  \param cond Condition.
 *  \param final Final operation.
 */
#define CORO_WAIT( cond, final ) \
	do { \
		*co_p = &&CORO_LABEL; \
CORO_LABEL: \
		if (!( cond )) { \
			final; \
			return CO_WAIT; \
		} \
	} while ( 0 )

/**
 *  \brief Restart the coroutine.
 *  \param final Final operation.
 */
#define CORO_RESTART( final ) \
	do { \
		*co_p = NULL; \
		final; \
		return CO_YIELD; \
	} while ( 0 )

/**
 *  \brief Quit the coroutine.
 *  \param final Final operation.
 */
#define CORO_QUIT( final ) \
	do { \
		*co_p = &&CORO_LABEL; \
CORO_LABEL: \
		final; \
		return CO_END; \
	} while ( 0 )

/**
 *  \brief Call the coroutine.
 *  \param name Coroutine name.
 */
#define CORO_CALL( name )  coro_##name( &co_##name )

/**
 *  \brief Checking the coroutine is not completed.
 *  \param coro Result of the coroutine call.
 *  \return Alive flag.
 */
#define CORO_ALIVE( coro ) (( coro ) < CO_END )

/**
 *  \brief Start and waiting for the child coroutine is completed.
 *  \param coro Child coroutine.
 *  \param final Final operation.
 */
#define CORO_WAIT_CORO( coro, final ) \
	CORO_WAIT( !CORO_ALIVE( coro ), final )

/**
 *  \brief Initialize the semaphore.
 *  \param name Semaphore name.
 *  \param val Semaphore capacity.
 */
#define SEMAPHORE_INIT( name, val ) name = val

/**
 *  \brief Waiting and acquire the semaphore.
 *  \param name Semaphore name.
 *  \param final Final operation.
 */
#define SEMAPHORE_ACQUIRE( name, final ) \
	do { \
		CORO_WAIT(( name > 0 ), final ); \
		--name; \
	} while ( 0 )

/**
 *  \brief Release the semaphore.
 *  \param name Semaphore name.
 */
#define SEMAPHORE_RELEASE( name ) \
	do { \
		++name; \
	} while ( 0 )

/** \} */

#endif /* COROUTINE_H */
