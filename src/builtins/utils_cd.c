/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:42:36 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/17 16:44:21 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_cd(t_main *main, char *str)
{
	int	index;

	print_var(main->env_list);
	index = unset_env(main, str);
	unset_exp(main, str);
	return (index);
}

void	refresh_pwd(t_main *main, char *str)
{
	char	*pwd;

	pwd = ft_strjoin("PWD=", str);
	if (modify_var(&main->export_list, pwd) == false)
		insert_var_exp(main, pwd);
	if (modify_var(&main->env_list, pwd) == false)
		insert_var_env(main, pwd);
}

void	refresh_oldpwd(t_main *main, char *str)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", str);
	if (modify_var(&main->export_list, oldpwd) == false)
		insert_var_exp(main, oldpwd);
	if (modify_var(&main->env_list, oldpwd) == false)
		insert_var_env(main, oldpwd);
}