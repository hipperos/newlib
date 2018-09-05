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

#include <sys/sched.h>
#include <sys/cpuset.h>
#include <sys/features.h>

/*
 *  2.5 Primitive System Data Types,  P1003.1c/D10, p. 19.
 */

/* P1003.1c/D10, p. 141 */
#define PTHREAD_CREATE_DETACHED 0
#define PTHREAD_CREATE_JOINABLE 1

/** Thread identifier. */
typedef __uint32_t pthread_t;

typedef struct {
    /** Whether this thread is scheduled at the system or process scope. */
    int contentionscope;

    /** POSIX scheduler identifier (SCHED_FIFO etc.)*/
    int schedpolicy;

    /** Scheduler parameters (i.e. priority) */
    struct sched_param schedparam;

    /** Detach state (whether the thread is detached or joinable). */
    int detachstate;

    /** Core affinity of the thread. */
    cpu_set_t affinity;
} pthread_attr_t;

/* Mutexes */

/* Values for blocking protocol. */
#define PTHREAD_PRIO_NONE    0
#define PTHREAD_PRIO_INHERIT 1
#define PTHREAD_PRIO_PROTECT 2

/* P1003.1c/D10, p. 118-119 */
#define PTHREAD_SCOPE_PROCESS 0
#define PTHREAD_SCOPE_SYSTEM  1

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
#define PTHREAD_MUTEX_DEFAULT PTHREAD_MUTEX_NORMAL

#endif /* !defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES) */

/** Mutex identifier. */
typedef struct {
    /** Pointer to the underlying futex. */
    uint32_t* futex_ptr;
#if defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES)
    /** Thread identifier of the owner of the mutex. */
    pthread_t owner;

    /** Number of times this mutex was locked (if recursive). */
    size_t lock_count;
#endif /* defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES) */

    /** Whether the mutex is initialized. */
    int is_initialized;

    /** Mutex type. */
    int type;
} pthread_mutex_t;

typedef struct {
    /** Whether the mutex attributes structure is initialized. */
    int is_initialized;
#if defined(_POSIX_THREAD_PROCESS_SHARED)
    /** Whether the mutex can be shared amongst processes. */
    int process_shared;
#endif /* defined(_POSIX_THREAD_PROCESS_SHARED) */
#if defined(_POSIX_THREAD_PRIO_PROTECT)
    int prio_ceiling;
    int protocol;
#endif /* defined(_POSIX_THREAD_PRIO_PROTECT) */
#if defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES)
    /** Mutex type. */
    int type;
#endif /* defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES) */
} pthread_mutexattr_t;

/*
 * PTHREAD_MUTEX_INITIALIZER is not supported for the moment.
 */
#if defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES)
#define _PTHREAD_MUTEX_INITIALIZER     \
    ((pthread_mutex_t){                \
        .futex_ptr = NULL,             \
        .type = PTHREAD_MUTEX_DEFAULT, \
        .is_initialized = 0,           \
        .owner = 0xFFFFFFFFu,          \
        .lock_count = 0u,              \
    })
#else
#define _PTHREAD_MUTEX_INITIALIZER     \
    ((pthread_mutex_t){                \
        .futex_ptr = NULL,             \
        .type = PTHREAD_MUTEX_DEFAULT, \
        .is_initialized = 0,           \
    })
#endif /* defined(_UNIX98_THREAD_MUTEX_ATTRIBUTES) */

#if defined(_POSIX_THREAD_PROCESS_SHARED)
/* NOTE: P1003.1c/D10, p. 81 defines following values for process_shared. */

/** The mutex is only visible within the creating process. */
#define PTHREAD_PROCESS_PRIVATE 0

/**
 * The mutex is visible to all processes with access to the memory where
 * the resource is located.
 */
#define PTHREAD_PROCESS_SHARED 1
#endif /* defined(_POSIX_THREAD_PROCESS_SHARED) */

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
/**
 * POSIX Barrier Object.
 */
typedef struct {
    /** Lock for internal data structure. */
    pthread_mutex_t mutex;

    /** Pointer to the underlying futex. */
    uint32_t* futex_ptr;

    /** Number of threads the barrier is configured for. */
    unsigned thread_count;

    /** Number of threads still needed to lift the barrier. */
    unsigned nb_left;

    /** Whether the barrier is initialized. */
    int is_initialized;
} pthread_barrier_t;

/**
 * POSIX Barrier Attributes.
 */
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
