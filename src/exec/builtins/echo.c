/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:04:44 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/18 03:45:18 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int echo_newline(char *command)
{
    int count;

    if (ft_strncmp(command, "-n", 2))
        return (0);
    count = 2;
    while (command[count])
    {
        if (command[count] != 'n')
            return (0);
        count++;
    }
    return (1);
}
int echo(char **command)
{
    int flag;
    int count;

    flag = 1;
    count = 1;
    while (command[count] && echo_newline(command[count]))
    {
        flag = 0; //nao imprime newline no final
        count++;
    }
    while (command[count])
    {
        ft_printf("%s", command[count]);
        if (command[count + 1])
            ft_printf(" ");
        count++;
    }
    if (flag)
        ft_printf("\n");
    return (0);
}
