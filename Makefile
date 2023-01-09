# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/07 04:53:46 by smiro             #+#    #+#              #

#                                                                              #
# **************************************************************************** #

################################################################################
### INIT
################################################################################

NAME		= miniRT
INC			= ./inc/
INC_HEADERS	= $(INC)minirt.h

FT_INC		= $(FT)/libft.h

FT			= $(INC)libft/
FT_LNK		= -L$(FT) -lft
FT_LIB		= $(FT)libft.a

SRC_DIR		= src/
OBJ_DIR		= obj/
LINKFLAGS	= -L. -lmlx -framework OpenGL -framework AppKit
CFLAGS		= -I $(INC) -MMD -Wall -Werror -Wextra -O3
RM			= rm -f

################################################################################
### COLORS
################################################################################

DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

################################################################################
### OBJECTS
################################################################################

SRC_FILES	=	main.c \
				parsing.c \
				parsing_la.c \
				error_manager.c \
				utils.c \
				init.c \
				parsing_cam.c \
				parsing_lp.c \
				draw.c \
				hooks.c \
				init_elem.c \
				parsing_sp.c \
				parsing_pl.c \
				parsing_cy.c \
				v_perspective.c \
				v_ray_intersections.c \
				v_shape_intersections.c \
				v_vectors.c \
				v_utils.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEP			= 	$(addsuffix .d, $(basename $(OBJ)))
B_OBJ		=	$(OBJ)

################################################################################
### RULES
################################################################################

all:
		@$(MAKE) -C $(FT)
		@echo "\n${ORANGE}Minilibx compilation $(DEF_COLOR)\n"
		@make -C ./mlx all
		@cp ./mlx/libmlx.dylib .
		@$(MAKE) $(NAME)

$(OBJ_DIR)%.o: %.c Makefile
			@mkdir -p $(dir $@)
			@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) $(LINKFLAGS) -o $(NAME)
			@echo "$(GREEN)\nCreated ${NAME} ✓$(DEF_COLOR)\n"

-include $(DEP)

bonus:		$(B_OBJ) $(NAME)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make -C ./mlx clean
			@make clean -C $(FT)
			@echo "\n${BLUE} ◎ $(RED)All objects cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f lib*.a
			@make fclean -C $(FT)
			@$(RM) -rf libmlx.dylib
			@echo "\n${BLUE} ◎ $(RED)All objects and executable cleaned successfully${BLUE} ◎$(DEF_COLOR)\n"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for fdf!$(DEF_COLOR)"

.PHONY:		all clean fclean re norm
