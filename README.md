# memvis

A small C/C++ header that draws **address blocks and the values they hold** as plain-text diagrams.

Copy `memvis.h` into your project, `#include` it from a `.c` / `.cpp` file, and call `memvis()`. The diagrams print to stdout (terminal or a log if you redirect). The idea is to stay lightweight, readable on a console, and useful when you are still getting comfortable with pointers.

It is early (v0.1). The supported types are growing one at a time.

## Why this exists

Pointers are easier to reason about when you can see:

- the address of a variable
- the value stored there
- and, for pointers, what the next hop actually points at

`memvis` is meant for that: debugging messy allocations, and teaching / learning `int*`, `int**`, arrays, and now `char` / `char[]`.

## What it can draw today

| `VAR_TYPE_t` | What you pass |
| --- | --- |
| `INTEGER` | address of an `int` (byte-by-byte, so endianness is visible) |
| `CHAR` | address of a `char` |
| `INTEGER_ARRAY` | `int` array (or pointer + length) |
| `CHAR_ARRAY` | `char` array |
| `POINTER_TO_POINTER_TO_INTEGER` | address of an `int**` (`&pp`) |
| `ARRAY_OF_N_POINTER_TO_INTEGER` | array of `int*` |

`CUSTOM`, `DOUBLE`, and a few other enum values are placeholders. They are not implemented yet.

## Quick start

`memvis` is a single header. Copy `memvis.h` into your project, include it from a `.c` / `.cpp` file, and call `memvis()`.

```c
#include "memvis.h"

int n = 42;
memvis(&n, INTEGER, 0);
```

```bash
cc example.c -o example
./example
```

Type-by-type arguments, how to read each diagram, and the usual pitfalls are commented in **[example.c](example.c)**. That file is the usage guide; compile it and you get the visualization too.

Addresses in the diagrams are from *your* process. They will not match the sample below.

## Example

[`example.c`](example.c) is the usage guide: a file-level comment on the API, then one commented section per type (`int *[]`, `int` array, `char` array, `int **`, byte-split `int`, single `char`).

Sample run (addresses from one machine; yours will differ):

<details>
<summary>Output of <code>example.c</code></summary>

```
--------------------MEMVIS REPRESENTATION START--------------------
MEMVIS VAR TYPE: ARRAY_OF_N_POINTER_TO_INTEGER
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
| 0x7ffee76d1650   | 0x7ffee76d1654   | 0x7ffee76d1658   |
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
 0x7ffee76d1690     0x7ffee76d1698     0x7ffee76d16a0



REPRESENTATION OF POINTER TO Integer IN INDEX 0
++++++++++++++++++
| 100            |
++++++++++++++++++
 0x7ffee76d1650



REPRESENTATION OF POINTER TO Integer IN INDEX 1
++++++++++++++++++
| 101            |
++++++++++++++++++
 0x7ffee76d1654



REPRESENTATION OF POINTER TO Integer IN INDEX 2
++++++++++++++++++
| 102            |
++++++++++++++++++
 0x7ffee76d1658


--------------------MEMVIS REPRESENTATION END----------------------

--------------------MEMVIS REPRESENTATION START--------------------
MEMVIS VAR TYPE: Integer Array
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
| 1                | 2                | 3                | 4                | 5                |
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
 0x7ffee76d1670     0x7ffee76d1674     0x7ffee76d1678     0x7ffee76d167c     0x7ffee76d1680


--------------------MEMVIS REPRESENTATION END----------------------

--------------------MEMVIS REPRESENTATION START--------------------
MEMVIS VAR TYPE: Character Array
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
| M                | E                | M                | V                | I                | S                |
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
 0x7ffee76d16b1     0x7ffee76d16b2     0x7ffee76d16b3     0x7ffee76d16b4     0x7ffee76d16b5     0x7ffee76d16b6


--------------------MEMVIS REPRESENTATION END----------------------

--------------------MEMVIS REPRESENTATION START--------------------
MEMVIS VAR TYPE:


REPRESENTATION OF POINTER(pp) HOLDING THE ADDRESS OF THE POINTER HOLDINGTHE ADDRESS OF THE Integer VARIABLE
++++++++++++++++++
|0x7ffee76d1668  | ==> pp
++++++++++++++++++
 0x7ffee76d1660   ==> &pp

REPRESENTATION OF THE POINTER HOLDING THE ADDRESS OF THE INTEGER VARIABLE
++++++++++++++++++
|0x5596ea107420  | ==> *pp
++++++++++++++++++
 0x7ffee76d1668   ==> pp

REPRESENTATION OF THE INTEGER VARIABLE AND THE VALUE IT IS HOLDING
++++++++++++++++++
| 3784          | ==> **pp
++++++++++++++++++
 0x5596ea107420   ==> *pp


--------------------MEMVIS REPRESENTATION END----------------------

--------------------MEMVIS REPRESENTATION START--------------------
MEMVIS VAR TYPE: Integer
I am Little Endian
The value is = 0x12345678

My Starting Address : 0x7ffee76d165c

|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
| 78               | 56               | 34               | 12               |
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
 0x7ffee76d165c     0x7ffee76d1664     0x7ffee76d166c     0x7ffee76d1674


--------------------MEMVIS REPRESENTATION END----------------------

--------------------MEMVIS REPRESENTATION START--------------------
MEMVIS VAR TYPE: Character
|++++++++++++++++++|
| M                |
|++++++++++++++++++|
 0x7ffee76d164f


--------------------MEMVIS REPRESENTATION END----------------------
```

</details>

How to read a block: the middle row is the stored value (or a pointer), the row under it is the address of that cell.

For `INTEGER`, memvis splits the value into bytes so you can see endianness. On little-endian, `0x12345678` shows up as `78 56 34 12`.

`CHAR` / `CHAR_ARRAY` print the character in the cell, not a numeric code.

## Contributing

Issues and PRs are welcome. Check the issue list first — there are bugs and features already written down.

This library is supposed to stay small and predictable. Please send a change you actually understand, and that you have run against `example.c` (or a similar snippet). Generated dumps that you have not read through will get closed.

## License

MIT. See [LICENSE](LICENSE).
