/*
 * memviz.h - v0.1.0 - text-based memory and pointer visualisation for C/C++
 *
 * Prints pointers, multi-level pointers and arrays as plain-text diagrams,
 * for the console or log files.
 *
 * Project:   https://github.com/jeshwanthreddy13/memvis
 * Author:    J Jeshwanth Reddy (@jeshwanthreddy13)
 * Copyright: (c) 2026 J Jeshwanth Reddy
 * License:   MIT (see LICENSE file)
 * First Commit: October 3rd, 2026
 * Latest Commit: October 3rd, 2026
 *
 * USAGE
 *   In .c/.cpp file:
 *       #include "memviz.h"
 *   Refer to example.c for working examples
 *
 * SUPPORTED VISUALISATIONS AS OF NOW
 *  1. INTEGER
 *  2. INTEGER ARRAY
 *  3. POINTER_TO_POINTER_TO_INTEGER
 *  4. ARRAY_OF_N_POINTER_TO_INTEGER
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define GLOBAL_VAR_ARR_SIZE 4

/**
 Different types of errors
 **/
typedef enum{
    MEM_SUCCESS,
    MEM_ERR_SET_GLOB_ARR_FAILURE,
    MEM_ERR_UNIMPLEMENTED,
    MEM_ERR_UNINITIALIZED,
    MEM_ERR_INVALID_TYPE
}ERROR_TYPE_t;

/**
 All types of possible types that memvis currently supports
 **/
typedef enum {
    CUSTOM,
    INTEGER,
    CHARACTER,
    DOUBLE,
    INTEGER_ARRAY,
    ADDRESS,
    POINTER_TO_INTEGER,
    POINTER_TO_CHARACTER,
    POINTER_TO_DOUBLE,
    POINTER_TO_POINTER_TO_INTEGER,
    ARRAY_OF_N_POINTER_TO_INTEGER,
    INVALID_TYPE
}VAR_TYPE_t;

/**
 Used to index the required fields from array gVarTypeArr
 **/
typedef enum {
    VAR_TYPE_PRINT_STRING,
    CONVERSION_SPECIFIER
}VAR_TYPE_ARR_INDEXER_t;

/**
 Stores the required information after setting the type
 **/
char *gVarTypeArr[GLOBAL_VAR_ARR_SIZE];

ERROR_TYPE_t memvis(void*, VAR_TYPE_t, size_t);
ERROR_TYPE_t memvis_ATP(int**, VAR_TYPE_t, size_t);
ERROR_TYPE_t memvis_uint32(uint32_t*);
ERROR_TYPE_t memvis_custom(void*, size_t);
ERROR_TYPE_t memvis_array(void*, VAR_TYPE_t, int);


ERROR_TYPE_t print_ContiguousBlocks(void *, VAR_TYPE_t, size_t);

/**
 sets gVarTypeArr with respective values w.r.t type

 varType => Expects VAR_TYPE_t variable
 **/
ERROR_TYPE_t set_gVarTypeArr(VAR_TYPE_t varType){

    if(varType >= INVALID_TYPE){
        printf("Error: Invalid Variable Type Passed!!, returning\n");
        return MEM_ERR_INVALID_TYPE;
    }

    if(varType ==  POINTER_TO_INTEGER){
        gVarTypeArr[VAR_TYPE_PRINT_STRING] = "Integer";
        gVarTypeArr[CONVERSION_SPECIFIER] = "d";
//        gVarTypeArr[VAR_TYPE] = INTEGER; TODO
        return MEM_SUCCESS;
    }

    else{
        gVarTypeArr[VAR_TYPE_PRINT_STRING] = "Integer"; // TBD - Temporary Hardcoded
        return MEM_SUCCESS;
    }                                               // To-be removed once architecture is confirmed

    return MEM_ERR_UNIMPLEMENTED;
}

/**
 unsets/initializes gVarTypeArr to null

 void
 **/
ERROR_TYPE_t unset_gVarTypeArr(){
    for(int i = 0; i < GLOBAL_VAR_ARR_SIZE; i++){
        gVarTypeArr[i] = "";
    }
    return MEM_SUCCESS;
}

ERROR_TYPE_t memvis_custom(void* customPlaceHolder, size_t typeSize){
    return MEM_ERR_UNIMPLEMENTED;
}

/**
 Represents the contiguous blocks of pointers and the values thry are pointing to

  placeHolder    => The address of the variable

  varType        => The type of variable to be dereferenced at the end

  _no_of_blocks_ => The number of contiguous memory blocks
 **/
ERROR_TYPE_t memvis_ATP(int** placeHolder, VAR_TYPE_t varType, size_t _no_of_blocks_){ //ARRAY_OF_N_POINTER_TO_INTEGER

    print_ContiguousBlocks(placeHolder, ADDRESS, _no_of_blocks_);

    for(int i = 0; i < _no_of_blocks_; i++){
        printf("\n\nREPRESENTATION OF POINTER TO %s IN INDEX %d \n", gVarTypeArr[VAR_TYPE_PRINT_STRING], i);
        printf("++++++++++++++++++\n");
        printf("| %-15d|\n",*(*(placeHolder+i)));
        printf("++++++++++++++++++\n");
        printf(" %-18p\n\n",*(placeHolder+i));
    }
    return MEM_SUCCESS;
}

ERROR_TYPE_t memvis_array(void* placeHolder, VAR_TYPE_t var_type, int _no_of_blocks_){

    if(var_type == INTEGER_ARRAY){
        return print_ContiguousBlocks(placeHolder, INTEGER, _no_of_blocks_);
    }
}

