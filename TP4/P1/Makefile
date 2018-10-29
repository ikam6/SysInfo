# /*--------------------------------------------------------/
#     Code fait par :
#     Lienhard Alexia
#     et
#     Smiljkovic Marko
# /--------------------------------------------------------*/

CC = gcc
CFLAGS = -c # -Wall avant le -c (pour voir tous les warnings)

OFLAGS = -o # -Wall avant le -o (pour voir tous les warnings)

MAIN = main.c
CMODULE = listDir.c PrintInfo.c
OMODULE = listDir.o PrintInfo.o
HMODULE = listDir.h PrintInfo.h
TARGET = ultra-cp


program : $(OMODULE) main.o
	$(CC) $(OMODULE) main.o $(OFLAGS) $(TARGET)

main.o : $(MAIN) $(HMODULE)
	$(CC) $(CFLAGS) $(MAIN) $(OFLAGS) main.o

$(OMODULE) : $(CMODULE)
	$(CC) $(CFLAGS) $(CMODULE)

clean :
	rm $(TARGET) *.o
