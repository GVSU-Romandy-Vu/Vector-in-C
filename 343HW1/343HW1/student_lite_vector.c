#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
It's an arrayList
lite_vector field variables:
(unsigned long long) length: size of the lite_vector, used to keep track of "data" size.
(unsigned long long) max_capacity: used to determine if the vector should expand
(unsigned long long) type_size: useless, since it only holds pointers and all pointers have the same memory size?
(void**) data: a pointer that holds a void pointer (void pointer is universal?) [Also the "dynamic" array?]

realloc(): increase or decrease the size of the specified memory, moving it if necessary
calloc(): has 2 parameter where 1 is the # of elements and the second is the bytes to be allocated for each element and initalize to 0.
malloc(): allocates the specified bytes
memcpy(dest, source, byte_amount): copies data from source to dest

*/


/*****************************************************************
 *
 *Acts like "constuctor"
 *Creates a pointer that holds a lite_vector
 *
 * @param type_size size of the type_size in bits (doesn't matter though).
 * @return a pointer that holds a lite_vector.
 ****************************************************************/
lite_vector* lv_new_vec(size_t type_size){
    //Create it in the heap instead of stack with malloc.
    lite_vector* vector = (lite_vector*) malloc(sizeof(lite_vector));

    //Will be as an index to add elements to data, and checking data needs expanding.
    vector->length = 0;

    /* Set max_capacity to 13 for  Max value of for indexing array ends in a 3).
     */
    vector->max_capacity = 13;

    /*Treat void** data as void* data[] (An array that holds pointers)
     * Created in the heap as more memory is needed due to resizing
     * 
     */
    vector->data = (void**)calloc(13,sizeof(void*));

    return vector;
}



/*************************************************************************
 *
 *Frees the pointer holding a lite_vector and it's data.
 *
 *@para vec The pointer that holds the lite_vector to be freed.
 *************************************************************************/
void lv_cleanup(lite_vector* vec){
    //Check if the lite_vector is created
    if(vec != NULL){
        //free data first before freeing vec
        free(vec->data);
        free(vec);
    }
}

/***********************************************************************
 *
 * Determines the length of the lite_vector that the pointer is holding.
 *
 * @param vec a lite_vector pointer that is being used to check its size.
 * @return the size of the lite_vector that vec is holding of type size_t (unsigned long long)
 **********************************************************************/
size_t lv_get_length(lite_vector* vec){
    //Check if lite_vector has been created
    if(vec == NULL){
    return 0; //return 0 because of clang.
    }
    
    return vec->length;
}


/********************************************************************
 *
 *Returns the lite_vector pointer to it's default state (max_capicity = 10,
 *length = 0, no elements in data).
 *
 * @param vec The lite_vector pointer whose lite_vector is being cleared.
 * @return A new lite_vector for the lite_vector pointer.
 ********************************************************************/
bool lv_clear(lite_vector* vec){
    //Check if vec is null (doesn't need to be cleared)
    if(vec == NULL){
        return false;
    }
    
    //Free data, dynamically allocate memory to it, and reset length and max_capacity
    free(vec->data);
    vec->data = (void**)calloc(13, sizeof(void*));
    vec->max_capacity = 13;
    vec->length = 0;
    //DON'T USE lv_cleanup() and lv_new_vec(); it creates memory leaks.
    
    
    return true;
}

/************************************************************************
 *
 *Retrieves a memory address from the pointer who holds a lite_vector
 *
 * @param vec the lite_vector pointer whose lite_vector data element is being retrieved
 * @param index the specified index to retrieve the element from the data
 * @return the memory address of the lite_vector pointer data.
 ***********************************************************************/
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

/************************************************************************
 *
 * The private function for lv_append to check if data should be given more memory
 *
 * lv_resize is essentially private since we marked it static.
 * The job of this function is to attempt to resize the vector.
 * There may be functions you can call to do this for you, or
 * you may write it yourself.  Either way it isn't too hard.
 * With everything though, check to make sure the code worked
 * and return appropriately.  Do NOT destroy the data if the code
 * fails.  If the resize cannot complete, the original vector
 * must remain unaffected.
 *
 * @param vec The lite_vector pointer whose lite_vector data is being checked
 * @return True if max_capacity is increased, False if failed to transfer data or  increase capacity.
 ************************************************************************/
static bool lv_resize(lite_vector* vec){
    //Not checking if lite_vector is created, because it is checked in lv_append (hopefully)
    

    /*The max capacity of any lite_vector is num = 18446744073709551613 due to the max index value and max length of type unsigned long long (size_t).
     * Although the maximum number of size_t is num +  2, the num will be 0. If the max_capacity is num + 1, it will
     * bug out length (length will be set to 0 if all data is full).
     * So return false if adding 10 more memory space will reset max_capacity
     * Can't check if vec->max_capacity == num because of warning*/
    if(vec->max_capacity + 10 < vec->max_capacity){
        return false;
    }
    //give lite_vector's data more memory to hold 10 additional memory addresses.
    void** replace = (void**)calloc(vec->length + 10, sizeof(void*));
    memcpy(replace, vec->data, sizeof(void*)*vec->length); //my grade depends on this function working properly.

    //Check if the copy is the same, and if not remove copy and return false.
    for(size_t i = 0; i <= vec->length; i++){
	    if(vec->data[i] != replace[i]){
		    free(replace);
		    return false;
	    
	    }
    
    }

    //free from heap to avoid memory leaks
    free(vec->data);

    //transfer the copy with additional memory space.
    vec->data = replace;

    //This line of code below works, but clang has a warning on it.
    //realloc(vec->data, (sizeof(void*) * vec->length) + (sizeof(void) * 10))
    
    //Update the max_capacity to check if the vec needs to be updated again.
    vec->max_capacity += 10;
    return true;

}

bool lv_append(lite_vector* vec, void* element){
    //Checks if vec is not null first
    if(vec == NULL){
        return false;
    }


    //Check if vec needs to resize, with lv_resize(vec) will resize (increase) vec->data capacity.
    if(vec->length >= vec->max_capacity){

        if(!lv_resize(vec)){
		return false;
        }
    }
    //length is index, so use that to place element, then increment it.
    vec->data[vec->length] = element;
    vec->length++;
    return true;

}
