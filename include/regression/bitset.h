#ifndef REGRESSION_BITSET_H
#define REGRESSION_BITSET_H

/**
 * @file
 * 
 * @brief Operations for creating and manipulating a bitset.
 * 
 * A bitset is effectively an array of bools that are packed such that each bool
 * takes up only a single bit in memory.
 * 
 * This implementation is inspired by the recommendation provided by the C FAQ:
 * http://c-faq.com/misc/bitsets.html
 * 
 * Though this implementation deviates from the macro-based approach provided
 * by the FAQ, and opts for a somewhat more typesafe approach.
 */

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

//--- DEFINES ------------------------------------------------------------------

/**
 * The type to use for a bitset.
 * 
 * A single element of this type only represents a single slot containing at
 * most @c CHAR_BITS bits. To create a bitset containing more bits, create an
 * array of this type and use @ref BITSET_SIZE to determine the size.
 * 
 * Example:
 *     // Statically allocate a bitset containing 27 bits
 *     bitset my_bits[BITSET_SIZE(27)] = {0};
 */
typedef char bitset;

/**
 * Convert the size of a bitset to the minimum number of slots needed to hold
 * the bits.
 * 
 * Use this to determine the size of a @ref bitset array to create your bitset.
 * See @ref bitset for an example of how to declare a bitset properly.
 * 
 * @param[in] bits
 *     The number of bits in the bitset.
 * 
 * @return
 *     The number of slots needed in the bitset to hold the bits.
 * 
 * @note If @p bits is not aligned on a @c CHAR_BITS boundary, the total size
 *       of the bitset array is going to be slightly larger than the requested
 *       number of bits. This is unavoidable, since there's no way to allocate
 *       less than a byte of space in C.
 */
#define BITSET_SIZE(bits) (((((size_t)(bits) - 1) / CHAR_BIT) + 1) * CHAR_BIT)

//--- STATIC -------------------------------------------------------------------

/**
 * Determine the mast to use to isolate a particular bit within its slot in a
 * bitset.
 * 
 * @param[in] bit
 *     The index of the bit in the bitset.
 *  
 * @return
 *     The mask to apply to the byte containing the bit to isolate the bit.
 */
inline uint8_t bitset_mask(size_t bit)
{
    return 1 << (bit % CHAR_BIT);
}

/**
 * Determine the slot index of a particular bit.
 * 
 * @param[in] bit
 *     The index of the bit in the bitset.
 * 
 * @return
 *     The index of the byte containing the bit in the bitsef. 
 */
inline size_t bitset_slot(size_t bit)
{
    return bit / CHAR_BIT;
}

//--- INSTANCE -----------------------------------------------------------------

/**
 * Set a particular bit in a bitset to @c 0.
 * 
 * @param[out] bitset
 *     The bitset to modify.
 * @param[in] bit 
 *     The index of the bit to set.
 */
inline void bitset_clear(bitset bitset[], size_t bit)
{
    bitset[bitset_slot(bit)] &= ~bitset_mask(bit);
}

/**
 * Set a particular bit in a bitset to @c 1.
 * 
 * @param[out] bitset
 *     The bitset to modify.
 * @param[in] bit 
 *     The index of the bit to set.
 */
inline void bitset_set(bitset bitset[], size_t bit)
{
    bitset[bitset_slot(bit)] |= bitset_mask(bit);
}

/**
 * Test the value of a particular bit in a bitset.
 * 
 * @param[in] bitset
 *     The bitset to check.
 * @param[in] bit
 *     The index of the bit to test.
 * 
 * @return
 *     The value of the bit.
 */
inline bool bitset_test(const bitset bitset[], size_t bit)
{
    return bitset[bitset_slot(bit)] & bitset_mask(bit);
}

/**
 * Write a particular value to a bit in the bitset.
 * 
 * @param[out] bitset
 *     The bitset to modify.
 * @param[in] bit
 *     The index of the bit to modify.
 * @param[in] value 
 *     The value to set the bit to.
 */
inline void bitset_write(bitset bitset[], size_t bit, bool value)
{
    if (value)
    {
        bitset_set(bitset, bit);
    }
    else
    {
        bitset_clear(bitset, bit);
    }
}

/**
 * Print a bitset to stdout.
 * 
 * @param[in] bitset
 *     The bitset to print. 
 * @param[in] size
 *     The size (in bits) of the bitset.
 */
inline void bitset_print(const bitset bitset[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d", bitset_test(bitset, i));
    }
}

#endif // REGRESSION_BITSET_H