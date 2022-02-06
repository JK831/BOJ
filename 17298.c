#include <stdio.h>
#include <stdlib.h>


typedef int element;

typedef struct stacktype{
    int top;
    element* arr;
}stack;

void stack_init(stack* s, int n) {
    s->top = -1;
    s->arr = malloc(sizeof(int) * n);
}

int full(stack* s) {
    if (s->top == (sizeof(s->arr) / sizeof(s->arr[0]) - 1))
        return 1;
    return 0;
}

void push(stack* s, element n) {
    if (full(&s)) printf("full\n");
    s->arr[++(s->top)] = n;
}

int empty(stack* s) {
    if (s->top == -1) return 1;
    return 0;
}

void pop(stack* s) {
    if (empty(&s)) printf("empty\n");
    else (s->top)--;
}


int main() {
    int N;
    int* arr;
    int* ans;
    stack s;

    scanf("%d", &N);

    arr = malloc(sizeof(int) * N);
    ans = malloc(sizeof(int) * N);

    stack_init(&s, N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = N - 1; i >= 0; i--) {
        while (!empty(&s) && s.arr[s.top] <= arr[i])
            pop(&s);
        if (empty(&s)) ans[i] = -1;
        else ans[i] = s.arr[s.top];

        push(&s, arr[i]);
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i]);
    }
}
