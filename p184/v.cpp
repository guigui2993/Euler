#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <string>
#include <format>
#include <algorithm>
#include <sstream>

inline int dst(int x, int y, int d){
	return x*x+y*y >= d*d;
}

//p = ay-ax*(ay-by)/(ax-bx)
inline float s(int ax, int ay, int bx, int by){
	if(ax == bx){
		std::cout << "ERROR!" << std::endl;
		return 0;
	}
	float r = (float)(ay)-(float)(ax*(ay-by))/(float)(ax-bx);
	if(r<0.0001 && r > 0.0001)
		std::cout << "ERROR 0 !" << std::endl;
	return r;
}
int main(int args, char **argv){
	/*
	 * p184 Brute Force
	 * ABC O seen as vector
	 * mAB, mAO, mBO
	 *
	 * size 2, 3 ok
	 *
	 * y = mx+p
	 * p = ay-ax*(ay-by)/(ax-bx)
	 *
	 * size: 2 : 8
	 * size: 3 : 360
	 * size: 4 : 
	 * size: 5 : 2656 wrong : => 10600
	 *
	 * size: 10: 
	 *
	 * size: 15: 
	 * size: 20: 
	 *
	 * size: 105: 
	 *
	*/

	std::set<std::string> set;
	//std::cout << std::endl;
	int lim = 5, cnt = 0;
	if(args==2)
		lim = std::atoi(argv[1]);

	// ax <= bx <= cx
	for(int ax=1-lim;ax<lim;++ax){
		for(int ay=1-lim;ay<lim;++ay){
			if(dst(ax, ay, lim))
				break;
			for(int bx=ax;bx<lim;++bx){
				int by=1-lim;
				if(ax==bx)
					by = ay+1
				for(int by=1-lim;by<lim;++by){
					if(dst(bx, by, lim))
						break;
					for(int cx=bx;cx<lim;++cx){
						for(int cy=1-lim;cy<lim;++cy){ // might be problem !
							if(dst(cx, cy, lim))
								break;
							// check (0;0) in the middle
							
							if(ax == bx){ // AB vertical
								//check AC above 0 and BC below 0 or the opposite
								if(ax==cx)
									continue; // aligned => no triangle
								if(ax*cx>=0) // A and C must be apart from (0;0)
									continue;
								float p_bc = s(bx, by, cx, cy);
								float p_ac = s(ax, ay, cx, cy);
								if(p_bc*p_ac>=0) // BC below && AC above or the opposite
									continue;
							}else if(bx == cx){ // BC vertical
								//check AC above 0 and BC below 0 or the opposite
								if(ax*cx>=0) // A and C must be apart from (0;0)
									continue;
								float p_ab = s(ax, ay, bx, by);
								float p_ac = s(ax, ay, cx, cy);
								if(p_ab*p_ac>=0) // AB below && AC above or the opposite
									continue;
							}else if(ax == cx){ // AC vertical
								//check AC above 0 and BC below 0 or the opposite
								if(bx*cx>=0) // B and C must be apart from (0;0)
									continue;
								float p_ab = s(ax, ay, bx, by);
								float p_bc = s(bx, by, cx, cy);
								if(p_ab*p_bc>=0) // AB below && AC above or the opposite
									continue;
							}else{//no vertical side
								float p_ab = s(ax, ay, bx, by);
								float p_ac = s(ax, ay, cx, cy);
								float p_bc = s(bx, by, cx, cy);
								// y = m*x+p
								float ab_c_y = (float)(ay-by)/(float)(ax-bx)*cx+p_ab;// y of ab line @ cx
								float ac_b_y = (float)(ay-cy)/(float)(ax-cx)*bx+p_ac;// y of ab line @ bx
								float bc_a_y = (float)(by-cy)/(float)(bx-cx)*ax+p_bc;// y of ab line @ ax

								/*
								if(ay==0&&ax==-1&&bx==0&&by==1&&cx==1&&cy==-1){
									std::cout << p_ab << " " << p_ac << " " << p_bc << std::endl;
									std::cout << ab_c_y << " " << ac_b_y << " " << bc_a_y << std::endl;
								}*/
								if((cy-ab_c_y)*p_ab>=0)//zero not between them
									continue;

								if((by-ac_b_y)*p_ac>=0)//zero not between them
									continue;

								if((ay-bc_a_y)*p_bc>=0)//zero not between them
									continue;
							}
							//if(ty*uy>=0) // top & bottom apart from (0;0)
							//	continue;

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

	std::cout << "size "<<  lim << " : " << set.size() << std::endl;

	/*
	for(std::set<std::string>::const_iterator it = set.begin();it!=set.end();++it){
		std::cout << *it << std::endl;
	}*/

	return 0;
}
