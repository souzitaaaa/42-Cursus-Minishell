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
	{
		printf("1\n");
		result = ft_arrnl_strnl_arrjoin(join.before, join.str, join.after);
	}
	else if (before == ' ' || before == 0 || before == '\t')
	{
		print_arr(join.after);
		result = ft_arrnl_strarrjoin(join.before, join.str, join.after);
	}
	else if (after == ' ' || after == 0 || after == '\t')
	{
		printf("3\n");
		free_bef = true;
		result = ft_arrstrnl_arrjoin(join.before, join.str, join.after);
	}
	else
	{
		printf("4\n");
		result = ft_arrstrarrjoin(join.before, join.str, join.after);
	}
	if (after != 0 || free_bef == false)
		free(join.before);
	free(join.after);
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
	if (*join.str == '\0')
	{
		printf("batata\n");
		ft_free_str(&join.str);
	}
	if (aux->type == DQUOTE && join.str)
		join.str = check_expansion_str(main, join.str);
	len = get_min(ft_strclen(str + aux->end + 1, SQUOTE),
			ft_strclen(str + aux->end + 1, DQUOTE));
	printf("len: %d\n", len);
	join.after = out_of_quotes(str, aux->end + 1, len, main);
	if (join.before == NULL && join.after == NULL)
	{
		printf("entra aqui first if\n");
		if (join.str == NULL)
		{
			printf("e boi\n");
			result = NULL;
		}
		else
			result = str_to_arr(join.str, true);
	}
	else if (join.before == NULL)
	{
		printf("join.before null\n");
		if(join.str == NULL)
			result = join.after;
		else
		{
			printf("aqui caralho\n");
			result = check_join(join, 0, str[aux->end + 1]);
		}
	}
	else if (join.after == NULL)
	{
		if(join.str == NULL)
			result = join.before;
		else
			result = check_join(join, str[aux->start - 1], 0);
	}
	else
	{
		result = check_join(join, str[aux->start - 1], str[aux->end + 1]);
	}
	return (result);
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
		printf("AAAAIIII\n");
		printf("str: %s.\n", str);
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
			if(temp)
			{
				if(result == NULL)
				{
					printf("entra 1\n");
					result = ft_arrdup(temp);
					ft_free_array(&temp);
					main->flags.free = true;
				}
				else if (str[aux->start - 1] == ' ' || str[aux->start - 1] == '\t')
				{
					printf("entra 2\n");
					result = ft_arrnl_joinfree(result, temp);
				}
				else
				{
					printf("entra 3\n");
					result = ft_arrjoinfree(result, temp);
				}
			}
		}
		if(!main->flags.free)
			free(temp);
		aux = aux->next;
	}
	return (result);
}
