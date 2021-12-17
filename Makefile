all:
	cl65 -t nes 0xColorTest.c -o 0xColorTest.nes
clean:
	rm -rf *.o
