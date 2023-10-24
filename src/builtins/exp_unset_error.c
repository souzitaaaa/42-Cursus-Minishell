/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unset_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:29:46 by jenny             #+#    #+#             */
/*   Updated: 2023/10/24 17:59:35 by jede-ara         ###   ########.fr       */
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

bool	special_char(char *str, int fd, char *command)
{
	char	*temp;

	temp = ft_calloc(sizeof(char), ft_strclen(str, '=') + 1);
	ft_strccpy(temp, str, '=');
	if ((str[0] >= '0' && str[0] <= '9') || ft_strchr(temp, '+')
		|| ft_strchr(temp, '*') || ft_strchr(temp, '%') || ft_strchr(temp, '?')
		|| ft_strchr(temp, '/') || ft_strchr(temp, '`') || ft_strchr(temp, '.')
		|| ft_strchr(temp, ',') || ft_strchr(temp, ':')
		|| ft_strchr(temp, '\\'))
	{
		invalid_identifier(fd, command, temp);
		ft_free_str(&temp);
		return (true);
	}
	if (ft_strchr(temp, '-'))
	{
		invalid_option(fd, command, temp);
		ft_free_str(&temp);
		return (true);
	}
	ft_free_str(&temp);
	return (false);
}

/*Essa função é usada para validar caracteres na unset e na export,
se for os caracteres informados tem devolver erros especificos*/
int	validations_ch(char *str, int fd, char *command)
{
	if (ft_strchr(str, '`'))
	{
		error_syntax("newline");
		return (2);
	}
	else if (special_char(str, fd, command) == true)
		return (2);
	else if (special_char(str, fd, command) == true)
		return (1);
	else if (ft_strchr(str, '('))
	{
		error_syntax("newline");
		return (258);
	}
	else if (ft_strchr(str, ')'))
	{
		error_token(fd, str);
		return (258);
	}
	return (0);
}
