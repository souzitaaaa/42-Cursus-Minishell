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

char	**check_join(t_join join, char before, char after)
{
	char	**result;
	bool	free_bef;

	free_bef = false;
	if ((before == ' ' || before == 0 || before == '\t')
		&& (after == ' ' || after == 0 || after == '\t'))
		result = check_join_options(join, 1);
	else if (before == ' ' || before == 0 || before == '\t')
		result = ft_arrnl_strarrjoin(join.before, join.str, join.after);
	else if (after == ' ' || after == 0 || after == '\t')
	{
		free_bef = true;
		result = check_join_options(join, 2);
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
			result = ft_arr_bzero();
		else
			result = str_to_arr(join.str, true);
	}
	if (option == 2)
	{
		if (join.str == NULL)
			result = ft_arrdup_bzero_first(join.after, str[aux->end + 1]);
		else
			result = check_join(join, 0, str[aux->end + 1]);
	}
	if (option == 3)
	{
		if (join.str == NULL)
			result = ft_arrdup_bzero_last(join.before, str[aux->start - 1]);
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
	t_help			help;

	init_help(&help, str);
	aux = quotes.head;
	while (quotes.counter++ < quotes.size)
	{
		main->flags.free = false;
		if (aux->index == 0)
			index_zero(main, aux, &help);
		else
			not_first(main, aux, &help);
		if (!main->flags.free)
			free(help.temp);
		aux = aux->next;
	}
	print_arr(help.result);
	return (help.result);
}
