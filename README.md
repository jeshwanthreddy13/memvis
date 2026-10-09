# memvis
A lightweight and simple C/C++ library that visualises memory from simple pointers to multi-level pointers and arrays, as plain-text diagrams. Print them to the console or write them to log files to debug your code and understand how it works.

The goal of this project is help debug memory issues related to allocations. It is also very useful for understanding and learing complex pointer allocations and handling.

Please feel free to contribute and raise PR's, but no AI slop.
This project has been developed with the intention of it being very reliable and intuitive. Hence, only raise meaningfull PRs where you understand the change and the existing working in and out.

Refer to the list of issues to see if you can contribute to any of the BUGs or feature enhancements.

Currently supported visualisations are:

1. INTEGER
2. INTEGER ARRAY
3. POINTER_TO_POINTER_TO_INTEGER
4. ARRAY_OF_N_POINTER_TO_INTEGER

HOW TO USE?

Call `memvis` with the following arguments:
  - argument 1 => The address of the variable that needs to be visualised
  - argument 2 => The type of the variable passed, refer to enum `VAR_TYPE_t`
  - argument 3 => The total numbers of blocks to be visualised

It is as simple as this for now!! Please refer to `example.c`


Output of example.c

```

--------------------MEMVIS REPRESENTATION START--------------------

|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
| 0x7ffcd72ea900   | 0x7ffcd72ea904   | 0x7ffcd72ea908   |
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
 0x7ffcd72ea940     0x7ffcd72ea948     0x7ffcd72ea950    



REPRESENTATION OF POINTER TO Integer IN INDEX 0 
++++++++++++++++++
| 100            |
++++++++++++++++++
 0x7ffcd72ea900    



REPRESENTATION OF POINTER TO Integer IN INDEX 1 
++++++++++++++++++
| 101            |
++++++++++++++++++
 0x7ffcd72ea904    



REPRESENTATION OF POINTER TO Integer IN INDEX 2 
++++++++++++++++++
| 102            |
++++++++++++++++++
 0x7ffcd72ea908    


--------------------MEMVIS REPRESENTATION END----------------------

--------------------MEMVIS REPRESENTATION START--------------------

|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
| 1                | 2                | 3                | 4                | 5                |
|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|++++++++++++++++++|
 0x7ffcd72ea920     0x7ffcd72ea924     0x7ffcd72ea928     0x7ffcd72ea92c     0x7ffcd72ea930    


--------------------MEMVIS REPRESENTATION END----------------------


--------------------MEMVIS REPRESENTATION START--------------------



REPRESENTATION OF POINTER(pp) HOLDING THE ADDRESS OF THE POINTER HOLDINGTHE ADDRESS OF THE Integer VARIABLE
++++++++++++++++++
|0x7ffcd72ea918  | ==> pp
++++++++++++++++++
 0x7ffcd72ea910   ==> &pp

REPRESENTATION OF THE POINTER HOLDING THE ADDRESS OF THE INTEGER VARIABLE
++++++++++++++++++
|0x5b53dfbb86b0  | ==> *pp
++++++++++++++++++
 0x7ffcd72ea918   ==> pp

REPRESENTATION OF THE INTEGER VARIABLE AND THE VALUE IT IS HOLDING
++++++++++++++++++
| 3784          | ==> **pp
++++++++++++++++++
 0x5b53dfbb86b0   ==> *pp


--------------------MEMVIS REPRESENTATION END----------------------


--------------------MEMVIS REPRESENTATION START--------------------

I am Little Endian
The value is = 0x12345678

My Starting Address : 0x7ffcd72ea90c

++++++++++++++++++|+++++++++++++++++|+++++++++++++++++|+++++++++++++++++++
| 0x78            | 0x56            | 0x34            | 0x12             |
++++++++++++++++++|+++++++++++++++++|+++++++++++++++++|+++++++++++++++++++
0x0x7ffcd72ea90c   0x0x7ffcd72ea90d  0x0x7ffcd72ea90e  0x0x7ffcd72ea90f   



--------------------MEMVIS REPRESENTATION END----------------------


```
