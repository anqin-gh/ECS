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
define C20
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# $(1) : Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

######################################################################
### CONFIG
######################################################################
APP 		:= game
CFLAGS 		:= -Wall -Wextra -pedantic
CPPFLAGS	:= $(CFLAGS) -std=c++17
CPP			:= g++
C			:= gcc
MKDIR		:= mkdir -p
SRC			:= src
OBJ			:= obj
LIBDIR		:= lib
LIBS		:= $(LIBDIR)/picoPNG/libpicopng.a $(LIBDIR)/tinyPTC/libtinyptc.a -lX11
INCDIRS		:= -I$(SRC) -I$(LIBDIR)

ifdef DEBUG
	CPPFLAGS += -g -DDEBUG
else
	CPPFLAGS += -O3
endif

ALLCPPS		:= $(shell find $(SRC) -type f -iname *.cpp)
ALLCS		:= $(shell find $(SRC) -type f -iname *.c)
ALLOBJ		:= $(foreach F,$(ALLCS) $(ALLCPPS),$(call C20,$(F)))
SUBDIRS		:= $(shell find $(SRC) -type d)
OBJSUBDIRS	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CPP) -o $(APP) $(ALLOBJ) $(LIBS)

# Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CPP),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CPPFLAGS) $(INCDIRS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))

$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

.PHONY: info clean cleanall libs libs-clean libs-cleanall

info :
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLOBJ))

# Clean rules
clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) ./$(APP)

# Lib rules
libs:
	$(MAKE) -C $(LIBDIR) all

libs-clean:
	$(MAKE) -C $(LIBDIR) clean

libs-cleanall:
	$(MAKE) -C $(LIBDIR) cleanall