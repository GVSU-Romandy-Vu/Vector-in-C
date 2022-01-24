#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
It's an arrayList not a LinkedList
lite_vector field variables:
(unsigned long long) length: size of the lite_vector?
(unsigned long long) max_capacity: used to determine if the vector should expand?
(unsigned long long) type_size: useless, since it only holds pointers and all pointers have the same memory size, no parameter check of what element type is added?
(void**) data: a pointer that holds a void pointer (void pointer is universal?) [Also the "dynamic" array?]

realloc(): increase or decrease the size of the specified memory, moving it if necessary
calloc(): has 2 parameter where 1 is the # of elements and the second is the bytes to be allocated for each element and initalize to 0.
malloc(): allocates the specified bytes
memcpy(dest, source, byte_amount): copies data from source to dest


*/

//type_size is useless, memory addresses are only entered which have the same no matter what
//Acts like a "constructor"

lite_vector* lv_new_vec(size_t type_size){
    //Create it in the heap instead of stack with malloc.
    lite_vector* vector = (lite_vector*) malloc(sizeof(lite_vector));

    //Set length  to keep track of # of elements in vector->data.
    vector->length = 0;

    //Initally set max_capacity to 10, and used to check if length == max_capacity for updating.
    vector->max_capacity = 10;

    //Dynamically create the data (memory address array) in the heap, (will be change in size)
    vector->data = (void**)calloc(10,sizeof(void*));

    return vector;
}

//The clear() function use recursion?


void lv_cleanup(lite_vector* vec){
    //Check if the lite_vector is created
    if(vec != NULL){
        //free data first before freeing vec
        free(vec->data);
        free(vec);
    }
}

size_t lv_get_length(lite_vector* vec){
    //Check if lite_vector has been created
    if(vec == NULL){
    return 0; //return 0 because of clang.
    }
    
    return vec->length;
}

//reset


bool lv_clear(lite_vector* vec){
    //Check if vec is null (doesn't need to be cleared)
    if(vec == NULL){
        return false;
    }
    
    //Restarting to default state == creating lite_vector (i.e. using constructor)
    //remove current vec data
    lv_cleanup(vec);
    vec = lv_new_vec(1);
    return true;
}

//search through array
void* lv_get(lite_vector* vec, size_t index){
    
    //Check if lite_vector has been created to avoid errors
    if(vec == NULL){
        return NULL;
    }
    //Check if index is "out of bounds"
    if(index < (size_t)0 || index > vec->length){
        return NULL;
    }
    return vec->data[index];
}

/**
 * lv_resize is essentially private since we marked it static.
 * The job of this function is to attempt to resize the vector.
 * There may be functions you can call to do this for you, or
 * you may write it yourself.  Either way it isn't too hard.
 * With everything though, check to make sure the code worked
 * and return appropriately.  Do NOT destroy the data if the code
 * fails.  If the resize cannot complete, the original vector
 * must remain unaffected.
 */
static bool lv_resize(lite_vector* vec){
    //Not checking if lite_vector is created, because it is checked in lv_append (hopefully)
    

    /*+10 takes the additional elements to be added to the array. 
    Statement should be true if vec->max + 10 > 18,446,744,073,709,551,614 (max size for size_t) leading
    to a negative. Therefore any max_capacity for any lite vector is 18,446,744,073,709,551,610*/
    if(vec->max_capacity + 10 < vec->max_capacity){
        return false;
    }
    //give lite_vector's data more memory to hold 10 additional memory addresses.
    void** replace = (void**)calloc(vec->length + 10, sizeof(void*));
    memcpy(replace, vec->data, sizeof(void*)*vec->length);
    free(vec->data);
    vec->data = replace;
    //Update the max_capacity to check if the vec needs to be updated again.
    vec->max_capacity += 10;
    return true;

}

bool lv_append(lite_vector* vec, void* element){
    //Checks if vec is not null first
    if(vec == NULL){
        return false;
    }


    //Check if vec needs to resize, create a copy
    if(vec->length >= vec->max_capacity){
        //FIXME: Something could be wrong here.

        if(lv_resize(vec)){
		//So it works?
        }
        else{
            return false;
        }
    }
        vec->data[vec->length] = element;
        vec->length++;
        return true;
    


}
