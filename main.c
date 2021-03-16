#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>

struct linked_list {
    struct linked_list *next, *previous;
    char data;
};

struct linked_list* new_next(struct linked_list *curr){
    struct linked_list *temp = malloc(sizeof(struct linked_list*)*2+sizeof(int));
    temp->previous = curr;
    temp->next = NULL;
    temp->data = 'B';
    curr->next = temp;
    return temp;
}
struct linked_list* new_previous(struct linked_list *curr){
    struct linked_list *temp = malloc(sizeof(struct linked_list*)*2+sizeof(int));
    temp->next = curr;
    temp->previous = NULL;
    temp->data = 'B';
    curr->previous = temp;
    return temp;
}
struct linked_list* get_head(struct linked_list *curr){
    while(curr->previous!=NULL)
        curr=curr->previous;
    return curr;
}


int main() {
    FILE *fp;
    char input[150], *store;
    long states = 0, start = 0, end = 0;
    struct instruction{
        char write;
        int move_right;
        long state;
    };
    struct instruction **arr2d = calloc(sizeof(struct instruction*), (size_t)255);
    struct linked_list *current = malloc(sizeof(struct linked_list*)*2+sizeof(int));
    current->previous = NULL;

    // "/home/csc241/Desktop/Assignments/second_semester/
    //   programming_languages/assignment_1/input.txt"
    printf("\nEnter input file directory ");
    scanf("%149s", input);
    fp = fopen(input, "r");
    if (fp == NULL) {
        printf("Error: Cannot find file");
        exit(1);
    }
    for (int i = 0; fgets(input, 99, fp); i++) {
        switch (i) {

        case 0 :
            printf("Initial tape contents: %s",input);
            for (int j = 0; strncmp(&input[j], "\n", 1) != 0; j++) {
                struct linked_list *temp = malloc(sizeof(struct linked_list*)*2+sizeof(int));
                temp->next = NULL;
                temp->previous = current;
                temp->data = 0;
                current->data = input[j];
                current->next = temp;
                current = current->next;
            }
            current = current->previous;
            current->next = NULL;
            break;

        case 1 :
            //printf("%s",input);
            states = strtol(&input[0], &store, 10);
            for(int j = 0; j < 255; j++)
                arr2d[j] = calloc((size_t)states, sizeof(struct instruction));
            break;

        case 2 :
            //printf("%s",input);
            start = strtol(&input[0], &store, 10);
            break;

        case 3 :
            //printf("%s",input);
            end = strtol(&input[0], &store, 10);
            break;

        default :
            //printf("%s",input);
            arr2d[input[2]][strtol(&input[0], &store, 10)] = (struct instruction){
                input[4],
                input[6]==*("R")?1:0,
                strtol(&input[8], &store, 10)
            };

        }
    }
    fclose(fp);

    current = get_head(current);
    while(start!=end){
        struct instruction temp = arr2d[current->data][start];
        current->data = temp.write;
        current = temp.move_right?
                current->next==NULL?new_next(current):current->next:
                current->previous==NULL?new_previous(current):current->previous;
        start = temp.state;
    }

    printf("Final tape contents: ");
    current = get_head(current);
    while(current->next!=NULL){
        printf("%c", current->data);
        current = current->next;
    }
    printf("%c",current->data);
    return 0;
}
