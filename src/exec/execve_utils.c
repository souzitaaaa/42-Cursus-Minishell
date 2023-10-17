/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:46:02 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/16 18:07:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pathname(char	*pathname, int flag)
{
	if (flag == 1)
		ft_free_str(&pathname);
}

void	error_execve(char *str, t_main *main)
{
	if (!ft_strchr(str, '/') && ft_strncmp("./", str, 2)) //cmd normal
		error_msg_cmd(str, STDERR_FILENO);
	else 													//se começar por "/"" (ou seja se der o caminho)
		error_msg_file(str, STDERR_FILENO);
	ft_free_array(&main->env_arr);
	exit_child(main, 127, true);
}
