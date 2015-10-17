#include <stdio.h>


int max_heap[1024];
int heap_count;


int get_level(int count)
{
    int i;
    int level = 0;
    
    for (i = count; i > 0; i = (i >> 1))
        level++;

    return level;
}

void show_heap(void)
{
    int i;
    int level;
    int count = heap_count;

    if (heap_count == 0) {
        printf("empty\n");
        return;
    }

    printf("----\n");
    for (level = 0; level < get_level(heap_count); level++) {
        for (i = (1 << level) - 1; i < (1 << (level + 1)) - 1; i++) {
            printf("%d ", max_heap[i]);
        }
        printf("\n");
    }
    printf("----\n");
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

        /* printf("swap(%d %d)\n", max_heap[parent_index(index)], val); */
        max_heap[parent_index(index)] = val;
        max_heap[index] = tmp;

        index = parent_index(index);
        if (index == 0) break;
    }
}    

int pop_heap(void)
{
    int ret = max_heap[0];
    int index;

    max_heap[0] = max_heap[--heap_count];
    max_heap[heap_count] = 0;

    index = 0;
    while (index < heap_count) {
        int tmp;

        /* printf("l=%d r=%d\n", max_heap[left_index(index)], */
        /*        max_heap[right_index(index)]); */

        if (max_heap[left_index(index)] > max_heap[right_index(index)]) {
            /* printf("swap:%d-%d\n", index, left_index(index)); */
            tmp = max_heap[left_index(index)];
            max_heap[left_index(index)] = max_heap[index];
            max_heap[index] = tmp;
            index = left_index(index);
        } else {
            /* printf("swap:%d-%d\n", index, right_index(index)); */
            tmp = max_heap[right_index(index)];
            max_heap[right_index(index)] = max_heap[index];
            max_heap[index] = tmp;
            index = right_index(index);
        }
    }
    
    return ret;
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

    printf("pop=%d\n", pop_heap());
    show_heap();
    printf("pop=%d\n", pop_heap());
    show_heap();
    printf("pop=%d\n", pop_heap());
    show_heap();


    printf("===================\n");
    printf("pop=%d\n", pop_heap());
    show_heap();
    printf("pop=%d\n", pop_heap());
    show_heap();
    
    return 0;
}
