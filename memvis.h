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
 *  2. CHARACTER
 *  3. INTEGER ARRAY
 *  4. CHARACTER ARRAY
 *  5. POINTER_TO_POINTER_TO_INTEGER
 *  6. ARRAY_OF_N_POINTER_TO_INTEGER
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
    MEM_ERR_NULL,
    MEM_ERR_SET_GLOB_ARR_FAILURE,
    MEM_ERR_UNIMPLEMENTED,
    MEM_ERR_NONE,
    MEM_ERR_INVALID_TYPE
}ERROR_TYPE_t;

/**
 All types of possible types that memvis supports or will support in the future
 **/
typedef enum {
    CUSTOM,
    INTEGER,
    CHAR,
    DOUBLE,
    INTEGER_ARRAY,
    CHAR_ARRAY,
    ADDRESS,
    POINTER_TO_INTEGER,
    POINTER_TO_CHAR,
    POINTER_TO_DOUBLE,
    POINTER_TO_POINTER_TO_INTEGER,
    ARRAY_OF_N_POINTER_TO_INTEGER,
    INVALID_TYPE
}VAR_TYPE_t;

/**
 Used to index the required fields from array gVarInfoArr
 **/
typedef enum {
    BASE_VAR_TYPE_PRINT_STRING,
    VAR_TYPE_PRINT_STRING,
    CONVERSION_SPECIFIER
}VAR_INFO_ARR_INDEXER_t;

/**
 Used to index the required fields from array gVarTypeArr
 **/
typedef enum{
    VAR_TYPE,
    BASE_VAR_TYPE
}VAR_TYPE_ARR_INDEXER_t;

/**
 Stores the required information after setting the type
 **/
char *gVarInfoArr[GLOBAL_VAR_ARR_SIZE];
VAR_TYPE_t gVarTypeArr[GLOBAL_VAR_ARR_SIZE];
size_t gVarSize = 0;

ERROR_TYPE_t memvis(void*, VAR_TYPE_t, size_t);
ERROR_TYPE_t memvis_ATP(int**, VAR_TYPE_t, size_t);
ERROR_TYPE_t memvis_int(int*);
ERROR_TYPE_t memvis_custom(void*, size_t);
ERROR_TYPE_t memvis_array(void*, VAR_TYPE_t, int);


ERROR_TYPE_t PrintContiguousBlocks(void *, VAR_TYPE_t, size_t);
ERROR_TYPE_t PrintOneByteBlocks(char *, VAR_TYPE_t, size_t);

/**
 sets gVarInfoArr with respective values w.r.t type

 varType => Expects VAR_TYPE_t variable
 **/
