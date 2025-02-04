#include <iostream>
#include <string>
#include <format>
#include <chrono>
#include <ctime>
#include <cmath>
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
	 * try to simplify the cases
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
	 * size: 20: x (77188968 + ) 0.3
	 * size: 25: 300344032 TBC (1.36604s)
	 * size: 30: 913888744
	 * size: 33: 1630362432 (9.54s)
	 * size: 35: overflow :D
	 * size: 50: overflow :D (41s)
	 * size: 105: 
	 *
	*/

	int lim = 2, cnt = 0, c = 0;
	int c1 = 0, c2 = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

// d(A) > d(B) > d(C)
//
// CASE 1: d(A) > d(B) > d(C)

for(int ax=-1;ax>-lim;--ax){
	for(int ay=0;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			break;
		for(int bx=1-lim;bx<lim;++bx){
			//for(int by=ay*bx/ax+1;by<lim;++by){// bx>=0 & by > ay*bx/ax & ax <0 & ay <=0
			for(int by=1-lim;by<ay*bx/ax;++by){
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				for(int cx=1-lim;cx<lim;++cx){
					int cyMax = cx*by/bx;
					if(cyMax*bx==by*cx)
						cyMax--;
					int cyMin = cx*ay/ax; // cy > cx*ay/ax
					if(float(cyMin)<=float(cx*ay)/float(ax))
						cyMin++;
					// cx*by >= 0 (if bx ==0)
					if(bx==0 && cx*by >= 0)
						continue;
					// cy > cx*by/bx (if bx >0)
					if(bx>0){
						int cyMin2 = cx*by/bx;
						if(float(cyMin2)<=float(cx*by)/float(bx))
							cyMin2++;
						//cyMin = std::min(cyMin, cyMin2);
					}
					// cy < cx*by/bx (if bx <0)
					if(bx<0){
						int cyMax2 = cx*by/bx+1;
						if(float(cyMax2)>=float(cx*by)/float(bx))
							cyMax2--;
					}
					for(int cy=cyMin;cy<lim;++cy){ // cy > cx*ay/ax
					/*
					int cySqtMax = std::sqrt(bx*bx+by*by-cx*cx);
					if(cySqtMax*cySqtMax == bx*bx+by*by-cx*cx)
						cySqtMax--;
					cyMin = std::max(cyMin, -cySqtMax);
					cyMax = std::min(cyMax, cySqtMax);
					int cySqtA = std::sqrt(ax*ax+ay*ay-cx*cx);
					
					int tot = cyMax-cyMin+1;
					if(tot > 0){
						c1 += tot;cnt += tot;c += tot;
						if(cySqtA*cySqtA == ax*ax+ay*ay-cx*cx && ax*ax+ay*ay-cx*cx >= 0){
							if(cySqtA <=cyMax && cySqtA >= cyMin){
								cnt--;c--;}
							if(-cySqtA <=cyMax && -cySqtA >= cyMin && cySqtA!=0){
								cnt--;c--;}
						}
					}*/
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) <= (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if(cx*by >= bx*cy) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++;c++;
					}
				}
			}
			for(int by=ay*bx/ax;by<lim;++by){
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				int ABxAO = bx*-ay+ax*by; // AB x AO
				if(ABxAO==0)
					continue;
				for(int cx=1-lim;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) <= (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if(((cx-ax)*-ay+ax*(cy-ay)) <= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((bx-cx)*-cy+cx*(by-cy)) <= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++;c++;
					}
				}
			}
		}
	}
}

