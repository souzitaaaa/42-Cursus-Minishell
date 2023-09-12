/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:34 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/12 18:21:35 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//atualizar o OLDPWD e PWD no cd
/*Echo:
•	comando echo nao printa \n
•	quantos mais argumentos são corridos mais \n existem no output
•	echo -na ola nao funciona, nao printa o ola na mesma linha que o prompt
•	echo -nnnnnnnnn -nnnnnnnnna nao funciona, nao esta a printar o                       -nnnnnnnnna  na mesma linha que o prompt
Export:
•	export 2=mario nao pode funcionar
•	export PATH=ola coloca o programa a receber input  deixa de funcionar ???
•	export PAT=olaaaaaaaaaaaaaaaaaaa da heap use after free 
(ultils_export.c linha 83)
•	export ola= ; se tentar unset ola a variável continua presente */
char	*only_cd(t_main *main, bool  child)
{
	char *home;
	char *aux;
	
	home = getenv("HOME");
	if (home == NULL)
	{
		error_cd(STDERR_FILENO);
		if (child)
			exit(1);
		set_exit_code(main, 1);
		return (NULL);
	}
	aux = ft_substr(home, 1, ft_strlen(home) - 1);
	free(aux);
	return (home);
}

char *find_home(char *path, t_main *main, bool child)
{
	char *home;
	char *aux;

	if (path[0] == '~')
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			error_msg_file(path, STDERR_FILENO);
			if (child)
				exit(1);
			set_exit_code(main, 1);
			return (NULL);
		}
		aux = ft_substr(path, 1, ft_strlen(path) - 1);
		free(aux);
		return (home);
	}
	return (ft_strdup(path));
}

int change_dir(char *path, t_main *main, bool child)
{
	if (chdir(path) == 0)
		set_exit_code(main, 0);
	else
	{
		error_msg_file(path, STDERR_FILENO);
		if (child)
			exit(1);
		set_exit_code(main, 1);
	}
	return (0);
}

void cd(char *path, t_main *main, bool child)
{
	char	*new_path;
	int		dir;
	char	*current;

	if (path == NULL)
	{
		new_path = only_cd(main, child);
		current = ft_calloc(sizeof(char), 4096);
		getcwd(current, 4096);
		change_dir(new_path, main, child);
		dir = change_dir(new_path, main, child);
		if (dir == 0)
			{
				main->prev = ft_calloc(sizeof(char), ft_strlen(current) + 1);
				ft_strlcpy(main->prev, current, ft_strlen(current) + 1);
			}
	}
	else
	{
		if (ft_strcmp(path, "-") == 0)
		{
			if (main->prev)
			{
				change_dir(main->prev, main, child);
				ft_printf("%s\n", main->prev);
			}
			else
			{
				error_cd(STDERR_FILENO);
				if (child)
					exit(1);
				set_exit_code(main, 1);
			}
		}
		else
		{
			new_path = find_home(path, main, child);
			current = ft_calloc(sizeof(char), 4096);
			getcwd(current, 4096);
			dir = change_dir(new_path, main, child);
			if (dir == 0)
			{
				main->prev = ft_calloc(sizeof(char), ft_strlen(current) + 1);
				ft_strlcpy(main->prev, current, ft_strlen(current) + 1);
				
			}
		}
		if (child)
			exit(0);
		set_exit_code(main, 0);
	}
}