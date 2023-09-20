/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:04 by jenny             #+#    #+#             */
/*   Updated: 2023/09/20 20:26:42 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//VER DE ADD O OLDPWD 
int	unset_cd(t_main *main, char *str)
{
	int	index;
	
	ft_printf("unset cd 1\n");
	print_var(main->env_list);
	index = unset_env(main, str);
	ft_printf("unset cd 2\n");
	unset_exp(main, str);
	ft_printf("unset cd 3\n");
	return (index);
}

void	refresh_pwd(t_main *main, char *str)
{
	t_var	*new_pwd;
	int		index;
	char	*pwd;
	
	pwd = ft_strjoin("PWD=", str);
	ft_printf("\n\n\033[1;31mEXPORT BEFORE\033[0m\n\n");
	print_var(main->env_list);
	index = unset_cd(main, "PWD");
	new_pwd = var_node(pwd);
	ft_printf("index refresh %d:\n", index);
	ft_printf("\n\n\033[1;31mEXPORT AFTER\033[0m\n\n");
	print_var(main->env_list);
	add_index_var(&main->env_list, new_pwd, index);
	ft_printf("index refresh %d:\n", index);
	add_index_var(&main->export_list, new_pwd, index);
	//print_var(main->env_list);
}
void	refresh_oldpwd(t_main *main, char *str)
{
	t_var	*new_oldpwd;
	char	*oldpwd;
	int		index;
	
	ft_printf("refresh oldpwd 1\n");
	oldpwd = ft_strjoin("OLDPWD=", str);
	ft_printf("refresh oldpwd 2\n");
	//ft_printf("\n\n\033[1;31mENV BEFORE\033[0m\n\n");
	//print_var(main->env_list);
	index = unset_cd(main, "OLDPWD");
	//ft_printf("\n\n\033[1;31mENV AFTER\033[0m\n\n");
	//print_var(main->env_list);
	ft_printf("refresh oldpwd 3\n");
	new_oldpwd = var_node(oldpwd);
	ft_printf("index refresh old: %d\n", index);
	//print_var(main->env_list);
	add_index_var(&main->env_list, new_oldpwd, index);
	ft_printf("\n\n\033[1;31mEXPORT BEFORE\033[0m\n\n");
	print_var(main->export_list);
	add_index_var(&main->export_list, new_oldpwd, index);
	ft_printf("\n\n\033[1;31mEXPORT AFTER\033[0m\n\n");
	print_var(main->export_list);
}