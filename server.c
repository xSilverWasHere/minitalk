/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:03:43 by jpedro-g          #+#    #+#             */
/*   Updated: 2025/10/29 10:48:17 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_client_signal(int signum, siginfo_t *siginfo, void *context)
{
	static char	current_char;
	static int	bit_index;

	(void) context;
	current_char <<= 1;
	current_char |= (signum == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", current_char);
		bit_index = 0;
		current_char = 0;
	}
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
		exit(ft_printf("Error sending signal\\n"));
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = &handle_client_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(ft_printf("Error setting up signal handler\n"));
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
