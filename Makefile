
# COMPILATION
CC				= gcc 
FLAGS			= -Wall -Werror -Wextra -g

# EXECUTABLE
NAME		= ft_ls

# PATH
SRCS_PATH	= srcs
OBJS_PATH	= objs
INC_PATH	= -I incl

	### SOURCES FILES ###
FILES		= main.c \
			  list_utils.c \
			  utils.c \
			  init_main_struct.c \
			  exit.c \
			  print.c

			  # OBJECT FILES

SRCS		= $(addprefix $(SRCS_PATH)/, $(FILES))
OBJS		= $(addprefix $(OBJS_PATH)/, $(FILES:.c=.o))

# COLORS
RED			= \033[1;31m
GREEN		= \033[1;32m
CYAN		= \033[1;36m
RESET		= \033[0m

# TEXTES
START_TXT		= printf "$(CYAN)=== Compiling ft_ls ===\n$(RESET)"
END_TXT			= printf "$(GREEN)=== ft_ls Compilated ===\n$(RESET)"
CHARG_LINE_TXT	= printf "$(GREEN)█$(RESET)"
CLEAN_TXT		= printf "$(RED) Deleting all files\n$(RESET)"
FCLEAN_TXT		= printf "$(RED) Deleting $(NAME)\n$(RESET)"
NL_TXT			= printf "\n"

# RULES
all:		tmp start $(NAME)

start:
			@$(START_TXT)

art:
			@tput setaf 2; cat doc/ascii_art/project; tput sgr0
			@tput setaf 2; cat doc/ascii_art/name; tput sgr0


$(NAME):	$(OBJS)
			@$(NL_TXT)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)
			@$(END_TXT)

tmp:
			@/bin/mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c 
					@/bin/mkdir -p $(@D)
					$(CC) $(FLAGS) $(INC_PATH) -c $< -o $@
					@$(CHARG_LINE_TXT)

clean:
			@$(CLEAN_TXT)
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@$(FCLEAN_TXT)
			rm -rf $(NAME) $(HOSTLIB) $(TEST_N)
			@$(NL_TXT)

re:			fclean all

rt:			fclean all test t

.PHONY:		clean fclean tmp re all
