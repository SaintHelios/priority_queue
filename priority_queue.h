#pragma once
#include "queue.h"
#include <iostream>

template <typename T>
class priority_queue {
private:
	size_t priorities_amount;
	queue<T>* priority_queues;
public:
	priority_queue(size_t priorities_amount = 3);
	void push(T value, size_t priority);
	T pop();
	bool is_empty();
};

template <typename T> bool priority_queue<T>::is_empty() {
	bool switcher = true;
	for (size_t i = 0; i < priorities_amount; ++i) {
		if (priority_queues[i].size() != 0) {
			switcher = false;
			break;
		}
	}
	return switcher;
}

template <typename T> priority_queue<T>::priority_queue(size_t priorities_amount) {
	this->priorities_amount = priorities_amount;
	this->priority_queues = new queue<T>[this->priorities_amount];
}

template <typename T> void priority_queue<T>::push(T value, size_t priority) {
	if (priority <= priorities_amount) priority_queues[priority - 1].push(value);
	else {
		queue<T>* to_copy = new queue<T>[priority];
		for (size_t i = 0; i < priorities_amount; ++i) {
			to_copy[i] = priority_queues[i];
		}
		to_copy[priority - 1].push(value);
		delete[] priority_queues;
		priorities_amount = priority;
		priority_queues = to_copy;
	}
}

template <typename T> T priority_queue<T>::pop() {
	if (this->is_empty()) {
		std::cout << "queue is empty" << std::endl;
	}

	else {
		size_t i = 0;
		T to_return;
		for (; i < priorities_amount; ++i) {
			if (priority_queues[i].size() != 0) break;
		}
		to_return = priority_queues[i].pop();
		return to_return;
	}
}