build: cpp/gen-header.cpp cpp/gen-freq.cpp
	g++ cpp/gen-header.cpp -o gen-header
	g++ cpp/gen-freq.cpp -o gen-freq

clean:
	rm gen-header gen-freq