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
APP 		:= libpicopng.a
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
rm			:= rm

ifdef DEBUG
	CPPFLAGS += -g
else
	CPPFLAGS += -O3
endif

ALLCPPS		:= $(shell find $(SRC) -type f -iname *.cpp)
ALLCS		:= $(shell find $(SRC) -type f -iname *.c)
ALLOBJ		:= $(foreach F,$(ALLCS) $(ALLCPPS),$(call C20,$(F)))
SUBDIRS		:= $(shell find $(SRC) -type d)
OBJSUBDIRS	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

# Generate library
$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)

# Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CPP),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CPPFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))

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
