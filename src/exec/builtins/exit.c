/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:19:35 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/12 16:19:35 by rimarque         ###   ########.fr       */
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

void	ft_exit(char **command)
{
	int exit_code;

	//free_everything(); //!É PARA DAR FREE AQUI
	ft_putendl_fd("exit", STDERR_FILENO);
	if(!command[1])
	{
		exit(0);
	}
	if(ft_isnbr(command[1]) && command[2] == NULL)
	{
		exit_code = ft_atoi(command[1]);
		exit((unsigned char)exit_code);
	}
	if(ft_isnbr(command[1]) && command[2])
	{
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
		exit(1);
	}
	if(!ft_isnbr(command[1]))
	{
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
}
