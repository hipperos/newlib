/*
 * Static implementation of CPU-set functions for HIPPEROS. Based on bitfields.
 *
 * We currently support up to 32 CPUs using this API. CPU IDs start from 0
 * up to 31.
 */

#include <stdint.h>

typedef struct {
    uint32_t __bits;
} cpu_set_t;

static inline void CPU_ZERO(cpu_set_t* set)
{
    set->__bits = 0u;
}

static inline void CPU_SET(int cpu, cpu_set_t* set)
{
    const uint32_t bit = (1u << cpu);
    set->__bits |= bit;
}

static inline void CPU_CLR(int cpu, cpu_set_t* set)
{
    const uint32_t bit = (1u << cpu);
    set->__bits &= ~bit;
}

static inline int CPU_ISSET(int cpu, cpu_set_t* set)
{
    const uint32_t bit = (1u << cpu);
    return (set->__bits & bit) != 0u;
}

static inline int CPU_COUNT(const cpu_set_t* set)
{
    return __builtin_popcountl(set->__bits);
}

static inline void
CPU_AND(cpu_set_t* destset, const cpu_set_t* set1, const cpu_set_t* set2)
{
    destset->__bits = set1->__bits & set2->__bits;
}

static inline void
CPU_OR(cpu_set_t* destset, const cpu_set_t* set1, const cpu_set_t* set2)
{
    destset->__bits = set1->__bits | set2->__bits;
}

static inline void
CPU_XOR(cpu_set_t* destset, const cpu_set_t* set1, const cpu_set_t* set2)
{
    destset->__bits = set1->__bits ^ set2->__bits;
}

static int CPU_EQUAL(const cpu_set_t* set1, const cpu_set_t* set2)
{
    return set1->__bits == set2->__bits;
}
