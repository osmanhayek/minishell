// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_advsplit.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/01 21:39:41 by ohayek            #+#    #+#             */
// /*   Updated: 2023/08/06 21:09:36 by ohayek           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// #define MAX_COMMAND_LENGTH 100

// void ft_run_exit()
// {
//     exit(0);
// }

// int main() {
//     int pid;
//     char    buffer[MAX_COMMAND_LENGTH];
    
//     pid = fork();
    
//     if (pid == 0) {
//         ft_run_exit(); // Replace with the desired directory path
//     } else {
//         wait(NULL);
//         printf("HELLO");
//     }
    
//     return 0;
// }
