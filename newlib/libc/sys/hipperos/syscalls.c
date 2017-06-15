#include <reent.h>

#include <stdint.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>

extern void abort(void);

/* HIPPEROS system calls */
extern void h_exit(int status);
extern unsigned int h_getPid(void);
extern int h_log(uint8_t category,
                 uint16_t messageType,
                 const char* contentPtr,
                 uint32_t contentLength);


#undef errno
extern int errno;

char* __env[1] = {0};
char** environ = __env;

void _exit(int status)
{
    h_exit(status);
    __builtin_unreachable();
}

int _close_r(struct _reent* r, int fd)
{
    return -1;
}

int _execve_r(struct _reent* r,
              const char* name,
              char* const* argv,
              char* const* env)
{
    r->_errno = ENOMEM;
    return -1;
}

int _fork_r(struct _reent* r)
{
    r->_errno = ENOTSUP;
    return -1;
}

int _fstat_r(struct _reent* r, int file, struct stat* st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _getpid_r(struct _reent* r)
{
    return h_getPid();
}

int _isatty_r(struct _reent* r, int file)
{
    r->_errno = ENOSYS;
    return 0;
}

int _kill_r(struct _reent* r, int pid, int sig)
{
    r->_errno = EINVAL;
    return -1;
}

int _link_r(struct _reent* r, const char* old, const char* new)
{
    r->_errno = EMLINK;
    return -1;
}

off_t _lseek_r(struct _reent* r, int fd, off_t pos, int whence)
{
    return 0;
}

int _open_r(struct _reent* r, const char* buf, int flags, int mode)
{
    return -1;
}

_ssize_t _read_r(struct _reent* r, int file, void* ptr, size_t len)
{
    return 0;
}

void* _sbrk_r(struct _reent* r, ptrdiff_t incr)
{
    register char* stack_ptr asm("sp");
    extern char _app_bss_end; /* Defined by the linker */
    static char* heap_end;
    char* prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_app_bss_end;
    }
    prev_heap_end = heap_end;
    if (heap_end + incr > stack_ptr) {
        _write_r(r, 1, "Heap and stack collision\n", 25);
        abort();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

int _stat_r(struct _reent* r, const char* file, struct stat* st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

_CLOCK_T_ _times_r(struct _reent* r, struct tms* buf)
{
    return -1;
}

_ssize_t _write_r(struct _reent* r, int file, const void* ptr, size_t len)
{
    h_log(0u, 1u, ptr, len);
    return len;
}
