########################################################################
# makefile for every project
######################################################################## 

include Makefile.generated.mkcfg

$(eval $(foreach projectinclude,$(PROJECTINCLUDES),$(eval $(call include-public-modules,$(projectinclude)))))
$(eval $(call include-local-modules,null))
$(eval $(call set-object-dirs,null))


$(TARGET): $(OBJS)
	@echo $(PROJECT_SUBDIR)$(PROJECT_NAME) \> Linking...
	@$(GCCLINKER) $(GCCLINKER_ARG_FLAGS) $(GCCLINKER_ARG_OUT) $^ $(GCCLINKER_ARG_LIBS) 

define make-goal
$(1)%.obj: %.cpp
	@echo $(PROJECT_SUBDIR)$(PROJECT_NAME) \> Compiling... $$(notdir $$@)
	@$(CC) $(INCLUDES) $(CFLAGS) -c $$< -o $$@

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
	@rm -rf $(OBJS) $(TARGET) $(INTERMEDIATE_DIR) $(BINARY_DIR)
	@echo $(PROJECT_SUBDIR)$(PROJECT_NAME): Cleaned intermediate and binary folder.

-include $(OBJS:.obj=.d)

$(eval $(foreach mdir,$(OBJ_DIRS),$(eval $(call make-goal,$(mdir)))))
