repword: repword.cpp
	g++ -std=gnu++17 -Wall repword.cpp -o repword

test: repword
	./repword testvector.txt > output.txt
	python3 test.py output.txt expected.txt

clean:
	rm -f output.txt repword


