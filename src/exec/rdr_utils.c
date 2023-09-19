/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:36:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/30 19:36:58 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	 set_rdr_err(t_main *main)
{
	main->flags.rdr_err = true;
}

void	rdr_error(char *str, t_main *main, int options)
{
	//!ERROR HANDLING "bad file descriptor" set exit code
	if (options == 0)
		error_msg_file(str, STDERR_FILENO);
	if (options == 1)
		error_msg_fd(str, STDERR_FILENO);
	set_rdr_err(main); //parar os rdr exceto o here doc
}
