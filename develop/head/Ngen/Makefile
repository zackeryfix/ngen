# build env
SHARED 	   = .so
DEBUG      = -D__DEBUG__

# project properties
PROJECT 	= Ngen
PROJECTVER	= 0.3
MAINTAINER	= zackeryfix@gmail.com

# project library references
REFRENCES 	= 

# project files & directories
OUTPUT_DIR	= ../bin
OUTPUT_EXT	= $(SHARED)
IMPORT_DIRs	= ../lib
EXPORT_DIR	= ../bin/lib
HEADER_DIRs	= include
SOURCE_DIR	= .
OBJECT_DIR	= obj


# files path resoultion
OUTPUT_FILE	= $(OUTPUT_DIR)/$(PROJECT)$(OUTPUT_EXT)
EXPORT_FILE	= $(EXPORT_DIR)/lib$(PROJECT).def
STATIC_FILE	= $(EXPORT_DIR)/lib$(PROJECT).a
HEADERS		= $(ls $(HEADER_DIR)/*.hpp)
SOURCES		= $(ls $(SOURCE_DIR)/*.cpp)
OBJECTS		= $(ls $(OBJECT_DIR)/*.o)
LIBRARIES	= $(patsubst %, -L%, $(REFRENCES)) -static-libgcc

OBJ_FILENAME	= $(patsubst $(OBJECT_DIR)/%.hpp, %, $(OBJECTS))
HPP_FILENAME	= $(patsubst $(HEADER_DIR)/%.hpp, %, $(HEADERS))
CPP_FILENAME	= $(patsubst $(SOURCE_DIR)/%.hpp, %, $(SOURCES))

# common commands
COMPILER	= g++
FLAGS		= -D__DEBUG__
RM		= rm -f
LD		= ld
ASM		= as
LS		= ls

# compiler options
COMPILER_FLAGS	= $(DEBUG) -I$(HEADER_DIR) -std=c++11 -g3


SRCS	= ./*.cpp
OBJ	= obj/*.o
LIBS	= -static-libgcc
INCS     = -I"include"
CXXINCS  = -I"include"
BIN      = ../bin/$(PROJECTID).so
CXXFLAGS = $(CXXINCS) -std=c++11 -g3
CFLAGS   = $(INCS)-std=c++11 -g3
RM       = rm -f
DEF      = ../bin/lib$(PROJECTID).def
STATIC   = ../bin/lib$(PROJECTID).a


pre-make:

all: pre-make %

clean:
	$(RM) $(OBJ) $(BIN) $(DEF) $(STATIC)

$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(COMPILER) -c -o $@ $< $(COMPILER_FLAGS)

debug: $(OBJ)
	$(CPP) -shared $(OBJ) -o $(BIN) $(LIBS) -Wl,--output-def,$(DEF),--out-implib,$(STATIC),--add-stdcall-alias

$(OBJ) : $(SRCS)
	$(CPP) -c Ngen.Delegate.cpp -o obj/Ngen.Delegate.o $(CXXFLAGS)