ERROR_TYPE_t print_ContiguousBlocks(void *placeHolder, VAR_TYPE_t var_type, size_t _no_of_blocks_){

    char fmt_val[10] = "| 0x%-15";
    char fmt_addr[9] = " %-18p";
    size_t varSize = sizeof(int);// TODO - HardCoded to `int` as of now
    size_t pointSize = sizeof(void*);

    fmt_val[9] = '\0';

    printf("|");
    for(int i = 0; i < _no_of_blocks_; i++){
        printf("++++++++++++++++++|");
    }
    printf("\n");

    /*Printing the values within the blocks*/
    for(int i = 0; i < _no_of_blocks_; i++){
        switch(var_type){
            case ADDRESS:
                printf("| %-17p", *(((int **)placeHolder)+i));
                break;
            case INTEGER:
                printf("| %-17d", *(int *)(placeHolder+(i*varSize)));
                break;
        }
    }

    printf("|\n|");
    for(int i = 0; i < _no_of_blocks_; i++){
        printf("++++++++++++++++++|");
    }

    printf("\n");

    for(int i = 0; i < _no_of_blocks_; i++){
        if(var_type == ADDRESS){
            printf(fmt_addr, (((void**)placeHolder)+i));
            continue;
        }
        printf(fmt_addr, (placeHolder+(i*varSize)));
    }

    printf("\n\n");

    return MEM_SUCCESS;

}
ERROR_TYPE_t memvis_PTP(int*** placeHolder, VAR_TYPE_t var_type){

    printf("\n\nREPRESENTATION OF POINTER(pp) HOLDING THE ADDRESS OF THE POINTER HOLDING"
            "THE ADDRESS OF THE %s VARIABLE\n", gVarTypeArr[VAR_TYPE_PRINT_STRING]);
    printf("++++++++++++++++++\n");
    printf("|%-16p| ==> pp\n",*placeHolder);
    printf("++++++++++++++++++\n");
    printf(" %-16p ==> &pp\n\n",placeHolder);

    printf("REPRESENTATION OF THE POINTER HOLDING THE ADDRESS OF THE INTEGER VARIABLE\n");
    printf("++++++++++++++++++\n");
    printf("|%-16p| ==> *pp\n",**placeHolder);
    printf("++++++++++++++++++\n");
    printf(" %-16p ==> pp\n\n",*placeHolder);

    printf("REPRESENTATION OF THE INTEGER VARIABLE AND THE VALUE IT IS HOLDING\n");
    printf("++++++++++++++++++\n");
    printf("| %-14d| ==> **pp\n",***placeHolder);
    printf("++++++++++++++++++\n");
    printf(" %-16p ==> *pp\n\n",**placeHolder);

    return MEM_SUCCESS;
}

ERROR_TYPE_t memvis_uint32(uint32_t* value){

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    printf("I am Little Endian\n");
#else
    printf("I am Big Endian\n");
#endif
    printf("The value is = 0x%x\n\n", *value);
    char *ch = (char*)value;
    printf("My Starting Address : %p\n\n", value);
    printf("++++++++++++++++++");printf("|+++++++++++++++++");printf("|+++++++++++++++++");printf("|+++++++++++++++++++\n");
    printf("| 0x%-14x",*(ch++));printf("| 0x%-14x",*(ch++));printf("| 0x%-14x",*(ch++));printf("| 0x%-14x |\n",(*ch));
    printf("++++++++++++++++++");printf("|+++++++++++++++++");printf("|+++++++++++++++++");printf("|+++++++++++++++++++\n");
    ch -= 3;
    printf("0x%-17p", ch++);printf("0x%-16p", ch++);printf("0x%-16p", ch++);printf("0x%-17p\n\n\n", ch);

}

/**
 Main function that is called by the user. The global variables are set and the
 respective sub-functions are called

 placeHolder => pointer that holds the address

 var_type => contains the type of variable to be visualized

 _no_of_blocks_
 **/
ERROR_TYPE_t memvis(void* placeHolder, VAR_TYPE_t var_type, size_t _no_of_blocks_){

    ERROR_TYPE_t retVal = MEM_ERR_UNINITIALIZED;
    if(set_gVarTypeArr(var_type) != MEM_SUCCESS){
        unset_gVarTypeArr();
        printf("[MEMVIS] Invalid VAR_TYPE\n");
        return MEM_ERR_SET_GLOB_ARR_FAILURE;
    }
    printf("\n--------------------MEMVIS REPRESENTATION START--------------------\n\n");
    switch(var_type){
    case INTEGER_ARRAY:
        retVal = memvis_array(placeHolder, var_type, _no_of_blocks_);
        break;
    case INTEGER:
        retVal = memvis_uint32((uint32_t*)placeHolder);
        break;
    case POINTER_TO_POINTER_TO_INTEGER:
        retVal = memvis_PTP((int***)placeHolder, var_type);
        break;
    case ARRAY_OF_N_POINTER_TO_INTEGER:
        retVal = memvis_ATP((int**)placeHolder, var_type, _no_of_blocks_);
        break;
    default :
        printf("[MEMVIS] Error: UNIMPLEMENTED!!, Returning\n");
        retVal = MEM_ERR_UNIMPLEMENTED;
    }
    unset_gVarTypeArr();
    printf("\n--------------------MEMVIS REPRESENTATION END----------------------\n\n");
    return retVal;
}
