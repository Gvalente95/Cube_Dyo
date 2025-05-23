/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:00:30 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/05/16 18:02:06 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mlx_utils.h"

void	wrap_mouse(t_md *md, int delta_x, int delta_y)
{
	t_vec2	block_pos;
	t_vec2	delta_block;

	block_pos = v2(md->win_sz.x - 200, md->win_sz.y - 200);
	mlx_mouse_move(md->mlx, md->win, block_pos.x, block_pos.y);
	delta_block = v2(block_pos.x + delta_x, block_pos.y + delta_y);
	md->mouse.prev = block_pos;
	md->mouse.world = block_pos;
	(void)delta_block;
}

void	set_mouse_lock(t_md *md, int lock)
{
	if (lock)
	{
		if (!md->is_linux)
			md->mouse.locked = 1;
	}
	else
	{
		md->mouse.locked = 0;
	}
}
