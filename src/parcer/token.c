/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:02:18 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/24 16:53:25 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

//* Vai tratar de expandir a string para a o seu respetivo valor na variavel de ambiente
	//* ela vai percorrer a lista das env ate achar uma identica ao valor que lhe manda-mos
	//* quando encontrar vai copiar oque esta depois do = para dentro dessa str
char	*expand(t_main *main, char *str)
{
	int		count = 0;
	t_var	*aux = main->env_list.head;
	char *expanded = NULL;

			printf("\033[1;32m\t\tExpanding\033[0m\n");
			printf("str: %s and str + 1: %s\n", str, str + 1);
	if (ft_strncmp(str, "$?", ft_strlen(str)) == 0)
	{
		printf("Encontrada variavel de ambiente: %s\n\tExit code: %i\n", str, main->exit_code);
		expanded = malloc(sizeof(char) * get_number_len(main->exit_code));
		expanded = ft_itoa(main->exit_code);
		return (expanded);
	}
	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str + 1, aux->var, ft_strlen(str) - 1) == 0)
		{
			printf("Encontrada variavel de ambiente: %s\n\tNa envp: %s\n", str, aux->var);
			expanded = malloc(sizeof(char) * ft_strlen(aux->var) - ft_strlen(str) + 1);
			ft_strlcpy(expanded, aux->var + ft_strlen(str), ft_strlen(aux->var) - ft_strlen(str) + 1);
			return (expanded);
		}
		aux = aux->next;
	}
	return("Var nao encontrada");
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
				arr[i] = expand(main, arr[i]);
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
	new->token.arr = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
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
