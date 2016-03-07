all:hw1.cpp
	g++ hw1.cpp -Wall -std=c++11 -o hw1.out && ./hw1.out && echo "######" && cat ./output.txt
check:
	valgrind --leak-check=full ./hw1.out
refs:
	valgrind --tool=cachegrind ./hw1.out
clean:
	rm -f output.txt
	rm -f hw1.out
	rm -f cachegrind.*
