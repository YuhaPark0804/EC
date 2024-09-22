#include <stdio.h>

int main()
{
    unsigned char num1 = 1;    // 0000 0001
    unsigned char num2 = 3;    // 0000 0011
    unsigned char num3 = 162;    // 162: 1010 0010
    unsigned char num4;
    num4 = ~num3;


    printf("%d\n", num1 & num2);
    printf("%d\n", num1 | num2);
    printf("%d\n", num1 ^ num2);
    printf("%u\n", num4);    // 93: 0101 1101: num1의 비트 값을 뒤집음

    return 0;
}