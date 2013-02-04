SOURCES = shuffle.c
CC = clang
CFLAGS = -Wextra -pedantic -Werror

default: debug

shuffle: shuffle.o

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

include $(subst .c,.d,$(SOURCES))

%.d: %.c
	$(CC) $(CPPFLAGS) -MM -MG $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

