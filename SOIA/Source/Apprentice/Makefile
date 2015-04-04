########################################################################
# makefile for Apprentice AI project
########################################################################

include Make.cfg

##################################################
# CC / FLAGS
CC = g++
CFLAGS = -m64 -g -std=gnu++11 -pthread -fpermissive -w -Lc:/MinGW/lib -isystemC:\MinGW\include\c++\4.8.2 -isystemC:\MinGW\include\c++\4.8.2\backward -isystemC:\MinGW\include\c++\4.8.2\x86_64-w64-mingw32 -isystemC:\MinGW\mingw\include -isystemC:\MinGW\lib64\gcc\x86_64-w64-mingw32\4.8.2\include -isystemC:\MinGW\lib64\gcc\x86_64-w64-mingw32\4.8.2\include-fixed -D def_CCGCC
CLFLAGS = -Zi -nologo -EHsc -Ddef_CCCL -Od
##################################################

all: checkdirs testbuild/Apprentice.dll
	echo $(BUILD_DIR)

testbuild/Apprentice.dll: $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(EXEC) $^ $(LIBS)
	echo -SOIAstd: link

define make-goal
$1/%.obj: %.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c $$< -o $$@
endef

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@




#$(BUILD_DIR)/%.obj: %.cpp
#	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<
#	echo -SOIAstd: $@

rebuild:
	make clean
	make all

clean:
	rm -rf $(OBJS) $(EXEC)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))