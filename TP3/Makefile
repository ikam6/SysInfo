# /*--------------------------------------------------------/
#     Code fait par :
#     Lienhard Alexia
#     et
#     Smiljkovic Marko
# /--------------------------------------------------------*/

CC = gcc
CFLAGS = -c # -Wall avant le -c (pour voir tous les warnings)
OFLAGS = -o # -Wall avant le -c (pour voir tous les warnings)
LIBFLAGS = -lssl -lcrypto

MAIN = main.c
CMODULE = module1.c module2.c
OMODULE = module1.o module2.o
TARGET = hash

program : $(MAIN) $(OMODULE)
	$(CC) $(OFLAGS) $(TARGET) $(MAIN) $(OMODULE) $(LIBFLAGS)

module : $(CMODULE)
	$(CC) $(CFLAGS) $(CMODULE) $(LIBFLAGS)

clean :
	rm $(TARGET) $(OMODULE)
