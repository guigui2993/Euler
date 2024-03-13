/*
 * P195
 *
 * */

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <set>
#include <string>
#include <bits/stdc++.h>


int main(int args, char **argv){
	std::set<std::tuple<int, int, int>> set;
	// a < b > c
	int LIM = std::atoi(argv[1]), n = std::atoi(argv[2]);
	int cc = 0;
	float s = 0, r = 0;
	for(int c=1;c<LIM;++c){
		for(int b=c+1;b<LIM;++b){
			/*
			s = (a+b+1)/2.0;
			r = sqrt((s-a)*(s-b)*(s-1)/s);
			if(r>n)
				break;
			*/
			int start_a = b-c+1;
			if(start_a<0)
				start_a = 1;
			for(int a=start_a;a<c;++a){
			//for(int c=1;c<a+b&&c<LIM;++c){
				s = (a+b+c)/2.0;
				r = (s-a)*(s-b)*(s-c)/s;
				if(r>n*n)
					break;
				else if(c*c==a*a+b*b-a*b){
					cc++;
					set.insert(std::make_tuple(b, c, a));
					//std::cout << a << " " << b << " " << c << " " << std::endl;
				}
			}
		}
	}
	std::cout << std::endl;
	std::cout << cc << std::endl;
	std::cout << set.size() << std::endl;

	int cnt = 0;
	std::set<std::tuple<int,int,int>>::const_iterator it;
	for(it = set.begin();it != set.end();++it){
		int b = std::get<0>(*it), c = std::get<1>(*it), a = std::get<2>(*it);
		//std::cout << std::get<0>(*it) << " " << std::get<1>(*it) << " "<< std::get<2>(*it) << std::endl;

		s = (a+b+c)/2.0;
		r = (s-a)*(s-b)*(s-c)/s;
		if(r<n*n)
			cnt++;

	}
	std::cout << cnt << std::endl;

	return 0;
}
