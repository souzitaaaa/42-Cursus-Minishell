/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:47:44 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/08 14:59:16 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Imprime o valor da variavel, tudo que esta antes do sinal de =*/
void	print_variable(char *var)
{
	char	*aux;

	aux = ft_calloc(sizeof(char), ft_strclen(var, '=') + 2);
	ft_strlcpy(aux, var, ft_strclen(var, '=') + 2);
	ft_printf("declare -x %s", aux);
	free (aux);
}

/*Imprime o valor da variavel, tudo que esta depois do sinal de =*/
void	print_value(char *var)
{
	char	*aux;

	aux = ft_calloc(sizeof(char), ft_strlen(var) - ft_strclen(var, '=') + 1);
	ft_strlcpy(aux, var + ft_strclen(var, '=') + 1, ft_strlen(var) + 1);
	ft_printf("\"%s\"\n", aux);
	free (aux);
}

/*Essa função ordena a lista de variaveis de ambiente de acordo com a tabela
ascii e imprime de acordo com a formatação da export*/
void	sort_print_export(t_env *exp)
{
	t_var	*current;
	char	*aux;

	exp->i = 0;
	current = exp->head;
	aux = NULL;
	sort_ascii(exp);
	while (exp->i++ < exp->size)
	{
		print_variable(current->var);
		free (aux);
		if (ft_strchr(current->var, '='))
		{
			print_value(current->var);
			free (aux);
		}
		else
			ft_printf("\n");
		current = current->next;
	}
}

int	variable_treatment(t_main *main, char *variable)
{
	if (variable[0] == '=')
	{
		if (main->flags.not_print == false)
			error_export(STDERR_FILENO);
		return (2);
	}
	if (!ft_strchr(variable, '='))
	{
		if (verify_var(main, variable) == false)
			insert_var(&main->export_list, variable);
	}
	else
	{
		if (modify_var(&main->export_list, variable) == false)
			insert_var(&main->export_list, variable);
		if (modify_var(&main->env_list, variable) == false)
			insert_var(&main->env_list, variable);
	}
	return (0);
}

void	export(t_main *main, char **array, bool child)
{
	int	exit_code;

	main->env_list.i = 1;
	exit_code = 0;
	if (array[1] == 0 || ft_strcmp(array[1], ";") == 0)
	{
		if (main->flags.not_print == false)
			sort_print_export(&main->export_list);
	}
	else
	{
		while (array[main->env_list.i] != NULL)
		{
			if (main->flags.not_print == false)
				main->error = validations_ch(array[main->env_list.i],
						STDERR_FILENO, array[0]);
			if (main->error)
				exit_code = main->error;
			else
				exit_code = variable_treatment(main, array[main->env_list.i]);
			main->env_list.i++;
		}
	}
	exit_child(main, exit_code, child);
}
