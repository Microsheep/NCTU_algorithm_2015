all:hw4.cpp
	g++ -I msgpack-c/include hw4.cpp -Wall -std=c++11 -o hw4.out && echo "######" && ./hw4.out
diff:
	diff ./sample_output.txt ./output.txt
check:
	valgrind --leak-check=full ./hw4.out
refs:
	valgrind --tool=cachegrind ./hw4.out
clean:
	rm -f output.txt
	rm -f hw4.out
	rm -f cachegrind.*
