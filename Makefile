CXX=g++
CFLAGS= -c -Wall -Werror

bin/geometry.exe: obj/geometry.o obj/calculations.o obj/checks.o 
		$(CXX) -I src -Wall -Werror -o bin/geometry.exe obj/geometry.o obj/calculations.o obj/checks.o

obj/calculations.o: src/libgeometry/calculations.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o obj/calculations.o src/libgeometry/calculations.cpp

obj/checks.o: src/libgeometry/checks.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o obj/checks.o src/libgeometry/checks.cpp

obj/geometry.o: src/geometry/geometry.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o obj/geometry.o src/geometry/geometry.cpp

-include geometry.d checks.d calculations.d

