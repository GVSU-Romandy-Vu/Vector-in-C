#include <stdio.h>
#include "lite_vector.h"

int main(int argc, char** argv){
	/*lite_vector* lv = lv_new_vec(sizeof(int*));
	int x[1000];
	for(int i=0; i<1000; ++i) {
		x[i] = i;
		printf("Array addres: %p\n", (x + i * sizeof(int*)));
		lv_append(lv, &(x[i]));
	};

	for(int i=0; i<1000; ++i){
		int* p = lv_get(lv, i);
		int val = *p;
		printf("%i\t", val);
	}

	lite_vector* lv2 = lv_new_vec(sizeof(char*));
	lv_append(lv2, "Mr. ");
	lv_append(lv2, "W. ");
	lv_append(lv2, "says ");
	lv_append(lv2, "hi!");
	printf("%s\n", (char*)lv_get(lv2, 0));
	*/
	int w = 121;
	lite_vector* lv = lv_new_vec(5);
	printf("Memory of &data %p \n", &lv->data);
	printf("Memory of data %p \n", lv->data);
	printf("Max cap: %zu\n", lv->max_capacity);
	int x[w];
	for(int i = 0; i < w; i++){
		x[i] = i;
		lv_append(lv, &x[i]);
	
	}
	printf("Size of data %zu:\n", lv->length);
	for(int i = 0; i < w; i++){
		int* p = lv_get(lv, i);
		int val = *p;
		printf("Index %d = %d\n", i, val);
	}
	printf("Memory of &data %p \n", &lv->data);
	printf("Memory of data %p \n", lv-> data);
	printf("Max cap: %zu\n", lv->max_capacity);
	lv_clear(lv);
	printf("Value of pointer: %p \n", lv);
	printf("Memory address of pointer: %p \n", &lv);
	printf("Length: %zu", lv->length);
	printf("Max cap: %zu", lv->max_capacity);
	lv_cleanup(lv);
}
