/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:46:02 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/24 16:39:03 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Liberta o pathname, se lhe tiver sido alocada memoria
void	free_pathname(char	*pathname, int flag)
{
	if (flag == 1)
		ft_free_str(&pathname);
}

//*Se o comando for dado sem path (ex. hdas) ou se for um script
//ou programa a executar a executar (ex: ./gjsgfsj) da msg de erro de comando
//*Se o comando for dado com path (ex. /bin/jasgfg)
//da msg de erro de ficheiro
//*O exit code e sempre 127
void	error_execve(char *str, t_main *main)
{
	if (!ft_strncmp("./", str, 2) && str[2] == '\0')
	{
		error_msg_file(str, STDERR_FILENO, IS_D);
		exit_child(main, 126, true);
	}
	if (!access((const char *)str, F_OK))
	{
		error_msg_file(str, STDERR_FILENO, P_D);
		exit_child(main, 126, true);
	}
	if (!ft_strchr(str, '/'))
		error_msg_cmd(str, STDERR_FILENO);
	else
		error_msg_file(str, STDERR_FILENO, FILE_ERROR);
	exit_child(main, 127, true);
}
