// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int is_delimiter(char c, char *del) {
//     while (*del) {
//         if (c == *del)
//             return 1;
//         del++;
//     }
//     return 0;
// }

// int count_tokens(char *str, char *del) {
//     int count = 0;
//     int is_token = 0;

//     while (*str) {
//         if (is_delimiter(*str, del)) {
//             if (is_token) {
//                 is_token = 0;
//                 count++;
//             }
//         } else {
//             is_token = 1;
//         }
//         str++;
//     }

//     if (is_token)
//         count++;

//     return count;
// }

// char **ft_split(char *str, char *del) {
//     int token_count = count_tokens(str, del);
//     char **tokens = (char **)malloc((token_count * 2 + 1) * sizeof(char *));

//     if (tokens == NULL)
//         return NULL;

//     int index = 0;
//     int token_start = 0;
//     int token_length = 0;

//     while (*str) {
//         if (is_delimiter(*str, del)) {
//             if (token_length > 0) {
//                 tokens[index] = (char *)malloc((token_length + 1) * sizeof(char));
//                 strncpy(tokens[index], str - token_length, token_length);
//                 tokens[index][token_length] = '\0';
//                 index++;
//             }
//             tokens[index] = (char *)malloc(2 * sizeof(char));
//             strncpy(tokens[index], str, 1);
//             tokens[index][1] = '\0';
//             index++;
//             token_length = 0;
//         } else {
//             token_length++;
//         }
//         str++;
//     }

//     if (token_length > 0) {
//         tokens[index] = (char *)malloc((token_length + 1) * sizeof(char));
//         strncpy(tokens[index], str - token_length, token_length);
//         tokens[index][token_length] = '\0';
//         index++;
//     }

//     tokens[index] = NULL;
//     return tokens;
// }

// void free_tokens(char **tokens) {
//     if (tokens) {
//         for (int i = 0; tokens[i] != NULL; i++) {
//             free(tokens[i]);
//         }
//         free(tokens);
//     }
// }

// int main() {
//     char str[] = "osman|<<hayek";
//     char del[] = "|<";

//     char **s1 = ft_split(str, del);

//     for (int i = 0; s1[i] != NULL; i++) {
//         printf("s1[%d] = %s\n", i, s1[i]);
//     }

//     free_tokens(s1);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_delimiter(char c, char *del) {
    while (*del) {
        if (c == *del)
            return 1;
        del++;
    }
    return 0;
}

int count_tokens(char *str, char *del) {
    int count = 0;
    int is_token = 0;

    while (*str) {
        if (strncmp(str, ">>", 2) == 0 || strncmp(str, "<<", 2) == 0) {
            if (is_token) {
                is_token = 0;
                count++;
            }
            count++;
            str += 2;
        } else if (is_delimiter(*str, del)) {
            if (is_token) {
                is_token = 0;
                count++;
            }
            count++;
            str++;
        } else {
            is_token = 1;
            str++;
        }
    }

    if (is_token)
        count++;

    return count;
}

char **ft_split_tok(char *str, char *del) {
    int token_count = count_tokens(str, del);
    char **tokens = (char **)malloc((token_count + 1) * sizeof(char *));

    if (tokens == NULL)
        return NULL;

    int index = 0;
    //int token_start = 0;
    int token_length = 0;

    while (*str) {
        if (strncmp(str, ">>", 2) == 0 || strncmp(str, "<<", 2) == 0) {
            if (token_length > 0) {
                tokens[index] = (char *)malloc((token_length + 1) * sizeof(char));
                strncpy(tokens[index], str - token_length, token_length);
                tokens[index][token_length] = '\0';
                index++;
            }
            tokens[index] = (char *)malloc(3 * sizeof(char));
            strncpy(tokens[index], str, 2);
            tokens[index][2] = '\0';
            index++;
            str += 2;
            token_length = 0;
        } else if (is_delimiter(*str, del)) {
            if (token_length > 0) {
                tokens[index] = (char *)malloc((token_length + 1) * sizeof(char));
                strncpy(tokens[index], str - token_length, token_length);
                tokens[index][token_length] = '\0';
                index++;
            }
            tokens[index] = (char *)malloc(2 * sizeof(char));
            strncpy(tokens[index], str, 1);
            tokens[index][1] = '\0';
            index++;
            str++;
            token_length = 0;
        } else {
            token_length++;
            str++;
        }
    }

    if (token_length > 0) {
        tokens[index] = (char *)malloc((token_length + 1) * sizeof(char));
        strncpy(tokens[index], str - token_length, token_length);
        tokens[index][token_length] = '\0';
        index++;
    }

    tokens[index] = NULL;
    return tokens;
}

void free_tokens(char **tokens) {
    if (tokens) {
        for (int i = 0; tokens[i] != NULL; i++) {
            free(tokens[i]);
        }
        free(tokens);
    }
}
