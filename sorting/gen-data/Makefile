PKG = gen-data
CC = g++
OBJS = gen-data.o mersenne.o
SRC = gen-data.cpp mersenne.cpp
CFLAGS = -O2 -c -Wall

all: $(PKG)

$(PKG): $(OBJS)
	$(CC) $(OBJS) -o $(PKG)
$(OBJS): $(SRC)
	 $(CC) $(CFLAGS) $(SRC)

clean:
	rm -f $(OBJS) $(PKG)
	rm -f reverse* random-*

.PHONY: all clean
