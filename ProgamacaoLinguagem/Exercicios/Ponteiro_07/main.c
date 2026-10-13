#include <stdio.h>

struct Aluno {
    char nome[30];
    int idade;
};

int main()
{
    int n[2] = {10,20};
    int *ptr = n;
    
    printf("%d\n", n[0]);
    printf("%d\n", n[1]);

    printf("%d\n", *ptr);
    printf("%d\n", *(ptr+1));

    return 0;
}
