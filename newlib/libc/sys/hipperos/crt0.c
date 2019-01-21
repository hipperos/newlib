/*
 * Maestro Fake crt0
 *
 * Inspired by the RTEMS one.
 * This allow to pass the link tests of autoconf.
 */

#include <reent.h>

#include <time.h> /* struct timespec */

void maestro_provides_crt0(void) {}  /* dummy symbol so file always has one */

#define MAESTRO_STUB(ret, func, body) \
ret maestro_stub_##func body; \
ret func body

/* Maestro specific functions. */
MAESTRO_STUB(struct _reent*, hnewlib_getreent(void), { return 0; })

/* Maestro provides some of its own routines including a Malloc family */
MAESTRO_STUB(void *,malloc(size_t s), { return 0; })
MAESTRO_STUB(void *,realloc(void* p, size_t s), { return 0; })
MAESTRO_STUB(void, free(void* ptr), { })
MAESTRO_STUB(_PTR, calloc(size_t s1, size_t s2), { return 0; })
MAESTRO_STUB(int, posix_memalign(void **p, size_t si, size_t s2), { return -1; })

/* stubs for functions Maestro provides */
MAESTRO_STUB(int, clock_gettime(clockid_t clk_id, struct timespec *tp), { return -1; })
MAESTRO_STUB(int, close (int fd), { return -1; })
MAESTRO_STUB(int, nanosleep(const struct timespec *req, struct timespec *rem), { return -1; })
MAESTRO_STUB(int, ftruncate(int fd, off_t length), { return -1; })
MAESTRO_STUB(_off_t, lseek(int fd, _off_t offset, int whence), { return -1; })
MAESTRO_STUB(int, lstat(const char *path, struct stat *buf), { return -1; })
MAESTRO_STUB(int, open(const char *pathname, int flags, int mode), { return -1; })
MAESTRO_STUB(_ssize_t, read(int fd, void *buf, size_t count), { return -1; })
MAESTRO_STUB(int, stat(const char *path, struct stat *buf), { return -1; })
MAESTRO_STUB(int, unlink(const char *pathname), { return -1; })
MAESTRO_STUB(_ssize_t, write (int fd, const void *buf, size_t nbytes), { return -1; })

/* stubs for functions from reent.h */
MAESTRO_STUB(int, _close_r (struct _reent *r, int fd), { return -1; })

MAESTRO_STUB(pid_t, getpid (), { return -1; })
MAESTRO_STUB(pid_t, _getpid_r (struct _reent *r), { return -1; })
#if !defined(REENTRANT_SYSCALLS_PROVIDED)
/* cf. newlib/libc/reent/linkr.c */
MAESTRO_STUB(int, _link_r (struct _reent *r, const char *oldpath, const char *newpath), { return -1; })
#endif
MAESTRO_STUB(_off_t, _lseek_r ( struct _reent *ptr, int fd, _off_t offset, int whence ), { return -1; })
MAESTRO_STUB(int, _open_r (struct _reent *r, const char *buf, int flags, int mode), { return -1; })
MAESTRO_STUB(_ssize_t, _read_r (struct _reent *r, int fd, void *buf, size_t nbytes), { return -1; })
MAESTRO_STUB(int, _rename_r (struct _reent *r, const char *a, const char *b), { return -1; })

MAESTRO_STUB(int, _stat_r (struct _reent *r, const char *path, struct stat *buf), { return -1; })
MAESTRO_STUB(_CLOCK_T_, _times_r (struct _reent *r, struct tms *ptms), { return -1; })
MAESTRO_STUB(int, _unlink_r (struct _reent *r, const char *path), { return -1; })
MAESTRO_STUB(_ssize_t, _write_r (struct _reent *r, int fd, const void *buf, size_t nbytes), { return -1; })

MAESTRO_STUB(void, _exit(int status), { while(1); })

MAESTRO_STUB(int, _isatty_r(struct _reent* r, int file), { return -1; })
MAESTRO_STUB(int, _fstat_r(struct _reent* r, int file, struct stat* st), { return -1; })

/* stdlib.h */
MAESTRO_STUB(_PTR, _realloc_r(struct _reent *r, _PTR p, size_t s), { return 0; })
MAESTRO_STUB(_PTR, _calloc_r(struct _reent *r, size_t s1, size_t s2), { return 0; })
MAESTRO_STUB(_PTR, _malloc_r(struct _reent * r, size_t s), { return 0; })
MAESTRO_STUB(_VOID, _free_r(struct _reent *r, _PTR *p), { })

/* sys/mman.h */

MAESTRO_STUB(void*, mmap(void* addr, size_t len, int prot, int flags, int fildes, off_t off), { return (void*) 0; })
MAESTRO_STUB(int, munmap(void *addr, size_t len), { return -1; })

/* pthread.h */
MAESTRO_STUB(int, pthread_setcancelstate(int state, int *oldstate), { return -1; })

/* stubs for functions required by libc/stdlib */
MAESTRO_STUB(void, __assert_func(const char *file, int line, const char *failedexpr), { })

MAESTRO_STUB(void, _start(void), { })
