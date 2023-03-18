# COLOR

CLEAR		:= \e[0K

SRED		:= \033[0;31m
SGREEN		:= \033[0;32m
SYELLOW		:= \033[0;33m
SCYAN		:= \033[0;36m
SPURPLE		:= \033[0;35m
SOFF		:= \033[0m

RED			:= '\033[0;31m'
GREEN		:= '\033[0;32m'
YELLOW		:= '\033[0;33m'
CYAN		:= '\033[0;36m'
PURPLE		:= '\033[0;35m'
OFF			:= '\033[0m'

# VARIABLES

NAME			:= minishell

# SRCS

#  LIBFT

SRCS_LIBFT_DIR	:= srcs/libft/

SRCS_LIBFT		:= char/ft_isalnum.c char/ft_isalpha.c char/ft_isascii.c char/ft_isdigit.c \
				char/ft_isprint.c char/ft_tolower.c char/ft_toupper.c char/ft_all_isdigit.c \
				conversion/ft_atoi.c conversion/ft_atoi_long.c conversion/ft_itoa.c \
				malloc/ft_calloc.c malloc/ft_split.c malloc/ft_strdup.c malloc/ft_strjoin.c malloc/ft_strjoin_all.c malloc/ft_strmapi.c \
				malloc/ft_strtrim.c malloc/ft_substr.c mem/ft_bzero.c mem/ft_memchr.c mem/ft_memcmp.c \
				mem/ft_memcpy.c mem/ft_memmove.c mem/ft_memset.c \
				print/ft_putchar_fd.c print/ft_putendl_fd.c print/ft_putnbr_fd.c print/ft_putstr_fd.c \
				string/ft_strchr.c string/ft_striteri.c string/ft_strlcat.c string/ft_strlcpy.c \
				string/ft_strlen.c string/ft_strcmp.c string/ft_strncmp.c string/ft_strnstr.c string/ft_strrchr.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c liste_chaine/ft_lstnew.c \
				liste_chaine/ft_lstadd_front.c liste_chaine/ft_lstsize.c liste_chaine/ft_lstlast.c \
				liste_chaine/ft_lstadd_back.c liste_chaine/ft_lstdelone.c liste_chaine/ft_lstclear.c \
				liste_chaine/ft_lstiter.c liste_chaine/ft_lstmap.c liste_chaine/ft_lstprint_type.c \
				liste_chaine/ft_lstjoin.c

SRCS_LIBFT		:= ${addprefix ${SRCS_LIBFT_DIR},${SRCS_LIBFT}}

#  MINISHELL

SRCS_DIR	:= srcs/srcs_minishell/

SRCS		+= main.c boucle_minishell.c

#   pjay
SRCS        += parsing/utils/utils_1.c parsing/set_signal.c parsing/free.c parsing/initiate_list.c parsing/quote/for_the_trim.c \
				parsing/type.c parsing/quote/quote.c parsing/utils/utils_2.c parsing/utils/split_parsing.c parsing/utils/split_utils.c \
				parsing/exit_boucle.c parsing/quote/check_quote.c parsing/utils/new_string.c parsing/utils/new_string_utils.c \
				parsing/utils/separate_pipe.c parsing/check_pars.c parsing/block_signal.c parsing/quote/check_quote_2.c\

#   obouhlel
SRCS		+= execution/utils/free_1.c execution/utils/free_2.c execution/utils/free_3.c execution/utils/ft_msg.c \
			execution/utils/open.c execution/utils/close.c execution/utils/heredoc.c execution/utils/random.c execution/utils/utils.c \
			execution/env/ft_envi_add_back.c execution/env/ft_envi_last.c execution/env/ft_envi_new.c \
			execution/env/ft_envi_size.c execution/env/ft_envi_to_env.c execution/env/ft_env_to_envi.c \
			execution/env/ft_get_key.c execution/env/ft_get_value.c execution/env/ft_get_envi.c \
			execution/env/ft_get_env.c execution/env/ft_envi_update_value.c execution/env/ft_envi_print.c execution/env/ft_envi_null.c \
			execution/parent_1.c execution/parent_2.c execution/exec_1.c execution/exec_2.c execution/exec_3.c \
			execution/args.c execution/path.c execution/child_1.c execution/child_2.c \
			execution/expend_1.c execution/expend_2.c \
			execution/builtins.c execution/builtins/ft_pwd.c execution/builtins/ft_echo.c execution/builtins/ft_env.c \
			execution/builtins/ft_export.c execution/builtins/ft_cd.c execution/builtins/ft_cd_bis.c \
			execution/builtins/ft_unset.c execution/builtins/ft_exit.c

SRCS		:= ${addprefix ${SRCS_DIR},${SRCS}}

# OBJS & DEPS & LIB

LIB_DIR			:= ./lib/

OBJS_DIR		:= ./objs/

OBJS_LIBFT		:= ${SRCS_LIBFT:.c=.o}

OBJS_LIBFT		:= $(addprefix $(OBJS_DIR),$(OBJS_LIBFT))

OBJS			:= $(SRCS:.c=.o)

OBJS			:= $(addprefix $(OBJS_DIR),$(OBJS))

DEPS			:= ${OBJS:.o=.d} ${OBJS_LIBFT:.o=.d}

# PROGRESS BAR

NB_OBJS			= ${words ${OBJS}, ${OBJS_LIBFT}}

COUNTER			= 1

PROGRESS		= 0

DONE 			= 100

SPACE		 	= 0

FILL			= 0

EMPTY			= 0

define PROGRESS_BAR
	$(eval PROGRESS=$(shell echo $$(($(COUNTER) * 100 / $(NB_OBJS)))))
	$(eval DONE=$(shell echo $$(($(PROGRESS) * 30 / 100))))
	$(eval SPACE=$(shell echo $$((30 - $(DONE)))))
	$(eval FILL=$(shell printf "%*s" ${DONE} | sed 's/ /█/g'))
	$(eval EMPTY=$(shell printf "%*s" ${SPACE} | sed 's/ /█/g'))
	printf "\r${CLEAR}${SYELLOW}Compile : ${SGREEN}${FILL}${SRED}${EMPTY} ${SGREEN}%3d%%${SOFF} %s.c" ${PROGRESS} $1
	$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
endef

# COMMANDS

AR				:= ar rcs

CC				:= gcc

CFLAGS			:= -Wall -Wextra -Werror -MMD -g3

CFLAGS_DEBUG	:= -Wall -Wextra -Werror -MMD -g3 -fsanitize=address

RM				:= rm -rf

MKDIR			:= mkdir -p

# RULES

all		: ${NAME}

${NAME}	: ${OBJS_LIBFT} ${OBJS}
		@${MKDIR} ${LIB_DIR}
		@${AR} ${LIB_DIR}libft.a ${OBJS_LIBFT}
		@${CC} ${CFLAGS} ${OBJS} -L ${LIB_DIR} -lft -lreadline -o ${NAME}
		@printf "\r${CLEAR}${SCYAN}${NAME}${SOFF} ${SGREEN}✔${SOFF}\n"

run		: ${NAME}
		@./${NAME}

leak 	: fclean ${OBJS_LIBFT} ${OBJS}
		@${MKDIR} ${LIB_DIR}
		@${AR} ${LIB_DIR}libft.a ${OBJS_LIBFT}
		@${CC} ${CFLAGS} ${OBJS} -L ${LIB_DIR} -lft -lreadline -o ${NAME}
		@printf "\r${CLEAR}${SCYAN}${NAME}${SOFF} ${SGREEN}✔${SOFF}\n"
		@printf "${SYELLOW}WARNING\t${SRED}Le minishell va se lancer avec valgrind\n${SOFF}"
		@sleep 1
		@valgrind --leak-check=full --show-leak-kinds=all --suppressions=./.readline.supp --track-fds=yes ./minishell

debug	: fclean ${OBJS_LIBFT} ${OBJS}
		@${MKDIR} ${LIB_DIR}
		@${AR} ${LIB_DIR}libft.a ${OBJS_LIBFT}
		@${CC} ${CFLAGS_DEBUG} ${OBJS} -L ${LIB_DIR} -lft -lreadline -o ${NAME}
		@printf "\r${CLEAR}${SCYAN}${NAME} avec fsanitize${SOFF} ${SGREEN}✔${SOFF}\n"
		@printf "${SYELLOW}WARNING\t${SRED}Le minishell va se lancer sans l'environnement\n${SOFF}"
		@sleep 1
		@env -i ./minishell

clean	:
		@${RM} ${OBJS_DIR} ${LIB_DIR}
		@printf "${SCYAN}All objects and library ${SRED}delete ${SOFF}\n"

fclean	: clean
		@${RM} ${NAME}
		@printf "${SCYAN}${NAME}${SRED} delete${SOFF}\n"

re		: fclean all

.PHONY	: all clean fclean re test

# RECETTE

$(OBJS_DIR)%.o	: %.c
				@${MKDIR} $(@D)
				@${CC} ${CFLAGS} -c $< -o $@
				@$(call PROGRESS_BAR, $(basename $(notdir $<)))

-include $(DEPS)
