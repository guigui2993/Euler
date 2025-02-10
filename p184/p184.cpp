#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <chrono>
#include <ctime>
#include <cmath>
#include <ratio>
#include <set>
#include <map>
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

template<typename POD>
void serialize(std::string& fileName, std::vector<POD> const& v){
	// this only works on built in data types (PODs)
	static_assert(std::is_trivial<POD>::value && std::is_standard_layout<POD>::value,
		"Can only serialize POD types with this function");

	std::ofstream outfile{fileName, std::ios::binary};
	auto size = v.size();
	outfile.write(reinterpret_cast<char const*>(&size), sizeof(size));
	outfile.write(reinterpret_cast<char const*>(v.data()), v.size() * sizeof(POD));
	outfile.close();
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
	 * size: 4 : 2728 => bug ?
	 * size: 5 : 10600
	 * size: 6 : 
	 *
	 * size: 8 : ok (246216 + )
	 * size: 10: 1101232 ok
	 * size: 11: 2039688 ok
	 * size: 15: 13638120 ok
	 * size: 20: x (77188968 + ) 0.118497s 0.0347521s
	 * size: 25: 300344032 TBC (1.36604s)
	 * size: 30: 913888744
	 * size: 33: 1630362432 (9.54s)
	 * size: 35: overflow :D
	 * size: 50: 19799265048 (1.61448s)
	 * size: 105: 
	 *
	*/

	std::vector<int> listIsoBig;
	std::vector<int> listEquiLat;
	std::vector<int> listIsoSmall;
	std::vector<int> listAny;
	std::vector<int> listAll;
	long long int cnt = 0;
	int lim = 2, c = 0, cntAny = 0, cntEqui = 0, cntIsoBig = 0, cntIsoSmall = 0;
	int c1 = 0, c2 = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

// d(A) > d(B) > d(C)
//
// CASE 1: d(A) > d(B) > d(C)

for(int ax=-1;ax>-lim;--ax){
	int aySqtMax = std::sqrt(lim*lim-ax*ax);
	if(aySqtMax*aySqtMax == lim*lim-ax*ax)
		aySqtMax--;
	int ayMin = -aySqtMax;
	for(int ay=0;ay>=ayMin;--ay){
		for(int bx=1-lim;bx<lim;++bx){
			int byMin = 1-lim, byMax = ay*bx/ax-1;
			/*
			// is it slower ?
			int bySqtMax = std::sqrt(ax*ax+ay*ay-bx*bx);
			if(bySqtMax*bySqtMax == ax*ax+ay*ay-bx*bx)
				bySqtMax--;
			byMin = std::max(byMin, -bySqtMax);
			byMax = std::min(byMax, bySqtMax);
			*/
			for(int by=byMin;by<=byMax;++by){
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				
				int cxMin = 1-lim, cxMax = lim-1;
				int cxSqtMax = std::sqrt(bx*bx+by*by);
				if(cxSqtMax*cxSqtMax == bx*bx+by*by)
					cxSqtMax--;
				cxMin = std::max(cxMin, -cxSqtMax);
				cxMax = std::min(cxMax, cxSqtMax);
				for(int cx=cxMin;cx<=cxMax;++cx){
					int cyMax = lim-1;
					int cyMin = cx*ay/ax; // cy > cx*ay/ax
					if(float(cyMin)<=float(cx*ay)/float(ax))
						cyMin++;
					if(bx==0 && cx*by >= 0)// cx*by >= 0 (if bx ==0)
						continue;
					if(bx>0){// cy > cx*by/bx (if bx >0)
						int cyMin2 = cx*by/bx;
						if(float(cyMin2)<=float(cx*by)/float(bx))
							cyMin2++;
						cyMin = std::max(cyMin, cyMin2);
					}
					// cy < cx*by/bx (if bx <0)
					if(bx<0){ //cx*by < bx*cy
						int cyMax2 = cx*by/bx;  // 1.1 => 2
						if(cyMax2*bx>cx*by)
							cyMax2++;
						cyMax = std::min(cyMax, cyMax2-1);
					}

					int cySqtMax = std::sqrt(bx*bx+by*by-cx*cx);
					if(cySqtMax*cySqtMax == bx*bx+by*by-cx*cx)
						cySqtMax--;
					cyMin = std::max(cyMin, -cySqtMax);
					cyMax = std::min(cyMax, cySqtMax);

					int tot = cyMax-cyMin+1;
					if(tot > 0){
						cnt += tot;
					}
				}
			}
			int by = ay*bx/ax;
			if(bx*ay == ax*by)
				by++;
			for(;by<lim;++by){ // by > ay*bx/ax
				if(dst(bx, by, lim) || (ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(B) < d(A)
					continue;
				int cxMin = 1-lim, cxMax = lim-1;
				int cxSqtMax = std::sqrt(bx*bx+by*by);
				if(cxSqtMax*cxSqtMax == bx*bx+by*by)
					cxSqtMax--;
				cxMin = std::max(cxMin, -cxSqtMax);
				cxMax = std::min(cxMax, cxSqtMax);
				for(int cx=cxMin;cx<=cxMax;++cx){
					if(bx*bx+by*by-cx*cx<=0)
						continue;
					int cyMax = cx*ay/ax; // cy < cx*ay/ax
					int cyMin = 1-lim;
					if(cyMax*ax<=cx*ay)
						cyMax--;
					if(bx==0 && cx*by <= 0)// cx*by <= 0 (if bx ==0)
						continue;
					
					if(bx<0){// cy > cx*by/bx (if bx <0)
						int cyMin2 = cx*by/bx;
						if(float(cyMin2)<=float(cx*by)/float(bx))
							cyMin2++;
						cyMin = std::max(cyMin, cyMin2);
					}
					
					if(bx>0){// cy < cx*by/bx (if bx >0)
						int cyMax2 = cx*by/bx;  // 1.1 => 2
						if(cyMax2*bx<cx*by)
							cyMax2++;
						cyMax = std::min(cyMax, cyMax2-1);
					}
					
					int cySqtMax = std::sqrt(bx*bx+by*by-cx*cx);
					if(cySqtMax*cySqtMax == bx*bx+by*by-cx*cx)
						cySqtMax--;
					cyMin = std::max(cyMin, -cySqtMax);
					cyMax = std::min(cyMax, cySqtMax);

					int tot = cyMax-cyMin+1;
					if(tot > 0){
						cnt += tot;
					}
				}
			}
		}
	}
}
cntAny = cnt;
// square length
std::map<int, std::set<std::pair<int, int>>> lengths;
for(int ax=0;ax<lim;++ax){
	for(int ay=0;ay<lim;++ay){
		lengths[ax*ax+ay*ay].insert(std::pair<int,int>(ax, ay));
		lengths[ax*ax+ay*ay].insert(std::pair<int,int>(-ax, ay));
		lengths[ax*ax+ay*ay].insert(std::pair<int,int>(ax, -ay));
		lengths[ax*ax+ay*ay].insert(std::pair<int,int>(-ax, -ay));
	}
}
/*
std::vector<int> tri = {ax, ay, bx, by, cx, cy};
listEquiLat.insert(listEquiLat.end(), tri.begin(), tri.end());
listIsoBig.insert(listIsoBig.end(), tri.begin(), tri.end());
listIsoSmall.insert(listIsoSmall.end(), tri.begin(), tri.end());
listAny.insert(listAny.end(), tri.begin(), tri.end());
listAll.insert(listAll.end(), tri.begin(), tri.end());
*/
std::cout << "L: " << lengths.size() << std::endl;
// rotations
/*
 * (-7;-1)(-1;-7)(5;5) <180> (-5;-5)(1;7)(7;1) 1
(-5;-5)(1;7)(7;1) <180> (-7;-1)(-1;-7)(5;5) 1
(-5;0)(-3;-4)(4;3) <180> (-4;-3)(3;4)(5;0) 1
(-4;-3)(3;4)(5;0) <180> (-5;0)(-3;-4)(4;3) 1
 * */
for(int ax=-1;ax>-lim;--ax){
	int aySqtMax = std::sqrt(lim*lim-ax*ax);
	if(aySqtMax*aySqtMax == lim*lim-ax*ax)
		aySqtMax--;
	int ayMin = -aySqtMax;
	for(int ay=0;ay>=ayMin;--ay){
		// d(A) == d(B) -> one located bottom left (A)
		for(std::set<std::pair<int, int>>::const_iterator it = lengths[ax*ax+ay*ay].begin();it!=lengths[ax*ax+ay*ay].end();++it){
			int bx = it->first, by = it->second;
			//int bxMin = ax, byMin = 1-lim; //ay*bx/ax-1; //TBC
			//if(ax==bx)
			///	byMin = ay+1;
			//if(bx<bxMin || by < byMin)
			//	continue;
			int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
			if(ABxAO==0)
				continue;
			for(int cx=1-lim;cx<=lim-1;++cx){
				for(int cy=1-lim;cy<=lim-1;++cy){
					if((ax*ax)+(ay*ay) < (cx*cx)+(cy*cy)) // d(C) <= d(B) = d(A)
						continue;
					
					//std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
					//std::vector<std::pair<int, int>> ptsLst = {A, B, C};
					//std::sort(ptsLst.begin(), ptsLst.end());
					//std::cout << "\t" << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
					
					// case A and B bottom left quadrant
					//if((bx>=0 || by>0) && (bx-ax)*(cy-ay)+(ax-cx)*(by-ay) >= 0) // TODO C below AB : TBC We need something to remove the rotation (90 or 180)
					if((bx-ax)*(cy-ay)+(ax-cx)*(by-ay) >= 0) // TODO C below AB : TBC We need something to remove the rotation (90 or 180)
						continue;
					// if d(A) = d(B) = d(C)
					if(cx*cx+cy*cy==ax*ax+ay*ay){
						//if(cx<=0||cy<0) // not enough
						//	continue;
						if(bx>0)
							continue;
						if(cy<0)
							continue;
					}

					//	Remove the rotations!!!!!!
					//if(ay<ax)
					//	continue;
					if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
						continue;
					if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
						continue;
//
					//std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
					if(cx*cx+cy*cy==ax*ax+ay*ay)
						cntEqui++;
					else // C < A=B
						cntIsoBig++;
//
					cnt++;
				}
			}

		}
		//std::cout << std::endl;
		
		// d(A) > d(B)
		for(int bx=1-lim;bx<lim;++bx){
			for(int by=1-lim;by<lim;++by){
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO TODO check ABC
				if(ABxAO==0)
					continue;
				if((ax*ax)+(ay*ay) <= (bx*bx)+(by*by)) // d(A) > d(B) = d(C)
					continue;
				for(std::set<std::pair<int, int>>::const_iterator it = lengths[bx*bx+by*by].begin();it!=lengths[bx*bx+by*by].end();++it){
					int cx = it->first, cy = it->second;
					int cxMin = bx, cyMin = 1-lim; //ay*bx/ax-1; //TBC
					if(cx==bx)
						cyMin = by+1;
					if(cx<cxMin || cy < cyMin)
						continue;
					
					//std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
					//std::vector<std::pair<int, int>> ptsLst = {A, B, C};
					//std::sort(ptsLst.begin(), ptsLst.end());
					//std::cout << "\t" << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
					
					//if((bx-ax)*(cy-ay)+(ax-cx)*(by-ay) >= 0) // TODO C below AB : TBC We need something to remove the rotation (90 or 180)
					//	continue;
					if(((cx-ax)*-ay+ax*(cy-ay)) * ABxAO  >= 0) // AC x AO &&  AB x AO opposite sign != 0
						continue;
					if(((ax-cx)*-cy+cx*(ay-cy)) * ((bx-cx)*-cy+cx*(by-cy)) >= 0) // CA x CO &&  CB x CO opposite sign != 0
						continue;
//
					//std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
					cntIsoSmall++;
//
					cnt++;
				}
		//	int byMin = 1-lim, byMax = ay*bx/ax-1;
			}
		}
	}
}

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
	std::cout << "EquiLat: " << cntEqui*4 << std::endl;
	std::cout << "Iso Big: " << cntIsoBig*4 << std::endl;
	std::cout << "Iso small: " << cntIsoSmall*4 << std::endl;
	std::cout << "Any: " << cntAny*4 << std::endl;
	std::cout << "size "<<  lim << " : " << cnt << "  " << cnt*4 << std::endl;
	//std::cout << "A<B<C "<<  lim << " : " << c << "  " << c*4 << std::endl;
	//std::cout << "diff "<< c2 << "  " << c1 << std::endl;

return 0;
}
