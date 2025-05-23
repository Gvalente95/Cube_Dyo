/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:51:20 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/05/05 11:01:19 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	init_inv_pages(t_inventory *inv)
{
	int	i;
	int	x;

	inv->num_pages = 3;
	inv->num_items[0] = PCKP_TYPE_LEN - 1;
	inv->num_items[1] = 5;
	inv->num_items[2] = 0;
	inv->page = 0;
	x = -1;
	while (++x < inv->num_pages)
	{
		i = -1;
		while (x == 0 && ++i < inv->num_items[x])
			inv->items[i] = 0;
		while (x == 1 && ++i < inv->num_items[x])
			inv->pokemon_team[i] = NULL;
		inv->hov_indexes[x] = 0;
	}
}

void	init_inventory(t_md *md, t_inventory *inv)
{
	const t_vec2	sz = _v2(md->prm.txt_sc * 20);
	const int		tx_sc = md->prm.txt_sc;
	const int		line_h = md->prm.txt_sc * 1.75f;
	const t_vec2	pannel_sz = v2((tx_sc * 1.2f) * 5, line_h * 3);

	init_inv_pages(inv);
	inv->active = 0;
	inv->sel_i = -1;
	inv->img = init_img(md, sz, NULL, -1);
	inv->sz = inv->img->size;
	inv->p = v2(md->win_sz.x / 2 - sz.x / 2, md->win_sz.y / 2 - sz.y / 2);
	inv->held_used = 0;
	inv->opt_img = init_img(md, pannel_sz, NULL, _BLACK);
	inv->opt_sz = inv->opt_img->size;
	inv->held_sz = _v2(md->win_sz.x * .2);
	inv->held_screen_img = NULL;
	inv->held_i = -1;
	inv->line_height = line_h;
	md->inv.inv_map = NULL;
}
