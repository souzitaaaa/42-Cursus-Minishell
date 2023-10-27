/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:18:42 by dinoguei          #+#    #+#             */
/*   Updated: 2023/10/18 16:18:42 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**str_to_arr(char *str, bool free)
{
	char	**result;

	result = ft_calloc(2, sizeof(char *));
	result[0] = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_strlcpy(result[0], str, ft_strlen(str) + 1);
	if (free)
		ft_free_str(&str);
	return (result);
}

void	init_help(t_help *help, char *str)
{
	help->result = ft_calloc(1, sizeof(char *));
	help->temp = NULL;
	help->str = str;
}

void	index_zero(t_main *main, t_node_quotes *aux, t_help *help)
{
	help->temp = ft_quotes(aux, help->str, main, true);
	if (help->temp == NULL)
		ft_free_array(&help->result);
	else
		help->result = ft_arrnl_joinfree(help->result, help->temp);
}

void	not_first(t_main *main, t_node_quotes *aux, t_help *help)
{
	help->temp = ft_quotes(aux, help->str, main, false);
	if (help->temp)
	{
		if (help->result == NULL)
		{
			help->result = ft_arrdup(help->temp);
			ft_free_array(&help->temp);
			main->flags.free = true;
		}
		else if (help->str[aux->start - 1] == ' '
			|| help->str[aux->start - 1] == '\t')
			help->result = ft_arrnl_joinfree(help->result, help->temp);
		else
			help->result = ft_arrjoinfree(help->result, help->temp);
	}
}

char	**check_join_options(t_join join, int option)
{
	char	**result;

	if (option == 1)
	{
		if (join.str == NULL)
			result = ft_arrjoin(join.before, join.after);
		else
			result = ft_arrnl_strnl_arrjoin(join.before, join.str, join.after);
	}
	else
	{
		if (join.str == NULL)
			result = ft_arrjoin(join.before, join.after);
		else
			result = ft_arrstrnl_arrjoin(join.before, join.str, join.after);
	}
	return (result);
}
