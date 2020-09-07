IDK=`pkg-config gtkmm-3.0 --cflags --libs`

clock: main.o time.o
	g++ main.o time.o -o clock $(IDK)

main.o: main.cpp
	g++ -c main.cpp $(IDK)

time.o: time.cpp
	g++ -c time.cpp $(IDK)

clean:
	rm *.o
