/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_env.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:58:54 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <stdlib.h>
#include "extra.hpp"
#include <sys/types.h>
#include <sys/socket.h>

class cgi_env
{
private:
    std::map<std::string, std::string> _data;
    char **ret;
    int client;
public:
    cgi_env(/* args */);
    cgi_env(int val);
    ~cgi_env();
    void push(std::string key, std::string value);
    char **get_env();
    char *get_var(std::string key, std::string value);
    void print_cgi();
    int check_key(std::string tmp);
};
