#include "minishell.h"

bool	valid_cmd(char *cmd_path)
{
    struct stat	buffer;

    if (access(cmd_path, F_OK | X_OK)
        || stat(cmd_path, &buffer)
        || !S_ISREG(buffer.st_mode)
        || !(buffer.st_mode & S_IXUSR))
        return (false);
    return (true);
}