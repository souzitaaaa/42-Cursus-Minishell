/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:04 by jenny             #+#    #+#             */
/*   Updated: 2023/10/03 17:15:37 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	validations_ch(char *str, int fd, char *command) 
{
    int i = 0;
	
	if (str[i] == '-')
	{
        ft_putstr_fd("minishell: ", fd);
		ft_putstr_fd(command, fd);
		ft_putstr_fd(": '", fd);
        ft_putstr_fd(str, fd);
        ft_putstr_fd("': invalid option\n", fd);
		return (2);
    }
	else if (str[1] < '0' || str[1] > '9' || str[i] == '+' || str[i] == '*' || str[i] == '%' || str[i] == '?' || str[i] == '/' || str[i] == '\\')
	{
        ft_putstr_fd("minishell: ", fd);
		ft_putstr_fd(command, fd);
		ft_putstr_fd(": '", fd);
        ft_putstr_fd(str, fd);
        ft_putstr_fd("': not a valid identifier\n", fd);
		return (1);
    }
	else if (str[i] == '(')
	{
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd("syntax error near unexpected token 'newline'\n", fd);
		return (258);
    }
	else if (str[i] == ')')
	{
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd("syntax error near unexpected token '", fd);
        ft_putstr_fd(str, fd);
        ft_putstr_fd("'\n", fd);
		return (258);
    }
	return (0);
}
