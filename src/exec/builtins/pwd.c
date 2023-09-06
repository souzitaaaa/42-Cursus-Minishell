/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:17:24 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/04 19:46:16 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pwd(t_main *main, bool child)
{
	char	*pwd;

	pwd = ft_calloc(sizeof(char), 4096);
	getcwd(pwd, 4096);
	ft_printf("%s\n", pwd);
	free(pwd);
	if (child)
        exit(0);
	set_exit_code(main, 0);
}
