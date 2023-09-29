/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:47:44 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/29 11:48:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*fazer uma funcao que dá erro em: - + * = % ? / | \ () e não adicionar
export -=jenny : bash: export: -=: invalid option
export: usage: export [-nf] [name[=value] ...] or export -p
export+=jenny : bash: export: `+=jenny': not a valid identifier
export *=jenny: bash: export: `*=jenny': not a valid identifier
export =jenny: bash: export: `=jenny': not a valid identifier(o nosso faz: minishell: zsh: bad assignment)
export %=jenny: bash: export: `%=jenny': not a valid identifier
export ?=jenny: bash: export: `?=jenny': not a valid identifier
export /=export: bash: export: `/=export': not a valid identifier
export |=export: bash: =export: command not found
export \=export: bash: export: `=export': not a valid identifier
export (=export: bash: syntax error near unexpected token `=export'
export )=export: bash: syntax error near unexpected token `)'*/

void swap_var(t_var *var1, t_var *var2)
{
	char	*temp;

	temp = ft_strdup(var1->var);
    free(var1->var);
    var1->var = ft_strdup(var2->var);
    free(var2->var);
    var2->var = temp;
}

void sort_ascii(t_env *exp)
{
    int count = 0;
    t_var *current;

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

void ft_export(t_env *exp)
{
    t_var *current;
    char *temp;

    current = exp->head;
    exp->i = 0;
    sort_ascii(exp);
	ft_printf("size exp: %d\n", exp->size);
    while (exp->i++ < exp->size)
    {
		ft_printf("%d: ", current->index);
        temp = ft_calloc(sizeof(char),ft_strclen(current->var, '=') + 2);
        ft_strlcpy(temp, current->var, ft_strclen(current->var, '=') + 2);
        ft_printf("declare -x %s", temp);
        free(temp);
		if (ft_strchr(current->var, '='))
		{
			temp = ft_calloc(sizeof(char), ft_strlen(current->var) - ft_strclen(current->var, '=') + 1);
			ft_strlcpy(temp, current->var + ft_strclen(current->var, '=') + 1, ft_strlen(current->var) + 1);
			ft_printf("\"%s\"\n", temp);
        	free(temp);
		}
		else
			ft_printf("\n");
        current = current->next;
    }
}

void export(t_main *main, char **array, bool child)
{
	int	i;

    i = 1;
    if (array[1] == 0)
	{
		if (main->flags.not_print == false)
        	ft_export(&main->export_list);
	}
    else
    {
        while(array[i] != NULL)
        {
            if (array[i][0] == '=') //fazer uma funcao que dá erro em: - + * = % ? / | \ ()
			{
				if (main->flags.not_print == false)
					error_export(STDERR_FILENO);
                if (child)
                    exit(2);
                set_exit_code(main, 2);
			}
			else
            {
                if (!ft_strchr(array[i], '='))
                {
					if (modify_var_exp(main, array[i]) == false)
               			insert_var_exp(main, array[i]);
                }
            	else
				{
					if (modify_var_exp(main, array[i]) == false)
               			insert_var_exp(main, array[i]);
					if (modify_var_env(main, array[i]) == false)
               			insert_var_env(main, array[i]);
				}
            }
            i++;
        }
    }
    if (child)
        exit(0);
    set_exit_code(main, 0);
}
