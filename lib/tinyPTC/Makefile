######################################################################
### MACROS
######################################################################

# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

# $(1) : Source file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# $(1) : Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

######################################################################
### CONFIG
######################################################################
UNAME   	:= $(shell uname)
APP 		:= libtinyptc.a
CFLAGS 		:= -Wall -Wextra -pedantic
CPPFLAGS	:= $(CFLAGS) -std=c++14
CPP			:= g++
C			:= gcc
AR			:= ar
ARFLAGS		:= -crs
RANLIB		:= ranlib
MKDIR		:= mkdir -p
SRC			:= src
OBJ			:= obj
RM			:= rm

ifeq ($(UNAME),Linux)
	OS := linux
else 
   OS := windows
endif

ifdef CROSSWIN
	C:=x86_64-w64-mingw32-gcc
	CPP:=x86_64-w64-mingw32-g++
	AR:=x86_64-w64-mingw32-ar
	RANLIB:=x86_64-w64-mingw32-ranlib
	OS:=windows
endif

ifdef DEBUG
   CPPFLAGS += -g 
	CPPFLAGS += -g
   CPPFLAGS += -g 
	CFLAGS  += -g
else ifdef SANITIZE
	CPPFLAGS += -fsanitize=address -fno-omit-frame-pointer -O1 -g
	CFLAGS  += -fsanitize=address -fno-omit-frame-pointer -O1 -g
else 
   CPPFLAGS += -O3
   CFLAGS  += -O3
endif

ALLCPPS		:= $(shell find $(SRC)/$(OS) -type f -iname *.cpp)
ALLCS		:= $(shell find $(SRC)/$(OS) -type f -iname *.c)
ALLOBJ		:= $(foreach F,$(ALLCS) $(ALLCPPS),$(call C2O,$(F)))
SUBDIRS		:= $(shell find $(SRC) -type d)
OBJSUBDIRS	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

# Generate library
$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)

# Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CPP),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CPPFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))

$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

.PHONY: info

info:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))
	$(info $(ALLCPPSOBJ))

# Clean rules
clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) ./$(APP)
