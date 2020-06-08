#include "malloc.h"
#include <stdio.h>
#include <unistd.h>


void testMallocAndFree() {
    //The heap grows as necessary
    printf("The heap grows as necessary.\n");
    void* ptr1 = mymalloc(17);
    void* ptr2 = mymalloc(8);
    void* ptr3 = mymalloc(1234);
    report();

    //Free blocks are re-used when possible
    printf("Free blocks are re-used when possible.\n");
    printf("Free'd here:\n");
    myfree(ptr1);
    report();
    printf("Used here:\n");
    printf("*Note that it is the exact size of the previous free block.\n");
    ptr1 = mymalloc(24);
    report();

    //Free blocks are split and coalesced
    printf("Free blocks are split and coalesced.\n");
    myfree(ptr3);
    printf("Highest malloc address freed:\n");
    report();
    myfree(ptr1);
    printf("Lowest malloc address freed next, but is now the head of the free list:\n");
    report();
    myfree(ptr2);
    printf("Middle malloc address is free'd, and coalesced:\n");
    report();

    printf("Worst fit is used to split largest free block:\n");
    ptr1 = mymalloc(777);
    report();
    printf("Same block also free'd and coalesced:\n");
    myfree(ptr1);
    report();

    printf("5 blocks malloc'd for use, ready to be free'd:\n");
    printf("*Note that all blocks in free list will be kept in order throughout test.\n");
    void* rptr = mymalloc(1288);
    ptr1 = mymalloc(123);
    ptr2 = mymalloc(123);
    ptr3 = mymalloc(123);
    void* ptr4 = mymalloc(123);
    void* ptr5 = mymalloc(123);
    report();
    printf("Block 5 free'd:\n");
    myfree(ptr5);
    report();
    printf("Block 1 free'd:\n");
    myfree(ptr1);
    report();
    printf("Block 2 free'd and coalesced:\n");
    myfree(ptr2);
    report();
    printf("Block 4 free'd and coalesced:\n");
    myfree(ptr4);
    report();
    printf("Block 3 free'd all blocks coalesced:\n");
    myfree(ptr3);
    report();

    printf("Large malloc request, too large for free list:\n");
    ptr1 = mymalloc(77713);
    report();

    printf("All heap free and coalesced.\n");
    myfree(rptr);
    myfree(ptr1);
    report();

/* The following properties are always apparent in every report:
      - The heap is always an alternating sequence of free and allocated blocks, with the entire heap accounted for
      - The free-block list is in sorted order and includes all free blocks on the heap
*/ 
}

int main(int argc, char **argv) {
    printf("\n\n"); //printf allocates memory for its self
    testMallocAndFree();
    return 0;
}