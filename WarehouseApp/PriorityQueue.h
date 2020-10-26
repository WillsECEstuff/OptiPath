#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "Order.h"

class PriorityQueue
{
private:

	std::vector<Order> pq;
	int Parent(int i);
	int Left(int i);
	int Right(int i);

	void heapify_down(int i);
	void heapify_up(int i);


public:
	int size(void);
	bool isEmpty(void);
	void pushOrder(Order order);
	Order popOrder(void);
	Order peekOrder(int index);
	Order popOrderAt(int index);

};

