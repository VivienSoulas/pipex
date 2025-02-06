/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:01:14 by vsoulas           #+#    #+#             */
/*   Updated: 2025/02/06 16:17:35 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Permissions: 0644 (rw-r--r--)
void	initial_struct(char **argv, t_pipex *pipex)
{
	pipex->infile = argv[1];
	pipex->arg1 = argv[2];
	pipex->arg2 = argv[3];
	pipex->outfile = argv[4];
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->path_cmd1 = NULL;
	pipex->path_cmd2 = NULL;
}

// create a pipe and check for errors
// pipe is a 2D array of file descriptors
// pipe_fd[0] is the read end of the pipe
// pipe_fd[1] is the write end of the pipe
void	ft_create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		ft_clean_up(pipex);
		perror("Error: Could not create pipe\n");
		exit(EXIT_FAILURE);
	}
}

// Manually search each sub-array of envp for "PATH="
// return the path +5 (so wihtout "PATH=") if found, NULL if not found
char	*ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

//	redirect standard input to infile (pipex->in_fd)
//	redirect standard output to pipe_fd[1] (pipe write end)
// close unused file descriptors :
//		pipe_fd[0] read end of the pipe
//		pipe-fd[1] after duplication
void	ft_child1(t_pipex *pipex, char **envp)
{
	pipex->in_fd = open(pipex->infile, O_RDONLY);
	if (pipex->in_fd == -1)
	{
		ft_clean_up(pipex);
		ft_printf("bash: %s: No such file or directory\n", pipex->infile);
		exit(EXIT_FAILURE);
	}
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->path_cmd1, pipex->cmd1, envp);
}

void	ft_child2(t_pipex *pipex, char **envp)
{
	pipex->out_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd == -1)
	{
		ft_clean_up(pipex);
		ft_printf("Error: could not write in %s\n", pipex->outfile);
		exit(EXIT_FAILURE);
	}
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->path_cmd2, pipex->cmd2, envp);
	exit(127);
}
