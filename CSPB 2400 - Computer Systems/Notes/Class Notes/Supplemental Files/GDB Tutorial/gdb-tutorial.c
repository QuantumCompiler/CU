#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void function_one();
extern int function_sub(int a, int b);
extern void function_two();

int main()
{
    function_one();
    function_two();
}

/**************************************************************************/
void function_one()
{
    int x = 10;
    int y = 5;
    int z;

    z = function_sub(x, y);
    printf("x-y is %d\n", z);
}

int function_sub(int a, int b)
{
    int q = a -b;
    printf("I have computed q as %d\n", q);
    return q;
}

/**************************************************************************/

#define N 8
int int_empty[N];
int int_full[N] = {0xdeadbeef, 0xb01dface,
                    0xf005ba11, 0x5ca1ab1e,
                    0xca11ab1e, 0xba5eba11,
                    0x0ddba11, 0xb0a710ad};

char *str_init_ptr = "this is a constant string";
char *str_ptr;
#define STRBUF 128
char str_buffer[STRBUF];

struct LinkedList {
    int data;
    struct LinkedList *next;
};
struct LinkedList *root = NULL;

void function_two()
{
    int i;
    struct LinkedList *toor;

    printf("First, let's copy the full to the empty\n");
    memcpy(int_empty, int_full, sizeof(int) * N);

    printf("Now, let's compare the two\n");
    printf("The result is %d\n", memcmp(int_empty, int_full, sizeof(int) * N));
    
    printf("Length of initialized string is %ld\n", strlen(str_init_ptr));
    printf("Length of un-initialized string is %ld\n", strlen(str_ptr));
    printf("Size of str_ptr is %ld\n", sizeof(str_ptr));

    strncpy(str_buffer, str_init_ptr, sizeof(char) * STRBUF);
    printf("String is now %s\n", str_buffer);

    for(i = 0; i < 4; i++) {
        struct LinkedList *ptr = malloc(sizeof(struct LinkedList));
        ptr -> data = i;
        ptr -> next = root;
        root = ptr;
    }

    /* Now, print out the list */
    toor = root;
    while (!toor) {
        printf("Data is %d\n", toor -> data);
        toor = toor -> next;
    }
}