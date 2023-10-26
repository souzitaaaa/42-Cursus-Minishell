/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:00:31 by joe               #+#    #+#             */
/*   Updated: 2023/10/26 23:59:04 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*
COLORS
*/
# define RESET "\033[0m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN 	"\033[1;36m"
# define WHITE 	"\033[1;37m"
# define BRIGHT_BLUE "\033[1;94m"
# define BRIGHT_MAGENTA 	"\033[1;95m"
# define GRAY	"\033[1;90m"

//Reset
# define COLOUR_RESET "\001\033[0m\002"

# define SYNTAX_ERROR "syntax error near unexpected token `"
# define CMD_ERROR "command not found"
# define FILE_ERROR "No such file or directory"
# define FD_ERROR "Bad file descriptor"
# define IS_D "Is a directory"
# define P_D "Permission denied"
# define AMBIG "ambiguous redirect"

# define SQUOTE 39
# define DQUOTE 34

#endif
