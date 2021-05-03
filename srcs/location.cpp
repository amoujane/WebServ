/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:59:36 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/location.hpp"

location::location(/* args */):path(""),root(""),index(0),par_error(0),_access(""){
}

location::~location(){
	
}

std::string location::get_body_s(){
	return (body_s);
};

std::vector<std::string> location::get_methods(){
	return (this->allowed);
};

void location::set_methods(std::string methods)
{
	this->allowed = ft_split(methods, ", ");
	std::vector<std::string>::iterator it = allowed.begin();
	while (it != allowed.end() && par_error == 0)
	{
		if (*it != "GET" && *it != "PUT" && *it != "POST" && *it != "HEAD" && *it != "TRACE" && *it != "OPTIONS" && *it != "DELETE")
			par_error = 1;
		it++;
	}
}

std::string location::get_access()
{
	return (_access);
}

void location::set_access(std::string val)
{
	_access = val;
}

void location::set_path(std::string path){
	this->path = path;
}

void location::set_root(std::string root){
	this->root = root;
}

int location::valid()
{
	if (par_error == 0)
		return (1);
	return (0);
}

void location::set_default(std::string def){
	default_file = ft_split(def, ",");
}

std::string location::get_path(){
	return (this->path);
}

std::string location::get_root(){
	return (this->root);
}

std::vector<std::string>  location::get_default()
{
	return (this->default_file);
}

int location::get_index()
{
	return (this->index);
}

void location::print_location()
{
	std::vector<std::string>::iterator it;
	std::cout << "Path: " + this->get_path() << std::endl;
	std::cout << "root: " + this->get_root() << std::endl;
	std::cout << "default: ";
	it = default_file.begin();
	while (it != default_file.end())
	{
		std::cout << *it << "\t";
		it++;
	}
	std::cout << std::endl;
	std::cout << "Allowed Methods: ";
	it = allowed.begin();
	while (it != allowed.end())
	{
		std::cout << "\t" << *it;
		it++;
	}
	std::cout << std::endl;
	std::cout << "Limit Body Size: " << limit_client_body << std::endl;
	if (index == 0)
		std::cout << "index: off" << std::endl;
	else
		std::cout << "index: on" << std::endl;
	if (par_error == 0)
		std::cout << "No Error" << std::endl;
	else
		std::cout << "Error" << std::endl;
	std::cout << std::endl;
}
void location::set_index(std::string var)
{
	if (var == "on")
		this->index = 1;
}

std::string location::get_string_methods()
{
	std::string ret;
	std::vector<std::string>::iterator it = allowed.begin();
	ret.clear();

	for ( ; it != allowed.end(); it++)
	{
		if (it != allowed.begin())
			ret += ", ";
		ret += *it;
	}
	return (ret);
}

int location::get_limit(){
	return (limit_client_body);
};

void location::set_limit_body_size(std::string var)
{
	body_s = var;
	this->limit_client_body = ft_atoi(var.c_str());
};


int location::ft_method_check(std::string val)
{
    std::vector<std::string>::iterator it = allowed.begin();

	while (it != allowed.end())
	{
		if (val == *it)
			return (1);
		it++;
	}
	return (0);
}
