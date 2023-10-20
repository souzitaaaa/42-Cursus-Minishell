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

/*Essa funcao percorre a lista de variaveis e ordena de acordo com a tabela ascii*/
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

/*Essa função ordena a lista de variaveis de ambiente de acordo com a tabela ascii e imprime de acordo com a
formatação da export*/
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

void	export(t_main *main, char **array, bool child)
{
	int	i;
	int	exit_code;
	int	error;

	i = 1;
	exit_code = 0;
	error = 0;
	if (array[1] == 0 || ft_strcmp(array[1], ";") == 0)
	{
		if (main->flags.not_print == false)
			sort_print_export(&main->export_list);
	}
	else
	{
		while(array[i] != NULL)
		{
			if (main->flags.not_print == false)
				error = validations_ch(array[i], STDERR_FILENO, array[0]);
			if (error)
			{
				exit_code = error;
				i++;
				continue ;
			}
			if (array[i][0] == '=')
			{
				if (main->flags.not_print == false)
					error_export(STDERR_FILENO);
				exit_child(main, 2, child);
			}
			else
			{
				if (!ft_strchr(array[i], '='))
				{
					if (verify_var(main, array[i]) == false)
						insert_var_exp(main, array[i]);
				}
				else
				{
					if (modify_var(&main->export_list, array[i]) == false)
						insert_var_exp(main, array[i]);
					if (modify_var(&main->env_list, array[i]) == false)
						insert_var_env(main, array[i]);
				}
			}
			i++;
		}
	}
	exit_child(main, exit_code, child);
}
