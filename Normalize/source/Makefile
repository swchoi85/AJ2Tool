../trans : trans.o normalize.o ./Lib/libj2cutil.a
	g++ -o ../trans trans.o -L./Lib -lj2cutil `pkg-config --libs --cflags opencv4` -std=c++17
	g++ -o ../normalize normalize.o -L./Lib -lj2cutil `pkg-config --libs --cflags opencv4` -std=c++17

trans.o : trans.cpp
	g++ -c -o trans.o trans.cpp  `pkg-config --libs --cflags opencv4` -std=c++17

normalize.o : normalize.cpp
	g++ -c -o normalize.o normalize.cpp  `pkg-config --libs --cflags opencv4` -std=c++17

clean:
	rm *.o ../trans ../normalize
	rm -rf ../Conv ../Trans ../Check ../Error
