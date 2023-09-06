#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <shared_mutex>
//==========================================================================================
struct Node
{
	Node(int v) :value(v), node_mutex(new std::mutex), next(nullptr){};
	int value;
	Node* next;
	std::mutex* node_mutex;
};
//------------------------------------------------------------------------------------------
class FineGrainedQueue
{
public:
	FineGrainedQueue();
	~FineGrainedQueue();
	void insertIntoMiddle(int value, int pos);
	void push_back(int);
	void show();

private:
	void _clean_up();
	Node* head{nullptr};
	std::mutex* queue_mutex{nullptr};

};
//------------------------------------------------------------------------------------------
