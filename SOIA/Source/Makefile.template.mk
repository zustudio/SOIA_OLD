########################################################################
# makefile for every project
######################################################################## 

include Makefile.generated.mkcfg

$(eval $(foreach projectinclude,$(PROJECTINCLUDES),$(eval $(call include-public-modules,$(projectinclude)))))
$(eval $(call include-local-modules,null))
$(eval $(call set-object-dirs,null))

ifeq ($(def_IDE_VisualStudio),1)
	ECHOCMD := :
else
	ECHOCMD := echo 
endif


$(TARGET): $(OBJS)
	echo $(PROJECT_SUBDIR)$(PROJECT_NAME) \> Linking...
	$(LINKER) $(LINKER_ARG_FLAGS) $(LINKER_ARG_OUT) $^ $(LINKER_ARG_LIBS)
	@rm -rf /obj /Debug


define make-goal
$(1)%.obj: %.cpp
	$(ECHOCMD) $(PROJECT_SUBDIR)$(PROJECT_NAME) \> Compiling... $$(notdir $$<)
	gcc $(INCLUDES) $(GCC_CFLAGS) -MM -MF"$$(@:.obj=.d)" -MT$$(@) "$$<"
	$(CC) $(INCLUDES) $(CFLAGS) -c $(COMPILER_INFILE) $(COMPILER_OUTFILE)
endef



all: checkdirs $(TARGET)

checkdirs: $(OBJ_DIRS) $(BINARY_DIR)

$(OBJ_DIRS):
	@mkdir -p $@

$(BINARY_DIR):
	@mkdir -p $@

rebuild:
	make clean
	make all

clean:
	@rm -rf $(INTERMEDIATE_DIR) $(BINARY_DIR)
	@echo $(PROJECT_SUBDIR)$(PROJECT_NAME): Cleaned intermediate and binary folder.

-include $(OBJS:.obj=.d)

$(eval $(foreach mdir,$(OBJ_DIRS),$(eval $(call make-goal,$(mdir)))))
