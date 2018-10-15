CC = gcc
CFLAGS = -c
OFLAGS = -o
LIBFLAGS = -lssl -lcrypto

MAIN = main.c
MODULE1 = module1
MODULE2 = module2
CMODULE = module1.c module2.c
OMODULE = module1.o module2.o
TARGET = hash

program : $(MAIN)
	$(CC) $(OFLAGS) $(TARGET) $(MAIN) $(OMODULE) $(LIBFLAGS)

module : $(MODULE)
	$(CC) $(CFLAGS) $(CMODULE) $(LIBFLAGS)

clean :
	rm $(TARGET) $(OMODULE)
