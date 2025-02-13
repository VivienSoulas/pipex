/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:47 by vsoulas           #+#    #+#             */
/*   Updated: 2025/02/13 14:32:57 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// unset PATH goes into seg fault
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		perror("Error: Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	initial_struct(argv, &pipex);
	ft_create_pipe(&pipex);
	ft_check_args_cmd1(&pipex, envp);
	ft_check_args_cmd2(&pipex, envp);
	ft_create_fork(&pipex, envp);
	return (EXIT_SUCCESS);
}

// split the arguments into command(s) and argument(s)
// check if the command is found and executable with access()
// find the path of the command
void	ft_check_args_cmd1(t_pipex *pipex, char **envp)
{
	if (pipex->arg1 == NULL || pipex->arg1[0] == '\0')
	{
		pipex->path_cmd1 = NULL;
		return ;
	}
	pipex->cmd1 = ft_split(pipex->arg1, ' ');
	if (pipex->cmd1 == NULL || pipex->cmd1[0][0] == '\0')
		exit(EXIT_FAILURE);
	if (access(pipex->cmd1[0], F_OK | X_OK) == 0)
	{
		pipex->path_cmd1 = ft_strdup(pipex->cmd1[0]);
		if (pipex->path_cmd1 == NULL)
		{
			ft_free_split(pipex->cmd1);
			exit(EXIT_FAILURE);
		}
	}
	else
		pipex->path_cmd1 = get_env_path(pipex->cmd1[0], envp, pipex);
}

void	ft_check_args_cmd2(t_pipex *pipex, char **envp)
{
	if (pipex->arg2 == NULL || pipex->arg2[0] == '\0')
	{
		pipex->path_cmd2 = NULL;
		return ;
	}
	pipex->cmd2 = ft_split(pipex->arg2, ' ');
	if (pipex->cmd2 == NULL || pipex->cmd2[0][0] == '\0')
		ft_clean_up(pipex);
	if (access(pipex->cmd2[0], F_OK | X_OK) == 0)
	{
		pipex->path_cmd2 = ft_strdup(pipex->cmd2[0]);
		if (pipex->path_cmd2 == NULL)
		{
			ft_clean_up(pipex);
			exit(EXIT_FAILURE);
		}
	}
	else
		pipex->path_cmd2 = get_env_path(pipex->cmd2[0], envp, pipex);
}

// fork first child process and check for errors
// if first child1 succeded: call ft_child1
// execute commade
// if child2 succeded: call ft_child2;
void	ft_create_fork(t_pipex *pipex, char **envp)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		ft_clean_up(pipex);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		ft_child1(pipex, envp);
		ft_clean_up(pipex);
		exit(EXIT_FAILURE);
	}
	ft_fork_pid2(envp, pipex);
}

void	ft_fork_pid2(char **envp, t_pipex *pipex)
{
	pid_t	pid2;
	int		status;

	pid2 = fork();
	if (pid2 == -1)
	{
		ft_clean_up(pipex);
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		ft_child2(pipex, envp);
		ft_clean_up(pipex);
		exit(127);
	}
	ft_clean_up(pipex);
	waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}
