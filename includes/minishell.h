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
void	error_msg_fd(char *str, int fd);
void	error_msg_hd(char *str, int fd, int line);

/*
!EXIT_CODE.C
*/
void	set_exit_code(t_main *main, int exit_code);

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
!PROMPT
*/
void	prompt_diogo(t_prompt *prompt_list);
void	prompt_rita(t_prompt *prompt_list);
void    prompt_jenny(t_prompt *prompt_list);
void	prompt_jo(t_prompt *prompt_list);
void    prompt_default(t_prompt *prompt_list);

#endif
