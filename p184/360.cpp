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
	 * test to list unique shape
	 * list all possible triangles : ex: 3 -> 360
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

	std::set<std::string> s;
	int lim = 2, cnt = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

// ax <= bx <= cx
for(int ax=-1;ax>-lim;--ax){
	for(int ay=1-lim;ay<lim;++ay){
		if(dst(ax, ay, lim))
			continue; // ax*ax+ay*ay < lim*lim : maybe split in 2 ; 0 lim, -lim 0
		for(int bx=ax;bx<lim;++bx){
			int byMax = lim;
			if(bx==ax)
				byMax = ay;
			for(int by=1-lim;by<byMax;++by){
				if(dst(bx, by, lim))
					continue;
				int ABxAO = (bx-ax)*-ay+ax*(by-ay); // AB x AO
				if(ABxAO==0)
					continue;
				for(int cx=std::max(bx,1);cx<lim;++cx){
						int cyMax = lim;
						if(bx==cx)
							cyMax = by;
					for(int cy=1-lim;cy<cyMax;++cy){
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


						/*
						// try the other angles
						std::vector<std::string> v;
						v.push_back("("+ std::to_string(ax) + ";" + std::to_string(ay) + ")");
						v.push_back("(" + std::to_string(bx) + ";" + std::to_string(by) + ")");
						v.push_back("(" + std::to_string(cx) + ";" + std::to_string(cy) + ")");
						std::sort(v.begin(), v.end());

						std::string pts = v[0]+v[1]+v[2];

						//std::cout << pts << " <= pts " << std::endl;

						//horizontal mirror
						v.clear();
						v.push_back("("+ std::to_string(-ax) + ";" + std::to_string(ay) + ")");
						v.push_back("(" + std::to_string(-bx) + ";" + std::to_string(by) + ")");
						v.push_back("(" + std::to_string(-cx) + ";" + std::to_string(cy) + ")");
						std::sort(v.begin(), v.end());
						std::string h_m = v[0]+v[1]+v[2];

						// vertical mirror
						v.clear();
						v.push_back("("+ std::to_string(ax) + ";" + std::to_string(-ay) + ")");
						v.push_back("(" + std::to_string(bx) + ";" + std::to_string(-by) + ")");
						v.push_back("(" + std::to_string(cx) + ";" + std::to_string(-cy) + ")");
						std::sort(v.begin(), v.end());
						std::string v_m = v[0]+v[1]+v[2];

						// vertical / horizontal mirror
						v.clear();
						v.push_back("("+ std::to_string(-ax) + ";" + std::to_string(-ay) + ")");
						v.push_back("(" + std::to_string(-bx) + ";" + std::to_string(-by) + ")");
						v.push_back("(" + std::to_string(-cx) + ";" + std::to_string(-cy) + ")");
						std::sort(v.begin(), v.end());
						std::string vh_m = v[0]+v[1]+v[2];
						*/
						/*
						std::string pts = "("+ std::to_string(ax) + ";" + std::to_string(ay) + ")(" + std::to_string(bx) + ";" + std::to_string(by) + ")(" + std::to_string(cx) + ";" + std::to_string(cy) + ")";
						
						//horizontal mirror
						std::string h_m = "("+ std::to_string(-ax) + ";" + std::to_string(ay) + ")(" + std::to_string(-bx) + ";" + std::to_string(by) + ")(" + std::to_string(-cx) + ";" + std::to_string(cy) + ")";
						
						// vertical mirror
						std::string v_m = "("+ std::to_string(ax) + ";" + std::to_string(-ay) + ")(" + std::to_string(bx) + ";" + std::to_string(-by) + ")(" + std::to_string(cx) + ";" + std::to_string(-cy) + ")";
						// vertical / horizontal mirror
						std::string vh_m = "("+ std::to_string(-ax) + ";" + std::to_string(-ay) + ")(" + std::to_string(-bx) + ";" + std::to_string(-by) + ")(" + std::to_string(-cx) + ";" + std::to_string(-cy) + ")";
						*/

						/*
						if(s.contains(h_m) || s.contains(v_m) || s.contains(vh_m))
							continue;
						if(ax<=bx && bx < cx && by < ay && cy <= ay && by<=cy)
							s.insert(pts);
						*/
					}
				}
			}
		}
	}
}

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	//std::cout << "Duration: " << time_span.count() << "s" << std::endl;
	//std::cout << "size "<<  lim << " : " << cnt << std::endl;
	//std::cout << "size Set "<< s.size() << std::endl;
/*
	for(std::set<std::string>::const_iterator it = s.begin();it!=s.end();++it){
		std::cout << *it << std::endl;
	}
*/
return 0;
}
