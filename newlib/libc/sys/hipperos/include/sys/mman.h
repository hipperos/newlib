#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/types.h>

/** Page cannot be accessed. */
#define PROT_NONE 0

/** Page can be read. */
#define PROT_READ 1

/** Page can be written. */
#define PROT_WRITE 2

/** Page can be executed. */
#define PROT_EXEC 4

/**
 * Interpret vAddr exactly.
 *
 * @note Not supported.
 */
#define MAP_FIXED 0

/**
 * Changes are private.
 */
#define MAP_PRIVATE (1 << 0)

/**
 * Share changes.
 *
 * @note Not supported.
 */
#define MAP_SHARED (1 << 1)

/**
 * The mapping is not backed by any file; its contents are initialized to zero.
 *
 * @note Not POSIX but Linux-compliant.
 */
#define MAP_ANONYMOUS (1 << 2)

/**
 * Does not allocate memory but maps the provided physical address.
 *
 * @note HIPPEROS Extension.
 */
#define MAP_FIXED_PADDR (1 << 3)

/**
 * DMA memory allocation request.
 *
 * @note HIPPEROS Extension.
 */
#define MAP_DMA (1 << 4)

/**
 * Cacheability is provided.
 *
 * This is required to distinguish the lack of cacheability specification and
 * the policy of ID 0.
 */
#define _MAP_CACHEABILITY_PROVIDED (1 << 8)

/**
 * Cacheability.
 *
 * @note HIPPEROS Extension.
 */
#define MAP_CACHEABILITY(x) (_MAP_CACHEABILITY_PROVIDED | (((x) & 0x7F) << 9))

/** This is the value returned by mmap in case of failure. */
#define MAP_FAILED ((void*) -1)

/**
 * @brief Maps pages of memory.
 *
 * @warning This is the POSIX mmap signature.
 *          While we provide it for compatibility with existing code, there are
 *          several restrictions on its usage.
 *          Please use h_mmap() instead.
 *
 * There are 2 usages for this function:
 * 1. allocate normal memory (dynamic memory allocation)
 * 2. allocate DMA memory (for drivers, physical address is provided)
 *
 * Protection flags are used to give the appropriate access rights to the pages.
 * It is either ::PROT_READ, ::PROT_WRITE or a bitwise inclusive OR of both.
 * Some architectures do not support write-only protection flags, in which case
 * read permission will be added.
 *
 * The mapping starts and ends at a page boundary, meaning that the mapped
 * region starts at the page boundary equal to the result value and ends at
 * the boundary region after or equal to `result + length`.
 *
 * The @p flags argument determines whether an allocation should be performed
 * and the cacheability attributes.
 * `MAP_ANONYMOUS` must be set in @p flags.
 *
 * You can optionally also add `MAP_DMA`.
 * This will allocate a buffer suitable for DMA operations (contiguous in
 * physical memory) and its physical address will be returned.
 *
 * The cacheability can be optionally provided.
 * If they are not provided, the region will be mapped with a best-fit policy:
 *  - normal-memory allocation: write-through, write-back cache policy;
 *  - DMA memory allocation: uncacheable cache policy;
 * If the default policy does not fit, the cacheability can be provided by
 * doing a bitwise inclusive OR of the original @p flags and
 * `MAP_CACHEABILITY(x)` where `x` is an architecture-specific value that you
 * can find in the arch-specific memory management header file
 * ( `hipperos/arch/<arch>/<arch>_mm.h` of the HIPPEROS hapi).
 *
 * @param[in]   addr
 *              The address.
 * @param[in]   len
 *              Length in bytes of the region.
 * @param[in]   prot
 *              Desired memory protection of the mapping.
 * @param[in]   flags
 *              Attributes regarding the operation.
 * @param[in]   fildes
 *              Unused (must be set to -1).
 * @param[in]   off
 *              Unused (must be set to 0).
 *
 * @returns The virtual address where the region has been mapped.
 */
void* mmap(void* addr, size_t len, int prot, int flags, int fildes, off_t off);

/**
 * @brief Unmaps pages of memory.
 *
 * @param[in]   addr
 *              Start address to unmap (must be at a page boundary).
 * @param[in]   len
 *              Length in bytes.
 *
 * @returns 0 if the call succeeded, another value otherwise.
 */
int munmap(void *addr, size_t len);

#endif /* _SYS_MMAN_H_ */
