/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:29:40 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/25 10:41:42 by marvin           ###   ########.fr       */
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
void	set_exit_code(t_main *main, int exit_code);
void	ft_exit(char **command, bool child, t_main *main, bool input);
void	exit_child(t_main *main, int exit_code, bool child);

/*
!EXPORT
*/
void	sort_print_export(t_env *exp);
void	export(t_main *main, char **array, bool child);

/*
!PDW
*/
void	pwd(t_main *main, bool child);

/*
!UNSET
*/
void	remove_var(t_env *env, int index);
void	unset_exp(t_main *main, char *str);
int		unset_env(t_main *main, char *str);
void	unset(t_main *main, char **array, bool child);

/*
!UTILS_EXPORT
*/
void	swap_var(t_var *var1, t_var *var2);
void	sort_ascii(t_env *exp);
void	insert_var(t_env *list, char *str);
bool	modify_var(t_env *list, char *str);
void	copy_exp(t_main *main);

/*
!UTILS_CD
*/
void	refresh_pwd(t_main *main, char *str);
void	refresh_oldpwd(t_main *main, char *str);
char	*find_home(char *path, t_main *main, bool child);
int		change_dir(char *path, t_main *main);
char	*get_envvar(char *str, t_env *env_list);
void	check_cd(char **command, t_main *main, bool child);

/*
!UTILS_BUILTINS
*/
int		ft_isnbr(const char *str);
int		validations_ch(char *str, int fd, char *command);
bool	verify_var(t_main *main, char *str);

#endif
