#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <iterator>
#include <vector>
#include <algorithm>

std::ostream& operator<<(std::ostream &out, const std::pair<int, int> &p) {
    out << "(" << p.first << ";" << p.second << ")";
    return out;
}

#define _USE_MATH_DEFINES
// is the define usefull ?

using namespace std;

int main(int args, char **argv){
	std::set<std::string> setFull;
	std::set<std::string> set2;
	std::set<std::vector<std::pair<int, int>>> set360, setU, setDiff;
	std::string pointList;
	int ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0;
	std::string fileName1("360");
	std::string fileName2("76");

	if(args==2)
		fileName2 = std::string(argv[1]);

	std::ifstream file;
	file.open(fileName1);
	std::cout << "Openning " << fileName1 << std::endl;
	if(!file.is_open()){
		std::cerr << "Can't open the file" << std::endl;
		return -1;
	}
	while(file){
		std::getline(file, pointList);
		if(sscanf(pointList.c_str(), "(%d;%d)(%d;%d)(%d;%d)", &ax, &ay, & bx, &by, &cx, &cy) != 6)
			break;

		setFull.insert(pointList);

		std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
		std::vector<std::pair<int, int>> ptsLst = {A, B, C};
		// do we need to sort ?
		set360.insert(ptsLst);
		setDiff.insert(ptsLst);
	}
	
	std::ifstream file2;
	file2.open(fileName2);
	std::cout << "Openning " << fileName2 << std::endl;
	if(!file2.is_open()){
		std::cerr << "Can't open the file" << std::endl;
		return -2;
	}
	int cnt = 0;
	while(file2){
		std::getline(file2, pointList);
		if(sscanf(pointList.c_str(), "(%d;%d)(%d;%d)(%d;%d)", &ax, &ay, &bx, &by, &cx, &cy) != 6)
			break;
		
		set2.insert(pointList);
		
		std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
		std::vector<std::pair<int, int>> ptsLst = {A, B, C};
		setU.insert(ptsLst);

		std::vector<std::pair<int, int>> r90 = {
			std::pair<int, int>(-ay, ax),
			std::pair<int, int>(-by, bx),
			std::pair<int, int>(-cy, cx)};
		std::sort(r90.begin(), r90.end());

		std::vector<std::pair<int, int>> r270 = {
			std::pair<int, int>(ay, -ax),
			std::pair<int, int>(by, -bx),
			std::pair<int, int>(cy, -cx)};
		std::sort(r270.begin(), r270.end());

		std::vector<std::pair<int, int>> r180 = {
			std::pair<int, int>(-ax, -ay),
			std::pair<int, int>(-bx, -by),
			std::pair<int, int>(-cx, -cy)};
		std::sort(r180.begin(), r180.end());

		if(set360.contains(r90))
			cnt++;
		if(set360.contains(r180))
			cnt++;
		if(set360.contains(r270))
			cnt++;
		if(set360.contains(ptsLst))
			cnt++;

		// Making difference 360-U x 4rotations
		setDiff.erase(ptsLst);
		setDiff.erase(r90);
		setDiff.erase(r180);
		setDiff.erase(r270);
	}

	std::cout << "List of points that are rotation:" << std::endl;
	int c2 = 0;
	for(std::set<std::vector<std::pair<int,int>>>::const_iterator it=setU.begin(); it!=setU.end();++it){
		int ax = (*it)[0].first, ay = (*it)[0].second, bx = (*it)[1].first, by = (*it)[1].second, cx = (*it)[2].first, cy = (*it)[2].second;
		std::pair<int, int> A(ax, ay), B(bx, by), C(cx, cy);
		std::vector<std::pair<int, int>> ptsLst = {A, B, C};

		std::vector<std::pair<int, int>> r90 = {
			std::pair<int, int>(-ay, ax),
			std::pair<int, int>(-by, bx),
			std::pair<int, int>(-cy, cx)};
		std::sort(r90.begin(), r90.end());

		std::vector<std::pair<int, int>> r270 = {
			std::pair<int, int>(ay, -ax),
			std::pair<int, int>(by, -bx),
			std::pair<int, int>(cy, -cx)};
		std::sort(r270.begin(), r270.end());

		std::vector<std::pair<int, int>> r180 = {
			std::pair<int, int>(-ax, -ay),
			std::pair<int, int>(-bx, -by),
			std::pair<int, int>(-cx, -cy)};
		std::sort(r180.begin(), r180.end());
		
		if(setU.contains(r90)){
			if(ptsLst[0]==r90[0] && ptsLst[1] == r90[1] && ptsLst[2] == r90[2])
				continue;
			std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << " < 90> " << r90[0] << r90[1] << r90[2] << std::endl;
		}
		if(setU.contains(r270)){
			if(ptsLst[0]==r270[0] && ptsLst[1] == r270[1] && ptsLst[2] == r270[2])
				continue;
			std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << " <270> " << r270[0] << r270[1] << r270[2] << std::endl;
		}
		if(setU.contains(r180)){
			if(ptsLst[0]==r180[0] && ptsLst[1] == r180[1] && ptsLst[2] == r180[2])
				continue;
			std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << " <180> " << r180[0] << r180[1] << r180[2] << std::endl;
		}
	
		/*
		if(setU.contains(r90) || setU.contains(r270) || setU.contains(r180))
			std::cout << ptsLst[0] << ptsLst[1] << ptsLst[2] << std::endl;
		*/
	}
	std::cout << "End list" << std::endl;

	//std::cout << setFull.size() << std::endl;
	//std::cout << set2.size() << std::endl;
	//std::cout << std::endl;
	std::cout << set360.size() << std::endl;
	std::cout << setU.size() << std::endl;
	std::cout << cnt << std::endl;
	std::cout << std::endl;

	std::cout << c2 << std::endl;
	std::cout << std::endl;

	std::cout << "Difference between 360 and U:" << std::endl;
	//std::set_difference(set360.begin(), set360.end(), setU.begin(), setU.end(),std::inserter(setDiff, setDiff.begin()));
	
	for(std::set<std::vector<std::pair<int,int>>>::const_iterator it=setDiff.begin(); it!=setDiff.end();++it)
		std::cout << (*it)[0] << (*it)[1] << (*it)[2] << std::endl;
		//int ax = (*it)[0].first, ay = (*it)[0].second, bx = (*it)[1].first, by = (*it)[1].second, cx = (*it)[2].first, cy = (*it)[2].second;

	std::cout << "Diff size: " << setDiff.size() << std::endl;

	return 0;
}
