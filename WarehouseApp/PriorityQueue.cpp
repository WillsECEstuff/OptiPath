#include "PriorityQueue.h"

int PriorityQueue::Parent(int i)
{
	return (i - 1)/2;
}

int PriorityQueue::Left(int i)
{
	return (2 * i + 1);
}

int PriorityQueue::Right(int i)
{
	return (2 * i + 2);
}

void PriorityQueue::heapify_down(int i)
{
	// get the left and right node index of index i
	int left = Left(i);
	int right = Right(i);
	
	int largest = i;

	// get the priority from the left/right indices
	int leftPriority = pq[left].getPriority();
	int rightPriority = pq[right].getPriority();
	

	// compare the priority of A[i] with its left and right
	// child and find largest priority
	if (left < size() && leftPriority > pq[i].getPriority()) {
		largest = left;
	}
	if (right < size() && rightPriority > pq[largest].getPriority()) {
		largest = right;
	}

	// swap with child having greater priority and call
	// heapify-down on the child
	if (largest != i) {
		std::swap(pq[i], pq[largest]);
		heapify_down(largest);
	}
	

}

void PriorityQueue::heapify_up(int i)
{
	// check if order at index i and its parent violates
	// the heap property
	int parentIndex = Parent(i);

	int parentPriority = pq[parentIndex].getPriority();
	int nodePriority = pq[i].getPriority();

	if (i && parentPriority < nodePriority) {
		// swap the 2 nodes if heap is violated
		std::swap(pq[i], pq[parentIndex]);

		// call heapify_up on the parent
		heapify_down(parentIndex);
	}
}

int PriorityQueue::size(void)
{
	return pq.size();
}

bool PriorityQueue::isEmpty(void)
{
	return size() == 0;
}

void PriorityQueue::pushOrder(Order order)
{
	// insert the new element to the end of the vector
	pq.push_back(order);

	// get the element index and call heapify_up
	int index = size() - 1;
	heapify_up(index);
}

Order PriorityQueue::popOrder(void)
{
	try {
		// if heap has no elements, throw an exception
		if (size() == 0) {
			throw std::out_of_range("Vector<Order>::at() : " 
				"index is out of range(Heap underflow)");
		}
		Order o = pq[0];

		// replace the root of the heap with the last element
		pq[0] = pq.back();
		pq.pop_back();

		// call heapify_down on root
		heapify_down(0);

		// return the max element
		return o;
	}
	catch (const std::out_of_range& oor) {
		std::cout << "\n" << oor.what();
	}
}

Order PriorityQueue::peekOrder(int index)
{
	try {
		// if heap has no elements, throw an exception
		if (size() == 0) {
			throw std::out_of_range("Vector<Order>::at() : "
				"index is out of range(Heap underflow)");
		}

		// if the index is greater than heap size
		if (index > size()) {
			throw std::out_of_range("Vector<Order>::at() : "
				"index is out of range(Heap overflow)");
		}

		// if the index is less than 0
		if (index < 0) {
			throw std::out_of_range("Vector<Order>::at() : "
				"index is out of range(Heap underflow)");
		}

		// return the Order at index
		return pq[index];
	}
	catch (const std::out_of_range& oor) {
		std::cout << "\n" << oor.what();
	}
}

Order PriorityQueue::popOrderAt(int index)
{
	try {
		// if heap has no elements, throw an exception
		if (size() == 0) {
			throw std::out_of_range("Vector<Order>::at() : "
				"index is out of range(Heap underflow)");
		}

		// if the index is greater than heap size
		if (index > size()) {
			throw std::out_of_range("Vector<Order>::at() : "
				"index is out of range(Heap overflow)");
		}

		// if the index is less than 0
		if (index < 0) {
			throw std::out_of_range("Vector<Order>::at() : "
				"index is out of range(Heap underflow)");
		}
		Order o = pq[index];

		// replace the root of the heap with the last element
		pq[index] = pq.back();
		pq.pop_back();

		// call heapify_down on root
		heapify_down(index);

		// return the max element
		return o;
	}
	catch (const std::out_of_range& oor) {
		std::cout << "\n" << oor.what();
	}
}
