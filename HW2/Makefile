all:hw2.cpp
	g++ -I msgpack-c/include hw2.cpp -Wall -std=c++11 -o hw2.out && ./hw2.out && echo "######" && diff ./sample_output.txt ./output.txt
check:
	valgrind --leak-check=full ./hw2.out
refs:
	valgrind --tool=cachegrind ./hw2.out
clean:
	rm -f output.txt
	rm -f hw2.out
	rm -f cachegrind.*
