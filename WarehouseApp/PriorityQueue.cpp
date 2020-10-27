#include "PriorityQueue.h"

/**
 * @brief	Private member function.
 *			Gets the parent index of index i
 * 
 * @param	i		index position
 * @return	int		returns parent index location
 */
int PriorityQueue::Parent(int i)
{
	return (i - 1)/2;
}

/**
 * @brief	Private member function.
 *			Gets the left child index of index i
 * 
 * @param	i		index position
 * @return	int		returns left child index position
 */
int PriorityQueue::Left(int i)
{
	return (2 * i + 1);
}

/**
 * @brief	Private member function.
 *			Gets the right child index of index i
 *
 * @param	i		index position
 * @return	int		returns right child index position
 */
int PriorityQueue::Right(int i)
{
	return (2 * i + 2);
}

/**
 * @brief	Private member function.
 *			Moves the object at index i down the heap
 *			if applicable
 * 
 * @param	i		index position
 */
void PriorityQueue::heapify_down(int i)
{
	// get the left and right node index of index i
	int left = Left(i);
	int right = Right(i);
	
	int largest = i;
	

	// compare the priority of A[i] with its left and right
	// child and find largest priority
	if (left < size() && pq[left].getPriority() > pq[i].getPriority()) {
		largest = left;
	}
	if (right < size() && pq[right].getPriority() > pq[largest].getPriority()) {
		largest = right;
	}

	// swap with child having greater priority and call
	// heapify-down on the child
	if (largest != i) {
		std::swap(pq[i], pq[largest]);
		heapify_down(largest);
	}
	

}

/**
 * @brief	Private member function.
 *			Moves the object at index i up the heap
 *			if applicable
 *
 * @param	i		index position
 */
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
		heapify_up(parentIndex);
	}
}


/**
 * @brief	returns the size of the priority queue
 *			(# of Order objects)
 * 
 * @return	int		size of priority queue
 */
int PriorityQueue::size(void)
{
	size_t size = pq.size();
	if (size > INT_MAX) {
		throw std::overflow_error("size is larger than INT_MAX");
	}
	return static_cast<int>(size);
}

/**
 * @brief	returns true of there are no Order objects in 
 *			the priority queue; false otherwise
 * 
 * @return	bool	true if pq is empty
 */
bool PriorityQueue::isEmpty(void)
{
	return size() == 0;
}

/**
 * @brief	Adds the Order object into the priority queue
 *			and automatically moves its position within
 *			the queue through its priority
 * 
 * @param	order		Completed Order object
 */
void PriorityQueue::pushOrder(Order order)
{
	// insert the new element to the end of the vector
	pq.push_back(order);

	// get the element index and call heapify_up
	int index = size() - 1;
	heapify_up(index);
}

/**
 * @brief	Gets an Order object from the root of the
 *			priority queue (index = 0). The resulting 
 *			Order object is then removed from the pq.
 * 
 * @return	Order		Order object that had the highest
 *						priority at time of pop.
 */
Order PriorityQueue::popOrder(void)
{
	
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

/**
 * @brief	Returns an Order object from a supplied index
 *			location. Does not remove the Order from the
 *			priority queue. NOTE: index does not mean that 
 *			the order of priority goes from highest to 
 *			lowest. This pq implements a binary heap.
 * 
 * @param	index		index position
 * @return	Order		Order object at index
 */
Order PriorityQueue::peekOrder(int index)
{
	
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

/**
 * @brief	Gets an Order object from the the supplied 
 *			index in the priority queue . The resulting 
 *			Order object is then removed from the pq. 
 *			NOTE: index does not mean that the order of 
 *			priority goes from highest to lowest. This 
 *			pq implements a binary heap.
 * 
 * @param	index		index position
 * @return	Order		Order object at index
 */
Order PriorityQueue::popOrderAt(int index)
{
	
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
