all:hw3.cpp
	g++ -I msgpack-c/include hw3.cpp -Wall -std=c++11 -o hw3.out && echo "######" && ./hw3.out
diff:
	diff ./sample_output.txt ./output.txt
check:
	valgrind --leak-check=full ./hw3.out
refs:
	valgrind --tool=cachegrind ./hw3.out
clean:
	rm -f output.txt
	rm -f hw3.out
	rm -f cachegrind.*
