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
	 *
	 * bugged for 5!!!
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
	int lim = 2, cnt = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

// ax <= bx <= cx
for(int ax=1-lim;ax<0;++ax){
for(int ay=1-lim;ay<lim;++ay){
	if(dst(ax, ay, lim))
		continue;
	for(int bx=ax;bx<lim;++bx){
	int bxMax = (ax==bx)? ay : lim;
	for(int by=1-lim;by<bxMax;++by){
		if(dst(bx, by, lim))
			continue;
for(int cx=std::max(1,bx);cx<lim;++cx){
	int cyMax = (cx==bx)? by : lim;
	for(int cy=1-lim;cy<cyMax;++cy){
		if(dst(cx, cy, lim))
			continue;
		// check (0;0) in the middle
		/*
		if(ax==bx){
			if(ay*cx-ax*cy <=0)
				continue;
		}else if(bx==cx){
			if(ax*cy-ay*cx >= 0)
				continue;
		}else{
		*/
		/*
			if((ax*cy-ay*cx)*(by*cx-bx*cy)>=0)
				continue;
			if((ay*cx-ax*cy)*(bx*ay-ax*by)>=0)
				continue;
		*/
		//}
		/*
		if(!(((ay-by)*ax<ay*(ax-bx) && ay*(ax-cx)>ax*(ay-cy))||((ay-by)*ax>ay*(ax-bx) && ay*(ax-cx)<ax*(ay-cy))))
			continue;
		if(!((-(ay-cy)*cx<-cy*(ax-cx) && -cy*(bx-cx)>-cx*(by-cy))||-(ay-cy)*cx>-cy*(ax-cx) && -cy*(bx-cx)<-cx*(by-cy)))
			continue;
		*/
/*
		if(!((ay-by)*ax<ay*(ax-bx) && ay*(ax-cx)>ax*(ay-cy)) && !((ay-by)*ax>ay*(ax-bx) && ay*(ax-cx)<ax*(ay-cy)))
			continue;
		if(!(-(ay-cy)*cx<-cy*(ax-cx) && -cy*(bx-cx)>-cx*(by-cy)) && !(-(ay-cy)*cx>-cy*(ax-cx) && -cy*(bx-cx)<-cx*(by-cy)))
			continue;
*/
		//(-1;-1) (1;0) (1;-1)  solution ?
		if(bx == cx && ax==cx)
			continue;
		if(ax == bx){
			if((float)(ay)/(float)(ax)>=(float)(ay-cy)/(float)(ax-cx)) // mAC <= AO
				continue;
			if((float)(ay-cy)/(float)(ax-cx)<=(float)(cy)/(float)(cx) && (float)(cy)/(float)(cx)>=(float)(by-cy)/(float)(bx-cx)) // mAC <= CO && mBC <= CO
				continue;
			if((float)(ay-cy)/(float)(ax-cx)>=(float)(cy)/(float)(cx) && (float)(cy)/(float)(cx)<=(float)(by-cy)/(float)(bx-cx)) // mAC >= CO && mBC >= CO
				continue;
		}else if(bx == cx){
			if((float)(ay-cy)/(float)(ax-cx)<=(float)(cy)/(float)(cx)) // mAC <= CO
				continue;
			if((float)(ay-by)/(float)(ax-bx)<=(float)(ay)/(float)(ax) && (float)(ay)/(float)(ax)>=(float)(ay-cy)/(float)(ax-cx)) // mAB <= AO && mAC <= AO
				continue;
			if((float)(ay-by)/(float)(ax-bx)>=(float)(ay)/(float)(ax) && (float)(ay)/(float)(ax)<=(float)(ay-cy)/(float)(ax-cx)) // mAB >= AO && mAC >= AO
				continue;
		}else{
			if((float)(ay-by)/(float)(ax-bx)<=(float)(ay)/(float)(ax) && (float)(ay)/(float)(ax)>=(float)(ay-cy)/(float)(ax-cx)) // mAB <= AO && mAC <= AO
				continue;
			if((float)(ay-by)/(float)(ax-bx)>=(float)(ay)/(float)(ax) && (float)(ay)/(float)(ax)<=(float)(ay-cy)/(float)(ax-cx)) // mAB >= AO && mAC >= AO
				continue;
			if((float)(ay-cy)/(float)(ax-cx)<=(float)(cy)/(float)(cx) && (float)(cy)/(float)(cx)>=(float)(by-cy)/(float)(bx-cx)) // mAC <= CO && mBC <= CO
				continue;
			if((float)(ay-cy)/(float)(ax-cx)>=(float)(cy)/(float)(cx) && (float)(cy)/(float)(cx)<=(float)(by-cy)/(float)(bx-cx)) // mAC >= CO && mBC >= CO
				continue;
		}
		/*
		std::cout << ":" << std::endl;
		std::cout << ((ay-by)*ax<ay*(ax-bx) && ay*(ax-cx)>ax*(ay-cy)) << std::endl;
		std::cout << ((ay-by)*ax>ay*(ax-bx) && ay*(ax-cx)<ax*(ay-cy)) << std::endl;
		*/
{
	//std::cout << (ay-by)*ax << " " << ay*(ax-bx) << " : " << ay*(ax-cx) << " " << ax*(ay-cy) << std::endl;
//if((ax*cy-ay*cx)*(by*cx-bx*cy)<0 && (ay*cx-ax*cy)*(bx*ay-ax*by)<0){
//if((ax*cy-ay*cx)*(by*cx-bx*cy)<0 && (ax*cy-ay*cx)*(ax*by-bx*ay)<0){
	std::string cooa("("+std::to_string(ax)+";"+std::to_string(ay)+")");
	std::string coob("("+std::to_string(bx)+";"+std::to_string(by)+")");
	std::string cooc("("+std::to_string(cx)+";"+std::to_string(cy)+")");
	std::cout << cooa << " ";
	std::cout << coob << " ";
	std::cout << cooc << " " << std::endl;
	cnt++;
	
	std::vector<std::string> v;
	v.push_back(std::format("({};{})", ax, ay));
	v.push_back(std::format("({};{})", bx, by));
	v.push_back(std::format("({};{})", cx, cy));
	std::sort(v.begin(), v.end());
	set.insert(v[0]+v[1]+v[2]);
}
	}
}
}
}
}
}

std::cout << "size "<<  lim << " : " << cnt << std::endl;
std::cout << "size "<<  lim << " : " << set.size() << std::endl;

/*
for(std::set<std::string>::const_iterator it = set.begin();it!=set.end();++it){
std::cout << *it << std::endl;
}
*/
return 0;
}
