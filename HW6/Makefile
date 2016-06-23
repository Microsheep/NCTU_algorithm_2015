all:hw6.cpp
	g++ hw6.cpp -Wall -std=c++11 -o hw6.out && echo "######" && ./hw6.out
diff:
	diff ./sample_output.txt ./output.txt
check:
	valgrind --leak-check=full ./hw6.out
refs:
	valgrind --tool=cachegrind ./hw6.out
clean:
	rm -f output.txt
	rm -f hw6.out
	rm -f cachegrind.*
