CC := clang
LINK := clang

CFLAGS := -Wall -Wextra -pedantic -ggdb -Wno-gnu-zero-variadic-macro-arguments
LIBS := `pkg-config --libs glew glfw3`

SRC_DIR := ./src
OBJ_DIR := ./build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
BIN := ./triangle

.PHONY : all release clean

all : $(BIN)

release : CFLAGS += -D_BUILD_RELEASE
release : $(BIN)

$(BIN) : $(OBJ)
	$(LINK) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f $(BIN)
	rm -f $(OBJ)
