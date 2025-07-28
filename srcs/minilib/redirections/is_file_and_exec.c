/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_file_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:26:48 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/25 21:04:09 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// int is_file_and_exec(char *file)
// {
//     static struct stat info;
//       // Call stat() to get file info; returns -1 on error
//     if (stat(file, &info) == -1)
//     {
//         perror("error stat"); // Print detailed error message (e.g., No such file)
//         return 1;             // Exit with error code
//     }

//     // Check if file is a regular file AND has execute permission for owner
//     if (S_ISREG(info.st_mode) && (info.st_mode & S_IXUSR) != 0)
//         printf("%s is a regular executable file.\n", file);
//     else
//         printf("%s is NOT a regular executable file.\n", file);

//     return 0; // Successful program termination
// }