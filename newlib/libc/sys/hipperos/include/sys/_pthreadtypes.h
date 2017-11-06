/*
 *  Written by Joel Sherrill <joel.sherrill@OARcorp.com>.
 *
 *  COPYRIGHT (c) 1989-2013, 2015.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  Permission to use, copy, modify, and distribute this software for any
 *  purpose without fee is hereby granted, provided that this entire notice
 *  is included in all copies of any software which is or includes a copy
 *  or modification of this software.
 *
 *  THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 *  WARRANTY.  IN PARTICULAR,  THE AUTHOR MAKES NO REPRESENTATION
 *  OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY OF THIS
 *  SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 */

/*
 * HIPPEROS implementation of standard types for POSIX threads.
 * Only a small subset of the entire specification is currently supported.
 */

#ifndef _SYS__PTHREADTYPES_H_
#define _SYS__PTHREADTYPES_H_

#if defined(_POSIX_THREADS)

#include <sys/cpuset.h>

/*
 *  2.5 Primitive System Data Types,  P1003.1c/D10, p. 19.
 */

/* P1003.1c/D10, p. 141 */
#define PTHREAD_CREATE_DETACHED 0
#define PTHREAD_CREATE_JOINABLE 1

/** Thread identifier. */
typedef __uint32_t pthread_t;

typedef struct {
    int detachstate;
    cpu_set_t affinity;
} pthread_attr_t;

#if defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES)

/* Values for mutex type */

/* The following defines are part of the X/Open System Interface (XSI). */

/*
 * This type of mutex does not detect deadlock. A thread attempting to
 * relock this mutex without first unlocking it shall deadlock. Attempting
 * to unlock a mutex locked by a different thread results in undefined
 * behavior.  Attempting to unlock an unlocked mutex results in undefined
 * behavior.
 */
#define PTHREAD_MUTEX_NORMAL 0

/*
 * A thread attempting to relock this mutex without first unlocking
 * it shall succeed in locking the mutex.  The relocking deadlock which
 * can occur with mutexes of type PTHREAD_MUTEX_NORMAL cannot occur with
 * this type of mutex.  Multiple locks of this mutex shall require the
 * same number of unlocks to release the mutex before another thread can
 * acquire the mutex. A thread attempting to unlock a mutex which another
 * thread has locked shall return with an error.  A thread attempting to
 * unlock an unlocked mutex shall return with an error.
 */
#define PTHREAD_MUTEX_RECURSIVE 1

/*
 * This type of mutex provides error checking. A thread attempting
 * to relock this mutex without first unlocking it shall return with an
 * error. A thread attempting to unlock a mutex which another thread has
 * locked shall return with an error. A thread attempting to unlock an
 * unlocked mutex shall return with an error.
 */
#define PTHREAD_MUTEX_ERRORCHECK 2

/*
 * Attempting to recursively lock a mutex of this type results
 * in undefined behavior. Attempting to unlock a mutex of this type
 * which was not locked by the calling thread results in undefined
 * behavior. Attempting to unlock a mutex of this type which is not locked
 * results in undefined behavior. An implementation may map this mutex to
 * one of the other mutex types.
 */
#define PTHREAD_MUTEX_DEFAULT 3

#endif /* !defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES) */

#if defined(__XMK__)
typedef unsigned int pthread_mutex_t; /* identify a mutex */

typedef struct {
    int type;
} pthread_mutexattr_t;

#else /* !defined(__XMK__) */
typedef __uint32_t pthread_mutex_t; /* identify a mutex */

typedef struct {
    int is_initialized;
#if defined(_POSIX_THREAD_PROCESS_SHARED)
    int process_shared; /* allow mutex to be shared amongst processes */
#endif
#if defined(_POSIX_THREAD_PRIO_PROTECT)
    int prio_ceiling;
    int protocol;
#endif
#if defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES)
    int type;
#endif
    int recursive;
} pthread_mutexattr_t;
#endif /* !defined(__XMK__) */

#define _PTHREAD_MUTEX_INITIALIZER ((pthread_mutex_t) 0xFFFFFFFF)

/* Condition Variables */

typedef __uint32_t pthread_cond_t; /* identify a condition variable */

#define _PTHREAD_COND_INITIALIZER ((pthread_cond_t) 0xFFFFFFFF)

typedef struct {
    int is_initialized;
    clock_t clock; /* specifiy clock for timeouts */
#if defined(_POSIX_THREAD_PROCESS_SHARED)
    int process_shared; /* allow this to be shared amongst processes */
#endif
} pthread_condattr_t; /* a condition attribute object */

/* Keys */

typedef __uint32_t pthread_key_t; /* thread-specific data keys */

typedef struct {
    int is_initialized; /* is this structure initialized? */
    int init_executed;  /* has the initialization routine been run? */
} pthread_once_t;       /* dynamic package initialization */

#define _PTHREAD_ONCE_INIT \
    {                      \
        1, 0               \
    }  /* is initialized and not run */
#endif /* defined(_POSIX_THREADS) */

/* POSIX Barrier Types */

#if defined(_POSIX_BARRIERS)
typedef __uint32_t pthread_barrier_t; /* POSIX Barrier Object */
typedef struct {
    int is_initialized; /* is this structure initialized? */
#if defined(_POSIX_THREAD_PROCESS_SHARED)
    int process_shared; /* allow this to be shared amongst processes */
#endif
} pthread_barrierattr_t;
#endif /* defined(_POSIX_BARRIERS) */

/* POSIX Spin Lock Types */

#if defined(_POSIX_SPIN_LOCKS)
typedef __uint32_t pthread_spinlock_t; /* POSIX Spin Lock Object */
#endif                                 /* defined(_POSIX_SPIN_LOCKS) */

/* POSIX Reader/Writer Lock Types */

#if defined(_POSIX_READER_WRITER_LOCKS)
typedef __uint32_t pthread_rwlock_t; /* POSIX RWLock Object */

#define _PTHREAD_RWLOCK_INITIALIZER ((pthread_rwlock_t) 0xFFFFFFFF)

typedef struct {
    int is_initialized; /* is this structure initialized? */
#if defined(_POSIX_THREAD_PROCESS_SHARED)
    int process_shared; /* allow this to be shared amongst processes */
#endif
} pthread_rwlockattr_t;
#endif /* defined(_POSIX_READER_WRITER_LOCKS) */

#endif /* ! _SYS__PTHREADTYPES_H_ */