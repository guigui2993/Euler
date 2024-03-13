/*
 * P195
 *
 * */

#include <iostream>
#include <stdlib.h>
#include <math.h>

int main(int args, char **argv){

	int LIM = std::atoi(argv[1]), n = std::atoi(argv[2]);
	int cc = 0, cciso = 0, ccother = 0;
	for(int a=1;a<LIM;++a)
		for(int b=1;b<LIM;++b)
			for(int c=1;c<LIM;++c){
				float s = (a+b+c)/2.0, r = sqrt((s-a)*(s-b)*(s-c)/s);
				if(r>n)
					break;
				if(c==a && a == b)
					cciso++;
				else if(c*c==a*a+b*b-a*b)
					ccother++;
					//std::cout << a << " " << b << " " << c << " " << std::endl;
			}
	cc = cciso + ccother;
	std::cout << cc <<" "<< cciso << " " << ccother << std::endl;
	return 0;
}