ERROR_TYPE_t set_gVarArrays(VAR_TYPE_t varType){

    if(varType >= INVALID_TYPE){
        printf("Error: Invalid Variable Type Passed!!, returning\n");
        return MEM_ERR_INVALID_TYPE;
    }

    if(varType == POINTER_TO_INTEGER){
        gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING] = "Integer";
        gVarInfoArr[VAR_TYPE_PRINT_STRING] = "POINTER TO INTEGER";
        gVarInfoArr[CONVERSION_SPECIFIER] = "d";
        gVarTypeArr[VAR_TYPE] = POINTER_TO_INTEGER;
        gVarTypeArr[BASE_VAR_TYPE] = INTEGER;
        gVarSize = sizeof(int);
        return MEM_SUCCESS;
    }

    else
        if(varType == INTEGER){
            gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING] = "Integer";
            gVarInfoArr[VAR_TYPE_PRINT_STRING] = "Integer";
            gVarInfoArr[CONVERSION_SPECIFIER] = "d";
            gVarTypeArr[VAR_TYPE] = INTEGER;
            gVarTypeArr[BASE_VAR_TYPE] = gVarTypeArr[VAR_TYPE];
            gVarSize = sizeof(int);
            return MEM_SUCCESS;
        }

    else
        if(varType == INTEGER_ARRAY){
            gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING] = "Integer";
            gVarInfoArr[VAR_TYPE_PRINT_STRING] = "Integer Array";
            gVarInfoArr[CONVERSION_SPECIFIER] = "d";
            gVarTypeArr[VAR_TYPE] = INTEGER_ARRAY;
            gVarTypeArr[BASE_VAR_TYPE] = INTEGER;
            gVarSize = sizeof(int);
            return MEM_SUCCESS;
        }
    else
        if(varType == CHAR_ARRAY){
            gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING] = "Character";
            gVarInfoArr[VAR_TYPE_PRINT_STRING] = "Character Array";
            gVarInfoArr[CONVERSION_SPECIFIER] = "c";
            gVarTypeArr[VAR_TYPE] = CHAR_ARRAY;
            gVarTypeArr[BASE_VAR_TYPE] = CHAR;
            gVarSize = sizeof(char);
            return MEM_SUCCESS;
        }

    else
        if(varType == CHAR){
            gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING] = "Character";
            gVarInfoArr[VAR_TYPE_PRINT_STRING] = "Character";
            gVarInfoArr[CONVERSION_SPECIFIER] = "c";
            gVarTypeArr[VAR_TYPE] = CHAR;
            gVarTypeArr[BASE_VAR_TYPE] = gVarTypeArr[VAR_TYPE];
            gVarSize = sizeof(char);
            return MEM_SUCCESS;
        }

    else
        if(varType == ARRAY_OF_N_POINTER_TO_INTEGER){
            gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING] = "Integer";
            gVarInfoArr[VAR_TYPE_PRINT_STRING] = "ARRAY_OF_N_POINTER_TO_INTEGER";
            gVarInfoArr[CONVERSION_SPECIFIER] = "d";
            gVarTypeArr[VAR_TYPE] = ARRAY_OF_N_POINTER_TO_INTEGER;
            gVarTypeArr[BASE_VAR_TYPE] = INTEGER;
            gVarSize = sizeof(char);
            return MEM_SUCCESS;
        }

    else{
        gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING] = "Integer"; // TBD - Temporary Hardcoded
        return MEM_SUCCESS;
    }                                               // To-be removed once architecture is confirmed

    return MEM_ERR_UNIMPLEMENTED;
}

/**
 unsets/initializes gVarInfoArr to null

 void
 **/
ERROR_TYPE_t unset_gVarArrays(){
    for(int i = 0; i < GLOBAL_VAR_ARR_SIZE; i++){
        gVarInfoArr[i] = "";
        gVarTypeArr[i] = INVALID_TYPE;
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

    PrintContiguousBlocks(placeHolder, ADDRESS, _no_of_blocks_);

    for(int i = 0; i < _no_of_blocks_; i++){
        printf("\n\nREPRESENTATION OF POINTER TO %s IN INDEX %d \n", gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING], i);
        printf("++++++++++++++++++\n");
        printf("| %-15d|\n",*(*(placeHolder+i)));
        printf("++++++++++++++++++\n");
        printf(" %-18p\n\n",*(placeHolder+i));
    }
    return MEM_SUCCESS;
}

ERROR_TYPE_t memvis_array(void* placeHolder, VAR_TYPE_t var_type, int _no_of_blocks_){

    if(var_type == INTEGER_ARRAY){
        return PrintContiguousBlocks(placeHolder, INTEGER, _no_of_blocks_);
    }
    if(var_type == CHAR_ARRAY){
        return PrintContiguousBlocks(placeHolder, CHAR, _no_of_blocks_);
    }
}

ERROR_TYPE_t PrintOneByteBlocks(char *placeHolder, VAR_TYPE_t var_type, size_t _no_of_blocks_){

    char fmt_val[8] = "| %-17x";
    char fmt_addr[9] = " %-18p";
    size_t varSize = gVarSize;
    size_t pointSize = sizeof(void*);

    printf("|");
    /*Printing the upper block boundary*/
    for(int i = 0; i < _no_of_blocks_; i++){
        printf("++++++++++++++++++|");
    }
    printf("\n");

    /*Printing the values within the blocks*/
    for(int i = 0; i < _no_of_blocks_; i++){
        printf(fmt_val, *(char *)(placeHolder+(i)));
    }

    /*Printing the lower block boundary*/
    printf("|\n|");
    for(int i = 0; i < _no_of_blocks_; i++){
        printf("++++++++++++++++++|");
    }
    printf("\n");

    /*Printing the address, 1 Byte Blocks*/
    for(int i = 0; i < _no_of_blocks_; i++){
        printf(fmt_addr, (((char**)placeHolder)+i));
    }

    printf("\n\n");
    return MEM_SUCCESS;
}

