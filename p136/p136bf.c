/* problem 136

x, y, z = x, x-r, x-2*r
x**2 - y**2-z**2 = x**2-

not: 3299992
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50000000

int main(int agrs, char **argv){
	char *l = malloc(sizeof(char)*SIZE);

	for(int i=0;i<SIZE;++i)
		l[i] = 0;

	int lim = atoi(argv[1]);
	int lim2 = atoi(argv[2]);
	int nmax = 0;
	for(int r=1;r<=lim;++r){
		for(int x=r+1;x<5*r;++x){
			int n = (5*r-x)*(x-r);
			int n2 = 6*x*r-x*x-5*r*r;

			//nmax = max(nmax,n)

			if(n > 0 && n < SIZE && x-2*r>0){
				l[n] += 1;
			}
		}
	}

	int s = 0;
	for(int i=0;i<lim2;++i){
		if(l[i] == 1)
			//printf("%d ",i);
			s++;
	}
	printf("\n");

	printf("%d\n",s);
	return 0;
}
