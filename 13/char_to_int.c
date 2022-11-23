#include <stdio.h>

int main()
{
    char a = '1';
    int a_1;
    char b = '2';
    int b_2;

    a_1 = a - '0';
    b_2 = b - '0';

    printf("%d\n", a_1);
    printf("%d\n", b_2);
    printf("%d\n", a_1 + b_2);

}
