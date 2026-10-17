/*
 * example.c — runnable usage guide for memvis
 *
 * memvis is header-only. Copy memvis.h next to your source (or onto your
 * include path), then:
 *
 *     #include "memvis.h"
 *
 * Compile this file with nothing extra to link:
 *
 *     cc example.c -o example
 *     ./example
 *
 * Diagrams go to stdout. Redirect if you want a log:
 *
 *     ./example > output.txt
 *
 * Addresses come from the running process. They change across machines and
 * often across runs (ASLR).
 *
 * ---------------------------------------------------------------------------
 * The call
 *
 *     ERROR_TYPE_t memvis(void *addr, VAR_TYPE_t type, size_t n_blocks);
 *
 * addr      Pointer to the object you want drawn.
 *           For a variable x, pass &x.
 *           For an array a, a already decays to a pointer — pass a.
 *
 * type      How to interpret those bytes. Must match what addr points at.
 *
 * n_blocks  How many cells to print, for arrays and pointer-arrays.
 *           Unused for a single int, char, or int ** — pass 0.
 *
 * Success returns MEM_SUCCESS. A wrong or unimplemented type prints an error.
 *
 * ---------------------------------------------------------------------------
 * How to read a cell
 *
 *     |++++++++++++++++++|
 *     | M                |   <- value stored here (char, int, or an address)
 *     |++++++++++++++++++|
 *      0x7ffee76d164f        <- address of that cell
 *
 * Arrays print several cells in a row. Adjacent elements have adjacent
 * addresses (stride is sizeof the element: 1 for char, usually 4 for int).
 *
 * ---------------------------------------------------------------------------
 * Not implemented yet (enum exists, memvis() will say UNIMPLEMENTED):
 *     CUSTOM, DOUBLE, POINTER_TO_DOUBLE, ADDRESS,
 *     POINTER_TO_INTEGER, POINTER_TO_CHAR
 *
 * A single int * can be drawn today as ARRAY_OF_N_POINTER_TO_INTEGER with
 * n_blocks == 1.
 *
 * Practical notes
 *   - Type must match the object or you will print garbage / read off the end
 *   - n_blocks is on you; memvis does not know array length
 *   - Do not pass NULL inner pointers; the follow-up dereference is unguarded as of now
 *   - Draw heap objects before free, stack objects while they are in scope
 */

#include <stdio.h>
#include <stdlib.h>
#include "memvis.h"

int main(void)
{
    /* ------------------------------------------------------------------
     * ARRAY_OF_N_POINTER_TO_INTEGER  —  int *b[N]
     *
     * Two layers:
     *   1. the pointer array itself (each cell holds an address)
     *   2. each pointer followed to the int it points at
     *
     * Pass &b (the array of pointers) and n_blocks == 3.
     * If the top-row addresses match the addresses printed under 100 / 101
     * / 102, the pointers are wired the way you think they are.
     * ------------------------------------------------------------------ */
    int x = 100, y = 101, z = 102;
    int *b[3];
    b[0] = &x;
    b[1] = &y;
    b[2] = &z;

    memvis(&b, ARRAY_OF_N_POINTER_TO_INTEGER, 3);

    /* ------------------------------------------------------------------
     * INTEGER_ARRAY  —  a row of ints
     *
     * Pass the array (decays to int *) and how many elements to show.
     * sizeof(xa)/sizeof(xa[0]) keeps the count tied to the declaration.
     * Each cell is one int; addresses increase by sizeof(int).
     * ------------------------------------------------------------------ */
    int xa[] = {1, 2, 3, 4, 5};
    memvis(xa, INTEGER_ARRAY, sizeof(xa) / sizeof(xa[0]));

    /* ------------------------------------------------------------------
     * CHAR_ARRAY  —  a row of characters
     *
     * Same box layout as INTEGER_ARRAY, but each cell is one byte and the
     * payload is printed as a character, not a numeric code.
     *
     * n_blocks is 6 so the trailing '\0' is left out. Pass 7 to show it.
     * Addresses increase by 1.
     * ------------------------------------------------------------------ */
    char charArray[7] = {'M', 'E', 'M', 'V', 'I', 'S', '\0'};
    memvis(charArray, CHAR_ARRAY, 6);

    /* ------------------------------------------------------------------
     * POINTER_TO_POINTER_TO_INTEGER  —  int **pp
     *
     * &pp -> pp -> *pp -> **pp
     *
     * Pass &pp, not pp. memvis needs the address of the int ** variable
     * so it can show all three levels. n_blocks is unused.
     *
     * Labels in the output:
     *   box "pp"    stores address of sp     address under the box is &pp
     *   box "*pp"   stores address of the int address under the box is pp
     *   box "**pp"  stores 3784               address under the box is *pp
     * ------------------------------------------------------------------ */
    int *sp = NULL;
    int **pp = NULL;
    sp = (int *)malloc(sizeof(int));
    *sp = 3784;
    pp = &sp;

    memvis(&pp, POINTER_TO_POINTER_TO_INTEGER, 0);
    free(*pp);

    /* ------------------------------------------------------------------
     * INTEGER  —  one int, split into bytes
     *
     * This is not a single box with 0x12345678. It prints one box per byte
     * plus the host endianness. n_blocks is ignored as of now; width is sizeof(int).
     *
     * Little-endian: 78 56 34 12  (lowest address = least significant byte)
     * Big-endian:    12 34 56 78
     *
     * Use this for layout (casts through char *, serialisation). If you
     * only want the numeric value in one cell, use INTEGER_ARRAY with
     * n_blocks == 1.
     * ------------------------------------------------------------------ */
    int tmp_val = 0x12345678;
    memvis(&tmp_val, INTEGER, 0);

    /* ------------------------------------------------------------------
     * CHAR  —  one character
     *
     * Pass the address of the char. You get one cell; the value is printed
     * as the character ('M'), not 77. n_blocks is ignored.
     * ------------------------------------------------------------------ */
    char tmp_charVal = 'M';
    memvis(&tmp_charVal, CHAR, 0);

    return 0;
}
