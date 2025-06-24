SRCDIR:=src/
INCDIR:=include/

CC:=gcc
C_FLAGS:=-W -Wextra -Wall -pedantic-errors -I$(INCDIR)

SRCFILES:=$(wildcard $(SRCDIR)*.c)

turtle: $(SRCFILES)
	$(CC) $(C_FLAGS) $(SRCFILES) -o turtle

debug: $(SRCFILES)
	$(CC) $(C_FLAGS) $(SRCFILES) -g -o turtle

clean: 
	@rm -f turtle