/*

for(int ax=1-lim;ax<0;++ax){
	for(int ay=0;ay>-lim;--ay){
		if(dst(ax, ay, lim))
			break;
		int bx = ax;
			///
			// ax==bx => ay < by < -ay & d(A) > d(B)
			for(int by=ay+1;by<-ay;++by){
				int ABxAO = ax*by-ay*bx; // AB x AO : ax*(by-ay) < 0
				for(int cx=1;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						// todo
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) == (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if((cx*cx)+(cy*cy) >= (ax*ax)+(ay*ay))
							continue;

						if((cx*-ay+ax*cy) <= 0) // AC x AO &&  AB x AO opposite sign != 0
						// ax*cy > ay*cx // cy> ay*cx/ax
						// cx*by > cy*bx // cy< cx*by/bx
							continue;
						if( (bx*-cy+cx*by) <= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++; c++;
					}
				}
			}
			///
		for(int bx=-1;bx>ax;--bx){
			for(int by=0;by>-lim;--by){ // B in bottom left quadrant; ax<0 & ay <=0 & bx<0 & by<=ay*bx/ax
				if(dst(bx, by, lim))
					break;
				if((ax*ax)+(ay*ay) == (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				int ABxAO = ax*by-ay*bx; // AB x AO : undetermine
				if(ABxAO==0)
					continue;
				for(int cx=1;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) == (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if((cx*cx)+(cy*cy) > (bx*bx)+(by*by) && (cx*cx)+(cy*cy) > (ax*ax)+(ay*ay))
							continue;

						if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
							continue;
						if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++; c++;
					}
				}
			}
			for(int by=1;by<lim;++by){ // bx<0 & by >0 & ax <0 & ay <=0
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) == (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				if((ax*ax)+(ay*ay) < (bx*bx)+(by*by) && (bx >= 0 || by > 0)) // if dB > dA => bottom left quadrant
					continue;
				int ABxAO = -1;
				for(int cx=1;cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) == (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;
						if((cx*cx)+(cy*cy) > (bx*bx)+(by*by) && (cx*cx)+(cy*cy) > (ax*ax)+(ay*ay))
							continue;

					//int cyMin = ay*cx/ax;
						if(ax*cy <= cx*ay) // AC x AO &&  AB x AO opposite sign -> cy > cx*ay/ax
							continue;
						if(((bx-cx)*-cy+cx*(by-cy)) <= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++; c++;
					}
				}
			}
		}
		for(int bx=0;bx<lim;++bx){
			for(int by=1-lim;by<0;++by){// bx>=0 & by <0 & ax <0 & ay <=0
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				for(int cx=std::max(1,bx);cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(cx==bx && cy <= by)
							continue;
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) <= (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;

						if(ax*cy >= cx*ay) // AC x AO &&  AB x AO opposite sign -> cy < cx*ay/ax
							continue;
						if(((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++; c++;
					}
				}
			}
			for(int by=0;by<=ay*bx/ax;++by){// bx>=0 & by <=ay*bx/ax & ax <0 & ay <=0
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) < d(A)
					break;
				// 2 cases: ABxAO <0 or >= 0
				if(ax*by==ay*bx)
					continue;
				for(int cx=std::max(1,bx);cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(cx==bx && cy <= by)
							continue;
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) <= (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;

						if(ax*cy >= cx*ay) // AC x AO &&  AB x AO opposite sign -> cy < cx*ay/ax TBC
							continue;
						if((bx*-cy+cx*by) >= 0) // CA x CO &&  CB x CO opposite sign != 0
							continue;
						cnt++; c++;
					}
				}
			}
			for(int by=ay*bx/ax+1;by<lim;++by){// bx>=0 & by > ay*bx/ax & ax <0 & ay <=0
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) < d(A)
					break;
				for(int cx=std::max(1,bx);cx<lim;++cx){
					for(int cy=1-lim;cy<lim;++cy){
						if(cx==bx && cy <= by)
							continue;
						if(dst(cx, cy, lim) || (bx*bx)+(by*by) == (cx*cx)+(cy*cy) || (ax*ax)+(ay*ay) <= (cx*cx)+(cy*cy)) // d(C) < d(B)
							continue;

						if(ax*cy <= cx*ay) // AC x AO &&  AB x AO opposite sign -> cy < cx*ay/ax TBC
							continue;
						if(bx*-cy+cx*by <= 0) // CA x CO &&  CB x CO opposite sign != 0
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
		for(int bx=-1;bx>ax;--bx){ //bx>ax otherwise impossible to have B < A
			for(int by=0;by>=1-lim;--by){
				if(dst(bx, by, lim))
					break;
				if((ax*ax)+(ay*ay) >= (bx*bx)+(by*by)) // d(B) > d(A)
					continue;
				for(int cx=1;cx<lim;++cx){
					int cyMin = ay*cx/ax;
					int cyMax = cx*by/bx;
					if(cyMin*ax==ay*cx)
						cyMin++;
					if(cyMax*bx==by*cx)
						cyMax--;
					int cySqtMax = std::sqrt(bx*bx+by*by-cx*cx);
					if(cySqtMax*cySqtMax == bx*bx+by*by-cx*cx)
						cySqtMax--;
					cyMin = std::max(cyMin, -cySqtMax);
					cyMax = std::min(cyMax, cySqtMax);
					int cySqtA = std::sqrt(ax*ax+ay*ay-cx*cx);
					
					int tot = cyMax-cyMin+1;
					if(tot > 0){
						c1 += tot;cnt += tot;c += tot;
						if(cySqtA*cySqtA == ax*ax+ay*ay-cx*cx && ax*ax+ay*ay-cx*cx >= 0){
							if(cySqtA <=cyMax && cySqtA >= cyMin){
								cnt--;c--;}
							if(-cySqtA <=cyMax && -cySqtA >= cyMin && cySqtA!=0){
								cnt--;c--;}
						}
					}
				}
			}
		}
	}
}
*/
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
	std::cout << "diff "<< c2 << "  " << c1 << std::endl;

return 0;
}
