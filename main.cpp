#include "FineGrainedQueue.h"

void ThreadFunc(FineGrainedQueue* FGQ, int val, int pos) {

	FGQ->insertIntoMiddle(val, pos);

}


//==========================================================================================
int main() {

	FineGrainedQueue FGQ;

	FGQ.push_back(1);
	FGQ.push_back(2);
	FGQ.push_back(3);
	FGQ.push_back(4);
	FGQ.push_back(5);

	std::cout << "Before insert:\n";
	FGQ.show();

	//int pos = 3;
	//FGQ.insertIntoMiddle(0, pos);
	//std::cout << "After insert into position "<<pos<<std::endl;
	//FGQ.show();

	//pos = 9;
	//FGQ.insertIntoMiddle(0, pos);
	//std::cout << "After insert into position " << pos << std::endl;
	//FGQ.show();

	std::thread t1([&] {ThreadFunc(&FGQ, 0, 3); });
	std::thread t2([&] {ThreadFunc(&FGQ, 0, 9); });

	t1.join();
	t2.join();

	std::cout << "After insert:\n";
	FGQ.show();




	return 0;
}
