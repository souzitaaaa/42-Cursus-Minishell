/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:29:40 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/16 18:06:56 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*
!CD
*/
void	cd(char *path, t_main *main, bool child);

/*
!ECHO
*/
void	echo(char **command, t_main *main, bool child);

/*
!ENV
*/
void	env(t_env *env, t_main *main, bool child, char **command);

/*
!EXIT
*/
void	ft_exit(char **command, bool child, t_main *main);
void	exit_child(t_main *main, int exit_code, bool child);

/*
!EXPORT
*/
void	ft_export(t_env *exp);
void    export(t_main *main, char **array, bool child);

/*
!PDW
*/
void	pwd(t_main *main, bool child);

/*
!UNSET
*/
void    remove_var(t_env *env, int index);
void	unset_exp(t_main *main, char *str);
int		unset_env(t_main *main, char *str);
void	unset(t_main *main, char **array, bool child);

/*
UTILS_EXPORT
*/
void    insert_var_exp(t_main *main, char *str);
void    insert_var_env(t_main *main, char *str);
bool    modify_var_exp(t_main *main, char *str);
bool    modify_var_env(t_main *main, char *str);
void	copy_exp(t_main *main);

/*
UTILS_BUILTINS
*/
int		ft_isnbr(const char *str);
void	refresh_pwd(t_main *main, char *str);
void	refresh_oldpwd(t_main *main, char *str);
int     validations_ch(char *str, int fd, char *command);
bool	verify_var(t_main *main, char *str);

#endif
