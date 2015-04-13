####################################################################
# global SOIA project makefile
####################################################################

PROJECT_DIRS := Environment/ Graphics/ Apprentice/ Supervisor/ Programs/UnitTest/ 

define make-project
@$(MAKE) -s -C $1 -f Makefile.generated.mk
endef

##################################################################
# Targets

.PHONY: all clean Environment Graphics Apprentice Supervisor UnitTest Documentation


# main targets
all: UnitTest

clean:
	@$(call make-project,Environment) clean
	@$(call make-project,Graphics) clean
	@$(call make-project,Apprentice) clean
	@$(call make-project,Supervisor) clean
	@$(call make-project,Programs/UnitTest) clean

rebuild: clean all

# individual projects
Environment: Makefiles
	$(call make-project,Environment) all

Graphics: Makefiles Environment
	$(call make-project,Graphics) all

Apprentice: Makefiles Environment
	$(call make-project,Apprentice) all

Supervisor: Makefiles Environment Graphics
	$(call make-project,Supervisor) all

UnitTest: Makefiles Environment Graphics Supervisor
	$(call make-project,Programs/UnitTest) all

# documentation
Documentation:
	rm -rf ../Documentation/GeneratedDocumentation
	cd ../Documentation/Doxygen && doxygen doxygen.cfg


MAKEFILES := $(addsuffix Makefile.generated.mk,$(PROJECT_DIRS)) $(addsuffix Makefile.generated.mkcfg,$(PROJECT_DIRS))

Makefiles: $(MAKEFILES)

define copy-files
$1Makefile.generated.mk: Makefile.template.mk
	cp $$< $$@
	@echo $(patsubst %/,%,$1): Copied $$(notdir $$@)
$1Makefile.generated.mkcfg: Makefile.template.mkcfg
	cp $$< $$@
	@echo $(patsubst %/,%,$1): Copied $$(notdir $$@)
endef

$(foreach pdir,$(PROJECT_DIRS),$(eval $(call copy-files,$(pdir))))