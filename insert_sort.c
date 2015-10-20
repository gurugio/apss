#include <stdio.h>


#define SWAP(a,b) {do {                         \
        int __tmp;                              \
        __tmp = (a);                            \
        (a) = (b);                              \
        (b) = __tmp;                            \
        } while (0);}
    

void insert_sort(int *array, int size)
{
    int i;
    int j;
    for (i = 0; i < size; i++) {
        for (j = i; j > 0; j--) {
            if (array[j] < array[j - 1])
                SWAP(array[j], array[j - 1]);
        }
    }
}

int main(void)
{
    int a=4, b=6;
    int data[] = {5, 1, 4, 3, 2};
    int i;

    SWAP(a,b);
    printf("%d %d\n", a, b);

    insert_sort(data, 5);
    for (i = 0; i < 5; i++)
        printf("%d\n", data[i]);
    return 0;
}
