NUM?=2
numbers=21 22 23 24 25 26 27 28 61 62
tests=project$(NUM)-exampleIO

run:
	for number in $(numbers); \
	do \
		./lab$(NUM) $(tests)/in$$number.txt > $(tests)/out.txt ; \
		diff $(tests)/out.txt $(tests)/out$$number.txt || (echo "diff failed on test $$number") \
	done
	rm $(tests)/out.txt

compile:
	g++ -Wall -Werror -std=c++17 -g *.cpp -o lab$(NUM)
