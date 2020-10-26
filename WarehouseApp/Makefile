GCC = g++
STD = -std=c++11
OBS = WarehouseApp.o Product.o Ticket.o Order.o Database.o
FLAGS = NONE

OptiPath: WarehouseApp.o Product.o Ticket.o Order.o Database.o
	$(GCC) $(STD) $(OBS) -o WarehouseApp

%.o : %.cpp
	$(GCC) $(STD) -c *.cpp

clean:
	-rm *.o

run: OptiPath
	./WarehouseApp
