CC := gcc
CXX := g++

ALL: server.out client.out clean
.PHONY: ALL


OBJ1 := select_echo_client.o mysock.o
OBJ2 := select_echo_server.o mysock.o

# Generate slect_echo_client.out
client.out: $(OBJ1)
	$(CC) -o $@ $^

select_echo_client.o: select_echo_client.c ../mysock.h 
	$(CC) -c -g $<

mysock.o: ../mysock.c ../mysock.h
	$(CC) -c -g $<

#Generate select_echo_server.out
server.out: $(OBJ2)
	$(CC) -o $@ $^

select_echo_server.o: select_echo_server.c
	$(CC) -c -g $<


.PHONY: clean
clean:
	rm -rf $(OBJ1) $(OBJ2)
