/*
Task 17. Implementation of FIFO page replacement
Your task is to write a program that calculates the number of page faults for a sequence of memory references (i.e., the
memory reference trace in the .mem-files) when using the FIFO (First-In-First-Out) page replacement policy.
Your program shall take as input the number of physical pages, the page size, and the name of the trace file, see the example
below:
./fifo no_phys_pages page_size filename
*/
#include <stdlib.h>
#include <stdio.h>

int find(int arr[], int n, int value){
    for(int i =0; i<n; ++i){
        if(arr[i]==value)
            return i;
    }
    return -1;
}

int main(int argc, char *argv[]){

    unsigned int page_faults=0;
    unsigned int no_phys_pages=atoi(argv[1]);
    unsigned int page_size=atoi(argv[2]);
    char *filename=argv[3];
    int arr[no_phys_pages];
    char line[256];
    unsigned int page=0;
    int found=-1;
    unsigned int next_place= 0;
    unsigned int int_line= 0;
    for (int i = 0; i < no_phys_pages; i++) {
    arr[i] = -1; //so that no accidenatl match occurs
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Could not open the file!");
    }
    else{
        while (fgets(line, sizeof(line), file)) {
            int_line = atoi(line);
            page=int_line/page_size;
            found=find(arr,no_phys_pages,page);
            if(found==-1){
                arr[next_place]= page;
                next_place=(next_place+1)%no_phys_pages;
                page_faults++;
            }
        }
        fclose(file);
    }
    printf("Total amount of page faults: %d\n",page_faults);
    
}