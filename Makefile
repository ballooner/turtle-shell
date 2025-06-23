SRCDIR:=src/
INCDIR:=include/

CC:=gcc
C_FLAGS:=-W -Wextra -Wall -pedantic-errors -I$(INCDIR)

SRCFILES:=$(wildcard $(SRCDIR)*.c)

turtle: $(SRCFILES)
	$(CC) $(C_FLAGS) $(SRCFILES) -o turtle

clean: 
	@rm -f turtle
