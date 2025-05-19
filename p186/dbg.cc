#include <iostream>
#include <cstdlib>
#include <string>

/*
 * populate the halffriend list
 * */

constexpr int RANGE = 1000000;

struct Node{
	int n=0; // number
	struct Node *next = nullptr;
};

struct List{
	int size=0; // list size
	struct Node *head = nullptr;
	struct Node *tail = nullptr;
};

List lN[RANGE]; // for each number => list that contains it

void print(){
	for(int i=0;i<RANGE;i++){
		Node *n = lN[i].head;
		std::cout << i << "\t:\t";
		int c = 0;
		do{
			std::cout << n->n << "\t";
			n = n->next;
			c++;
		}while(n != nullptr && c < 10);
		std::cout << std::endl;
		if(c>=10)
			std::cout << " Fc loop" << std::endl;

	}
}
void merge(List &l1, List &l2){
	if(l2.size > l1.size){ // merge in l1
		merge(l2, l1);
		return;
	}

	if(l1.tail->next != nullptr){
		std::cout << "problem with tail l1" << std::endl;
		return;
	}
	if(l2.tail->next != nullptr){
		std::cout << "problem with tail l2" << std::endl;
		return;
	}
	int c = 0;
	// merge in l1
	Node *n = l2.head;
	l1.tail->next = l2.head; // append l2 to l1
	//std::cout << "append "<< l2.head->n << " to " << l1.tail->n << std::endl;
	l1.tail = l2.tail; // update the new tail of l1
	//std::cout << "new tail of "<< l1.head->n << " is " << l2.tail->n << std::endl;
	int newSize = l1.size + l2.size;
	do{ // run through all nodes to update the list pointer
		if(c>10000){
			std::cout << "loop" << std::endl;
			return;
		}
		lN[n->n].head = l1.head;
		lN[n->n].tail = l1.tail;
		lN[n->n].size = newSize;
		n = n->next;
		c++;
	}while(n != nullptr);
}

int main(int agrs, char *argv[]){
	int pm = std::atoi(argv[1]);
	double percentage = std::atof(argv[2]);
	int lim = 1000000;
	int flSize = percentage*RANGE;
	std::cout << "Find " << pm << " with a fl size: " << flSize << std::endl;


	for(int i=0;i<RANGE;i++){
		lN[i].size = 1;
		lN[i].head = new Node();
		lN[i].tail = lN[i].head;
		lN[i].head->n = i;
	}
/*
	std::cout << "#######" << std::endl;
	print();
	std::cout << "insert: " << 4 << " " << 5 << std::endl;
	merge(lN[4], lN[5]);
	print();
	std::cout << "insert: " << 7 << " " << 8 << std::endl;
	merge(lN[7], lN[8]);
	print();
	std::cout << "insert: " << 1 << " " << 2 << std::endl;
	merge(lN[2], lN[1]);
	print();
	std::cout << "insert: " << 9 << " " << 7 << std::endl;
	merge(lN[9], lN[7]);
	print();
	std::cout << "insert: " << 3 << " " << 0 << std::endl;
	merge(lN[3], lN[0]);
	print();
	std::cout << "insert: " << 3 << " " << 8 << std::endl;
	merge(lN[3], lN[8]);
	print();
	return 0;
	*/

	// if called : caller then they are friends => remove caller : called
	unsigned long long int buff[55];
	
	int caller, called;
	// fill the buffer with the first 55 items
	for(unsigned long long int k=1;k<=55;++k){
		caller = called;
		called = buff[k-1] = (100003-200003*k +300007*k*k*k)%RANGE;
		if(k%2==0){
			if(lN[caller].head != lN[called].head){
				merge(lN[called], lN[caller]);
				//print();
			}
		}
	}
	
	caller = buff[54];
	called = buff[0] = (buff[31] + buff[0])%RANGE;
	if(lN[caller].head != lN[called].head){
		merge(lN[called], lN[caller]);
		//print();
	}

	int cnt = 29;
	for(int i=29;i<=lim;++i){ // 2*n-1 : 2*n
		int n = 2*i;
		caller = buff[(n-2)%55] = (buff[(n-26)%55] + buff[(n-2)%55])%RANGE;
		called = buff[(n-1)%55] = (buff[(n-25)%55] + buff[(n-1)%55])%RANGE;
		if(caller==called)
			continue;
		cnt++;
		//std::cout << cnt << std::endl;
		
		if(lN[caller].head != lN[called].head){ //merge if not in the same list
			merge(lN[called], lN[caller]);
			//print();
		}

		if(lN[pm].size >= flSize){
			std::cout << cnt << std::endl;
			std::cout << "group size: " << lN[pm].size << std::endl;
			return 0;
		}
	}
	std::cout << "not found" << std::endl;
	return 0;
}
