#include <stdio.h>
#include <stdlib.h>

#define DIM 128

typedef struct {
    char* start;
    size_t len;
    size_t cap;
} stack;

void stackInit(stack* arr) {
    arr->start = NULL;
    arr->len = 0;
    arr->cap = 0;
}

void nullCheck(void* ptr){ // check reallocate return for NULL
    if (!(ptr)) {
        printf("Out of memory");
        exit(1);
    }
}


void push(stack* arr, char num) {
    if (arr->cap == 0) {
        arr->cap = 1;
        arr->start = (char*) realloc(arr->start, sizeof(char) * arr->cap);
        nullCheck(arr->start);
        arr->start[arr->len++] = num;
    }
    else {
        if ((arr->len + 1) > arr->cap) {
            arr->cap *= 2;
            arr->start = (char*) realloc(arr->start, sizeof(char) * arr->cap);
            nullCheck(arr->start);
        }
        arr->start[arr->len++] = num;
    }
}

void stackDelTail(stack* arr) {
    if (arr->len > 0) {
        arr->len--;
        if (arr->len <= (arr->cap / 4)) {
            arr->cap /= 2;
            arr->start = (char*) realloc(arr->start, sizeof(char) * arr->cap);
        }
    }
}

void printStack(stack arr) {
    for (size_t i = 0; i < arr.len; i++) {
        printf("%c ", arr.start[i]);
        printf(" ");
    }
    printf("\n");
}

void freeStack(stack arr){
    free(arr.start);
}

void printStackInfo(stack arr){
    printf("%p\n", arr.start);
    printf("%zu\n", arr.len);
    printf("%zu\n", arr.cap);
}

//char getElementDynArr(stack arr, size_t i){
//    if (i < arr.len) {
//        return arr.start[i];
//    }
//    else {
//        printf("Index out of range");
//        exit(1);
//    }
//}

char pop(stack* arr) {
    char tmp = arr->start[arr->len - 1];
    stackDelTail(arr);
    return tmp;
}

char peek(stack* arr) {
    return arr->start[arr->len - 1];
}

int empty(stack arr){
    if (arr.len == 0) {
        return 1;
    }
    return 0;
}

void isEmpty(stack arr){
    printf("Stack is empty");
    if (empty(arr)) exit(1);
}


void scanString(char* start, size_t len) {
    size_t i = 0;
    while ((i < len - 1) || (start[i - 1] == '\n')) {
        scanf("%c", &start[i]);
        i++;
    }
    start[i] = '\0';
}



int main() {
    char string[DIM];
    char newString[DIM];

    // read string from input
    gets(string);
    // create stack
    stack operations;
    stackInit(&operations);
    size_t i = 0;
    size_t j = 0;
    do {
        if ((string[j] >= '0') && (string[j] <= '9')) {
            newString[i++] = string[j++];
        } else {
            if (string[j] == ')') {
                char tmp = pop(&operations);
                while ((tmp != '(') && (!empty(operations))) {
                    newString[i++] = tmp;
                    tmp = pop(&operations);
                }
                if (tmp != '(') {
                    printf("Wrong parentheses");
                    exit(1);
                }
                if (!empty(operations)) {
                    newString[i++] = pop(&operations);
                }
            } else if (string[j] != '(') {
                if (!empty(operations)) {
                        if (peek(&operations) != '(') {
                        char tmp = pop(&operations);
                        newString[i++] = tmp;
                        if ((tmp == '>') || (tmp == '<') || (tmp == '&') || (tmp == '|')) {
                            newString[i++] = pop(&operations);
                        }
                    }
                }
            }
            if (string[j] == ')') {
                j++;
            } else {
                char tmp = string[j];
                push(&operations, string[j++]);
                if ((tmp == '<') || (tmp == '>') || (tmp == '|') || (tmp == '&')) {
                    push(&operations, string[j++]);
                }
            }
        }
    } while (string[j]);
    if (!empty(operations)) {
        char tmp = pop(&operations);
        newString[i++] = tmp;
        if ((tmp == '>') || (tmp == '<') || (tmp == '|') || (tmp == '&')) {
            newString[i] = pop(&operations);
        }
    }
    newString[i] = '\0';
    printf("%s", newString);
    freeStack(operations);
    return 0;
}