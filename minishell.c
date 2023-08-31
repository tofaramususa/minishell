/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:34:02 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 15:14:47 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//write functions to start signals and write signal handlers

//the start of the execution:
/**
 * start_execution: 
*/
bool	start_execution(t_shell *bash) //function to execute and free everything
{
    write_to_funcfile("start_execution_called");
	if (bash->cmd_len >= 220) //calculate command length
	{
		ft_putstr_fd("Sorry too many commands\n", 2); //change this
		exit(1);
	}
	if (check_and_update_heredoc(*bash->s_commands, bash) == 1) //there is somekind or error here
	{
		garbage_collector(bash); //free all the functions
		return (true);
	}
	signal(SIGINT, SIG_IGN); //reset signal
	signal(SIGINT, sig_handler); //
	error_status = pipex(bash->cmd_len, *bash->s_commands, bash); //here is were the execution happens
    garbage_collector(bash);
	unlink(".tmp"); //remove the tmp file
	return (false);
}

// Parse function takes a str and turns it to an array of simple commands
bool parse(t_shell *bash)
{
	// char *word = "$PAT";
    write_to_funcfile("parse function called");
    char **final_result;
    if (!check_line(bash->line))
    {
        error_status = 0;
        return (false);
    }
    add_history(bash->line);
    final_result = ft_split_on_delims(bash->line);
    write_to_debugfile(ft_strjoin("","ARRAY CREATED"));
    print_array(final_result);
    if (!final_result)
	{
        return (false);	
    }
	bash->tokenlist = ft_tokenise(bash, final_result);
    if (!bash->tokenlist)
        return(false);
    print_tokens(bash->tokenlist);
	create_scmnd_array(bash, bash->tokenlist);
    print_scommands(bash->s_commands);
    return (true);
}

void init_bash(t_shell *bash)
{
    bash->dont = 0; //convert envp to an array 
    bash->s_commands = NULL;
    bash->env_vars = NULL;
    bash->isfreed = false;
}

<<<<<<< HEAD
void line_prompt(t_shell *bash)
{
    char *temp_str;
    char *prompt;

    prompt = NULL;
    temp_str = NULL;
    if(g_error_status == 0)
    {
        temp_str = ft_strjoin("🏀", getcwd(bash->pwd, 1024));
        prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
        bash->line = readline(prompt);
    }
    else
    {
        temp_str = ft_strjoin("🗑️ ", getcwd(bash->pwd, 1024));
        prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
        bash->line = readline (prompt);
    }
    if(prompt)
        safe_free(prompt);
    if(temp_str)
        safe_free(temp_str);
}
=======
>>>>>>> parent of cc186a9 (working)
//the int main
int main(int ac, char **av, char **envp)
{
    t_shell *bash;

    if(envp[0] == NULL)
        exit(printf("Error: No environment variables found"));
    if (ac > 2 || ft_array_len(av) > 2)
    exit(printf("To start [TheBash] enter: ./minishell"));
	bash = (t_shell *) malloc(sizeof(t_shell));
    if(!bash)
        return(1);
    error_status = 0;
    signal(SIGQUIT, SIG_IGN);
    create_envlist(bash, envp);
    while(1)
    {
        init_bash(bash);
        init_signals(); //handle the signals
        if(error_status == 0)
            bash->line = readline ("🏀\x1b[38;5;122m[TheBash]$ \x1b[0m");
        else
            bash->line = readline ("🗑️ \x1b[38;5;122m[TheBash]$ \x1b[0m");
        write_to_debugfile(ft_strjoin("","----------------------"));
        write_to_debugfile(ft_strjoin("COMMAND: ", bash->line));
        if(parse(bash))
        {
            start_execution(bash);
        }
<<<<<<< HEAD
        garbage_collector(&bash);
    }
        free_env_list(&bash->env_list);
        free(bash);
=======
    }
    free_env_list(bash->env_list);
    safe_free(bash);
>>>>>>> parent of cc186a9 (working)
}

//what we need to free for free_shell:
//the exit points: at each exit point we need to update the exit status
//X0 - signals to interrupt the function
//X1 -- when the string contains nothing, nothing has been allocated yet;
//X2 -- when the syntax check fails, at this point we have a linked_list of envp and array of envp; also have the tokenlist and array of tokens;
// -- X3 considering the bonus we may need the no matches found exit;
// X4 -- This is the final step of where we search for commands if they are there, if the word is not found then we need to exit, there are cases where there no commands just redirections
// X5 -- If too many commands have been entered -- at the start of execution we have the environment variables and the simple commands


// Free the s_commands. The key is that we need to iterate to every allocated thing but check if its not NULL then we free
//items to free are the command, the path which are strings, the args which are an array, then go into redirections 
// and free the filename and the heredoc_data;
