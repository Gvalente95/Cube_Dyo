/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:56:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 12:41:54 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define MENU 1
# define GAME 0
# define BSIZE 1024
# define PSIZE 10
# define STEP 10

# define MENU_SLOTS 3
# define PI 3.14159263589793

# define WI 1024
# define HI 512

# define SCALE_MAP 1

/*	move_limit == 2 * STEP	*/
# define MOVE_LIMIT 20
# define FOV_ANGLE 60.0
# define TILE_SIZE 16
# define FOV 1.0471975512
# define NUM_RAYS WI

/*	PROJ_CTE ==(environ) WI * 30	*/
# define PROJECTION_CONSTANT 42000

# define PLAYER_POS 9
# define WALL 1
# define OBJECT 2

# define MV_MOUSE 6
# define CLOSE 17
# define ESC 65307
# define A_UP 65362
# define A_DOWN 65364
# define A_LEFT 65361
# define A_RIGHT 65363
# define MV_UP 4
# define MV_DOWN 5
# define ENTER 13

# define GREEN 0x00FF00 
# define RED 0xFF0000
# define BLUE 0x0000FF
# define BLACK 0x000000
# define WHITE 0xFFFFFF

#endif
