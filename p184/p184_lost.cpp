#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>
#include <set>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>

std::ostream& operator<<(std::ostream &out, const std::pair<int, int> &p) {
    out << "(" << p.first << ";" << p.second << ")";
    return out;
}

inline int dst(int x, int y, int d){
	return x*x+y*y >= d*d;
}

int main(int args, char **argv){
	/*
	 * p184 Brute Force vector
	 *
	 * test to list unique shape and sorted
	 * 2 ok
	 * 3 : bug => 82 instead of 90
	 *
	 * size: 2 : 8
	 * size: 3 : 360
	 * size: 4 :
	 * size: 5 : 10600
	 *
	 * size: 10: 1101232 TBC
	 * size: 15: 13638120 TBC
	 * size: 25: 300344032 TBC (1.36604s)
	 * size: 30: 913888744 TBC 
	 * size: 105: 
	 *
	*/

	int lim = 2, cnt = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

// -lim < ax < 0; 0 < -ay < lim ; A in bottom left quadrant
// ax <= bx; ay <= by < lim
// bx <= cx; ay < cy <= by
// ax <= bx <= cx but ax != bx&cx
//
for(int ax=-1;ax>-lim;--ax){
	for(int ay=-1;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			continue;//break; // ax*ax+ay*ay < lim*lim : maybe split in 2 ; 0 lim, -lim 0
		for(int bx=ax;bx<lim;++bx){
			//for(int by=1-lim;by<byMax;++by){
			for(int by=ay+1;by<lim;++by){
				if(dst(bx, by, lim))
					continue;
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
				if(ABxAO==0)
					continue;
				for(int cx=std::max(bx+1,1);cx<lim;++cx){
					int cyMax = ay;
					if(ax==bx)
						cyMax++;
					//for(int cy=ay+1;cy<=by;++cy){
					for(int cy=ay+1;cy<=0;++cy){
						if(dst(cx, cy, lim))
							continue;
						if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++;
						//std::cout << "("<< ax << ";" << ay << ")" << "("<< bx << ";" << by << ")" << "("<< cx << ";" << cy << ")" << std::endl;
						std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
						std::vector<std::pair<int, int>> ptsLst = {A, B, C};
						std::sort(ptsLst.begin(), ptsLst.end());

						std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
					}
				}
			}
		}
	}
}

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;
std::cout << "size "<<  lim << " : " << cnt << std::endl;

return 0;
}
