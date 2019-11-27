# Rules for building each .o
assign8.o: assign8.c
	gcc -g -c assign8.c -o assign8.o

# Rules for building the executable
assign8: assign8.o
	gcc -g -o assign8 assign8.o

# Remove all .o files
clean:
	rm -f assign8.o
