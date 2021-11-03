#include "pathfinder.h"

int get_node_index(char **nodes, char *node)
{
    for (int i = 0; nodes[i] != NULL; i++)
    {
        if (!mx_strcmp(nodes[i], node)) return i;
    }
    return -1;
}

void mx_del_bridges(t_bridge ***bridges)
{
    for (int i = 0; (*bridges)[i] != NULL; i++)
    {
        mx_strdel(&(*bridges)[i]->A);
        mx_strdel(&(*bridges)[i]->B);
        free((*bridges)[i]);
    }
    *bridges = NULL;
}

t_bridge *mx_get_bridge(const char *s)
{
    t_bridge *res = malloc(sizeof *res);
    char **parts = mx_strsplit(s, ',');
    res->length = mx_atoi(parts[1]);
    char **names = mx_strsplit(parts[0], '-');
    res->A = mx_strdup(names[0]);
    res->B = mx_strdup(names[1]);
    mx_del_strarr(&names);
    mx_del_strarr(&parts);
    return res;
}

int mx_get_weight(char **nodes, int *weights, char *s)
{
    for (int i = 0; nodes[i] != NULL; i++)
    {
        if (!mx_strcmp(nodes[i], s)) return weights[i];
    }
    return 0;
}

bool mx_isvalid_line(const char *s)
{
    int delim_i = mx_get_char_index(s, '-');
    if (delim_i <= 0) return false;
    char *word = mx_strndup(s, delim_i);
    if (!mx_isword(word))
    {
        mx_strdel(&word);
        return false;
    }
    char *first = mx_strdup(word);
    mx_strdel(&word);
    s += delim_i + 1;
    delim_i = mx_get_char_index(s, ',');
    if (delim_i <= 0)
    {
        mx_strdel(&first);
        mx_strdel(&word);
        return false;
    }
    word = mx_strndup(s, delim_i);
    if (!mx_isword(word) || mx_strcmp(first, word) == 0)
    {
        mx_strdel(&first);
        mx_strdel(&word);
        return false;
    }
    mx_strdel(&word);
    mx_strdel(&first);
    s += delim_i + 1;
    if (!mx_isnum(s) || mx_atoi(s) < 1) return false;
    return true;
}

bool is_blacklisted(int c, int *blacklist, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (blacklist[i] == c) return true;
    }
    return false;
}

int get_path(int *len, int *weights, char **nodes, t_bridge **bridges, int count, char *from, char **path, int *blacklist, int *blked, int *permblkd)
{
    int cur_len = 0;
    int cur_weight = -1;
    int from_weight = 0;
    int steps = 1;
    char *cur_node = from;
    int prev_bridge_i = -1;
    path[0] = from;
    int needed_bridge = -1;
    bool break_flag = true;
    bool fell = true;
    for (int j = 0; j < count + 1 && break_flag; j++)
    {
        fell = true;
        from_weight = mx_get_weight(nodes, weights, from);
        for (int i = 0; bridges[i] != NULL; i++)
        {
            if (is_blacklisted(i, blacklist, *blked)) continue;
            if (!mx_strcmp(bridges[i]->A, from))
            {
                cur_node = bridges[i]->B;
                cur_weight = mx_get_weight(nodes, weights, bridges[i]->B);
                cur_len = bridges[i]->length;
            }
            else if (!mx_strcmp(bridges[i]->B, from))
            {
                cur_node = bridges[i]->A;
                cur_weight = mx_get_weight(nodes, weights, bridges[i]->A);
                cur_len = bridges[i]->length;
            }
            else continue;
            if (from_weight < cur_len) continue;
            if (cur_weight == 0)
            {
                blacklist[*blked] = i;
                *blked += 1;
                path[steps] = cur_node;
                len[steps - 1] = cur_len;
                steps++;
                break_flag = false;
                fell = false;
                needed_bridge = i;
                break;
            }
            if (from_weight - cur_len == cur_weight)
            {
                prev_bridge_i = i;
                len[steps - 1] = cur_len;
                from = cur_node;
                path[steps] = from;
                steps++;
                fell = false;
                break;
            }
        }
        if (fell)
        {
            if (!mx_strcmp(from, path[0]))
            {
                return -1;
            }
            j = 0;
            from = path[0];
            steps = 1;
            blacklist[*blked] = prev_bridge_i;
            *blked += 1;
            if (!mx_strcmp(bridges[prev_bridge_i]->A, path[0])
                || !mx_strcmp(bridges[prev_bridge_i]->B, path[0]))
            {
                blacklist[*permblkd] = prev_bridge_i;
                *permblkd += 1;
                *blked = *permblkd;
            }
        }
        if (!break_flag && (!mx_strcmp(bridges[needed_bridge]->A, path[0])
                            || !mx_strcmp(bridges[needed_bridge]->B, path[0])))
        {
            blacklist[*permblkd] = needed_bridge;
            *permblkd += 1;
            *blked = *permblkd;
        }
    }
    path[steps] = NULL;
    return steps;
}

