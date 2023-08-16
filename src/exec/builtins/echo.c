/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:04:44 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/16 21:07:15 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int echo_newline(char *command)
{
    int i;

    if (ft_strncmp(command, "-n", 2))
        return (0);
    i = 2;
    while (command[i])
    {
        if (command[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int echo(char **command)
{
    int flag;
    int i;

    flag = 1;
    i = 1;
    while (command[i] && echo_newline(command[i]))
    {
        flag = 0; //nao imprime newline no final
        i++;
    }
    while (command[i])
    {
        ft_printf("%s", command[i]);
        if (command[i + 1])
            ft_printf(" ");
        i++;
    }
    if (flag)
        ft_printf("\n");
    return (0);
}
