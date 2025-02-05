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
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	*infile;
	char	*outfile;
	char	*arg1;
	char	*arg2;
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
	int		pipe_fd[2];
}	t_pipex;

void	ft_check_args_cmd1(t_pipex *pipex, char **envp);
void	ft_check_args_cmd2(t_pipex *pipex, char **envp);
char	*get_env_path(char *cmd, char **envp, t_pipex *pipex);
void	ft_create_fork(t_pipex *pipex, char **envp);
void	ft_free_split(char **array);
void	ft_clean_up(t_pipex *pipex);
void	initial_struct(char **argv, t_pipex *pipex);
void	ft_create_pipe(t_pipex *pipex);
char	*ft_find_path(char **envp);
void	ft_child1(t_pipex *pipex, char **envp);
void	ft_child2(t_pipex *pipex, char **envp);

#endif