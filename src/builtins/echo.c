/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:04:44 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/04 14:55:06 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Essa função verifica se há -n*/
int	echo_newline(char *command)
{
	int	count;

	count = 0;
	if (ft_strcmp(command, "-n") == 0)
		return (1);
	if (ft_strncmp(command, "-n", 2) == 0)
	{
		count = 2;
		while (command[count] && command[count] == 'n')
			count++;
		if (!command[count])
			return (1);
	}
	return (0);
}

/*A função echo imprime o que for mandado logo depois do comando, se tiver -n dá um \n*/
void	echo(char **command, t_main *main, bool child)
{
	int	count;
	int	flag;

	count = 1;
	flag = 0;
	while (command[count] && echo_newline(command[count]))
	{
		flag = 1;
		count++;
	}
	while (command[count])
	{
		ft_printf("%s", command[count]);
		if (command[count + 1])
			ft_printf(" ");
		count++;
	}
	if (!flag)
		ft_printf("\n");
	exit_child(main, 0, child);
}
