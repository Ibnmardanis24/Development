# INFO: Include this at the end of each Makefile in individual SUBDIRS

# Directories paths

# define binaries for CXX-compiler, linker and the archive program
CC = g++
LD = ld
AR = ar

OS = $(shell uname)
# switch output directory based on Operating System
# Pointers are truncated to 32-bit in Snow Leopard for some weird reason. So switch to -m32
ifeq ($(OS), Darwin) # MAC OS X
	OBJDIR = $(OUTDIR)/mac
	#CXXFLAGS += -m32
	#LDFLAGS += -m32
else
ifeq ($(OS), Linux) # Linux
	OBJDIR = $(OUTDIR)/linux
endif
endif

CXXFLAGS_DEBUG += -g -Wall
CXXFLAGS_OPT += -O2
CXXFLAGS += -fPIC

# if debug is not the target, define 'opt' flags for compilation
ifeq ($(filter  debug,$(MAKECMDGOALS)),)
CXXFLAGS += $(CXXFLAGS_OPT)
endif

ifdef LIBNAME_MT
CXXFLAGS_MT += -pthread
CXXFLAGS_MT += -D_MULTI_THREADED_
LDFLAGS_MT += -lpthread
endif

ARFLAGS += 

# define INCLUDE paths and files
INCLUDE += 

# define dependent libraries and paths
LIBS +=



# object files and binaries are created in 'linux_x86' folders within their respective SUBDIRS
SRCDIR = src
OUTDIR = out
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
OBJS_MT = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%_mt.o, $(SRCS))

.PHONY: $(SUBDIRS) $(TEST_SUBDIRS)


# Recursively build object files from C++ source files in current directory and subdirectories defined earlier
# if LIBNAME is defined, build an archive(static library)
# Else just build object files
# NOTE: 'all' target has a :: so it can be 'overridden' in child makefiles - define all:: target in child makefiles to execute both targets
all:: libs tests

libs: $(OBJS) $(SUBDIRS) $(LIBNAME) $(LIBNAME_MT)

$(LIBNAME): | $(OBJDIR) 
ifneq "$(LIBNAME)" ""
	$(AR) rcs $(OBJDIR)/lib$(LIBNAME).a $(OBJS)
ifeq ($(OS), Darwin)  # Mac OS El capitan and higher use clang by default - switch to clang command line
	#$(CC) -shared -fPIC -dylib -flat_namespace -undefined suppress -o $(OBJDIR)/lib$(LIBNAME).dylib $(OBJS) -lgcc $(LDFLAGS)
	$(CC) -shared -fPIC -dynamiclib -flat_namespace -undefined suppress -o $(OBJDIR)/lib$(LIBNAME).dylib $(OBJS) $(LDFLAGS)
else
ifeq ($(OS), Linux)
	$(CC) -shared -o $(OBJDIR)/lib$(LIBNAME).so $(LDFLAGS) -Wl,--whole-archive $(OBJDIR)/lib$(LIBNAME).a -Wl,--no-whole-archive
	cp -f $(OBJDIR)/lib$(LIBNAME).so $(BASE_DIR)/$(OBJDIR)/lib$(LIBNAME).so
else
	@echo 'Unknown Operating System'
	exit 1;
endif
endif
endif # end ifneq "$(LIBNAME)" ""

$(LIBNAME_MT): | $(OBJDIR) 
ifneq "$(LIBNAME_MT)" ""
	$(AR) rcs $(OBJDIR)/lib$(LIBNAME_MT).a $(OBJS_MT)
ifeq ($(OS), Darwin) 
	#$(CC) -shared -fPIC -dylib -flat_namespace -undefined suppress -o $(OBJDIR)/lib$(LIBNAME_MT).dylib $(OBJS_MT) -lgcc $(LDFLAGS) $(LDFLAGS_MT)
	$(CC) -shared -fPIC -dynamiclib -flat_namespace -undefined suppress -o $(OBJDIR)/lib$(LIBNAME_MT).dylib $(OBJS_MT) $(LDFLAGS) $(LDFLAGS_MT)
else
ifeq ($(OS), Linux)
	$(CC) -shared -o $(OBJDIR)/lib$(LIBNAME_MT).so $(LDFLAGS) $(LDFLAGS_MT) -Wl,--whole-archive $(OBJDIR)/lib$(LIBNAME_MT).a -Wl,--no-whole-archive
	cp -f $(OBJDIR)/lib$(LIBNAME_MT).so $(BASE_DIR)/$(OBJDIR)/lib$(LIBNAME_MT).so
else
	@echo 'Unknown Operating System'
	exit 1;
endif
endif
endif # end ifneq "$(LIBNAME)" ""

exe: 
ifneq "$(EXE)" ""
	$(CC) $(CXXFLAGS) $(INCLUDE) $< -o $(OBJDIR)/$(EXE) $(LDFLAGS) 
endif # end ifneq "$(EXE)" ""


# Build for a given sub-directory	
$(SUBDIRS): 
	@if [ -d `pwd`/$@ ] ; \
    then \
        $(MAKE) $(MKFLG) -C $@ MWD=$(MWD)$@/ $(MAKECMDGOALS); \
    else \
        echo "<$@>: No such directory!"; \
		exit 1; \
    fi


# Build object files from C sources in the current working directory	
$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CXXFLAGS) $(INCLUDE) $(TEST_INCLUDE) -c $< -o $@

# Build MT versions of the object files
	$(CC) $(CXXFLAGS) $(CXXFLAGS_MT) $(INCLUDE) $(TEST_INCLUDE) -c $< -o $(basename $@)_mt.o


$(OBJDIR): 
	mkdir -p $@

debug: CXXFLAGS+=$(CXXFLAGS_DEBUG)
ifeq "$(filter-out debug, $(MAKECMDGOALS))" ""
debug: all
else
debug: $(filter-out debug, $(MAKECMDGOALS))
endif

# 'opt' CXXFLAGS are on by default if debug isn't defined
ifeq "$(filter-out opt, $(MAKECMDGOALS))" ""
opt: all
else
opt: $(filter-out opt, $(MAKECMDGOALS))
endif


# find all 'linux_x86' folders created and delete them
clean: $(SUBDIRS) $(TEST_SUBDIRS) 
	rm -rf $(OBJDIR)

# Clean the object files generated for this system
cleanobj: $(SUBDIRS) $(TEST_SUBDIRS)
	rm -rf $(OBJDIR)/*.o

# Clean everything ever compiled.
cleanall: $(SUBDIRS) $(TEST_SUBDIRS)
	rm -rf $(OUTDIR)

include $(BASE_DIR)/build/Makefile.test.inc
