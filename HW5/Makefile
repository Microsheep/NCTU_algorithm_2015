all:hw5.cpp
	g++ -I msgpack-c/include hw5.cpp -Wall -std=c++11 -o hw5.out && echo "######" && ./hw5.out
diff:
	diff ./sample_output.txt ./output.txt
check:
	valgrind --leak-check=full ./hw5.out
refs:
	valgrind --tool=cachegrind ./hw5.out
clean:
	rm -f output.txt
	rm -f hw5.out
	rm -f cachegrind.*
