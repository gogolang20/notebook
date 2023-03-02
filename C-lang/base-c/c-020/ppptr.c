#include <stdio.h>

int main(void)
{
    int var = 3000;
    int *ptr;
    int **pptr;
    int ***ppptr;

    ptr = &var;
    pptr = &ptr;
    ppptr = &pptr;

    printf("var address:%p var=%d\n", &var, var);
    printf("ptr address:%p ptr save address:%p *ptr=%d\n", &ptr, ptr, *ptr);
    printf("pptr address:%p pptr save address:%p **pptr=%d\n", &pptr, pptr, **pptr);
    printf("ppptr address:%p ppptr save address:%p ***ppptr=%d\n", &ppptr, ppptr, ***ppptr);
    /*
var address:000000000064FE1C var=3000
ptr address:000000000064FE10 ptr save address:000000000064FE1C *ptr=3000
pptr address:000000000064FE08 pptr save address:000000000064FE10 **pptr=3000
ppptr address:000000000064FE00 ppptr save address:000000000064FE08 ***ppptr=3000
    */
    return 0;
}