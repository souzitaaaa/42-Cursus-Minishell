/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:29:26 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/16 19:20:19 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_group/include/libft.h"
# include "parcer.h"
# include "env.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <time.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

/*
COLORS
*/
# define RESET "\033[0m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN 	"\033[1;36m"
# define WHITE 	"\033[1;37m"

/*
MAIN STRUCT
*/
typedef struct s_main
{
	char 			*input_prompt;
	t_list			tokens;
	char			**envp;
	t_env			env;
	//t_ast 			*imput_exec;
}t_main;

/*
INIT.C
*/
void		init_list(t_list *stack, t_main *main);
void		init_env(t_env *stack);

/*
LIST.C
*/
void		shift_index(t_list *stack);
void		put_head_node(t_list *stack, t_node *new);
t_node		*remove_head(t_list *stack);
void		insert_head(t_list *stack, t_node *new);
void		insert_last(t_list *stack, t_node *new);

/*
ENVP
*/
void    	list_var(t_main *main);
void  		print_var(t_env env);
/*
LEXER.C
*/
void	lexer(t_main *main);

/*
EXTRA_TOKENS.C
*/
void	search_extra_tokens(t_main *main, int *i);
bool	special_chr(char c);


/*
TOKEN.C
*/
t_node	*create_n(t_main *main, t_type token, int *i, char *str);
int		add_token(t_main *main, t_type token, int *i, char *str);

/*
FREE.C
*/
void		free_list(t_list *stack);
void		free_env(t_env *stack);


/*
quotes.C
*/
int check_quotes(char c, int quotes); 
int check_quotes_print(t_main *main);

#endif
