##############
#
# Compiler
#
##############
CC	= cc
CFLAGS	= -Wall -Wextra -Werror \
	-I$(INCDIR) \
	-I$(LIBDIR)/$(LIBMLXDIR) \
	-I$(LIBDIR)/$(LIBFTDIR) \
	-O2 \
	-DPROFILE \
	-DPROFILE_FPS \

CLFLAGS	= -lXext -lX11 -lm

##############
#
# Project files
#
##############
SRCDIR	= src
OBJDIR	= build
INCDIR	= src

OBJ	= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
NAME = miniRT
SRC	= core/core.c \
	  core/graphics.c \
	  core/graphics_render.c \
	  draw.c \
	  inputs.c \
	  timer.c \
	  render.c \
	  colors.c \
	  maths/maths.c \
	  maths/vec3.c \
	  maths/vec3_1.c \
	  ray.c \
	  camera.c \


##############
#
# Libraries
#
##############
LIBDIR	= lib
LIBMLXDIR	= minilibx-linux
LIBMLX	= $(LIBDIR)/$(LIBMLXDIR)/libmlx.a
LIBFTDIR	= 42-libft
LIBFT	= $(LIBDIR)/$(LIBFTDIR)/libft.a

##############
#
# Build
#
##############

.PHONY:	all clean fclean re

all:	$(NAME)

$(NAME): $(OBJ) $(LIBMLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(CLFLAGS)

clean:
	rm -rf $(OBJDIR)
	@make -sC $(LIBDIR)/$(LIBMLXDIR) clean
	@make -sC $(LIBDIR)/$(LIBFTDIR) clean

fclean:	clean
	rm -f $(NAME)
	@make -sC $(LIBDIR)/$(LIBFTDIR) fclean

re:	fclean all

#
# project srcs build
#
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

#
# libs build
#
$(LIBMLX):
	@make -sC $(LIBDIR)/$(LIBMLXDIR)

$(LIBFT):
	@make -sC $(LIBDIR)/$(LIBFTDIR)
