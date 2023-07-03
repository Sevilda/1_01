#include <stdio.h>

void main()
{
    
    //The two sides of a rectangle, to be called a and b.
    int a, b=0;
    printf("Please provide the measurements of a rectangle(format: a, b):\n");

    //Read two integer values. 
    scanf("%d, %d", &a, &b);

    printf("\n%d, %d", a, b);
    
    //Area=a*b
    printf("Terulet: %d\n", a*b);

    //Perimeter=2*(a+b)
    printf("Kerulet: %d", 2*(a+b));

}