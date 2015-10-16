#include <stdio.h>


int max_heap[1024];
int heap_count;

void show_heap(void)
{
    int i;
    printf("count=%d\n", heap_count);
    for (i = 0; i < heap_count; i++) {
        printf("%d ", max_heap[i]);
    }
    printf("\n");
}

int parent_index(int child_index)
{
    return (child_index - 1) >> 1;
}

int left_index(int parent_index)
{
    return 2 * parent_index + 1;
}

int right_index(int parent_index)
{
    return 2 * parent_index + 2;
}

int insert_heap(int val)
{
    int index = heap_count;
    max_heap[heap_count++] = val;

    if (index == 0) return index;

    while (max_heap[parent_index(index)] < val) {
        int tmp = max_heap[parent_index(index)];

        printf("swap(%d %d)\n", max_heap[parent_index(index)], val);
        max_heap[parent_index(index)] = val;
        max_heap[index] = tmp;

        index = parent_index(index);
        if (index == 0) break;
    }
}    

int main(void)
{
    insert_heap(60);
    show_heap();
    insert_heap(70);
    show_heap();
    insert_heap(80);
    show_heap();
    insert_heap(90);
    show_heap();
    insert_heap(100);
    show_heap();
    insert_heap(75);
    show_heap();
    
    return 0;
}
