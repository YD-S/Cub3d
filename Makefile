
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MD -g

NAME = cub3D
NAME_BONUS = cub3D_bonus
SRC_DIR = src
SRC_DIR_BONUS = bonus
SRC = main.c map_parse.c paint_map.c hooks.c init.c raycast.c validate.c map_utils.c parse_utils.c parse_utils2.c parse_utils3.c hooks_utils.c paint_map_utils.c paint_map_utils2.c validate_utils.c conditions.c conditions2.c raycast_utils.c check_horizontal.c check_vertical.c projection.c
SRC_BONUS = main_bonus.c map_parse_bonus.c paint_map_bonus.c hooks_bonus.c init_bonus.c raycast_bonus.c validate_bonus.c map_utils_bonus.c parse_utils_bonus.c parse_utils2_bonus.c parse_utils3_bonus.c hooks_utils_bonus.c paint_map_utils_bonus.c paint_map_utils2_bonus.c validate_utils_bonus.c conditions_bonus.c conditions2_bonus.c raycast_utils_bonus.c check_horizontal_bonus.c check_vertical_bonus.c projection_bonus.c
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

SRC_FILES_BONUS = $(addprefix $(SRC_DIR_BONUS)/, $(SRC_BONUS))
OBJ_DIR_BONUS = $(BUILD_DIR)/obj
OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ_FILES_BONUS = $(addprefix $(OBJ_DIR_BONUS)/, $(OBJ_BONUS))

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

bonus: $(NAME_BONUS)

-include $(OBJ_FILES_BONUS:.o=.d)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@echo "\033[0;32mCompiling $<\033[0m"
	@mkdir -p $(basename $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME_BONUS): $(OBJ_FILES_BONUS)
	@make -C $(LIB_DIR)/MLX42/
	@make -C $(LIB_DIR)/libft
	@echo "\033[0;34mLinking $@\033[0m"
	@$(CC) $(CFLAGS) $(OBJ_FILES_BONUS) $(LIBS) $(MLX) -lglfw -L $(BREW) $(INCLUDES) -o $(BUILD_DIR)/$(NAME_BONUS) $(LIBFT)
	@echo "\033[0;33mFinished building $@\033[0m"
clean:
	@echo "\033[0;31mDeleting $(OBJ_DIR)\033[0m"
	@make -C $(LIB_DIR)/MLX42/ fclean
	@make -C $(LIB_DIR)/libft/ fclean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)

fclean: clean
	@echo "\033[0;31mDeleting $(BUILD_DIR)\033[0m"
	@make -C $(LIB_DIR)/MLX42/ fclean
	@make -C $(LIB_DIR)/libft/ fclean
	@rm -rf $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
