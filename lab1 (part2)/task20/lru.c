/*
Your task is to write a program that calculates the number of page faults for a sequence of memory references (i.e., the
memory reference trace in the .mem-files) when using the LRU (Least-Recently-Used) page replacement policy.
Your program shall take as input the number of physical pages, the page size, and the name of the trace file, see the example
below:
./lru no_phys_pages page_size filename

Observerat att det sker MINDRE page faults i denna varianten.
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
int find_least_recently(int arr[], int n){
    int least_used=0;
    for(int i =0; i<n; ++i){
        if(arr[i]<arr[least_used])
            least_used=i;
    }
    return least_used;
}

int main(int argc, char *argv[]){

    unsigned int page_faults=0;
    unsigned int no_phys_pages=atoi(argv[1]);
    unsigned int page_size=atoi(argv[2]);
    char *filename=argv[3];
    int pages[no_phys_pages];
    int recent[no_phys_pages];
    char line[256];

    unsigned int page=0;
    int found=-1;
    unsigned int next_place= 0;
    unsigned int int_line= 0;
    int time =0;

    for (int i = 0; i < no_phys_pages; i++) {
        pages[i] = -1; //so that no accidenatl match occurs
        recent[i]= -1;
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Could not open the file!");
    }
    else{
        while (fgets(line, sizeof(line), file)) {
            int_line = atoi(line);
            page=int_line/page_size;
            time++;

            found=find(pages,no_phys_pages,page);
            if(found==-1){
                page_faults++;

                int replace_index = -1;

                for (int i = 0; i < no_phys_pages; i++) {
                    if (pages[i] == -1) {
                        replace_index = i;
                        break;
                    }
                }
                if(replace_index==-1){
                    replace_index = find_least_recently(recent,no_phys_pages);
                }
                pages[replace_index]= page;
                recent[replace_index]=time;
            } else{
                recent[found]=time;
            }
        }
        fclose(file);
    }
    printf("Total amount of page faults: %d\n",page_faults);
    
}