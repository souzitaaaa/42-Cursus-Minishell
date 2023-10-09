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

void    single_quotes(t_main *main, int *i, int start, t_node_quotes *aux)
{
	char    *str;
	char    *out;
			printf("\033[1;35m\t\t(Single quotes treatment)\033[0m\n");
		printf("Start on the str: %c\n", main->input_prompt[aux->start]);
		printf("End on the str: %c\n", main->input_prompt[aux->end]);
	out = ft_substr(main->input_prompt, start, (aux->start - start));
		printf("aux out: %s\n", out);
	str = ft_substr(main->input_prompt, aux->start + 1, (aux->end - aux->start) - 1);
		printf("str: %s\n", str);
	out = ft_strjoin(out, str);
		printf("out: %s\n", out);
	add_token_quotes(main, STRING, i, out, false);
	(*i) = aux->end;
			printf("\033[1;35m\t\t(End single quotes treatment)\033[0m\n");
}

int	get_min(t_len *len_out)
{
	int	min = len_out->pipe;
	if (len_out->in < min)
		min = len_out->in;
	if (len_out->out < min)
		min = len_out->out;
	if (len_out->squote < min)
		min = len_out->squote;
	if (len_out->dquote < min)
		min = len_out->dquote;
	printf("min: %i\n", min);
	return (min);
}

int	get_len_out(t_main *main, t_node_quotes *aux)
{
	t_len len_out;

	len_out.pipe = ft_strclen(main->input_prompt + aux->end + 1, '|');
	printf("pipe: %i\n", len_out.pipe);
	len_out.in = ft_strclen(main->input_prompt + aux->end + 1, '<');
	printf("in: %i\n", len_out.in);
	len_out.out = ft_strclen(main->input_prompt + aux->end + 1, '>');
	printf("out: %i\n", len_out.out);
	len_out.squote = ft_strclen(main->input_prompt + aux->end + 1, SQUOTE);
	printf("squote: %i\n", len_out.squote);
	len_out.dquote = ft_strclen(main->input_prompt + aux->end + 1, DQUOTE);
	printf("dquote: %i\n", len_out.dquote);
	return (get_min(&len_out));
}

void    double_quotes(t_main *main, int *i, int start, t_node_quotes *aux)
{
	char    *str;
	char	**before;
	char	**after;
	char    *out;
	int     j = 0;
	char	**result;

			printf("\033[1;35m\t\t(Double quotes treatment)\033[0m\n");

		printf("Start on the str: %c\n", main->input_prompt[aux->start]);
		printf("End on the str: %c\n", main->input_prompt[aux->end]);
	out = ft_substr(main->input_prompt, start, (aux->start - start));
		printf("before out: %s\n", out);
	before = ft_split(out, ' ');;
	free(out);
	check_expansion(main, before);
	str = ft_substr(main->input_prompt, aux->start + 1, (aux->end - aux->start) - 1);
	while (str[j] != '\0')
	{
		if (ft_strchr("$", str[j]))
		{
			str = expand(main, str);
			break ;
		}
		j++;
	}
	printf("str: %s\n", str);
	if (get_len_out(main, aux) > 0)
	{
		out = ft_substr(main->input_prompt, aux->end + 1, get_len_out(main, aux));
		printf("after out: %s\n", out);
		after = ft_split(out, ' ');
		free(out);
		check_expansion(main, after);
		result = ft_arrstrarrjoin(before, str, after);
	}
	else
		result = ft_arrstrjoin(before, str);
	add_token_quotes(main, STRING, i, result, true);
	(*i) = aux->end;
		printf("\033[1;35m\t\t(End double quotes treatment)\033[0m\n");
}

t_node_quotes *get_node_quote(t_quotes *quotes, int *i)
{
	int		count = 0;
	t_node_quotes *aux = quotes->head;

	while(count++ < quotes->size)
	{
		if (aux->start == *i)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

void    quotes_treatment(t_main *main, int *i, int start)
{
	t_node_quotes *aux;

			printf("\033[1;35m\t[Quotes treatment]\033[0m\n");
				print_quotes(&main->quotes);
		aux = get_node_quote(&main->quotes, i);
				printf("type/start/end -> %c %i %i\n", aux->type, aux->start, aux->end);
		if (aux->type == SQUOTE)
			single_quotes(main, i, start, aux);
		else
			double_quotes(main, i, start, aux);
		printf("\033[1;35m\t[End quotes treatment]\033[0m\n");
}
