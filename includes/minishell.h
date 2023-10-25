/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:29:26 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/28 10:04:37 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_group/include/libft.h"
# include "defines.h"
# include "structs.h"
# include "quotes.h"
# include "pipes.h"
# include "exec.h"
# include "rdr.h"
# include "parser.h"
# include "lexer.h"
# include "builtins.h"
# include "tokens.h"
# include "destroy.h"
# include "envp.h"

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
!GLOBAL VARIABLE
*/
extern int	g_ex_status;

/*
!PRINT_START
*/
void	print_intro(void);

/*
!INIT.C
*/
void		init_env(t_env *stack);
void		init_input(t_main *main, char *input);
void		init_main(t_main *main, char ** env);
void		init_quotes(t_quotes *quotes);

/*
!SIGNAL.C
*/
void	signal_quit(int sig);
void	signal_quit1(int sig);
void	signal_quit2(int sig);
void	signal_handler(int sig);
void	signals(int options);
void	ft_wait(t_main *main);

/*
!ERROR_MSG
*/
void	error_msg_cmd(char *str, int fd);
void	error_msg_file(char *file, int fd, char *msg);
void	error_cd(int fd, char *str);
void	error_export(int fd);
void	error_env(int fd);
void	error_quotes(int fd);
void	error_syntax(char *token);
void	error_msg_fd(char *str, int fd);
void	error_msg_hd(char *str, int fd, int line);
void	error_with_arg(int fd, char *str);

/*
!INIT.C
*/
void		init_env(t_env *stack);
void		init_input(t_main *main, char *input);
void		init_main(t_main *main, char ** env);
void	    ini_variables_quotes(t_variables_quotes *s_var_quotes);
void	    init_input(t_main *main, char *input);
void	    init_ast(t_ast	*ast);
void	    init_lexer(t_lexer *stack);

/*
!GET.C
*/
t_main  *get_main(t_main	*main);
int		get_max(int a, int b);
int     get_min(int a, int b);
int     get_min_len(char *str, int i);

#endif
