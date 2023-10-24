/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/24 11:50:41 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Essa função insere a variável na lista especificada, no caso uso ela na export
e na env_list */
void	insert_var(t_env *list, char *str)
{
	t_var	*aux;
	char	*temp;

	temp = ft_calloc(sizeof(char), ft_strclen(str, '=') + 1);
	ft_strccpy(temp, str, '=');
	if (!ft_isnbr(temp))
	{
		aux = var_node(str);
		add_var(list, aux, -1);
	}
	ft_free_str(&temp);
}

/*Essa função percorre a lista, procura se o nome da variavel é o mesmo até
o sinal de =, se sim ela modifica a variavel */
bool	modify_var(t_env *list, char *str)
{
	t_var	*current;
	int		count;
	char	*temp;

	count = 0;
	current = list->head;
	while (count++ < list->size)
	{
		if (ft_strncmp(str, current->var, ft_strclen(str, '=')) == 0)
		{
			temp = ft_strdup(str);
			free(current->var);
			current->var = temp;
			return (true);
		}
		current = current->next;
	}
	return (false);
}

/*Essa funcao faz uma copia da export_list, ela é chamada no inicio do
programa onde insere a variavel OLDPWD vazia assim como funciona no bash*/
void	copy_exp(t_main *main)
{
	t_var	*aux;
	t_var	*new;

	main->export_list.i = 0;
	aux = main->env_list.head;
	while (main->export_list.i < main->env_list.size)
	{
		new = var_node(aux->var);
		add_var(&main->export_list, new, -1);
		main->export_list.i++;
		aux = aux->next;
	}
	if (!verify_var(main, "OLDPWD"))
	{
		new = var_node("OLDPWD");
		add_var(&main->export_list, new, -1);
	}
}

/*Essa função faz o swap para conseguir ordenar a lista*/
void	swap_var(t_var *var1, t_var *var2)
{
	char	*temp;

	temp = ft_strdup(var1->var);
	free (var1->var);
	var1->var = ft_strdup(var2->var);
	free (var2->var);
	var2->var = temp;
}

/*Essa funcao percorre a lista de variaveis e ordena de acordo com a
tabela ascii*/
void	sort_ascii(t_env *exp)
{
	int		count;
	t_var	*current;

	count = 0;
	current = exp->head;
	while (count < exp->size - 1)
	{
		if (ft_strcmp(current->var, current->next->var) > 0)
		{
			swap_var(current, current->next);
			count = 0;
			current = exp->head;
		}
		else
		{
			count++;
			current = current->next;
		}
	}
}
