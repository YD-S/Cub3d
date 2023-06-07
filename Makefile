
CC = gcc
CFLAGS = -Wall -Wextra -MD -g

NAME = cub3d
SRC_DIR = src
SRC = main.c map_parse.c paint_map.c hooks.c init.c raycast.c validate.c
BUILD_DIR = build
INCLUDE_DIR = includes
INCLUDES = -I ./$(INCLUDE_DIR) -I ./$(LIB_DIR)/libft/includes -I ./$(LIB_DIR)/MLX42/include
LIB_DIR = lib
LIBS = -L./$(LIB_DIR)
MLX = $(LIB_DIR)/MLX42/libmlx42.a
LIBFT = $(LIB_DIR)/libft/libft.a

ifeq ($(shell whoami), yash)
        BREW = /opt/homebrew/Cellar/glfw/3.3.8/lib/
else
        BREW = "/Users/$(USER)/.brew/opt/glfw/lib/"
endif


# Do not change these
SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_DIR = $(BUILD_DIR)/obj
OBJ = $(SRC:.c=.o)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(NAME)

-include $(OBJ_FILES:.o=.d)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[0;32mCompiling $<\033[0m"
	@mkdir -p $(basename $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_FILES)
	@make -C $(LIB_DIR)/MLX42/
	@make -C $(LIB_DIR)/libft
	@echo "\033[0;34mLinking $@\033[0m"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) $(MLX) -lglfw -L $(BREW) $(INCLUDES) -o $(BUILD_DIR)/$(NAME) $(LIBFT)
	@echo "\033[0;33mFinished building $@\033[0m"

clean:
	@echo "\033[0;31mDeleting $(OBJ_DIR)\033[0m"
	@make -C $(LIB_DIR)/MLX42/ fclean
	@make -C $(LIB_DIR)/libft/ fclean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "\033[0;31mDeleting $(BUILD_DIR)\033[0m"
	@make -C $(LIB_DIR)/MLX42/ fclean
	@make -C $(LIB_DIR)/libft/ fclean
	@rm -rf $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re
