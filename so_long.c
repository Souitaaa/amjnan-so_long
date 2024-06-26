/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:38 by csouita           #+#    #+#             */
/*   Updated: 2024/04/29 18:17:25 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int keycode_print(int keycode, t_data *data)
// {
//     (void)data;
//     printf("%d\n", keycode);
//     return 0;
// }
void map_rectangle(t_data *data)
{
    // printf("H = %d",data->height);
    // printf("W = %d",data->width);

    if (data->height == data->width)
    {
        write(1, "map is not rectangular", 23);
        exit(1);
    }
}

void exit_position(t_data *data)
{
    int i = 0;
    int j = 0;

    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (data->map[i][j] == 'E')
            {
                data->exit_height = i;
                data->exit_width = j;
            }
            j++;
        }
        i++;
    }
}
int all_collected(t_data *data)
{
    int i = 0;
    int j = 0;

    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (data->map[i][j] == 'C')
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

int move_player(int keycode, t_data *data)
{
    // printf("proob %d",keycode);
    if (keycode == Q || keycode == ESC)
    {
        close_window(data);
    }
    if (keycode == UP_KEY || keycode == W)
        print_up(data);
    if (keycode == LEFT_KEY || keycode == A)
        print_left(data);
    if (keycode == DOWN_KEY || keycode == S)
        print_down(data);
    if (keycode == RIGHT_KEY || keycode == D)
        print_right(data);
    player_position(data);
    draw_map(data);

    return 0;
}

int main(int ac, char *av[])
{
    (void)ac;
    t_data data;
    data.flag = 7;
    data.moves = 0;
    data.player_height = 0;
    data.player_width = 0;
    ft_memset(&data, 0, sizeof(int));
    data.height = 0;
    check_path(av[1]);
    map_check(av[1], &data);
    map_width(av[1], &data);
    map_rectangle(&data);
    map_arr(av[1], &data);
    check_map_border(&data);
    store_content(&data);
    check_exist_items(&data);
    check_file(&data);
    fill_items(&data);
    draw_map(&data);
    player_position(&data);
        printf("%d\n",data.player_height);
        printf("%d",data.player_width);
    // flood_fill(&data, data.player_height, data.player_width);
    // flood_fill_checker(&data);
    mlx_key_hook(data.mlx_window,move_player, &data);
    draw_map(&data);
    mlx_hook(data.mlx_window, 17, 0, close_window, &data);
    mlx_loop(data.mlx_ptr);
}
