/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_treatment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:18:03 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/25 16:18:03 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**out_of_quotes(char *str, int start, int len, t_main *main)
{
	char	*temp;
	char	**result;

	if (len > 0)
	{
		temp = ft_substr(str, start, len);
		result = ft_split(temp, ' ');
		ft_free_str(&temp);
		if (main->flags.hd == false)
			check_expansion_arr(main, result);
		return (result);
	}
	return (NULL);
}

char	**check_join(t_join join, char before, char after)
{
	char	**result;

	if (join.before == NULL && join.after == NULL)
	{
		result = str_to_arr(join.str);
		ft_free_str(&join.str);
	}
	else
	{
		if ((before == ' ' || before == 0) && (after == ' ' || after == 0))
		{
			result = ft_arrnl_strnl_arrjoin(join.before, join.str, join.after);
			free(join.before);
			free(join.after);
		}
		else if (before == ' ' || before == 0)
		{
			result = ft_arrnl_strarrjoin(join.before, join.str, join.after);
			free(join.before);
			ft_free_array(&join.after);
		}
		else if (after == ' ' || after == 0)
		{
			result = ft_arrstrnl_arrjoin(join.before, join.str, join.after);
			ft_free_str(&join.str);
			if (after == ' ')
			{
				free(join.after);
				free(join.before);
			}
		}
		else
		{
			result = ft_arrstrarrjoin(join.before, join.str, join.after);
			free(join.before);
			ft_free_array(&join.after);
		}
	}
	return (result);
}

char	**ft_quotes(t_node_quotes *aux, char *str, t_main *main, bool first)
{
	t_join	join;
	char	**result;
	int		len;

	if (first)
		join.before = out_of_quotes(str, 0, aux->start, main);
	else
		join.before = NULL;
	join.str = ft_substr(str, aux->start + 1, (aux->end - aux->start) - 1);
	if (aux->type == DQUOTE)
		join.str = check_expansion_str(main, join.str, false);
	len = get_min(ft_strclen(str + aux->end + 1, SQUOTE),
			ft_strclen(str + aux->end + 1, DQUOTE));
	join.after = out_of_quotes(str, aux->end + 1, len, main);
	if (join.before == NULL && join.after == NULL)
		result = check_join(join, 0, 0);
	else if (join.before == NULL)
		result = check_join(join, 0, str[aux->end + 1]);
	else if (join.after == NULL)
		result = check_join(join, str[aux->start - 1], 0);
	else
		result = check_join(join, str[aux->start - 1], str[aux->end + 1]);
	return (result);
}

char	**quotes_treatment(t_quotes quotes, char *str, t_main *main)
{
	t_node_quotes	*aux;
	char			**temp;
	char			**result;

	result = ft_calloc(1, sizeof(char *));
	aux = quotes.head;
	quotes.counter = 0;
	while (quotes.counter++ < quotes.size)
	{
		if (aux->index == 0)
		{
			temp = ft_quotes(aux, str, main, true);
			result = ft_arrnl_joinfree(result, temp);
		}
		else
		{
			temp = ft_quotes(aux, str, main, false);
			if (str[aux->start - 1] == ' ')
				result = ft_arrnl_joinfree(result, temp);
			else
				result = ft_arrjoinfree(result, temp);
		}
		free(temp);
		aux = aux->next;
	}
	return (result);
}
