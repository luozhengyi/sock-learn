CC = gcc
CXX = g++

# depend on director
DEP_DIR = ..

ALL: echo_client.out echo_server.out
.PHONY: ALL

OBJ1 = echo_client.o mysock.o
OBJ2 = echo_server.o mysock.o

# generate echo_client.out
echo_client.out: $(OBJ1)
	$(CC) -o $@ $^

echo_client.o: echo_client.c $(DEP_DIR)/mysock.h
	$(CC) -c -g $< 

mysock.o: $(DEP_DIR)/mysock.c $(DEP_DIR)/mysock.h
	$(CC) -c -g $<

# generate echo_server.out
echo_server.out: $(OBJ2)
	$(CC) -o $@ $^

echo_server.o: echo_server.c $(DEP_DIR)/mysock.h
	$(CC) -c  -g $<


.PHONY: clean
clean:
	rm -rf $(OBJ1) $(OBJ2)