CC = gcc
CFLAGS = -Wall -c
OFLAGS = -Wall -o
LIBFLAGS = -lssl -lcrypto

MAIN = main
MODULE1 = module1
MODULE2 = module2
TARGET = hash

main : $(SOURCE)
	$(CC) $(OFLAGS) $(TARGET) $(MAIN).c

module1 : $(MODULE1).c
	$(CC) $(CFLAGS) $(MODULE1).c $(LIBFLAGS)

module2 : $(MODULE2).c
	$(CC) $(CFLAGS) $(MODULE2).c $(LIBFLAGS)

full :
	$(CC) $(OFLAGS) $(TARGET) $(MAIN).c $(MODULE1).o $(MODULE2).o $(LIBFLAGS)

clean :
	rm -i $(TARGET)

crypto :
