# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joe <joe@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 17:57:43 by jcruz-da          #+#    #+#              #
#    Updated: 2023/09/28 17:07:56 by joe              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------  COLORS  --------------------------------
RESET			= \033[0m
BLACK 			= \033[1;30m
RED 			= \033[1;31m
GREEN 			= \033[1;32m
YELLOW		 	= \033[1;33m
BLUE			= \033[1;34m
PURPLE 			= \033[1;35m
CYAN 			= \033[1;36m
WHITE 			= \033[1;37m

#----------------------------------- COMMANDS ----------------------------------
CC				= cc
RM 				= rm -rf

#-----------------------------------  FLAGS  -----------------------------------
CFLAGS			= -Wall -Wextra -g -ggdb -fsanitize=address #-Werror
NPD				= --no-print-directory
RD				= -lreadline

#----------------------------------  FOLDERS ------------------------------------

LIBFTDIR 		= libft_group
LIBFT 			= $(LIBFTDIR)/libft.a
INCLUDE			= includes
SRCS			= src
_SUBFOLDERS		= parcer envp exec exec/builtins exec/rdr exec/pipes parcer/lexer parcer/lexer/lexer_tokens print_start quotes
VPATH			= $(SRCS) $(addprefix $(SRCS)/, $(_SUBFOLDERS))
OBJDIR			= obj

#--------------------------------- FILES  ---------------------------------------
NAME 			= minishell

_FILES 			= error_msg exit_code init list free prompts signal destroy\
					lexer token \
					parcer cmdcat ast syntax\
					extra_tokens output_tokens input_tokens lexer_utils\
					env_list env_arr \
					exec_cmd execve execve_utils \
					pipe pipe_utils\
					init_rdr rdr_in rdr_out rdr_app rdr_heredoc rdr_utils \
					child_aux \
					echo pwd env unset cd export utils_export  utils_builtins exit\
					print_img utils list_quotes

OBJ				= $(_FILES:%=%.o)
TARGET			= $(addprefix $(OBJDIR)/, $(OBJ))
_HEADERS		= structs.h defines.h minishell.h 
HDR				= $(addprefix $(INCLUDE)/, $(_HEADERS))

#---------------------------------  RULES  --------------------------------------

all: $(NAME)

$(NAME): $(OBJDIR) $(TARGET) $(LIBFT) main.c
	$(CC) $(CFLAGS) main.c $(TARGET) $(RD) -I $(INCLUDE) $(LIBFT) -o $(NAME)
	echo "[$(GREEN)Success$(RESET)] minishell created$(BOLD)$(RESET)"

$(OBJDIR)/%.o : %.c $(HDR)
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	echo "[$(CYAN)Compiling$(RESET)] libft$(RESET)"
	$(MAKE) $(NPD) -C $(LIBFTDIR)
	echo "[$(GREEN)Success$(RESET)] Libft compilation compleated!$(BOLD)$(RESET)"

clean:
	$(RM) $(OBJDIR)
	$(MAKE) clean $(NPD) -C  $(LIBFTDIR)
	echo "[$(RED)Deleting$(RESET)]  object files deleted$(BOLD)$(RESET)"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean $(NPD) -C $(LIBFTDIR)
	echo "[$(RED)Deleting$(RESET)]  .a deleted$(BOLD)"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
