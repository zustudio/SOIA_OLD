########################################################################
# global makefile for SOIA
########################################################################

include Makefile.rules

all: $(OBJS)
	$(CC) -o $(BINDIR)SOIA.exe $^
	@echo -SOIAstd: link

$(BINDIR)%.obj: $(MAKES)%.cpp
	$(CC) $(INCLUDES) -c -o $@ $^
	@echo -SOIAstd: $@

clean:
	rm -rf $(BINDID)%.obj

