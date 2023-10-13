/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:54 by marvin            #+#    #+#             */
/*   Updated: 2023/10/13 15:51:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*A partir da posição seguinte ao 1o $ verifica se há mais $
bool    check_more_var(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

int	get_number_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != '\0')
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*expand_exitcode(t_main *main, char *str, int i)
{
    char *expanded;
    char *out;

	printf("Encontrada variavel de ambiente: %s\n\tExit code: %i\n", str, main->exit_code);
	expanded = ft_calloc(get_number_len(main->exit_code), sizeof(char));
	expanded = ft_itoa(main->exit_code);
	out = join_expanded(str, expanded, 2);
	return (out);
}

char    *ft_arr_to_str(char **arr, char *str)
{
	int     i = 0;
	char    *out;
	
	if(str[ft_strlen(str) - 1] == '$')
		out = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	else
		out = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	i = 0;
	while (arr[i])
	{
		out = ft_strjoinfree(out, arr[i]);
		i++;
	}
	if(str[ft_strlen(str) - 1] == '$')
		out[ft_strlen(out)] = '$';
	printf("Str pós juntar: %s\n", out);
	return (out);
}

void	del_emptyline(char **arr)
{
	int	i;
	int j;

	i = 0;
	while(arr[i])
	{
		if(arr[i][0] == '\0')
		{
			if(arr[i + 1] == NULL)
				arr[i] = NULL;
			else
			{
				j = i;
				while (arr[j + 1])
				{
					arr[j] = arr[j + 1];
					j++;
				}
				arr[j] = NULL;
			}
		}
		i++;
	}
}