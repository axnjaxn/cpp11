all: initializers

initializers: initializers.cpp
	$(CXX) initializers.cpp -o $@ -std=c++11

clean:
	rm -f *~ *.o initializers
