#include <iostream>
#include <map>
#include <iterator>
#include "Euler.cc"

typedef unsigned long long int ulli;

int main(int agrs, char **argv){
	int n = std::atoi(argv[1]);

	std::map<ulli,int> factors;
	Euler::fact(factors, n);

	for(std::map<ulli, int>::const_iterator it=factors.begin();it!=factors.end();++it){
		std::cout << it->first << " " << it->second << std::endl;
	}

	for(int i=0;i<10;i++){
		std::cout << Euler::pow(i,i) << std::endl;
		std::cout << Euler::gcd(i,72) << std::endl;
	}
	return 0;
   }