ERROR_TYPE_t PrintContiguousBlocks(void *placeHolder, VAR_TYPE_t var_type, size_t _no_of_blocks_){

    /*Assigning initially for printing pointer types*/
    char fmt_val[8] = "| %-17p";
    char fmt_addr[9] = " %-18p";
    /*Assigning initially for printing pointer types*/
    size_t varSize = sizeof(void*);
    size_t pointSize = sizeof(void*);
    /*Assigning data type values if not pointer type*/
    if(var_type != ADDRESS){
        fmt_val[6] = gVarInfoArr[CONVERSION_SPECIFIER][0];
        varSize = gVarSize;
    }

    printf("|");
    /*Printing the upper block boundary*/
    for(int i = 0; i < _no_of_blocks_; i++){
        printf("++++++++++++++++++|");
    }
    printf("\n");

    /*Printing the values within the blocks may be address or values derefernced respectively*/
    for(int i = 0; i < _no_of_blocks_; i++){
        switch(var_type){
            case ADDRESS:
                printf(fmt_val, *(((int **)placeHolder)+i));
                break;
            case INTEGER:
                printf(fmt_val, *(int *)(placeHolder+(i*sizeof(int))));
                break;
            case CHAR:
                printf(fmt_val, *(char *)(placeHolder+(i*sizeof(char))));
                break;
        }
    }
    /*Printing the lower block boundary*/
    printf("|\n|");
    for(int i = 0; i < _no_of_blocks_; i++){
        printf("++++++++++++++++++|");
    }

    printf("\n");

    /*Printing the address of the block(s)*/
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
            "THE ADDRESS OF THE %s VARIABLE\n", gVarInfoArr[BASE_VAR_TYPE_PRINT_STRING]);
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

ERROR_TYPE_t memvis_int(int* value){

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    printf("I am Little Endian\n");
#else
    printf("I am Big Endian\n");
#endif
    printf("The value is = 0x%x\n\n", *value);
    char *ch = (char*)value;
    printf("My Starting Address : %p\n\n", value);
    PrintOneByteBlocks(ch, INTEGER, sizeof(int));
}

/**
 Main function that is called by the user. The global variables are set and the
 respective sub-functions are called

 placeHolder => pointer that holds the address

 var_type => contains the type of variable to be visualized

 _no_of_blocks_
 **/
ERROR_TYPE_t memvis(void* placeHolder, VAR_TYPE_t var_type, size_t _no_of_blocks_){

    ERROR_TYPE_t retVal = MEM_ERR_NONE;
    if(placeHolder == NULL){
        retVal = MEM_ERR_NULL;
        return retVal;
    }
    if(set_gVarArrays(var_type) != MEM_SUCCESS){
        unset_gVarArrays();
        printf("[MEMVIS] Invalid VAR_TYPE\n");
        return MEM_ERR_SET_GLOB_ARR_FAILURE;
    }
    printf("\n--------------------MEMVIS REPRESENTATION START--------------------\n");
    printf("MEMVIS VAR TYPE: %s\n", gVarInfoArr[VAR_TYPE_PRINT_STRING]);
    switch(var_type){
    case INTEGER_ARRAY:
        retVal = memvis_array(placeHolder, var_type, _no_of_blocks_);
        break;
    case CHAR_ARRAY:
        retVal = memvis_array(placeHolder, var_type, _no_of_blocks_);
        break;
    case INTEGER:
        retVal = memvis_int((int*)placeHolder);
        break;
    case CHAR:
        retVal = PrintContiguousBlocks((char*)placeHolder, CHAR, 1);
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
    unset_gVarArrays();
    printf("\n--------------------MEMVIS REPRESENTATION END----------------------\n");
    return retVal;
}
