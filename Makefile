#COLOR

RED			:= '\033[0;31m'
GREEN		:= '\033[0;32m'
YELLOW		:= '\033[0;33m'
CYAN		:= '\033[0;36m'
PURPLE		:= '\033[0;35m'
OFF			:= '\033[0m'

#VARIABLES

NAME		:= minishell

SRCS_DIR	:= srcs/srcs_minishell/

SRCS		+= main.c

SRCS		+= parsing/main.c parsing/utils_1.c parsing/set_signal.c

SRCS		+= execution/utils/type.c execution/utils/free_1.c execution/utils/free_2.c execution/utils/open.c \
			execution/main.c execution/vars_1.c execution/vars_2.c execution/args.c execution/path.c execution/child.c \
			# execution/builtins.c execution/builtins/ft_cd.c execution/builtins/ft_echo.c execution/builtins/ft_env.c \
			# execution/builtins/ft_exit.c execution/builtins/ft_export.c execution/builtins/ft_pwd.c execution/builtins/ft_unset.c

SRCS		:= ${addprefix ${SRCS_DIR},${SRCS}}

OBJS_DIR	:= objs/

OBJS		:= $(SRCS:.c=.o)

OBJS		:= $(addprefix $(OBJS_DIR),$(OBJS))

DEPS		:= ${OBJS:.o=.d}

LIB_DIR		:= libs/

LIBFT_DIR	:= srcs/libft/

LIBFT		:= libft.a

MAKE_LIBFT	:= ${addprefix ${LIBFT_DIR},${LIBFT}}

LIB_LIBFT	:= ${addprefix ${LIB_DIR},${LIBFT}}

PIPEX		:= libminishell.a

LIB_PIPEX	:= ${addprefix ${LIB_DIR},${PIPEX}}

LIBS		:= ${LIB_PIPEX} ${LIB_LIBFT}

AR			:= ar rcs

CC			:= cc

CFLAGS		:= -Wall -Wextra -Werror -MMD -g3

RM			:= rm -rf

MV			:= mv -f

MKDIR		:= mkdir -p

#RULES

all			: ${NAME}

${NAME}		: ${OBJS}
			@${MKDIR} ${LIB_DIR}
			@make -C ${LIBFT_DIR}
			@${MV} ${MAKE_LIBFT} ${LIB_DIR}
			@${AR} ${LIB_PIPEX} ${OBJS}
			@echo ${PIPEX} ${GREEN}"done"${OFF}
			@${CC} ${CFLAGS} ${LIBS} -o ${NAME} -lreadline
			@echo ${NAME} ${GREEN}"done"${OFF}


clean		:
			@make clean -C ${LIBFT_DIR}
			@${RM} ${OBJS_DIR} ${LIB_DIR}
			@echo "All objects and library "${RED}"delete"${OFF}

fclean		: clean
			@${RM} ${NAME}
			@echo ${NAME} ${RED}"delete"${OFF}

re			: fclean all

.PHONY		: all clean fclean re test

#RECETTE

-include $(DEPS)

$(OBJS_DIR)%.o	: %.c
				@${MKDIR} $(@D)
	        	@${CC} ${CFLAGS} -c $< -o $@
				@echo "$@ "${GREEN}"done"${OFF}
