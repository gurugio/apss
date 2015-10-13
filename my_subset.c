#include <stdio.h>


int arr[] = {1,2,3,4,5};
int result[10];

void print_result(int num)
{
    int i;
    for (i = 0; i < num; i++)
        printf("%d ", result[i]);
    printf("\n");
}

void my_subset(int start, int end, int index, int num)
{
    int i;

    if (num == index) {
        print_result(num);
        return;
    }

    // end - i + 1: remain elements of the master-set
    // num - index: the number of elements to be copied
    // the remain elem >= elem to be copied
    for (i = start; end - i + 1 >= num - index; i++) {
        result[index] = arr[i];
        //printf("%d ", arr[i]);
        my_subset(i + 1, end, index + 1, num);
    }

}


int main(void)
{

    my_subset(0, sizeof(arr)/sizeof(int) - 1, 0, 1);
    my_subset(0, sizeof(arr)/sizeof(int) - 1, 0, 2);


    // The number of subset: 3 among 5
    // select 3 among 5: 5*4*3
    // ignore the same element: 3*2*1
    // (5*4*3) / (3*2*1) = 10
    my_subset(0, sizeof(arr)/sizeof(int) - 1, 0, 3);
    // (5*4*3*2) / (4*3*2*1) = 5
    my_subset(0, sizeof(arr)/sizeof(int) - 1, 0, 4);

    return 0;
}
