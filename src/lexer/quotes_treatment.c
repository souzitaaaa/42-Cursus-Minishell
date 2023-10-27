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
		result = ft_split_tab(temp);
		ft_free_str(&temp);
		if (main->flags.hd == false)
			check_expansion_arr(main, &result);
		return (result);
	}
	return (NULL);
}

//echo '$PWD'$USERa"$PWD"
char	**check_join(t_join join, char before, char after)
{
	char	**result;
	bool	free_bef;

	free_bef = false;
	if ((before == ' ' || before == 0 || before == '\t')
		&& (after == ' ' || after == 0 || after == '\t'))
		result = ft_arrnl_strnl_arrjoin(join.before, join.str, join.after);
	else if (before == ' ' || before == 0 || before == '\t')
		result = ft_arrnl_strarrjoin(join.before, join.str, join.after);
	else if (after == ' ' || after == 0 || after == '\t')
	{
		free_bef = true;
		result = ft_arrstrnl_arrjoin(join.before, join.str, join.after);
	}
	else
		result = ft_arrstrarrjoin(join.before, join.str, join.after);
	if (after != 0 || free_bef == false)
		free(join.before);
	free(join.after);
	return (result);
}

char	**option_quotes(t_join join, t_node_quotes *aux, char *str, int option)
{
	char	**result;

	if (option == 1)
	{
		if (join.str == NULL)
			result = NULL;
		else
			result = str_to_arr(join.str, true);
	}
	if (option == 2)
	{
		if (join.str == NULL)
			result = join.after;
		else
			result = check_join(join, 0, str[aux->end + 1]);
	}
	if (option == 3)
	{
		if (join.str == NULL)
			result = join.before;
		else
			result = check_join(join, str[aux->start - 1], 0);
	}
	return (result);
}

char	**ft_quotes(t_node_quotes *aux, char *str, t_main *main, bool first)
{
	t_join	join;
	int		len;

	if (first)
		join.before = out_of_quotes(str, 0, aux->start, main);
	else
		join.before = NULL;
	join.str = ft_substr(str, aux->start + 1, (aux->end - aux->start) - 1);
	if (*join.str == '\0')
		ft_free_str(&join.str);
	if (aux->type == DQUOTE && join.str)
		join.str = check_expansion_str(main, join.str);
	len = get_min(ft_strclen(str + aux->end + 1, SQUOTE),
			ft_strclen(str + aux->end + 1, DQUOTE));
	join.after = out_of_quotes(str, aux->end + 1, len, main);
	if (join.before == NULL && join.after == NULL)
		return (option_quotes(join, aux, str, 1));
	if (join.before == NULL)
		return (option_quotes(join, aux, str, 2));
	if (join.after == NULL)
		return (option_quotes(join, aux, str, 3));
	return (check_join(join, str[aux->start - 1], str[aux->end + 1]));
}

char	**quotes_treatment(t_quotes quotes, char *str, t_main *main)
{
	t_node_quotes	*aux;
	char			**temp;
	char			**result;

	result = ft_calloc(1, sizeof(char *));
	aux = quotes.head;
	while (quotes.counter++ < quotes.size)
	{
		main->flags.free = false;
		if (aux->index == 0)
		{
			temp = ft_quotes(aux, str, main, true);
			if (temp == NULL)
				ft_free_array(&result);
			else
				result = ft_arrnl_joinfree(result, temp);
		}
		else
		{
			temp = ft_quotes(aux, str, main, false);
			if (temp)
			{
				if (result == NULL)
				{
					result = ft_arrdup(temp);
					ft_free_array(&temp);
					main->flags.free = true;
				}
				else if (str[aux->start - 1] == ' '
					|| str[aux->start - 1] == '\t')
					result = ft_arrnl_joinfree(result, temp);
				else
					result = ft_arrjoinfree(result, temp);
			}
		}
		if (!main->flags.free)
			free(temp);
		aux = aux->next;
	}
	return (result);
}
