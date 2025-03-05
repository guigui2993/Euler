/*
 * i.cc: improve the s.cc
 * s.cc: 4.47s
 * i.cc: 
P195

Check if needed to combine 2 times the (x, y, k)
even 1 pass still 4 missing
no pass ~200 missing

60° angle => c is the side opposite
Diophantine Equation: a²-a*b+b²=c²
=> b = (a+-sqrt(4*c²-3*a²))/2

Hypothese: only postive
=> b = (a+sqrt(4*c²-3*a²))/2

=> search for:
4*c²-3*a² = n² <=> (C²-3*a²) = n² with C = 2*c


Pell's equation:
a²-Ny²=k
solution: (m, 1, m²-N) => (a, y, k)
((a*m+N*b)/k, (a+b*m)/k, (m*m-N)/k)

C²-3*a² = k (=n²)
(m, 1, m²-3) => trivial solution, then
((C*m+3*b)/k, (C+b*m)/k, (m*m-3)/k)

Method 2:
list all trivial
Combine trivial solution so k1*k2 = n²
            ((x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2))
            ((x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2))
            ((x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2))

for each trivial solution, we find (m, 1, m²-3) with m >0 and <0
We can drop the m<0 because their solution will end up with a <0

should focus on prime solution not n*(a, b, c)
try something

#should find 1234 !
nMax = 946 => 1027 below 100 (945 => 843)

4 missing:
a	b	c
187	280	247
247	352	313
279	319	301
280	391	349

C	a	nSq
494	187	373
626	247	457
602	279	359
698	280	502

try to improve
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>
#include <set>
#include <iterator>
#include "Euler.cc"
#include <cstdint>
#include <chrono>
#include <ctime>

typedef unsigned long long int ulli;

void ad(std::set<std::tuple<int64_t,int64_t,int64_t>> &s, int mul, int64_t x, int64_t y, int64_t kSq){
	int gcd = Euler::gcd(Euler::gcd(x,y), kSq*mul);
	x /= gcd;
	y /= gcd;
	kSq = (kSq*mul)/gcd;
	double rr2 = (x*x-(kSq-y)*(kSq-y))*(3*y+kSq-x)/16.0/(3*y+kSq+x);
	//if(rr2 >10000)
	//	return;
	s.insert(std::tuple<int64_t,int64_t,int64_t>(x, y, kSq));
}

int main(int args, char **argv){
	int mMax = std::atoi(argv[1]); // 946
	std::vector<std::vector<int>> ts;
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	for(int m=3;m < mMax;++m) // do we need m<0 ?
		ts.push_back(std::vector<int>{m, 1, m*m-3});

	std::cout << "ts size: " << (ts.size()) << std::endl;

	/*
	for all trivial solution find the multiplier needed to make it square
	ex: k1 = 12 => we need k2 multiple of 3 so that k1*k2 = n²
	kLsit = {mul: [k, ]} i.e. {6: [6, 24, ...]}*/
	std::map<int, std::vector<int>> kList; // list of a, b, kSq appended (read them 3 yb 3)
	int cnt = 0;
	for(std::vector<std::vector<int>>::const_iterator it = ts.begin();it!=ts.end();++it){
		int a = (*it)[0], b = (*it)[1], k = (*it)[2];
		
		std::map<ulli,int> factors;
		Euler::fact(factors, k);
		int mul = 1, kSq = 1;
		for(std::map<ulli, int>::const_iterator it=factors.begin();it!=factors.end();++it){
			if(it->second % 2 == 1)
				mul *= it->first;
			kSq *= Euler::pow(it->first, it->second/2);
			//std::cout << it->first << " " << it->second << std::endl;
		}
		kList[mul].push_back(a);
		kList[mul].push_back(b);
		kList[mul].push_back(kSq);
		//std::cout << a << " " << b << " " << k << std::endl;
		cnt++;
	}
	std::cout << "kList size: " << cnt << std::endl;
	/*//Debug
	for(std::map<int, std::vector<int>>::const_iterator it=kList.begin();it!=kList.end();++it){
		std::cout << it->first << " " << it->second.size() << std::endl;
		std::vector<int>::const_iterator i = it->second.begin();
		for(;i!=it->second.end();++i){
			int a = *i++, b = *i++, kSq = *i;
			std::cout << "\t" << a << "\t" << b << "\t" << kSq << std::endl;
		}
	}*/

	/*
	combination k1k2: k1 and k2 not square beside 1, so combine with 1 and the k having the same mul together
	combination k and 1

	we are interested in k = n²
	1 trivial solution works: m=1 => k = 1
	other solutions must be a combination k1*k2
		xyk = {(2, 1, 1), (2, -1, 1), (1, 0, 1)} # (x, y, sqK)

	TODO gcd(x, y, kSq) = 1
	TODO check if (1, 0, 1) required
	*/
	std::set<std::tuple<int64_t,int64_t,int64_t>> xyk;
	xyk.insert(std::tuple<int64_t,int64_t,int64_t>(2, 1, 1));
	//xyk.insert(std::tuple<int64_t,int64_t,int64_t>(2, -1, 1));
	xyk.insert(std::tuple<int64_t,int64_t,int64_t>(1, 0, 1));
	std::map<int, std::vector<int>>::const_iterator itKl = kList.begin();
	for(;itKl!=kList.end();++itKl){
		int mul = itKl->first; // the key of kList is the mul
		for(std::vector<int>::const_iterator it1=itKl->second.begin();it1!=itKl->second.end();++it1){
			int64_t x1 = *it1++, y1 = *it1++, kSq1 = *it1;
			for(std::vector<int>::const_iterator it2=itKl->second.begin();it2!=itKl->second.end();++it2){
				int64_t x2 = *it2++, y2 = *it2++, kSq2 = *it2;

				int64_t x = x1*x2+3*y1*y2, y = x1*y2+x2*y1, kSq = kSq1*kSq2;
				if(kSq*mul==y)
					continue;
				if(x > 0 && y > 0)
					ad(xyk, mul, x, y, kSq);

				x = x1*x2-3*y1*y2; y = x1*y2-x2*y1;
				if(x>0 && y!=0){
					if(y<0)
						y *= -1;
					if(kSq*mul!=y)// TBC
						ad(xyk, mul, x, y, kSq);
				}

			}
		}
	}
	std::cout << "xyk size: " << xyk.size() << std::endl;

	int r2LIM = 10000;
	std::set<std::tuple<int64_t,int64_t,int64_t>>::const_iterator it1, it2;
	/*//DBG
	for(it1=xyk.begin();it1!=xyk.end();++it1){
		int x = std::get<0>(*it1), y = std::get<1>(*it1), kSq = std::get<2>(*it1);
		//if Euler.gcd(Euler.gcd(x,y), kSq) != 1:
		//std::cout << x << "\t" << y << "\t" << kSq << std::endl;
		if(x<0 || y <0 || kSq < 0)
			return -99;
	}*/
	
	//std::set<std::tuple<int64_t,int64_t,int64_t>> xyk2 = xyk;
	std::set<std::tuple<int64_t,int64_t,int64_t>> xyk2;
	for(it1=xyk.begin();it1!=xyk.end();++it1){
		int64_t x = std::get<0>(*it1), y = std::get<1>(*it1), kSq = std::get<2>(*it1);
		if(y!=kSq && x > 0 && y > 0){
			double rr2 = (x*x-(kSq-y)*(kSq-y))*(3*y+kSq-x)/16.0/(3*y+kSq+x);
			//if(rr2 >10000){
			//	continue;
				//std::cout << rr2 << " " << x << "\t" << y << "\t" << kSq << std::endl;
				//return 0;
			//}
			ad(xyk2, 1, x, y, kSq);
		}
	}

	std::set<std::tuple<int,int,int>> ll;
	ll.insert(std::tuple<int,int,int>(74, 33, 26));
