/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:47 by vsoulas           #+#    #+#             */
/*   Updated: 2025/01/24 17:04:18 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex infile "ls -l" "wc -l" outfile
// < infile ls -l | wc -l > outfile
int	main(int argc, char **argv)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("Error: Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	pipex.infile = argv[1];
	pipex.arg1 = argv[2];
	pipex.arg2 = argv[3];
	pipex.outfile = argv[4];
	pipex.in_fd = open(pipex.infile, O_RDONLY);
	if (pipex.in_fd == -1)
	{
		ft_printf("Error: Could not open file %s\n", pipex.infile);
		return (EXIT_FAILURE);
	}
	pipex.out_fd = open(pipex.outfile, O_WRONLY | O_CREAT);
		if (pipex.out_fd == -1)
	{
		ft_printf("Error: Could not open file %s\n", pipex.outfile);
		return (EXIT_FAILURE);
	}

	ft_check_args(&pipex);
	ft_create_pipe(&pipex);
	ft_create_fork(&pipex);
	close all file descriptors

	wait for both child processes to finish

	return (0);
}

void	ft_check_args(t_pipex *pipex)
{
	pipex->cm1 = ft_split(pipex->arg1, ' ');
	// check for NULL
	pipex->cm2 = ft_split(pipex->arg2, ' ');
	// check for NULL
	
}
// create a pipe and check for errors
// pipe is a 2D array of file descriptors
// pipe_fd[0] is the read end of the pipe
// pipe_fd[1] is the write end of the pipe
void	ft_create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		ft_printf("Error: Could not create pipe\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_create_fork(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;

// fork first child process and check for errors
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_printf("Couldn't fork pid1\n");
		exit(EXIT_FAILURE);
	}
//if in first child process:
	if (pid1 == 0)
	{
//redirect input from infile (pipex->in_fd)
		dup2(pipex->in_fd, STDIN_FILENO);
//redirect output to pipe_fd[1]
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
//close unused file descriptors
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
	}




	pid2 = fork();
	if (pid2 == -1)
	{
		ft_printf("Couldn't fork pid2\n");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		ft_child2(&pipex);
	}
}
