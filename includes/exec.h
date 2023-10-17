/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:03:31 by joe               #+#    #+#             */
/*   Updated: 2023/10/16 17:53:42 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/*
!CHILD_AUX
*/
void	wait_estatus(int pid, t_main *main);
void	wait_set_line(int pid, t_main *main);
void	error_fp(int pid, int exit_code, t_main *main);
int		ft_fork(t_main *main);
void	wait_estatus_p(t_main *main, t_ast ast);

/*
!EXEC_CMD
*/
void	exec_cmd(char **command, t_main *main, bool pipe);

/*
!EXECVE
*/
void	exec_other_cmd(char **cmd, t_main *main, bool pipe);
void	execution(char **cmd, t_main *main);

/*
!EXECVE_UTILS
*/
void	error_execve(char *str, t_main *main);
void	free_pathname(char	*pathname, int flag);





#endif
