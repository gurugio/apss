#include <stdio.h>

// test graph:
// 0->1->2
// 1->3
// 2->3
// 3->4
// 4->0
int graph_vertex[5][5] = {
    {1, 2, -1}, // 0
    {3, -1}, // 2
    {4, -1}, // 3
    {0, -1}  // 4
};

int visited[5] = {0,};

int dfs(int vertex)
{
    int i;

    printf("visiting:%d\n", vertex);
    visited[vertex] = 1;
    
    for (i = 0; i < 5; i++) {
        int next = graph_vertex[vertex][i];
        
        if (next < 0)
            break;

        if (visited[next] == 0)
            dfs(next);
    }
}

int main(void)
{
    int i;
    dfs(0);
    for (i = 0; i < 5; i++)
        printf("vertex=%d %s\n", i, visited[i] == 1 ? "visited" : "not-visited");
    return 0;
}
