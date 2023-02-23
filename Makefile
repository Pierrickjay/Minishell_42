#COLOR

RED            := '\033[0;31m'
GREEN        := '\033[0;32m'
YELLOW        := '\033[0;33m'
CYAN        := '\033[0;36m'
PURPLE        := '\033[0;35m'
OFF            := '\033[0m'

#VARIABLES

NAME        := minishell

#SRCS

SRCS_LIBFT_DIR := srcs/libft/

SRCS_LIBFT    := char/ft_isalnum.c char/ft_isalpha.c char/ft_isascii.c char/ft_isdigit.c \
            char/ft_isprint.c char/ft_tolower.c char/ft_toupper.c \
            conversion/ft_atoi.c conversion/ft_atoi_long.c conversion/ft_itoa.c \
            malloc/ft_calloc.c malloc/ft_split.c malloc/ft_strdup.c malloc/ft_strjoin.c malloc/ft_strmapi.c \
            malloc/ft_strtrim.c malloc/ft_substr.c mem/ft_bzero.c mem/ft_memchr.c mem/ft_memcmp.c \
            mem/ft_memcpy.c mem/ft_memmove.c mem/ft_memset.c \
            print/ft_putchar_fd.c print/ft_putendl_fd.c print/ft_putnbr_fd.c print/ft_putstr_fd.c \
            string/ft_strchr.c string/ft_striteri.c string/ft_strlcat.c string/ft_strlcpy.c \
            string/ft_strlen.c string/ft_strcmp.c string/ft_strncmp.c string/ft_strnstr.c string/ft_strrchr.c \
            gnl/get_next_line.c gnl/get_next_line_utils.c liste_chaine/ft_lstnew.c \
            liste_chaine/ft_lstadd_front.c liste_chaine/ft_lstsize.c liste_chaine/ft_lstlast.c \
            liste_chaine/ft_lstadd_back.c liste_chaine/ft_lstdelone.c liste_chaine/ft_lstclear.c \
            liste_chaine/ft_lstiter.c liste_chaine/ft_lstmap.c liste_chaine/ft_lstprint_type.c

SRCS_LIBFT    := ${addprefix ${SRCS_LIBFT_DIR},${SRCS_LIBFT}}

SRCS_DIR    := srcs/srcs_minishell/

SRCS        += main.c

SRCS        += parsing/utils_1.c parsing/set_signal.c parsing/free.c parsing/initiate_list.c parsing/for_the_trim.c \
				parsing/type.c parsing/quote.c parsing/utils_2.c

SRCS		+= execution/utils/free_1.c execution/utils/free_2.c execution/utils/open.c execution/utils/close.c execution/utils/here_doc.c \
			execution/exec.c execution/vars_1.c execution/vars_2.c execution/args.c execution/path.c execution/child_1.c execution/child_2.c \
			# execution/builtins.c execution/builtins/ft_cd.c execution/builtins/ft_echo.c execution/builtins/ft_env.c \
			# execution/builtins/ft_exit.c execution/builtins/ft_export.c execution/builtins/ft_pwd.c execution/builtins/ft_unset.c

SRCS    := ${addprefix ${SRCS_DIR},${SRCS}}

#OBJS & DEPS & LIB

LIB_DIR        := ./lib/

OBJS_DIR    := ./objs/

OBJS_LIBFT    := ${SRCS_LIBFT:.c=.o}

OBJS_LIBFT    := $(addprefix $(OBJS_DIR),$(OBJS_LIBFT))

OBJS        := $(SRCS:.c=.o)

OBJS        := $(addprefix $(OBJS_DIR),$(OBJS))

DEPS        := ${OBJS:.o=.d} ${OBJS_LIBFT:.o=.d}

#COMMANDS

AR            := ar rcs

CC            := cc

CFLAGS        := -Wall -Wextra -Werror -MMD -g3

RM            := rm -rf

MKDIR        := mkdir -p

#RULES

all            : ${NAME}

${NAME}            : ${OBJS_LIBFT} ${OBJS}
					@${MKDIR} ${LIB_DIR}
					@${AR} ${LIB_DIR}libft.a ${OBJS_LIBFT}
					@${CC} ${CFLAGS} ${OBJS} -L ${LIB_DIR} -lft -lreadline -o ${NAME}
					@echo ${NAME} ${GREEN}"done"${OFF}

clean            :
				@${RM} ${OBJS_DIR} ${LIB_DIR}
				@echo "All objects and library "${RED}"delete"${OFF}

fclean            : clean
				@${RM} ${NAME}
				@echo ${NAME} ${RED}"delete"${OFF}

re            : fclean all

.PHONY        : all clean fclean re test

#RECETTE

$(OBJS_DIR)%.o    : %.c
				@${MKDIR} $(@D)
				@${CC} ${CFLAGS} -c $< -o $@
				@echo "$@ "${GREEN}"done"${OFF}

-include $(DEPS)
