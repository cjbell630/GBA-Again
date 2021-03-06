#
# key_demo.mak
#
# Makefile for key demonstration
#
# NOTE: for educational purposes only. For real work, use 
# devkitPro's templates ( $(DEVKITPRO)/examples/gba/template )
# or tonclib's templates ( $(TONCCODE)/lab/template )

PATH := $(DEVKITARM)/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := my_obj_test
TITLE   := $(PROJ)

COBJS   := source/my_obj_test.o include/toolbox.o images/metr.o

SOBJS   := include/debug.o

OBJS	:= $(COBJS) $(SOBJS)

# --- boot type (MB=0 : normal. MB=1 : multiboot) ---

MB = 0

ifeq ($(MB),1)

TARGET	:= $(PROJ).mb
SPECS	:= -specs=gba_mb.specs

else

TARGET	:= $(PROJ)
SPECS	:= -specs=gba.specs

endif

# --- Compiling -------------------------------------------------------

CROSS	?= arm-none-eabi-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc
OBJCOPY	:= $(CROSS)objcopy


ARCH	:= -mthumb-interwork -mthumb

ASFLAGS	:= -mthumb-interwork
CFLAGS	:= $(ARCH) -O2 -Wall -fno-strict-aliasing
LDFLAGS	:= $(ARCH) $(SPECS)

.PHONY : build clean

# --- Build -----------------------------------------------------------

build : $(TARGET).gba


$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(TITLE)

$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

$(COBJS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for assembling .s -> .o files
$(SOBJ) : %.o : %.s
	$(AS) $(ASFLAGS) -c $< -o $@
# --- Clean -----------------------------------------------------------

clean : 
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o

#EOF
