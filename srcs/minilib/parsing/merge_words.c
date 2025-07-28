/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:34:15 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 19:44:46 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** This function merges consecutive WORD tokens that should be "glued" together
** because they appeared in the input string with no spaces between them.
** For example: "HELLO"'$USER' becomes one token "HELLOasmaa".
**
** It works by using two pointers:
** - 'i' is the "read" pointer, which iterates through the original token array.
** - 'k' is the "write" pointer, which points to the position in the new,
**   condensed token array.
*/
void merge_words(t_minishell *ms)
{
    t_token **orig;
    int       i;
    int       k;

    if (!ms || !ms->tok)
        return;

    orig = ms->tok;
    i = 0; // read index
    k = 0; // write index

    while (orig[i])
    {
        // Always copy the current token to the write position.
        // If they are the same token (i == k), this does nothing.
        // If tokens have been merged, this moves a later token to an earlier slot.
        ms->tok[k] = orig[i];

        // Check if the NEXT token can be merged into the CURRENT one.
        while (orig[i + 1]
               && ms->tok[k]->type == INUPT_WORD
               && orig[i + 1]->type == INUPT_WORD
               && orig[i + 1]->glued == 1)
        {
            char *joined_word;

            // Merge the two words together.
            joined_word = ft_strjoin(ms->tok[k]->word, orig[i + 1]->word);
            if (!joined_word)
                ft_exit(ms, "malloc failed", 1);

            // Free the old word in our destination token.
            free(ms->tok[k]->word);
            // Assign the new, joined word.
            ms->tok[k]->word = joined_word;

            // *** THE MAIN FIX IS HERE ***
            // We MUST free the token that we just absorbed, otherwise it is a memory leak.
            free(orig[i + 1]->word);
            free(orig[i + 1]);

            // Advance the read pointer ('i') to skip over the token we just merged.
            i++;
        }
        // Advance both pointers to move to the next position.
        k++;
        i++;
    }

    // Null-terminate the new, shorter token array.
    ms->tok[k] = NULL;
    // Update the total token count.
    ms->tokens_count = k;
}