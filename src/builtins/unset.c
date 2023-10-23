/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/23 19:51:35 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Essa função recebe um ponteiro para a estrutura t_env como argumento e
atualiza o index dos elementos na lista, precisamos saber o index para dar
unset*/
void	shift_index_env(t_env *stack)
{
	t_var	*element;

	stack->head->index = 0;
	element = stack->head->next;
	while (element != stack->head)
	{
		element->index = element->prev->index + 1;
		element = element->next;
	}
}

/*Essa funcao remove um nó da lista de acordo com o index dele usando a funcao
shift_index_env*/
void	remove_var(t_env *env, int index)
{
	t_var	*current;

	current = env->head;
	env->i = 0;
	if (env->size == 1)
		env->head = NULL;
	else
	{
		while (env->i++ < index)
			current = current->next;
		current->next->prev = current->prev;
		current->prev->next = current->next;
		if (index == 0)
			env->head = current->next;
		shift_index_env(env);
	}
	env->size--;
	free(current);
}

/*Essa função percorre a env_list e compara se a variável dada no input é a
mesma encontrada na lista, se sim ela remove*/
int	unset_env(t_main *main, char *str)
{
	int		count;
	int		index;
	t_var	*aux;

	count = 0;
	aux = main->env_list.head;
	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			index = aux->index;
			remove_var(&main->env_list, aux->index);
			return (index);
		}
		aux = aux->next;
	}
	index = main->env_list.size;
	return (index);
}

/*Essa função percorre a export_list e compara se a variável dada no input é
a mesma encontrada na lista, se sim ela remove*/
void	unset_exp(t_main *main, char *str)
{
	int		count;
	t_var	*aux;

	count = 0;
	aux = main->export_list.head;
	while (count++ < main->export_list.size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			remove_var(&main->export_list, aux->index);
			return ;
		}
		aux = aux->next;
	}
}

/*Essa funcao valida se a variavel que esta tentando ser removida é valida, 
se for ela dá unset da variavel nas duas listas: env_list e export_list.
Se não, dá uma mensagem de erro adaptada para cada situação*/
void	unset(t_main *main, char **array, bool child)
{
	int	i;
	int	exit_code;
	int	error;

	i = 1;
	exit_code = 0;
	while (array[i] != NULL)
	{
		if (main->flags.not_print == false)
			error = validations_ch(array[i], STDERR_FILENO, array[0]);
		if (error)
		{
			exit_code = error;
			i++;
			continue ;
		}
		unset_env(main, array[i]);
		unset_exp(main, array[i]);
		i++;
	}
	if (child)
		exit(exit_code);
	set_exit_code(main, exit_code);
}
