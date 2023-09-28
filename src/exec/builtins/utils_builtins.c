/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:04 by jenny             #+#    #+#             */
/*   Updated: 2023/09/26 17:22:45 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_isnbr(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return(0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return(0);
		str++;
	}
	return(1);
}

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
	if (modify_var_exp(main, pwd) == false)
		insert_var_exp(main, pwd);
	if (modify_var_env(main, pwd) == false)
		insert_var_env(main, pwd);
}
void	refresh_oldpwd(t_main *main, char *str)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", str);
	if (modify_var_exp(main, oldpwd) == false)
		insert_var_exp(main, oldpwd);
	if (modify_var_env(main, oldpwd) == false)
		insert_var_env(main, oldpwd);
}