NAME = cub3d

CC = gcc
CFLAGS += -Wall -Wextra -Werror
MFLAGS = mlx_linux -03
DFLAGS = -fsanitize=address -g
LINK_FLAGS = -L$(MDIR) -lmlx -L$(LDIR) -lft -lXext -lX11 -lm -lbsd

ODIR = objs
SDIR = src
HDIR = src/headers/
MDIR = libs/minilibx-linux
LDIR = libs/libft

MLX_WRP_DIR = ressources/mlx_wrapper/
MLX_WRAPPER = $(MLX_WRP_DIR)mlx_wrapper.a

A = src/checker/
D = src/display/
U = src/utils/
E = src/events/
S = src/setup/
R = src/cast/
F = src/fct_wrapper/

UTILS = $(U)libft.c $(U)string_array_dup.c $(U)string_array_find_last.c \
		$(U)string_array_find.c $(U)string_array_join.c $(U)string_array_match.c \
		$(U)string_array_slice.c $(U)string_array_sort.c $(U)string_array.c $(U)string.c \
		$(U)ft_split_str.c $(U)libft2.c
CHECKER = $(A)check_data.c $(A)check_colors.c $(A)check_map.c
DISPLAY = $(D)pixel_put.c
EVENTS = $(E)keyboard.c $(E)mouse.c $(E)engine.c $(E)menu.c $(E)events_checkers.c
SETUP = $(S)setup_game.c $(S)exit.c $(S)map_parse.c \
		$(S)parse_metadata.c $(S)map_parse_utils.c $(S)init_textures.c \
		$(S)read_file.c $(S)adjust_off_bounds.c
CASTING = $(R)raycaster.c $(R)draw_lines.c $(R)menu.c $(R)draw_shapes.c \
		$(R)raycast_computing.c $(R)draw_textures.c
FCT_WRAPPER = $(F)draw_wall_column.c $(F)ray_tools.c

INCLUDES = -I$(LDIR) -I$(HDIR) -I$(MDIR)

SRCS = $(SDIR)/main.c $(UTILS) $(CHECKER) $(DISPLAY) $(EVENTS) $(SETUP) $(CASTING)
OBJS = $(SRCS:.c=.o)
OBJS := $(patsubst $(SDIR)/%, $(ODIR)/%, $(OBJS))

$(MLX_WRAPPER):
	make -C $(MLX_WRP_DIR) PLATFORM=$(PLATFORM) --no-print-directory

all: $(ODIR) libs $(NAME)
	@echo "DOOOOM"

$(NAME): $(OBJS) $(MLX_WRAPPER)
	$(CC) $(CFLAGS) $(MLX_WRAPPER) $(OBJS) -o $@ $(LINK_FLAGS)

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(ODIR):
	@mkdir -p $(ODIR)

libs:
	@make -C $(MDIR)
	@make -C $(LDIR)

clean:
	@rm -rf $(ODIR)
	make -C $(MLX_WRP_DIR) clean
	@make -C $(MDIR) clean
	@make -C $(LDIR) clean
	@echo "Cleaned objects and libraries."

fclean: clean
	@rm -f $(NAME)
	@echo "Fully cleaned."

re: fclean all

dbug: CFLAGS += $(DFLAGS)
dbug: re

.PHONY: all clean fclean re dbug libs