ll.insert(std::tuple<int,int,int>(86, 35, 22));
ll.insert(std::tuple<int,int,int>(98, 39, 71));
ll.insert(std::tuple<int,int,int>(158, 51, 131));
ll.insert(std::tuple<int,int,int>(194, 55, 169));
ll.insert(std::tuple<int,int,int>(61, 28, 37));
ll.insert(std::tuple<int,int,int>(194, 57, 167));
ll.insert(std::tuple<int,int,int>(146, 63, 46));
ll.insert(std::tuple<int,int,int>(278, 69, 251));
ll.insert(std::tuple<int,int,int>(247, 36, 239));
ll.insert(std::tuple<int,int,int>(326, 75, 299));
ll.insert(std::tuple<int,int,int>(206, 77, 157));
ll.insert(std::tuple<int,int,int>(91, 40, 59));
ll.insert(std::tuple<int,int,int>(182, 85, 74));
ll.insert(std::tuple<int,int,int>(446, 85, 421));
	
	int cccc=0;
	///TRY COMBINATION
	for(it1=xyk.begin();it1!=xyk.end();++it1){
		int64_t x1 = std::get<0>(*it1), y1 = std::get<1>(*it1), kSq1 = std::get<2>(*it1);

		double a = y1, b = (y1+kSq1)/2.0, c = x1/2.0, s = (a+b+c)/2.0, r2 = (s-a)*(s-b)*(s-c)/s;
		if(r2>r2LIM)
			break; // opti
		for(it2=it1;it2!=xyk.end();++it2){
			int64_t x2 = std::get<0>(*it2), y2 = std::get<1>(*it2), kSq2 = std::get<2>(*it2);

			double a = x1+y1, b = (y1+x1+kSq1)/2.0, c = (x1+3*y1)/2.0, s = (a+b+c)/2.0, r2 = (s-a)*(s-b)*(s-c)/s;
			if(r2>r2LIM){
				break; // opti
			}
			int64_t x = x1*x2+3*y1*y2, y = x1*y2+x2*y1, kSq = kSq1*kSq2;
			double rr2 = (x*x-(kSq-y)*(kSq-y))*(3*y+kSq-x)/16.0/(3*y+kSq+x);
			//std::cout << rr2 << " " << x << "\t" << y << "\t" << kSq << std::endl;
			cccc++;
			//if(cccc>4)
			//	return 0;
				//DBG
			//	if(ll.find(std::tuple<int,int,int>(x, y, kSq)) != ll.end())

					//std::cout << x1 << "\t" << y1 << "\t" << kSq1 << "\t" << x2 << "\t" << y2 << "\t" << kSq2 << std::endl;
				//DBG
			if(kSq==y)
				continue;
			if(x > 0 && y > 0)
				ad(xyk2, 1, x, y, kSq);
		}
	}
	for(it1=xyk.begin();it1!=xyk.end();++it1){
		int64_t x1 = std::get<0>(*it1), y1 = std::get<1>(*it1), kSq1 = std::get<2>(*it1);
		
		double a = 1, b = (1+kSq1)/2.0, c = 1/2.0, s = (a+b+c)/2.0, r2 = (s-a)*(s-b)*(s-c)/s;
		if(r2>r2LIM)
			break; // useless
		for(it2=it1;it2!=xyk.end();++it2){
			int64_t x2 = std::get<0>(*it2), y2 = std::get<1>(*it2), kSq2 = std::get<2>(*it2);
			int64_t x = x1*x2-3*y1*y2, y = x1*y2-x2*y1, kSq = kSq1*kSq2;
			if(x>0 && y!=0){
				if(y<0)
					y *= -1;
				//DBG
			//double rr2 = (x*x-(kSq-y)*(kSq-y))*(3*y+kSq-x)/16.0/(3*y+kSq+x);
			double rr2 = (1.0*x*x-(kSq-y)*1.0*(kSq-y))*(3.0*y+kSq-x)/16.0/(3*y+kSq+x);

			//double rrr2 = (x*x-(kSq-y)*(kSq-y))/16.0*((3.0*y+kSq-x))/(3*y+kSq+x);
			//double rrr2 = (x*x-(kSq-y)*(kSq-y))*((3*y+kSq-x))/16.0/(3*y+kSq+x);
			//double rrr2 = (x*x-(kSq-y)*(kSq-y))/8.0*((3.0*y+kSq-x)-(0.0*x))/2.0/(3*y+kSq+x);
			//double rrr2 = (x*x-(kSq-y)*(kSq-y))/16.0*(1-double((x+x)/(y+y+y+kSq+x)));
			double xx = x, yy = y, kk = kSq;
			double rrr2 = (xx*xx-(kk-yy)*(kk-yy))/16.0*(1.0-((2.0*xx)/(3*yy+kk+xx)));
			double err = rr2-rrr2;
			if(err<0)
				err *= -1;
			if(err > 1000){
				std::cout << std::endl;
				std::cout << rr2 << " " << x << "\t" << y << "\t" << kSq << std::endl;
				std::cout << rrr2 << " " << x << "\t" << y << "\t" << kSq << std::endl;
				std::cout << std::endl;
			}
			cccc++;
			//if(cccc>4)
			//	return 0;
				//if(ll.find(std::tuple<int,int,int>(x, y, kSq)) != ll.end())
					//std::cout << x1 << "\t" << y1 << "\t" << kSq1 << "\t" << x2 << "\t" << y2 << "\t" << kSq2 << std::endl;
				//DBG
				if(kSq!=y)
					ad(xyk2, 1, x, y, kSq);
			}
		}
	}
	///END COMBINATION

	/*// DBG
	for(it1=xyk2.begin();it1!=xyk2.end();++it1){
		int64_t x = std::get<0>(*it1), y = std::get<1>(*it1), kSq = std::get<2>(*it1);
		//if Euler.gcd(Euler.gcd(x,y), kSq) != 1:
		//if(!(x>y && x > kSq))//&& y < kSq))
		//if(x < kSq)//&& y < kSq))
		//	std::cout << "\t" << x << "\t" << y << "\t" << kSq << std::endl;
		if(x<0 || y <0 || kSq < 0)
			return -99;
	}*/
	
	std::cout << "xyk2 size: " << xyk2.size() << std::endl;
	std::set<std::tuple<int,int,int>> triLst;

	int cc = 0, ccc=0;
	for(it1=xyk2.begin();it1!=xyk2.end();++it1){
		int64_t C = std::get<0>(*it1), a = std::get<1>(*it1), nSq = std::get<2>(*it1);
		/*if(nSq == a || C<=0 || a <=0){
			std::cout << C << "\t" << a << "\t" << nSq << std::endl;
			return -1;
		}*/
		/*DBG
		if(nSq==373)
			std::cout << C << "\t" << a << "\t" << nSq << std::endl;
		*/
				//DBG
				if(C==62 && a == 24 && nSq == 46)
					std::cout << "yo" << std::endl;//std::cout << x1 << "\t" << y1 << "\t" << kSq1 << x2 << "\t" << y2 << "\t" << kSq2 << std::endl;
				//DBG
		if(C%2!=0){
			C *= 2; a *= 2; nSq *= 2;
		}
		int64_t c = C/2;
		if((a+nSq)%2 != 0) //never happen
			continue;
		int64_t b = (a+nSq)/2;
		double s = (a+b+c)/2.0;
		double r2 = (s-a)*(s-b)*(s-c)/s;
		if(r2>r2LIM){
			ccc++;
			continue;
		}
		int64_t nbTri = std::sqrt(r2LIM/r2);

		if(b < a)
			std::swap(a, b);
		if(c < b)
			std::swap(c, b);
		if(c < a)
			std::swap(c, a);

		/*
		if (a, b, c) in triLst:
			print("DUP !!!")
			exit()
		if Euler.gcd(a,Euler.gcd(b,c)) != 1:
			print("GCD !!!")
			exit()
		if (a, b, c) in triLst or (b, c, a) in triLst or (c, a, b) in triLst or (a, c, b) in triLst or (b, a, c) in triLst or (c, b, a) in triLst: # useless
			continue
			print("dupy")
			print((a, b, c))
			#exit()
		*/
		if(triLst.find(std::tuple<int,int,int>(a, b, c)) == triLst.end()){
			cc += nbTri;
			triLst.insert(std::tuple<int,int,int>(a, b, c));
			//std::cout << a << "\t" << b << "\t" << c << "\t" << nbTri << std::endl;
			//std::cout << a << "\t" << b << "\t" << c << "\t" << nbTri << "\t" << C << "\t" << a << "\t" << nSq << std::endl;
		}
	}

	std::cout << "Nb of tri: " << triLst.size() << std::endl;
	std::cout << "ans: " << cc << std::endl;
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;
	std::cout << ccc << std::endl;
	return 0;
}
