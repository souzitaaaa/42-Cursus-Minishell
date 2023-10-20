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

char	*expand_more(t_main *main, char *str)
{
	int		i;
	char	**arr;
	char	*out;

	i = 0;
	arr = ft_split(str, 36);
	while (arr[i])
	{
		if (i != 0 || (i == 0 && *str == '$'))
		{
			arr[i] = ft_strjoinfree2("$", arr[i]);
			arr[i] = expand(main, arr[i]);
		}
		i++;
	}
	out = ft_arr_to_str(arr, str);
	ft_free_str(&str);
	ft_free_array(&arr);
	return (out);
}

int	get_min_len(char *str, int i)
{
	int		min;

	min = 0;
	min = get_min(ft_strclen(str + i + 1, ' '),
			ft_strclen(str + i + 1, SQUOTE));
	min = get_min(min, ft_strclen(str + i + 1, '\n'));
	return (min);
}

char	*expand_var(t_main *main, char *str, int i)
{
	int		count;
	char	*expanded;
	char	*out;
	t_var	*aux;

	aux = main->env_list.head;
	count = 0;
	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str + i + 1, aux->var, get_max(ft_strclen(aux->var, '='),
					get_min_len(str, i))) == 0)
		{
			expanded = ft_calloc(ft_strlen(aux->var)
					- ft_strclen(aux->var, '=') + 1, sizeof(char *));
			ft_strlcpy(expanded, aux->var + ft_strclen(aux->var, '=') + 1,
				ft_strlen(aux->var) - ft_strclen(aux->var, '=') + 2);
			out = join_expanded(str, expanded, ft_strclen(aux->var, '=') + 1);
			ft_free_str(&expanded);
			return (out);
		}
		aux = aux->next;
	}
	out = join_expanded(str, "\0", ft_strclen(str, ' ') - i);
	return (out);
}

//* Vai tratar de expandir a string para a o seu respetivo valor
//*  na variavel de ambiente ela vai percorrer a lista das
//*  env ate achar uma identica ao valor que lhe manda-mos quando
//*  encontrar vai copiar oque esta depois do = para dentro dessa str
char	*expand(t_main *main, char *str)
{
	char	*expanded;
	int		i;
	char	*out;

	i = ft_strclen(str, '$');
	if (check_more_var(str, i + 1) == true)
	{
		expanded = expand_more(main, str);
		return (expanded);
	}
	if (str[i + 1] == ' ' || str[i + 1] == '\0')
		return (str);
	if (ft_strncmp(str + i, "$?", 2) == 0)
		out = expand_exitcode(main, str);
	else
		out = expand_var(main, str, i);
	ft_free_str(&str);
	return (out);
}
