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

/*
 * BF_unopt: T(100) > 34s (LIM: 45000)
 * BF_improved: T(100) > 15s (LIM: 45000)
 *
*/

int main(int args, char **argv){
	std::set<std::tuple<int, int, int>> set;
	std::set<std::tuple<int, int, int>> set2;
	std::set<std::tuple<int, int, int>> result;
	// a < b > c
	
	/*
	 * c² = a² + b² - a*b
	 * b = (a +/- sqrt(4*c²-3*a²))/2
	 * b = (a + sqrt(4*c²-3*a²))/2
	 * b > (a + sqrt(4*c²-3*a²))/2
	 * c = (a + sqrt(4*c²-3*a²))/2
	 * 2*c = a + sqrt(4*c²-3*a²)
	 * (2*c-a)² = (4*c²-3*a²)
	 * 4*c²-4*a*c +a² = 4*c²-3*a²
	 * -4*a*c +a² = -3*a²
	 * 4*a*c  = 4*a²
	 * 4*c  = 4*a
	*/

	int LIM = std::atoi(argv[1]), n = std::atoi(argv[2]);
	int cc = 0, b = 0;
	float s = 0, r = 0;
	for(long long int c=2;c<LIM;++c){
		for(long long int a=1;a<c;++a){
			long long int x = std::round(std::sqrt(4*c*c-3*a*a));
			if(x*x == 4*c*c-3*a*a && (a+x)%2==0){
				b = (a+x)/2;
				if(b<c)
					continue;
				s = (a+b+c)/2.0;
				r = (s-a)*(s-b)*(s-c)/s;
				if(r>n*n)
					break;
				cc++;
				set.insert(std::make_tuple(b, c, a));
				std::cout << a << " " << b << " " << c << " " << std::endl;
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
		if(r<n*n && c*c==a*a+b*b-a*b && a != b)
			cnt++;

	}
	std::cout << cnt << std::endl;

	/*
	cc = 0;
	for(int c=1;c<LIM;++c){
		for(int b=c+1;b<LIM;++b){
			/ *
			s = (a+b+1)/2.0;
			r = sqrt((s-a)*(s-b)*(s-1)/s);
			if(r>n)
				break;
			* /
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
					set2.insert(std::make_tuple(b, c, a));
					//std::cout << a << " " << b << " " << c << " " << std::endl;
				}
			}
		}
	}
	std::set_difference(set2.begin(), set2.end(),set.begin(),set.end(),std::inserter(result, result.end()));


	std::cout << "check" << std::endl;
	std::cout << set2.size() << std::endl;
	std::cout << cc << std::endl;
	
	std::cout << "diff" << std::endl;
	std::cout << result.size() << std::endl;
	
	for(it = result.begin();it != result.end();++it){
		std::cout << std::get<0>(*it) << " " << std::get<1>(*it) << " "<< std::get<2>(*it) << std::endl;
	}

	*/
	return 0;
}