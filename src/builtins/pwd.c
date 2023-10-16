/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:17:24 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/16 18:12:40 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_main *main, bool child)
{
	char	*pwd;

	pwd = ft_calloc(sizeof(char), 4096);
	getcwd(pwd, 4096);
	ft_printf("%s\n", pwd);
	free(pwd);
	exit_child(main, 0, child);
}
