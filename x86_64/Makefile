include ../../py/mkenv.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# MicroPython feature configurations
# MICROPY_ROM_TEXT_COMPRESSION ?= 1

# include py core make definitions
include $(TOP)/py/py.mk

INC += -I.
INC += -I$(TOP)
INC += -I$(BUILD)

#  -mcmodel=large  
# Werror
# -mno-red-zone -mno-mmx -mno-sse -mno-sse2
CFLAGS += $(INC) -m32 -Wall -std=c99 -nostdlib -ffreestanding  $(COPT)
LDFLAGS +=  -m elf_i386 -nostdlib -T x86_64.ld # -Map=$@.map --cref --gc-sections
ASFLAGS  += -m32
# Tune for Debugging or Optimization
# CFLAGS += -g 
CFLAGS += -O0 -DNDEBUG
#CFLAGS += -fdata-sections -ffunction-sections

# Flags for optional C++ source code
CXXFLAGS += $(filter-out -std=c99,$(CFLAGS))

LIBS = 

SRC_S = boot.S

SRC_C = \
	main.c \
	mphalport.c \
	shared/libc/printf.c \
	shared/readline/readline.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \
 	$(BUILD)/_frozen_mpy.c \
	shared/libc/string0.c

SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c

OBJ += $(PY_CORE_O)
OBJ += $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_CXX:.cpp=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_S:.S=.o))

all: $(BUILD)/firmware.elf

$(BUILD)/%.o: %.S
	$(ECHO) "AS $<"
	$(Q)$(CC) $(ASFLAGS) -c -o $@ $<

$(BUILD)/%.S: %.c
	$(ECHO) "CC->ASM $<"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/_frozen_mpy.c: $(TOP)/../kernel/gen/kernel.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@
	
$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

include $(TOP)/py/mkrules.mk
