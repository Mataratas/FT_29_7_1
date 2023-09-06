#include "FineGrainedQueue.h"
//==========================================================================================
FineGrainedQueue::FineGrainedQueue():queue_mutex(nullptr), head(nullptr)
{
	queue_mutex = new std::mutex;
}
//==========================================================================================
FineGrainedQueue::~FineGrainedQueue() {
	_clean_up();
	if (queue_mutex)
		delete queue_mutex;
}
//==========================================================================================
void FineGrainedQueue::_clean_up() {
	std::lock_guard<std::mutex> ul(*queue_mutex);
	if (head) {
		Node* prev{nullptr};
		Node* cur{ head->next };
		while (cur) {
			if (cur->next) {
				prev = cur->next;
				delete cur;
				cur = prev;
			}
			else {
				delete cur;
				cur = nullptr;
			}
		}
		delete head;
		head = nullptr;
	}
}
//==========================================================================================

void FineGrainedQueue::insertIntoMiddle(int value, int pos) {
	queue_mutex->lock();
	int q_size{ 0 };
	Node* last{ head };
	while (last) {
		q_size++;
		last = last->next;
	}
	queue_mutex->unlock();
	if (pos >= q_size)
		push_back(value);
	else {
		int cnt{};
		last=head;
		Node* prev{ nullptr };
		while (last) {
			cnt++;
			if (cnt == pos) {
				if (prev) {
					prev->node_mutex->lock();
					prev->next = new Node(value);
					prev->node_mutex->unlock();

					prev->next->node_mutex->lock();
					prev->next->next = last;
					prev->next->node_mutex->unlock();
				}else {
					prev = last->next;

					last->node_mutex->lock();
					last->next = new Node(value);
					last->node_mutex->lock();

					last->next->node_mutex->lock();
					last->next->next = prev;
					last->next->node_mutex->unlock();
				}
				break;
			}
			prev = last;
			last = last->next;
		}
	}
}
//==========================================================================================
void FineGrainedQueue::push_back(int value) {
	if (!head) {
		queue_mutex->lock();
		head = new Node(value);
		queue_mutex->unlock();
	}
	else 
	{
		Node* last{head};
		while (last->next) {
			queue_mutex->lock();
			last = last->next;
			queue_mutex->unlock();
		}
		last->node_mutex->lock();
		last->next= new Node(value);
		last->node_mutex->unlock();
	}
}
//==========================================================================================
void FineGrainedQueue::show() {
	std::lock_guard<std::mutex> ul(*queue_mutex);
	Node* last{ head };
	while (last) {
		std::cout<<last->value<<" ";
		last = last->next;
	}
	std::cout << std::endl;
}
//==========================================================================================
