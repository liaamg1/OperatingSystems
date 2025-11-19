/*
Task 23. Implementation of Optimal page replacement (Bélády’s algorithm)
Your task is to write a program that calculates the minimum number of page faults for a sequence of memory references,
i.e., you should implement the Optimal page replacement policy (which is also known as Bélády’s algorithm).
Your program shall take as input the number of physical pages, the page size, and the name of the trace file, see the example
below:
./optimal no_phys_pages page_size filename
The program shall write the resulting number of page faults for that specific combination of number of pages and page size,
for either mp3d.mem or mult.mem.
Example execution:
mycomputer$ ./optimal 32 128 mp3d.mem
No physical pages = 32, page size = 128
Reading memory trace from mp3d.mem... Read 100000 memory references
Result: 824 page faults
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
int find_optimal(int pages[], int no_phys_pages, int memory[], int memory_length, int n, int page_size){
    int farthest = n;
    int replace_index = -1;

    for(int i=0; i<no_phys_pages;++i){
        int j;
        for(j=n+1;j<memory_length; ++j){
            if(memory[j]/page_size==pages[i]){
                break;
            }
        }
        if (j==memory_length){
            return i;
        }
        if(j>farthest){
            farthest=j;
            replace_index=i;
        }

    }
    if(replace_index==-1){
        return 0;
    } else {
        return replace_index;
    }
}

int main(int argc, char *argv[]){

    unsigned int page_faults=0;
    unsigned int no_phys_pages=atoi(argv[1]);
    unsigned int page_size=atoi(argv[2]);
    char *filename=argv[3];
    int pages[no_phys_pages];
    int memory[200000];

    char line[256];

    unsigned int page=0;
    int found=-1;
    unsigned int next_place= 0;
    unsigned int int_line= 0;
    unsigned int time =0;
    unsigned int memory_length=0;

    for (int i = 0; i < no_phys_pages; i++) {
        pages[i] = -1; //so that no accidenatl match occurs
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Could not open the file!");
    }
    else{
        while (fgets(line, sizeof(line), file)) {
            memory[memory_length++] = atoi(line);
        }
        fclose(file);
        for(int i=0; i<memory_length; ++i){
            page=memory[i]/page_size;
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
                    replace_index = find_optimal(pages,no_phys_pages,memory,memory_length,i,page_size);
                }
                pages[replace_index]= page;
            } 
        }
    
        
    }
    printf("No physical pages = %d, page size = %d\n", no_phys_pages, page_size);
    printf("Reading memory trace from %s... Read %d memory references\n", filename, memory_length);
    printf("Result: %d page faults\n", page_faults);

    
}