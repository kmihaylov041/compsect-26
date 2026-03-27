#include <stdio.h>

int nod (int a, int b) {
    int r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
int main()
{
    int a;
    int b;
    printf("Enter 2 numbers: \n");
    scanf("%d %d", &a, &b);
    
    
    printf("NOD = %d", nod(a,b));

    return 0;
}