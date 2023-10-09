# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 17:57:43 by jcruz-da          #+#    #+#              #
#    Updated: 2023/10/05 19:34:43 by rimarque         ###   ########.fr        #
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
CFLAGS			= -Wall -Wextra -g -ggdb #-fsanitize=address #-Werror
NPD				= --no-print-directory
RD				= -lreadline

#----------------------------------  FOLDERS ------------------------------------

LIBFTDIR 		= libft_group
LIBFT 			= $(LIBFTDIR)/libft.a
INCLUDE			= includes
SRCS			= src
_SUBFOLDERS		= parser envp exec builtins rdr pipes lexer tokens print_start quotes destroy
VPATH			= $(SRCS) $(addprefix $(SRCS)/, $(_SUBFOLDERS))
OBJDIR			= obj

#--------------------------------- FILES  ---------------------------------------
NAME 			= minishell

_FILES 			= error_msg exit_code init free prompts signal destroy \
					print_img utils list_quotes quotes_substr \
					list lexer token lexer_utils add_tokens create_nodes quotes_treatment aux_quotes \
					extra_tokens output_tokens input_tokens fd_token \
					parser cmdcat ast ast_utils ast_lexer syntax list_endnull \
					env_list env_arr \
					exec_cmd execve execve_utils child_aux \
					pipe pipe_utils rdr_input rdr_output \
					init_rdr rdr_in rdr_out rdr_app rdr_hd rdr_utils \
					echo pwd env unset cd export utils_export utils_builtins exit

OBJ				= $(_FILES:%=%.o)
TARGET			= $(addprefix $(OBJDIR)/, $(OBJ))
_HEADERS		= structs.h defines.h minishell.h exec.h lexer.h parser.h pipes.h quotes.h rdr.h structs.h builtins.h tokens.h
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
