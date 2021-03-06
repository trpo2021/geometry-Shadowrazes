CXX=g++
CFLAGS= -c -Wall -Werror
LIBG = obj/src/libgeometry
GEO = obj/src/geometry

bin/geometry.exe: $(GEO)/geometry.o $(LIBG)/libgeometry.a 
		$(CXX) -I src -Wall -Werror -o bin/geometry.exe $(GEO)/geometry.o $(LIBG)/calculations.o $(LIBG)/checks.o

$(LIBG)/libgeometry.a: $(LIBG)/checks.o $(LIBG)/calculations.o
		ar rcs $@ $^

$(LIBG)/calculations.o: src/libgeometry/calculations.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBG)/calculations.o src/libgeometry/calculations.cpp

$(LIBG)/checks.o: src/libgeometry/checks.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBG)/checks.o src/libgeometry/checks.cpp

$(GEO)/geometry.o: src/geometry/geometry.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(GEO)/geometry.o src/geometry/geometry.cpp

test: bin/test

bin/test: $(LIBG)/libgeometry.a obj/test/mytest.o
	$(CXX) -I src -Wall -Werror -o bin/test obj/test/mytest.o $(LIBG)/libgeometry.a 

obj/test/mytest.o: test/test.cpp
		$(CXX) -I src -I thirdparty $(CFLAGS) -MMD -o obj/test/mytest.o test/test.cpp

-include geometry.d checks.d calculating.d catch.d

.PHONY: clean

clean: 
	rm -rf $(GEO)/*.o $(GEO)/*.d $(LIBG)/*.o $(LIBG)/*.d bin/*.exe