CC=g++ -std=c++20 -o release/SQLiteTest.exe

run:
	$(CC) -lsqlite3 -I include/ src/*.cpp
clean:
	rm a.* *.gch resources/*.db