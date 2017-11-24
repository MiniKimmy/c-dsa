#include<stdio.h>
#include<stdlib.h>

#include"BFS.h"
int main()
{
    Graph* G = InitGraph(6,RepeatEdge);
    BFS* S = InitBFS(G, 0);
    Stack * stack = GetPath(S, 5);

    while (!IsEmptyStack(stack))
    {
        printf("%d ", *GetValue_Stack(stack));
        Pop_Stack(stack);
    }

    system("pause");
    return 0;
}
