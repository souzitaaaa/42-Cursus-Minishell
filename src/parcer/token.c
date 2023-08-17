/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:02:18 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/17 20:41:48 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand(t_main *main, char *str)
{
	if (ft_strcmp(str, ))
}

//* Esta funcao vai verificar se nos comandos foi inserido um $ para poder
	//* prosseguir com a expansao
void	check_expansion(t_main *main, char **arr)
{
	int i = 0;
	int j;

	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_strchr("$", arr[i][j]))
				expand(main, arr[i]);
			j++;
		}
		i++;
	}
}

//* Funcao que cria o novo node, criando uma arr dividindo as palavras e copiando essa mesma arr
	//* para a variavel arr, na t_token que vai ser onde vao estar guardados os tokens
t_node	*create_n(t_main *main, t_type token, int *index, char *str)
{
	t_node	*new;
	char	**arr;

	(void)main;
	(void)index;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	arr = ft_split(str, 32);
	check_expansion(main, arr);
	new->token.arr = malloc(sizeof(char *) * ft_arrlen(arr) + 1);
	ft_arrlcpy(new->token.arr, arr, ft_arrlen(arr) + 1);
	//! falta o free da arr
	return (new);
}

//* Vai adicionar o token a s_list criando um novo node com os parametros que eu mando
int	add_token(t_main *main, t_type token, int *i, char *str)
{
	t_node	*new;

	new = create_n(main, token, i, str);
	if (!new)
		return (1);
	insert_last(&main->tokens, new);
	return (0);
}
