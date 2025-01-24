#include <iostream>
#include <string>
#include <format>
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
	 * d(A) > d(B) > d(c)
	 * should be ok but problem when dA==dB , etc
	 * 2 nok
	 *
	 * 3 : bug => 104 instead of 90
	 *
	 * No missing but rotation included
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

// A is the furthest point from (0;0)
// C is the closest point from (0;0)
// d(A) >= d(B) >= d(C)
//
// -lim < ax <= 0; 0 < -ay < lim ; A in bottom left quadrant
// nope: ax <= bx; bx <= cx ; cx > 1
// nope: if(ax==bx) ay < by
// nope: if(bx==cx) by < cy
//
for(int ax=0;ax>-lim;--ax){
	for(int ay=-1;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			continue;//break; // ax*ax+ay*ay < lim*lim : maybe split in 2 ; 0 lim, -lim 0
		//for(int bx=ax;bx<lim;++bx){
		for(int bx=1-lim;bx<lim;++bx){
			//for(int by=(ax==bx)?ay+1:1-lim;by<lim;++by){ //if(ax==bx) ay < by
			for(int by=1-lim;by<lim;++by){ //if(ax==bx) ay < by
				//std::cout << std::format("({};{})({};{})", ax, ay, bx, by) << std::endl;
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) < (bx*bx)+(by*by)) // d(B) <= d(A)
					continue;
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
				if(ABxAO==0)
					continue;
				int cxMin = 1-lim;
				//if((ax*ax)+(ay*ay) == (bx*bx)+(by*by) && (bx < ax || (ax==bx && ay > by)))
				//if((ax*ax)+(ay*ay) == (bx*bx)+(by*by) && (bx < ax || (ay==by))) // stop before counting rotation
				//if((ax*ax)+(ay*ay) == (bx*bx)+(by*by) && (bx < ax || (ay==by) || (ax==bx && ay > by))) // stop before counting rotation
				//if((ax*ax)+(ay*ay) == (bx*bx)+(by*by) && (bx < ax || (ay==by) || (ax==bx && ay > by))) // stop before counting rotation
				int cyMin = 1-lim;
				if((ax*ax)+(ay*ay) == (bx*bx)+(by*by)){
					//if(ay >= by) // stop before counting rotation
					//	continue;
					//cyMin = 0; // cx >= 0 and cy >= 0
					//cxMin = 0; // lose some solution ...
					if(ax==bx)
						cyMin = 1;
					// ABxAC < 0

				}//cxMin = std::max(bx, ax);
				//for(int cx=std::max(bx,1);cx<lim;++cx){
				for(int cx=cxMin;cx<lim;++cx){
					//for(int cy=(bx==cx)?by+1:1-lim;cy<lim;++cy){
					for(int cy=cyMin;cy<lim;++cy){
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) < (cx*cx)+(cy*cy)) // d(C) <= d(B)
							continue;
						if(((ax*ax)+(ay*ay) == (bx*bx)+(by*by)) && (bx-ax)*(cy-ay)+(ax-cx)*(by-ay) <= 0) // C below AB : TBC
							continue;
						if((bx*bx)+(by*by) == (cx*cx)+(cy*cy) && cx < bx)
							continue;
						if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++;
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
