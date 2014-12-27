PKG = quadratic-sort-algos
CC = g++
OBJS = $(PKG).o
SRC = $(PKG).cpp
CFLAGS = -O2 -c -Wall

all: $(PKG)

$(PKG): $(OBJS)
	$(CC) $(OBJS) -o $(PKG)

$(OBJS): $(SRC)
	 $(CC) $(CFLAGS) $(SRC)

clean:
	rm -f $(OBJS) $(PKG)

.PHONY: all clean
