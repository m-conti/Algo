/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:37:51 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 15:37:53 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	visu_process(t_core *core, t_process *proc)
{
	int		i;

	i = 0;
	while (i < REG_NUMBER)
		mvprintw(Y_REG + i * 2, X_REG, "Reg[%i] : %#x", i, proc->reg[i]);
}
