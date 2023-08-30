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
!INIT.C
*/
void		init_env(t_env *stack);
void		init_input(t_main *main, char *input);
void		init_main(t_main *main, char ** env);


/*
!LIST.C
*/
void		shift_index(t_lexer *stack);
void		put_head_node(t_lexer *stack, t_node *new);
t_node		*remove_head(t_lexer *stack);
void		insert_head(t_lexer *stack, t_node *new);
void		insert_last(t_lexer *stack, t_node *new);


/*
!ENVP
*/
void		set_env_list(t_main *main, char **envp);
void  		print_var(t_env env);
void		set_env_arr(t_main *main);


/*
!EXEC
*/
void	set_exit_code(t_main *main, int exit_code);
int	exec_cmd(char **command, t_main *main);
void	test_exec(t_main *main);
void	exec_other_cmd(char **cmd, t_main *main);
void	execution(char **cmd, t_main *main);
void	error_management(char *str, t_main *main);
void	free_pathname(char	*pathname, int flag);


/*
!BUILTINS
*/
int		echo(char **command);
int		pwd(void);
int 	ft_env(t_env *env);
int		ft_unset(t_main *main, char *str);


/*
!LEXER.C
*/
void	lexer(t_main *main);


/*
!EXTRA_TOKENS.C
*/
void	search_extra_tokens(t_main *main, int *i);
bool	special_chr(char c);


/*
!OUTPUT_TOKENS.C
*/
void    search_output_tokens(t_main *main, int *i);


/*
!TOKEN.C
*/
t_node	*create_n(t_main *main, t_type token, int *i, char *str);
int		add_token(t_main *main, t_type token, int *i, char *str);



/*
!PARCER
*/
void	parcer(t_main *main);
void	test_ast(t_lexer tokens, t_ast *ast);

/*
!EXEC
*/
void	set_exit_code(t_main *main, int exit_code);
void	exec_cmd(char **command, t_main *main, bool pipe);

/*
!BUILTINS
*/
void	echo(char **command, t_main *main, bool pipe);
int		pwd(void);
int 	ft_env(t_env *env);
int		ft_unset(t_main *main, char *str);

/*
!EXECVE
*/
void	exec_other_cmd(char **cmd, t_main *main, bool pipe);
void	execution(char **cmd, t_main *main);
void	error_management(char *str, t_main *main);
void	free_pathname(char	*pathname, int flag);


/*
!PIPES
*/
void	init_pipe(t_ast ast, t_main *main);


/*
!FREE.C
*/
void		free_list(t_lexer *stack);
void		free_env(t_env *stack);


/*
!QUOTES.C
*/
int check_quotes(char c, int quotes);
int check_quotes_print(t_main *main);


/*
!SIGNAL.C
*/
void	signal_quit(int sig);
void	signal_quit1(int sig);
void	signal_quit2(int sig);
void	signal_handler(int sig);
void	signals(void);
void	ft_wait(t_main *main);


/*
!ERROR_MSG
*/
void	error_msg_cmd(char *str, int fd);
void	error_msg_file(char *str, int fd);
void	prompt_diogo(t_prompt *prompt_list);
void	prompt_rita(t_prompt *prompt_list);
void    prompt_jenny(t_prompt *prompt_list);
void	prompt_jo(t_prompt *prompt_list);
void    prompt_default(t_prompt *prompt_list);

#endif