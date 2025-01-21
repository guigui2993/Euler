#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <format>

inline int dst(int x, int y, int d){
	return x*x+y*y >= d*d;
}

int main(int args, char **argv){
	/*
	 * p184 Brute Force vector
	 * with set and exhaustive for loop
	 *
	 * size 2, 3 ok
	 *
	 * size: 2 : 8
	 * size: 3 : 360
	 * size: 4 :
	 * size: 5 : 10600
	 *
	 * size: 10: 
	 * size: 15: 
	 * size: 20: 
	 *
	 * size: 105: 
	 *
	*/

	std::set<std::string> set;
	std::set<std::string> setAll;
	int lim = 2, cnt = 0, cntAll = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

// ax <= bx <= cx
for(int ax=-1;ax>-lim;--ax){
for(int ay=1-lim;ay<lim;++ay){
	if(dst(ax, ay, lim))
		continue; // ax*ax+ay*ay < lim*lim : maybe split in 2 ; 0 lim, -lim 0
	for(int bx=ax;bx<lim;++bx){
	for(int by=1-lim;by<lim;++by){
		if(dst(bx, by, lim))
			continue;
for(int cx=bx;cx<lim;++cx){
	for(int cy=1-lim;cy<lim;++cy){
		if(dst(cx, cy, lim))
			continue;
		//std::cout << std::format("({};{})", ax, ay) << " " << std::format("({};{})", bx, by) << " " << std::format("({};{})", cx, cy) << std::endl;
		cntAll++;

		std::vector<std::string> v;
		v.push_back(std::format("({};{})", ax, ay));
		v.push_back(std::format("({};{})", bx, by));
		v.push_back(std::format("({};{})", cx, cy));
		std::sort(v.begin(), v.end());
		//setAll.insert(v[0]+v[1]+v[2]);

		// a1*b2-a2*b1
		// AC x AO
		//a1 = (cx-ax);
		//a2 = (cy-ay);
		//b1 = -ax;
		//b2 = -ay;

		if(((cx-ax)*-ay+ax*(cy-ay)) * ((bx-ax)*-ay+ax*(by-ay)) >= 0) // AC x AO &&  AB x AO opposite sign != 0
			continue;
		
		if(((cx-bx)*-by+bx*(cy-by)) * ((ax-bx)*-by+bx*(ay-by)) >= 0) // BC x BO &&  BA x BO opposite sign != 0
			continue;
		
		if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
			continue;

	cnt++;
	set.insert(v[0]+v[1]+v[2]);
}
	}
}
}
}
}

/*
for(std::set<std::string>::const_iterator it = set.begin();it!=set.end();++it){
std::cout << *it << std::endl;
}*/

std::cout << "size "<<  lim << " : " << cnt << std::endl;
std::cout << "size "<<  lim << " : " << set.size() << std::endl;
std::cout << "sizeAll "<<  lim << " : " << setAll.size() << " cntAll:" << cntAll  << std::endl;

return 0;
}
