########################################################################
# global makefile for SOIA
########################################################################

include Makefile.rules

# local definitions
BINDIR = Debug/
SRCDIR = src/

MAKES = src/Service/Console src/SysInterface

all:
	for i in $(MAKES); do make -C $$i; done
	$(CC) -o $(BINDIR)SOIA.exe \
		$(BINDIR)main.obj \
		$(BINDIR)ConsoleService.obj

clean:
	rm -rf $(BINDID)%.obj

