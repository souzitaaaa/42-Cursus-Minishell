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
t_var       *var_node(const char *var);
void        add_var(t_env *env, t_var *var_new);
void	    shift_index_env(t_env *stack);
void		set_env_list(t_main *main, char **envp);
void  		print_var(t_env env);
void		set_env_arr(t_main *main);

/*
!BUILTINS
*/
void    echo(char **command, t_main *main, bool child);
void    pwd(t_main *main, bool child);
void    env(t_env *env, t_main *main, bool child, char **command);
void	unset(t_main *main, char *str, bool child);
void    export(t_main *main, char **array, bool child);
void    insert_var(t_main *main, char *str, bool exp);
bool    modify_var(t_main *main, char *str, bool exp);
void	copy_exp(t_main *main);
void    remove_var(t_env *env, int index);
void    cd(char *path, t_main *main, bool child);
void	ft_exit(char **command, bool child, t_main main);

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
void    search_output_tokens(t_main *main, int *i, char *str);
bool    is_space(char c);
int     get_fd_rdr(t_main *main, int *i);

/*
!INPUT_TOKENS.C
*/
void    search_input_tokens(t_main *main, int *i, char *str);
void    get_rdr_in(t_main *main, int *i, t_type token, char *fd);

/*
!QUOTES_TREATMENT.C
*/
void    quotes_treatment(t_main *main, int *i, int start);
int     add_token_quotes(t_main *main, t_type token, int *i, char *str, bool expand);

/*
!TOKEN.C
*/
t_node	*create_n(t_main *main, t_type token, int *i, char *str);
int		add_token(t_main *main, t_type token, int *i, char *str);
int     add_prev_token(t_main *main, int *i, char *str);
char	*expand(t_main *main, char *cmp);
void	check_expansion(t_main *main, char **arr);

/*
!LEXER_UTILS
*/
void    remove_node(t_lexer *lexer, int index);
void    insert_node(t_lexer *lexer, t_node *new, int index);
void    print_tokens(t_lexer *tokens);

/*
!SYNTAX
*/
bool    syntax_analysis(t_main *main);

/*
!PARCER
*/
void	parcer(t_main *main);
void	test_ast(t_lexer tokens, t_ast *ast);
void	cmdcat(t_lexer *tokens);

/*
!EXEC
*/
void	set_exit_code(t_main *main, int exit_code);
void	exec_cmd(char **command, t_main *main, bool pipe);
void	pipex(t_ast *ast, t_main *main);

/*
!RDR
*/
void	init_rdr(t_lexer tokens, t_main *main);
void	rdr_in(char **arr, t_main *main);
void	rdr_out(char **arr, t_main *main);
void	rdr_app(char **arr, t_main *main);
void	rdr_hd(t_token token, t_main *main, int fd);
int		open_hd(char *lim, bool quotes, t_main *main);
void	rdr_error(char *str, t_main *main, int options);

/*
!EXECVE
*/
void	exec_other_cmd(char **cmd, t_main *main, bool pipe);
void	execution(char **cmd, t_main *main);
void	error_management(char *str);
void	free_pathname(char	*pathname, int flag);

/*
!CHILD_AUX
*/
void	wait_estatus(int pid, t_main *main);

/*
!FREE.C
*/
void		free_lexer(t_lexer *stack);
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
void	signals(int options);
void	ft_wait(t_main *main);

/*
!ERROR_MSG
*/
void	error_msg_cmd(char *str, int fd);
void	error_msg_file(char *str, int fd);
void	error_cd(int fd);
void	error_export(int fd);
void	error_quotes(int fd);

/*
!DESTROY
*/
void    destroy(t_main *main);

//!PROMPT
void	prompt_diogo(t_prompt *prompt_list);
void	prompt_rita(t_prompt *prompt_list);
void    prompt_jenny(t_prompt *prompt_list);
void	prompt_jo(t_prompt *prompt_list);
void    prompt_default(t_prompt *prompt_list);

#endif
