/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:38:15 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <iostream>
#include "extra.hpp"

class headers
{
private:
    std::map<std::string, std::string> _data;
	std::string http_status;
	std::string def;

public:
    headers(/* args */);
    ~headers();
	void push(std::string key, std::string value);
	void print_header(int fd);
	void set_http(int val, std::string stat);
	void reset_header();
	std::string get_file();
	std::string get_key(std::string key);
	std::string header_msg();
	
};
