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
	 * focus on A<B<C
	 * remove rotation by forcing the biggest distance to stay in the bottom left quadrant (A , B or C)
	 *
	 * size: 2 : 8
	 * size: 3 : 360
	 * size: 4 :
	 * size: 5 : 10600
	 * size: 6 : 
	 *
	 * size: 8 : ok (246216 + )
	 * size: 10: 1101232 ok
	 * size: 11: 2039688 ok
	 * size: 15: 13638120 ok
	 * size: 20: x (77188968 + ) 1.22s 0.6s 0.29855s 0.33 0.27s
	 * size: 25: 300344032 TBC (1.36604s)
	 * size: 30: 913888744
	 * size: 33: 1630362432 (9.54s)
	 * size: 35: overflow :D
	 * size: 105: 
	 *
	*/

	int lim = 2, cnt = 0, c = 0;
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

// CASE 1: d(A) > d(B) > d(C)

for(int ax=1-lim;ax<0;++ax){
	for(int ay=0;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			break;
		for(int bx=ax;bx<lim;++bx){
			int byMin = 1-lim;
			if(bx==ax)
				byMin = ay+1;
			for(int by=byMin;by<lim;++by){
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) == (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
				if(ABxAO==0)
					continue;
				for(int cx=std::max(1,bx);cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(cx==bx && cy <= by)
							continue;
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) == (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if((cx*cx)+(cy*cy) > (bx*bx)+(by*by) && (cx*cx)+(cy*cy) > (ax*ax)+(ay*ay))
							continue;

						if((ax*ax)+(ay*ay)>(bx*bx)+(by*by)){
							if((ax*ax)+(ay*ay) > (cx*cx)+(cy*cy)){
								if(ax>=0 || ay >0) // A > B&C
									continue;
							}else
								continue;// C > A&B
						}else{ // B > A
							if((bx*bx)+(by*by) > (cx*cx)+(cy*cy)){
								if(bx>=0 || by >0) // B > A&C
									continue;
							}else
								continue;// C > A&B
						}
						if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++; c++;
					}
				}
			}
		}
	}
	for(int ay=1;ay<lim;++ay){ // A in the top left quadrant => d(B) > d(A) & B in botton left quadrant
		if(dst(ax, ay, lim))
			break;
		for(int bx=-1;bx>=ax;--bx){
			int byMin = 1-lim;
			if(bx==ax)
				byMin = ay+1;
			for(int by=0;by>=byMin;--by){
				if(dst(bx, by, lim))
					break;//continue;
				if((ax*ax)+(ay*ay) >= (bx*bx)+(by*by)) // d(B) > d(A)
					continue;
				for(int cx=1;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(cx==bx && cy <= by)
							continue;
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) == (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if((cx*cx)+(cy*cy) > (bx*bx)+(by*by) && (cx*cx)+(cy*cy) > (ax*ax)+(ay*ay))
							continue;
						//
						if((bx*bx)+(by*by) > (cx*cx)+(cy*cy)){
							if(bx>=0 || by >0) // B > A&C
								continue;
						}else
							continue;// C > A&B
						//if((cx-ax)*-ay+ax*(cy-ay) >= 0) // AC x AO &&  AB x AO opposite sign != 0 ABxAO >0
						if(cx*-ay+ax*cy >= 0) // AC x AO &&  AB x AO opposite sign != 0 ABxAO >0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++; c++;
					}
				}
			}
		}
	}
}
						//std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
						//std::vector<std::pair<int, int>> ptsLst = {A, B, C};
						//std::sort(ptsLst.begin(), ptsLst.end());
						//std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
/*
// d(A) = d(B) = d(C)
for(int ax=0;ax>-lim;--ax){
	for(int ay=-1;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			break;
		for(int bx=1-lim;bx<lim;++bx){
			for(int by=1-lim;by<lim;++by){
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) < (bx*bx)+(by*by)) // d(B) <= d(A)
					continue;
				if((ax*ax)+(ay*ay) != (bx*bx)+(by*by)) // d(B) != d(A)
					continue;
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
				if(ABxAO==0)
					continue;
				for(int cx=1-lim;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) < (cx*cx)+(cy*cy)) // d(C) <= d(B)
							continue;
						if((bx*bx)+(by*by) != (cx*cx)+(cy*cy)) // d(B) != d(C)
							continue;
						if((bx-ax)*(cy-ay)+(ax-cx)*(by-ay) >= 0) // C below AB : TBC
							continue;
						if(bx < 0 && cy > 0)
							continue;
						if(bx >= 0 && cy <= 0)
							continue;
						if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++;
					}
				}
			}
		}
	}
}

// d(A) = d(B)
for(int ax=0;ax>-lim;--ax){
	for(int ay=-1;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			break;
		for(int bx=1-lim;bx<lim;++bx){
			for(int by=1-lim;by<lim;++by){
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) < (bx*bx)+(by*by)) // d(B) <= d(A)
					continue;
				if((ax*ax)+(ay*ay) != (bx*bx)+(by*by)) // d(B) != d(A)
					continue;
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
				if(ABxAO==0)
					continue;
				for(int cx=1-lim;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) <= (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if((bx-ax)*(cy-ay)+(ax-cx)*(by-ay) >= 0) // C below AB : TBC
							continue;
						if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++;
					}
				}
			}
		}
	}
}

// d(B) = d(C)
for(int ax=0;ax>-lim;--ax){
	for(int ay=-1;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			break;
		for(int bx=1-lim;bx<lim;++bx){
			for(int by=1-lim;by<lim;++by){
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) <= d(A)
					continue;
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
				if(ABxAO==0)
					continue;
				for(int cx=1-lim;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) < (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if((bx*bx)+(by*by) != (cx*cx)+(cy*cy)) // d(B) != d(C)
							continue;
						if((bx-ax)*(cy-ay)+(ax-cx)*(by-ay) >= 0) // C below AB : TBC
							continue;
						if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++;
					}
				}
			}
		}
	}
}
*/
						/*
						std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
						std::vector<std::pair<int, int>> ptsLst = {A, B, C};
						std::sort(ptsLst.begin(), ptsLst.end());
						std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
						*/
						/*
						if(ax==0&&ay==-5&&bx==-4&&by==-3&&cx==3&&cy==4){
							std::cout << std::format("({};{})({};{})({};{})\tyep", ax, ay, bx, by, cx, cy) << std::endl;
							std::cout << (bx-ax)*(cy-ay)+(ax-cx)*(by-ay) << std::endl;
						}*/

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;
	std::cout << "size "<<  lim << " : " << cnt << "  " << cnt*4 << std::endl;
	std::cout << "A<B<C "<<  lim << " : " << c << "  " << c*4 << std::endl;

return 0;
}
