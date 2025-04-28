/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:02:50 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/02 16:02:52 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	set_param_val(t_sim_params *params, int param_val, int index)
{
	if (index == 0)
		params->number_of_philos = param_val;
	if (param_val > 0)
	{
		if (index == 1)
			params->time_to_die = param_val;
		if (index == 2)
			params->time_to_eat = param_val;
		if (index == 3)
			params->time_to_sleep = param_val;
		if (index == 4)
		{
			params->number_of_meals = param_val;
			return (SUCCESS);
		}
		params->number_of_meals = UNSPECIFIED;
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	update_params(t_sim_params *params, int *index, char **split_argv)
{
	int	params_val;
	int	i;

	i = 0;
	while (split_argv && split_argv[i])
	{
		params_val = ft_atoi(split_argv[i]);
		if (set_param_val(params, params_val, *index) == FAILURE)
			return (FAILURE);
		(*index)++;
		i++;
	}
	return (SUCCESS);
}

t_sim_params	parse_params(int argc, char **argv)
{
	t_sim_params	params;
	char			**split_argv;
	int				index;
	int				i;

	memset(&params, 0, sizeof(t_sim_params));
	index = 0;
	i = 0;
	while (i < argc)
	{
		split_argv = ft_split(argv[i], ' ');
		if (!split_argv)
			exit_with_error_message(UNKNOWN_ERR);
		if (update_params(&params, &index, split_argv) == FAILURE)
		{
			cleanup_double_arr(split_argv);
			exit_with_error_message(INVALID_ARGS_ERR);
		}
		cleanup_double_arr(split_argv);
		i++;
	}
	if (index < 4)
		exit_with_error_message(NOT_ENOUGH_ARGS_ERR);
	return (params);
}
