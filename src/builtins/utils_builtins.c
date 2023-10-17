/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:04 by jenny             #+#    #+#             */
/*   Updated: 2023/10/06 14:44:16 by jenny            ###   ########.fr       */
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

int	validations_ch(char *str, int fd, char *command) 
{
    int i;
	
	i = 0;
	if (str[i] == '-')
	{
        ft_putstr_fd("minishell: ", fd);
		ft_putstr_fd(command, fd);
		ft_putstr_fd(": '", fd);
        ft_putstr_fd(str, fd);
        ft_putstr_fd("': invalid option\n", fd);
		return (2);
    }
	else if ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '*' || str[i] == '%' || str[i] == '?' || str[i] == '/' || str[i] == '\\')
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

bool	verify_var(t_main *main, char *str)
{
	int		count = 0;
	t_var	*aux;

	count = 0;
	aux = main->env_list.head;
	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
			return(true);
		aux = aux->next;
	}
	return (false);
}