void mx_print_path(int *weights, char **nodes, t_bridge **bridges, int count, char *from, int bridge_count)
{
    int *len = malloc(count * sizeof *len);
    char **path = malloc((count + 1) * sizeof *path);
    path[count] = NULL;
    int *blacklist = malloc(bridge_count * sizeof *blacklist);
    int perm_blocked = 0;
    int steps = 0;
    int blocked = 0;
    while (true)
    {
        steps = get_path(len, weights, nodes, bridges, count, from, path, blacklist, &blocked, &perm_blocked);
        if (steps == -1) break;

        for (int i = 0; i < 40; i++) mx_printchar('=');
        mx_printchar('\n');

        mx_printstr("Path: ");
        mx_printstr(path[0]);
        mx_printstr(" -> ");
        mx_printstr(path[steps - 1]);
        mx_printchar('\n');
        mx_printstr("Route: ");
        mx_print_strarr(path, " -> ");
        mx_printstr("Distance: ");
        int sum = 0;
        for (int i = 0; i < steps - 1; i++)
        {
            sum += len[i];
            mx_printint(len[i]);
            if (i + 1 != steps - 1) mx_printstr(" + ");
        }
        if (sum != len[0])
        {
            mx_printstr(" = ");
            mx_printint(sum);
        }
        mx_printchar('\n');
        for (int i = 0; i < 40; i++) mx_printchar('=');
        mx_printchar('\n');
    }
    free(len);
    free(path);
    free(blacklist);
}

void mx_set_weight(int **weights, char **nodes, char *s, int waight)
{
    for (int i = 0; nodes[i] != NULL; i++)
    {
        if (!mx_strcmp(nodes[i], s))
        {
            if ((*weights)[i] < waight && (*weights)[i] > 0) return;
            (*weights)[i] = waight;
            return;
        }
    }
}

bool is_visited(char **visited, char *s, int visits)
{
    for (int i = 0; i < visits; i++)
    {
        if (!mx_strcmp(visited[i], s)) return true;
    }
    return false;
}

void mx_weigh_nodes(int *weights, char **nodes,
                    t_bridge **bridges, int count)
{
    char **visited = malloc(count * sizeof *visited);
    char *curr;
    int visits = 0;
    int min = 0;
    int weight = 0;
    for (int i = 0; i < count; i++)
    {
        min = 0;
        while (is_visited(visited, nodes[min], visits)) min++;
        if (visits == count) break;
        for (int j = 0; j < count; j++)
        {
            if (is_visited(visited, nodes[j], visits)) continue;
            if (weights[j] >= 0 && (weights[min] < 0 || weights[min] > weights[j]))
            {
                min = j;
            }
        }
        curr = nodes[min];
        for (int j = 0; bridges[j] != NULL; j++)
        {
            if (!mx_strcmp(bridges[j]->A, curr))
            {
                if (is_visited(visited, bridges[j]->B, visits)) continue;
                weight = mx_get_weight(nodes, weights, curr);
                mx_set_weight(&weights, nodes, bridges[j]->B, weight + bridges[j]->length);
            }
            else if (!mx_strcmp(bridges[j]->B, curr))
            {
                if (is_visited(visited, bridges[j]->A, visits)) continue;
                weight = mx_get_weight(nodes, weights, curr);
                mx_set_weight(&weights, nodes, bridges[j]->A, weight + bridges[j]->length);
            }
        }
        visited[visits] = curr;
        visits++;
    }
    free(visited);
}

bool mx_isnum(const char *s)
{
    if (*s == '-') s++;
    while (*s != '\0')
    {
        if (!mx_isdigit(*s)) return false;
        s++;
    }
    return true;
}

bool mx_isword(const char *s)
{
    while (*s != '\0')
    {
        if (!mx_isalpha(*s)) return false;
        s++;
    }
    return true;
}

void mx_printerr(const char *s)
{
    write(STDERR_FILENO, s, mx_strlen(s));
}


int mx_atoi(const char *str) {
    int i = -1;
    int result = 0;

    while (str[++i]) {
        if (mx_isdigit(str[i]))
            result = result * 10 + str[i] - '0';
        if (!mx_isdigit(str[i]))
            return result;
    }
    return result;
}
