all: bin/gauss

bin/gauss: obj/main.o obj/mat_io.o obj/gauss.o obj/backsubst.o
	$(CC) -Wall -ggdb obj/main.o obj/mat_io.o obj/gauss.o obj/backsubst.o -o bin/gauss

obj/main.o: src/main.c src/mat_io.h src/gauss.h src/backsubst.h
	mkdir -p obj
	$(CC) -Wall -ggdb -c src/main.c -o obj/main.o -I src

obj/mat_io.o: src/mat_io.c src/mat_io.h
	mkdir -p obj
	$(CC) -Wall -ggdb -c src/mat_io.c -o obj/mat_io.o -I src

obj/gauss.o: src/gauss.c src/gauss.h src/mat_io.h
	mkdir -p obj
	$(CC) -Wall -ggdb -c src/gauss.c -o obj/gauss.o -I src

obj/backsubst.o: src/backsubst.c src/backsubst.h src/mat_io.h
	mkdir -p obj
	$(CC) -Wall -ggdb -c src/backsubst.c -o obj/backsubst.o -I src

clean:
	rm -f bin/gauss obj/*
