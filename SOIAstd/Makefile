########################################################################
# global makefile for SOIA
########################################################################

include make.cfg


all: $(OBJS)
ifeq ($(IDE),vs13)
	cl $(CLFLAGS) -Fe$(EXEC) $^ user32.lib gdi32.lib
else
	@$(CC) $(CFLAGS) -o $(EXEC) $^ $(LIBS)
	@echo -SOIAstd: link
endif

$(BINDIR)%.obj: %.cpp
ifeq ($(IDE),vs13)
	@cl $(CLFLAGS) -c $^
	@mv $(subst $(BINDIR),,$@) $(BINDIR)
else
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $^
	@echo -SOIAstd: $@
endif

%.cpp: %.h

rebuild:
	make clean
	make all

clean:
	rm -rf $(OBJS) $(EXEC)
ifeq ($(IDE),vs13)
	rm -rf $(subst .exe,.pdb,$(EXEC)) $(subst .exe,.ilk,$(EXEC))
endif

