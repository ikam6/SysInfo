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
CMODULE = listDir.c PrintInfo.c
OMODULE = listDir.o PrintInfo.o
TARGET = ultra-cp

#program : $(MAIN)
	#$(CC) $(OFLAGS) $(TARGET) $(MAIN)
program : $(MAIN) $(OMODULE)
	$(CC) $(OFLAGS) $(TARGET) $(MAIN) $(OMODULE)

module : $(CMODULE)
	$(CC) $(CFLAGS) $(CMODULE)

clean :
	rm $(TARGET)
