MPY_CROSS=../micropython/mpy-cross/build/mpy-cross
BUILD=gen
SRC_PY = \
    kernel.py

OBJ = $(addprefix $(BUILD)/, $(SRC_PY:.py=.mpy))

all: $(OBJ)

$(BUILD)/%.mpy: %.py
	echo "MPY $<"
	$(MPY_CROSS) -o $@ $<