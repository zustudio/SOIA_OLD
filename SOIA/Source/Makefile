####################################################################
# global SOIA project makefile
####################################################################

all:
	@echo global: make all
	@echo –SOIAstd: make all
	@$(MAKE) -s -C SOIAstd/

clean:
	$(MAKE) -f Environment/Makefile clean
	$(MAKE) -f Programs/UnitTest/Makefile clean

Environment.dll:
	$(MAKE) -f Environment/Makefile

UnitTest: Environment.dll
	$(MAKE) -f Programs/UnitTest/Makefile