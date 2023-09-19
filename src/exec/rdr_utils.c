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

void	rdr_error()
{
	//!ERROR HANDLING "bad file descriptor" set exit code
	set_rdr_err(main); //parar os rdr exceto o here doc
}

//!if rdr_err --> set exit code 1?
//!NAO FAZ O COMANDO


