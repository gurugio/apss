#include <stdio.h>


enum topping
{
    pepa,
    kech,
    onion,
    sosa,
    chee
};

int arr[] = {1,2,3,4,5};
int result[5];

void subset_range(int start, int end, int index, int r)
{
    int j, i;

    printf("%d %d %d %d\n", start, end, index, r);
    if (index == r) {
        for (j = 0; j < r; j++)
            printf("%d ", result[j]);
        printf("\n");
        return;
    }

    for (i = start; i <= end && end - i + 1 >= r - index; i++) {
        printf("result[%d] = arr[%d] = %d\n", index, i, arr[index]);
        result[index] = arr[i];
        subset_range(i+1, end, index+1, r);
    }
}


int main(void)
{
    unsigned long pizza = 0x2a;
    unsigned long subset;
    int i;

    for (subset = pizza; subset; subset = ((subset - 1) & pizza)) {
        printf("%lx\n", subset);
    }

    printf("-----------------------\n");
    subset_range(0, 4, 0, 2);
    subset_range(0, 4, 0, 3);

    return 0;
}
