#include <inttypes.h>
#include <stdio.h>
int main()
{

int stuff[2]={1234, 1};
long *x=(long *) stuff;
printf("%ld",*x);



return 0;
}
