/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unset_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:29:46 by jenny             #+#    #+#             */
/*   Updated: 2023/10/18 19:13:33 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	invalid_option(int fd, char *command, char *str)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(command, fd);
	ft_putstr_fd(": '", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("': invalid option\n", fd);
}

void	invalid_identifier(int fd, char *command, char *str)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(command, fd);
	ft_putstr_fd(": '", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

void	error_token(int fd, char *str)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd("syntax error near unexpected token '", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("'\n", fd);
}

/*Essa função é usada para validar caracteres na unset e na export, se for os caracteres informados tem
devolver erros especificos*/
int	validations_ch(char *str, int fd, char *command)
{
	if (str[0] == '`')
	{
		error_syntax("newline");
		return (2);
	}
	else if (str[0] == '-')
	{
		invalid_option(fd, command, str);
		return (2);
	}
	else if ((str[0] >= '0' && str[0] <= '9') || str[0] == '+' || str[0] == '*' || str[0] == '%' || str[0] == '?' || str[0] == '/' || str[0] == '\\' || str[0] == '.' || str[0] == ',' || str[0] == ':' || str[0] == '`')
	{
		invalid_identifier(fd, command, str);
		return (1);
	}
	else if (str[0] == '(')
	{
		error_syntax("newline");
		return (258);
	}
	else if (str[0] == ')')
	{
		error_token(fd, str);
		return (258);
	}
	return (0);
}
