#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Test {
        char *name;
        int age;
} ARF ;
 
int main () {
        int i;
        ARF *examp;
 
        ARF *testfunc() ;
 
        examp = testfunc();
 
        printf("sizeof *examp:%d sizeof examp:%d\n",sizeof(*examp),sizeof(examp));
        printf("%s is %d \n", examp[0].name, examp[0].age );
 
         for (i=0;i<3;i++) printf("%s is %d\n", examp[i].name,examp[i].age);
 
        return 0 ;
 
}
 
ARF *testfunc()
{
        ARF *bexamp ;
        if (  ( bexamp =  (struct Test *) malloc( 3 * sizeof(ARF) ) ) == NULL)   puts ("malloc fail");
 
        puts("HERE");
        fflush(stdout);
 
        bexamp[0].name=(char *) malloc ( (strlen("five")+1) * sizeof(char ) );
        strcpy(bexamp[0].name,"five");
        bexamp[0].age=5;
 
        bexamp[1].name=(char * ) malloc(5 * sizeof(char ) );
        strcpy(bexamp[1].name,"four");
        bexamp[1].age=4;
 
        bexamp[2].name=(char * ) malloc(5 * sizeof(char ) );
        strcpy(bexamp[2].name,"nine");
        bexamp[2].age=9;
 
        return bexamp ;
}