/* problem 136

x, y, z = x, x-r, x-2*r
x**2 - y**2-z**2 = x**2-

r² = n-k
(x-3*r)²=3*n-4*k
3n>=4k
r <= 7071



*/
#include <stdio.h>
#include <stdlib.h>

int main(int agrs, char **argv){
	int l[100];

	int lim = 50000000;
	int *w;
	w = malloc(lim*sizeof(int));

	for(int i=0;i<lim;++i)
		w[i] = 0;

	/*
	 * 2 intersting cases:
	 *	- r*r-a = 0 => 1 solution x = 2*r
	 *	- d >= r/2
	 * */
	int a = 0, x = 0, lim2 = 4082;
	for(int r=0;r<lim2;++r){
		for(int d=0;d<r;++d){
			a = r*r-d*d;
			if(d<r && d>0)
				w[4*a]+=2; // x = 2*r+2*d and 2*r-2*d
			else
				w[4*a]++; // x = 2*r+2*d or d=0 => twice same solution
		}
	}

	printf("finished\n");

	//printf("%d\n",s);
	return 0;
}
/*
	for(int r=0;r<lim2;++r){
		for(int d=0;d<(r+1)/2;++d){
			a = r*r-d*d;
			w[4*a]+=2; // x = 2*r+2*d and 2*r-2*d
		}
	}
*/
