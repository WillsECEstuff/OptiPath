#include <iostream>
#include "pch.h"
#include "CppUnitTest.h"

#include "../WarehouseApp/PriorityQueue.h"
#include "../WarehouseApp/PriorityQueue.cpp"
#include "../WarehouseApp/Order.h"
#include "../WarehouseApp/Order.cpp"
#include "../WarehouseApp/Product.h"
#include "../WarehouseApp/Product.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PriorityQueueTest
{
	TEST_CLASS(PriorityQueueTest)
	{
	public:
		
		TEST_METHOD(insertTest)
		{
			PriorityQueue p;
			Order o(1, 1);

			p.pushOrder(o);
			Order o2 = p.peekOrder(0);
			Assert::AreEqual(o.getPriority(), o2.getPriority());
			
		}

		TEST_METHOD(getSize)
		{
			PriorityQueue p;
			int actual = 0;
			int answer = p.size();

			Assert::AreEqual(actual, answer);
		}

		TEST_METHOD(pushPopMultipleOrders) {
			PriorityQueue p;
			//std::cout << p.getMaxSize() << std::endl;

			Order o(1, 90);
			p.pushOrder(o);
			
			Order o2(2, 50);
			p.pushOrder(o2);

			Order o3(3, 75);
			p.pushOrder(o3);

			Order o4(4, 99);
			p.pushOrder(o4);

			Order o5(5, 1);
			p.pushOrder(o5);

			Order o6(6, 66);
			p.pushOrder(o6);

			Assert::AreEqual(o4.getPriority(), p.popOrder().getPriority());
			Assert::AreEqual(o.getPriority(), p.popOrder().getPriority());
			Assert::AreEqual(o3.getPriority(), p.popOrder().getPriority());
			Assert::AreEqual(o6.getPriority(), p.popOrder().getPriority());
			Assert::AreEqual(o2.getPriority(), p.popOrder().getPriority());
			Assert::AreEqual(o5.getPriority(), p.popOrder().getPriority());

		}
	};
}
