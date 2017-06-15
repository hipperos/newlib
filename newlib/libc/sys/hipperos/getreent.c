#include <reent.h>

extern struct _reent* hnewlib_getreent(void);

struct _reent* __getreent(void)
{
    return hnewlib_getreent();
}
