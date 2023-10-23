/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:34 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/09 12:06:04 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	cd(char *path, t_main *main, bool child)
{
	char	*new_path;
	int		dir;
	char	*current;
	char	*path_pwd;
	char	*prev;

	current = ft_calloc(sizeof(char), 4096);
	getcwd(current, 4096);
	if (path == NULL || (path[0] == '~' && path[1] == '\0')) // cd sozinho e cd ~
	{
		new_path = get_envvar("HOME", &main->env_list);
		if (new_path)
		{
			dir = change_dir(new_path, main, child);
			if (dir == 0)
			{
				path_pwd = ft_calloc(sizeof(char), 4096);
				getcwd(path_pwd, 4096);
				refresh_pwd(main, path_pwd);
				refresh_oldpwd(main, current);
			}
		}
		else
		{
			if (main->flags.not_print == false)
				error_cd(STDERR_FILENO, "HOME");
			exit_child(main, 1, child);
			return ;
		}
	}
	else // cd -
	{
		if (ft_strcmp(path, "-") == 0)
		{
			prev = get_envvar("OLDPWD", &main->env_list);
			if(prev)
			{
				dir = change_dir(prev, main, child);
				if (dir == 0)
				{
					if (main->flags.not_print == false)
						ft_printf("%s\n", prev);
					path_pwd = ft_calloc(sizeof(char), 4096);
					getcwd(path_pwd, 4096);
					refresh_pwd(main, path_pwd);
					refresh_oldpwd(main, current);
				}
			}
			else
			{
				if (main->flags.not_print == false)
					error_cd(STDERR_FILENO, "OLDPWD");
				exit_child(main, 1, child);
				return ;
			}
		}
		else //cd normal
		{
			dir = change_dir(path, main, child);
			if (dir == 0)
			{
				path_pwd = ft_calloc(sizeof(char), 4096);
				getcwd(path_pwd, 4096);
				refresh_pwd(main, path_pwd);
				refresh_oldpwd(main, current);
			}
		}
		exit_child(main, 0, child);
	}
}*/

void	only_cd(char *current, t_main *main, bool child)
{
	char	*new_path;
	char	*path_pwd;
	int		dir;

	new_path = get_envvar("HOME", &main->env_list);
	if (new_path)
	{
		dir = change_dir(new_path, main, child);
		if (dir == 0)
		{
			path_pwd = ft_calloc(sizeof(char), 4096);
			getcwd(path_pwd, 4096);
			refresh_pwd(main, path_pwd);
			refresh_oldpwd(main, current);
		}
	}
	else
	{
		if (main->flags.not_print == false)
			error_cd(STDERR_FILENO, "HOME");
		exit_child(main, 1, child);
		return ;
	}
}

void	previous_path(char *current, t_main *main, bool child)
{
	int		dir;
	char	*path_pwd;
	char	*prev;

	prev = get_envvar("OLDPWD", &main->env_list);
	if (prev)
	{
		dir = change_dir(prev, main, child);
		if (dir == 0)
		{
			if (main->flags.not_print == false)
				ft_printf("%s\n", prev);
			path_pwd = ft_calloc(sizeof(char), 4096);
			getcwd(path_pwd, 4096);
			refresh_pwd(main, path_pwd);
			refresh_oldpwd(main, current);
		}
	}
	else
	{
		if (main->flags.not_print == false)
			error_cd(STDERR_FILENO, "OLDPWD");
		exit_child(main, 1, child);
		return ;
	}
}

void	regular_cd(char *current, char *path, t_main *main, bool child)
{
	int		dir;
	char	*path_pwd;

	dir = change_dir(path, main, child);
		if (dir == 0)
		{
			path_pwd = ft_calloc(sizeof(char), 4096);
			getcwd(path_pwd, 4096);
			refresh_pwd(main, path_pwd);
			refresh_oldpwd(main, current);
		}
}

void	cd(char *path, t_main *main, bool child)
{
	char	*current;

	current = ft_calloc(sizeof(char), 4096);
	getcwd(current, 4096);
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		only_cd(current, main, child);
	else if (ft_strcmp(path, "-") == 0)
		previous_path(current, main, child);
	else
		regular_cd(current, path, main, child);
	exit_child(main, 0, child);
	//free(current);
}