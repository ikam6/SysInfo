CC = gcc
CFLAGS = -Wall -c
OFLAGS = -Wall -o
LIBFLAGS = -lssl -lcrypto

MAIN = main
MODULE1 = module1
MODULE2 = module2
TARGET = outtest

main : $(SOURCE)
	$(CC) $(OFLAGS) $(TARGET) $(MAIN).c

module1 : $(MODULE1).c
	$(CC) $(CFLAGS) $(MODULE1).c

module2 : $(MODULE2).c
	$(CC) $(CFLAGS) $(MODULE2).c

full :
	$(CC) $(OFLAGS) $(TARGET) $(MODULE1).o $(MODULE2).o

clean :
	rm -i $(TARGET)

crypto :
