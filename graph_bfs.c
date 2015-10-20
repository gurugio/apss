
/* exercise for graph: breadth first search */
#include <stdio.h>


int graph_data[9][9] = {
    {7, 4, 1, 3, -1}, //a
    {0, 2, -1}, //b
    {1, -1}, //c
    {0, 6, -1}, //d
    {0, 5, -1}, //e
    {4, -1}, //f
    {3, 8, -1}, //g
    {0, -1}, //h
    {6, -1} //i
};
int visited[9];
int parent[9];
int queue[100];
int rear;
int tail;

void queue_push(int n)
{
    printf("push:%d\n", n);
    queue[tail++] = n;
}

int queue_pop(void)
{
    int ret;
    if (rear < tail) {
        printf("pop:%d\n", queue[rear]);
        return queue[rear++];
    }else // rear == tail : empty
        return -1;
}

int bsf(int start)
{
    int i;
    int current;
    
    queue_push(start);

    while ((current = queue_pop()) >= 0) {
        printf("visiting:%d\n", current);
        visited[current] = 1;
        for (i = 0; i < 9; i++) {
            int next = graph_data[current][i];
            if (next >= 0 && visited[next] == 0)
                queue_push(next);
            else if (next < 0)
                break;
        }
    }
}

int main(void)
{
    int i;
    queue_push(1);
    queue_push(2);
    queue_push(3);
    printf("%d\n", queue_pop());
    printf("%d\n", queue_pop());
    printf("%d\n", queue_pop());
    printf("%d\n", queue_pop());
    printf("%d\n", queue_pop());

    bsf(0);
    for (i = 0; i < 9; i++)
        printf("vertex:%d = %d\n", i, visited[i]);
    return 0;

    /* test result: seems OK */
/* ./a.out */
/* push:1 */
/* push:2 */
/* push:3 */
/* pop:1 */
/* 1 */
/* pop:2 */
/* 2 */
/* pop:3 */
/* 3 */
/* -1 */
/* -1 */
/* push:0 */
/* pop:0 */
/* visiting:0 */
/* push:7 */
/* push:4 */
/* push:1 */
/* push:3 */
/* pop:7 */
/* visiting:7 */
/* pop:4 */
/* visiting:4 */
/* push:5 */
/* pop:1 */
/* visiting:1 */
/* push:2 */
/* pop:3 */
/* visiting:3 */
/* push:6 */
/* pop:5 */
/* visiting:5 */
/* pop:2 */
/* visiting:2 */
/* pop:6 */
/* visiting:6 */
/* push:8 */
/* pop:8 */
/* visiting:8 */
/* vertex:0 = 1 */
/* vertex:1 = 1 */
/* vertex:2 = 1 */
/* vertex:3 = 1 */
/* vertex:4 = 1 */
/* vertex:5 = 1 */
/* vertex:6 = 1 */
/* vertex:7 = 1 */
/* vertex:8 = 1 */
}
