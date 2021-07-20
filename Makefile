CC=g++ -std=c++17

run:
	$(CC) main.cpp -lsqlite3
clean:
	rm a.* *.gch