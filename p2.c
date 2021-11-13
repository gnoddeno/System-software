#include <stdlib.h>
#include <stdio.h>
int global = 10 ;
int return_zero(){return 0;}
extern char etext,edata,end;
int main(){
	static int st_global = 10;
	int local =0 ;
	void *p1;
	p1 = malloc(1L << 28);

	printf("global = %ld\n",sizeof(global));
        printf("return_zero = %ld\n",sizeof(return_zero));
        printf("st_global = %ld\n",sizeof(st_global));
        printf("local = %ld\n",sizeof(local));
        printf("p1 = %ld\n",sizeof(p1));

	printf("address printf\n");
	printf("global = %p\n",&global);
        printf("return_zero = %p\n",return_zero);
        printf("st_global = %p\n",&st_global);
        printf("local = %p\n",&local);
        printf("p1 = %p\n",p1);

	printf("Symbol\n");
	printf("TEXT(CODE):	progran text (etext)	%10p\n",&etext);
	printf("DATA:	initialized data (edata)	%10p\n",&edata);
	printf("BSS:	uninitialized data (end)	%10p\n",&end);

}


