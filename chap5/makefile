CC := gcc
CXX := g++

# depend on director
DEP_DIR := ..

ALL: echo_client.out echo_server.out sig.out clean
.PHONY: ALL

OBJ1 := echo_client.o mysock.o
OBJ2 := echo_server.o 
OBJ3 := sig.o
OBJ4 := signal.o

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

$(OBJ2): echo_server.c $(DEP_DIR)/mysock.h
	$(CC) -c  -g $<

# generate sig.out
sig.out: $(OBJ3)
	$(CC) -o $@ $^

$(OBJ3): sig.c
	$(CC) -c -g $<


# generate signal.o
$(OBJ4): signal.c
	$(CC) -c -g $<


.PHONY: clean
clean:
	rm -rf $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
