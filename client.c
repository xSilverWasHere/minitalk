/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:25:51 by jpedro-g          #+#    #+#             */
/*   Updated: 2025/11/10 09:52:10 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_g_bit_received;

static void	send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		exit(ft_printf("Error sending signal\n"));
	g_bit_received = 0;
	while (!g_bit_received)
		pause();
}

void	handle_server_signal(int signum)
{
	if (signum == SIGUSR1)
		g_bit_received = 1;
}

static void	send_char(int pid, char *message)
{
	int		i;
	int		bit_pos;
	char	current_char;

	i = 0;
	while (1)
	{
		current_char = message[i];
		bit_pos = 7;
		while (bit_pos >= 0)
		{
			send_bit(pid, (current_char >> bit_pos) & 1);
			bit_pos--;
		}
		if (current_char == '\0')
			break ;
		i++;
	}
}

void	send_string(int pid, char *str)
{
	send_char(pid, str);
	send_char(pid, "\0");
}

int	main(int ac, char **av)
{
	struct sigaction	sig;
	int					pid;

	pid = ft_atoi(av[1]);
	if (ac != 3)
		exit (ft_printf("Invalid args\n"));
	if (pid > PID_MAX || pid <= 0)
		exit (ft_printf("Invalid PID\n"));
	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = &handle_server_signal;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		exit(ft_printf("Error setting up signal handler\n"));
	send_string(pid, av[2]);
	send_string(pid, "\n");
	ft_printf("Message sent!\n");
}
