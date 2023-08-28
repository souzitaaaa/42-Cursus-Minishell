/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:46:15 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/19 00:46:15 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	error_msg_cmd(char	*str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(CMD_ERROR, fd);
}

void	error_msg_file(char *str, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(FILE_ERROR, fd);
}
