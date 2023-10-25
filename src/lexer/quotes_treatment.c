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
			check_expansion_arr(main, result);
		return (result);
	}
	return (NULL);
}

//echo '$PWD'$USERa"$PWD"
char	**check_join(t_join join, char before, char after, t_main *main)
{
	char	**result;
	bool	free_bef;

	free_bef = false;
	if ((before == ' ' || before == 0 || before == '\t')
		&& (after == ' ' || after == 0 || after == '\t'))
	{
		printf("1\n");
		result = ft_arrnl_strnl_arrjoin(join.before, join.str, join.after);
		ft_free_str(&join.str);
	}
	else if (before == ' ' || before == 0 || before == '\t')
	{
		printf("2\n");
		printf("Before\n");
		print_arr(join.before);
		printf("str:%s\n", join.str);
		printf("After\n");
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
	if (after != 0 || free_bef == false || main->flags.free)
		free(join.before);
	free(join.after);
	print_arr(result);
	return (result);
}

char	last_ch(char** arr)
{
	int last_p;

	if(*arr == NULL)
		return(0);
	last_p = ft_arrlen(arr) - 1;
	return(arr[last_p][ft_strlen(arr[last_p]) - 1]);
}

char	first_ch(char** arr, t_main *main)
{
	main->flags.free = false;
	if(*arr == NULL)
	{
		main->flags.free = true;
		return(0);
	}
	return(arr[0][0]);
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
		join.str = check_expansion_str(main, join.str);
	len = get_min(ft_strclen(str + aux->end + 1, SQUOTE),
			ft_strclen(str + aux->end + 1, DQUOTE));
	join.after = out_of_quotes(str, aux->end + 1, len, main);
	if (join.before == NULL && join.after == NULL)
	{
		printf("ABD\n");
		result = str_to_arr(join.str);
	}
	else if(last_ch(join.before) == 0 && first_ch(join.after, main) == 0)
	{
		ft_free_array(&join.before);
		ft_free_array(&join.after);
		result = str_to_arr(join.str);
	}
	else if (join.before == NULL)
		result = check_join(join, 0, first_ch(join.after, main), main);
	else if (join.after == NULL)
		result = check_join(join, last_ch(join.before), 0, main);
	else
	{
		printf("AIII\n");
		result = check_join(join, last_ch(join.before), first_ch(join.after, main), main);
	}
	printf("result:\n");
	print_arr(result);
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
		printf("AAAAIIII\n");
		if (aux->index == 0)
		{
			temp = ft_quotes(aux, str, main, true);
			result = ft_arrnl_joinfree(result, temp);
		}
		else
		{
			temp = ft_quotes(aux, str, main, false);
			if (str[aux->start - 1] == ' ' || str[aux->start - 1] == '\t')
				result = ft_arrnl_joinfree(result, temp);
			else
				result = ft_arrjoinfree(result, temp);
		}
		free(temp);
		aux = aux->next;
	}
	return (result);
}
