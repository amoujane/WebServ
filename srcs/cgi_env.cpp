/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_env.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:58:51 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cgi_env.hpp"

cgi_env::cgi_env(/* args */)
{
    _data.insert(std::make_pair("AUTH_TYPE=", ""));
    _data.insert(std::make_pair("CONTENT_LENGTH=", ""));
    _data.insert(std::make_pair("CONTENT_TYPE=", ""));
    _data.insert(std::make_pair("GATEWAY_INTERFACE=", "CGI"));
    _data.insert(std::make_pair("PATH_INFO=", ""));
    _data.insert(std::make_pair("PATH_TRANSLATED=", ""));
    _data.insert(std::make_pair("QUERY_STRING=", ""));
    _data.insert(std::make_pair("REMOTE_ADDR=", ""));
    _data.insert(std::make_pair("REMOTE_IDENT=", ""));
    _data.insert(std::make_pair("REMOTE_USER=", ""));
    _data.insert(std::make_pair("REQUEST_METHOD=", ""));
    _data.insert(std::make_pair("REQUEST_URI=", ""));
    _data.insert(std::make_pair("SCRIPT_NAME=", ""));
    _data.insert(std::make_pair("SERVER_NAME=", ""));
    _data.insert(std::make_pair("SERVER_PORT=", ""));
    _data.insert(std::make_pair("SERVER_SOFTWARE=", "Webserver"));
    _data.insert(std::make_pair("SERVER_PROTOCOL=", "HTTP/1.1"));
    _data.insert(std::make_pair("REDIRECT_STATUS=", "200"));
    _data.insert(std::make_pair("SCRIPT_FILENAME=", ""));
}

cgi_env::cgi_env(int val)
{
    _data.insert(std::make_pair("AUTH_TYPE=", ""));
    _data.insert(std::make_pair("CONTENT_LENGTH=", ""));
    _data.insert(std::make_pair("CONTENT_TYPE=", ""));
    _data.insert(std::make_pair("GATEWAY_INTERFACE=", "CGI"));
    _data.insert(std::make_pair("PATH_INFO=", ""));
    _data.insert(std::make_pair("PATH_TRANSLATED=", ""));
    _data.insert(std::make_pair("QUERY_STRING=", ""));
    _data.insert(std::make_pair("REMOTE_ADDR=", ""));
    _data.insert(std::make_pair("REMOTE_IDENT=", ""));
    _data.insert(std::make_pair("REMOTE_USER=", ""));
    _data.insert(std::make_pair("REQUEST_METHOD=", ""));
    _data.insert(std::make_pair("REQUEST_URI=", ""));
    _data.insert(std::make_pair("SCRIPT_NAME=", ""));
    _data.insert(std::make_pair("SERVER_NAME=", ""));
    _data.insert(std::make_pair("SERVER_PORT=", ""));
    _data.insert(std::make_pair("SERVER_SOFTWARE=", "Webserver"));
    _data.insert(std::make_pair("SERVER_PROTOCOL=", "HTTP/1.1"));
    _data.insert(std::make_pair("REDIRECT_STATUS=", "200"));
    _data.insert(std::make_pair("SCRIPT_FILENAME=", ""));
    client = val;
}

int cgi_env::check_key(std::string tmp)
{
    tmp = tmp + "=";
    std::map<std::string, std::string>::iterator it = _data.begin();

    for ( ; it != _data.end(); it++)
    {
        if (it->first == tmp)
            return 0;
    }
    return 1;
}

cgi_env::~cgi_env()
{
}

void cgi_env::push(std::string key, std::string value)
{
    _data[key] = value;
}


char* cgi_env::get_var(std::string key, std::string value)
{
    std::string tmp;
    tmp = key + value;
    return(ft_strdup(tmp.c_str()));
}


void cgi_env::print_cgi()
{
    std::map<std::string, std::string>::iterator it = _data.begin();

    for( ; it != _data.end(); it++)
    {
        std::cerr << "first :" << it->first << " second :" << it->second << std::endl;
    }
}

char** cgi_env::get_env()
{
    std::map<std::string, std::string>::iterator it = _data.begin();
    int i = 0;
    ret = (char**)malloc(sizeof(char*) * (_data.size() + 1));
    while (it != _data.end())
    {
        ret[i] = get_var(it->first, it->second);
        it++;
        i++;
    }
    ret[i] = NULL;
    return (ret);
}
