########################################################################
# global makefile for SOIA
########################################################################

include Makefile.rules

all: $(OBJS)
	$(CC) -o $(BINDIR)SOIA.exe $^

$(BINDIR)%.obj: $(MAKES)%.cpp
	$(CC) $(INCLUDES) -c -o $@ $^

clean:
	rm -rf $(BINDID)%.obj

