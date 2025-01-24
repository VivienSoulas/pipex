/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:09:33 by vsoulas           #+#    #+#             */
/*   Updated: 2025/01/24 16:09:02 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <ft_printf.h>
# include <fcntl.h>

typedef struct s_pipex\
{
	int		in_fd;
	int		out_fd;
	char	*infile;
	char	*outfile;
	char	*arg1;
	char	*arg2;
	char	**cm1;
	char	**cm2;
	int		pipe_fd[2];
}	t_pipex;



#endif