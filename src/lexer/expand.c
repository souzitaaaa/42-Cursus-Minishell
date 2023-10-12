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

//Coisas a fazer:
//$ sozinho ou no final tem de imprimir $
// echo "$jdajks sjhkd"
//echo "                $USER           $m   hjgh     $PWD              gjg$"

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

//*A partir da posição seguinte ao 1o $ verifica se há mais $
bool    check_more_var(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char    *ft_arr_to_str(char **arr)
{
	int     i = 0;
	char    *out;
	
	out = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	i = 0;
	while (arr[i])
	{
		out = ft_strjoinfree(out, arr[i]);
		i++;
	}
	printf("Str pós juntar: %s\n", out);
	return (out);
}

char	*expand(t_main *main, char *str);

char	*expand_more(t_main *main, char *str)
{
	printf("\033[1;32m\t\t[Expanding More]\033[0m\n");
	int i = 0;
	char **arr;
	
	arr = ft_split(str, 36);
			printf("Arr das vars: \n");
			print_arr(arr);
	while (arr[i])
	{
		if (i != 0 || (i == 0 && *str == '$'))
		{
			arr[i] = ft_strjoin("$", arr[i]); //!DAR FREE AO ARR[i]
			arr[i] = expand(main, arr[i]);
		}
		i++;
	}
			printf("Arr das vars depois de expandir: \n");
			print_arr(arr);
	return (ft_arr_to_str(arr));
}

//* Vai tratar de expandir a string para a o seu respetivo valor na variavel de ambiente
	//* ela vai percorrer a lista das env ate achar uma identica ao valor que lhe manda-mos
	//* quando encontrar vai copiar oque esta depois do = para dentro dessa str
char	*expand(t_main *main, char *str)
{
	int		count = 0;
	t_var	*aux = main->env_list.head;
	char	*expanded;
	int     i = 0;
	char	*out;

	printf("str: .%s.\n", str);
	i = ft_strclen(str, '$');
	if (check_more_var(str, i + 1) == true)
	{
		expanded = expand_more(main, str);
		return (expanded);
	}
	printf("str: .%s.\n", str);
	printf("\033[1;32m\t\t[Expanding 1]\033[0m\n");
	printf("str: %s and str + 1: %s\n", str, str + 1);
	if (ft_strncmp(str + i, "$?", 2) == 0)
	{
		printf("Encontrada variavel de ambiente: %s\n\tExit code: %i\n", str, main->exit_code);
		expanded = ft_calloc(get_number_len(main->exit_code), sizeof(char));
		expanded = ft_itoa(main->exit_code);
		out = join_expanded(str, expanded, 2);
		return (out);
	}
	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str + i + 1, aux->var, ft_strclen(aux->var, '=')) == 0)
		{
			printf("Encontrada variavel de ambiente: %s\n\tNa envp: %s\n", str, aux->var);
			expanded = ft_calloc(ft_strlen(aux->var) - ft_strclen(aux->var, '=') + 1, sizeof(char *));
			ft_strlcpy(expanded, aux->var + ft_strclen(aux->var, '=') + 1, ft_strlen(aux->var) - ft_strclen(aux->var, '=') + 2);
			out = join_expanded(str, expanded, ft_strclen(aux->var, '=') + 1);
			printf("\033[1;32m\t\t[End expanding 2]\033[0m\n");
			return (out);
		}
		aux = aux->next;
	}
			printf("\033[1;32m\t\t[End expanding 1]\033[0m\n");
	return("\0");
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
