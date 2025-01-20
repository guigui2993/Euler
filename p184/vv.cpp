#include <iostream>
#include <string>
#include <algorithm>

inline int dst(int x, int y, int d){
	return x*x+y*y >= d*d;
}

int main(int args, char **argv){
	/*
	 * p184 Brute Force
	 * ABC O seen as vector
	 * mAB, mAO, mBO
	 *
	 * bugged for vertical side
	 * size 2, 3 ok
	 *
	 * size: 2 : 8
	 * size: 3 : 360
	 * size: 4 : 
	 * size: 5 : 2656 wrong : => 10600
	 *
	 * size: 10: 
	 * size: 15: 
	 * size: 20: 
	 *
	 * size: 105: 
	 *
	*/

	int lim = 2, cnt = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

// ax <= bx <= cx
for(int ax=1-lim;ax<lim;++ax){
for(int ay=1-lim;ay<lim;++ay){
	if(dst(ax, ay, lim))
		break;
	for(int bx=ax;bx<lim;++bx){
		int byMax = lim;
		if(ax==bx)
			byMax=ay;
	for(int by=1-lim;by<byMax;++by){
		if(dst(bx, by, lim))
			break;
for(int cx=bx;cx<lim;++cx){
	int cyMax = lim;
	if(bx==cx)
		cyMax = by;
	for(int cy=1-lim;cy<cyMax;++cy){ // might be problem !
		if(dst(cx, cy, lim))
			break;
		// check (0;0) in the middle
		
		if(ax==bx){
			if(ay*cx-ax*cy <=0)
				continue;
		}else if(bx==cx){
			if(ax*cy-ay*cx >= 0)
				continue;
		}else{
			if((ax*cy-ay*cx)*(by*cx-bx*cy)>=0)
				continue;
			if((ay*cx-ax*cy)*(bx*ay-ax*by)>=0)
				continue;
		}
{
//if((ax*cy-ay*cx)*(by*cx-bx*cy)<0 && (ay*cx-ax*cy)*(bx*ay-ax*by)<0){
//if((ax*cy-ay*cx)*(by*cx-bx*cy)<0 && (ax*cy-ay*cx)*(ax*by-bx*ay)<0){
	std::string cooa("("+std::to_string(ax)+";"+std::to_string(ay)+")");
	std::string coob("("+std::to_string(bx)+";"+std::to_string(by)+")");
	std::string cooc("("+std::to_string(cx)+";"+std::to_string(cy)+")");
	std::cout << cooa << " ";
	std::cout << coob << " ";
	std::cout << cooc << " " << std::endl;
	cnt++;
}
	}
}
}
}
}
}

std::cout << "size "<<  lim << " : " << cnt << std::endl;

/*
for(std::set<std::string>::const_iterator it = set.begin();it!=set.end();++it){
std::cout << *it << std::endl;
}*/

return 0;
}
