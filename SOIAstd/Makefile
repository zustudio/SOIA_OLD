########################################################################
# global makefile for SOIA
########################################################################

include make.config


all: $(OBJS)
ifeq ($(IDE),vs13)
	@cl -Zi -o $(EXEC) $^
else
	@$(CC) $(CFLAGS) -o $(EXEC) $^
	@echo -SOIAstd: link
endif

$(BINDIR)%.obj: $(MAKES)%.cpp
ifeq ($(IDE),vs13)
	@cl -Zi -c $^
	@mv $(subst $(BINDIR),,$@) $(BINDIR)
else
	@$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $^
	@echo -SOIAstd: $@
endif

rebuild:
	make clean
	make all

clean:
	rm -rf $(OBJS) $(EXEC)
ifeq ($(IDE),vs13)
	rm -rf $(subst .exe,.pdb,$(EXEC)) $(subst .exe,.ilk,$(EXEC))
endif

