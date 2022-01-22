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
lite_vector* lv_new_vec(size_t type_size){
}

//The clear() function use recursion?
void lv_cleanup(lite_vector* vec){
}

size_t lv_get_length(lite_vector* vec){
}

//set all the element in array to null
bool lv_clear(lite_vector* vec){
}

//search through array
void* lv_get(lite_vector* vec, size_t index){
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
//Most likely used by lv_append.
static bool lv_resize(lite_vector* vec){
}

bool lv_append(lite_vector* vec, void* element){
}