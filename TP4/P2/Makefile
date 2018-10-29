# /*--------------------------------------------------------/
#     Code fait par :
#     Lienhard Alexia
#     et
#     Smiljkovic Marko
# /--------------------------------------------------------*/

CC = gcc
CFLAGS = -c # -Wall avant le -c (pour voir tous les warnings)
OFLAGS = -o # -Wall avant le -c (pour voir tous les warnings)
# LIBFLAGS = -lssl -lcrypto

MAIN = main.c
CMODULE = list.c PrintInfo.c copyDir.c
OMODULE = list.o PrintInfo.o copyDir.o
TARGET = ultra-cp

#program : $(MAIN)
	#$(CC) $(OFLAGS) $(TARGET) $(MAIN)
program : $(MAIN) $(OMODULE)
	$(CC) $(OFLAGS) $(TARGET) $(MAIN) $(OMODULE)

module : $(CMODULE)
	$(CC) $(CFLAGS) $(CMODULE)

clean :
	rm $(TARGET) $(OMODULE)
