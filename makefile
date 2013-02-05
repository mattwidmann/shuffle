EXE = shuffle
SOURCES = shuffle.c

CC = clang
CFLAGS = -std=c11 -Wextra -pedantic -Werror

default: debug

$(EXE): shuffle.o

%.o: %.c %.d

.PHONY = debug release

debug: CFLAGS += -g
debug: CPPFLAGS += -DDEBUG
debug: shuffle

release: CPPFLAGS += -DNDEBUG
release: shuffle

.PHONY = clean

clean:
	rm -f *.o *.d shuffle

install: release
	cp $(EXE) ~/.bin/

include $(subst .c,.d,$(SOURCES))

%.d: %.c
	$(CC) $(CPPFLAGS) -MM -MG $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

