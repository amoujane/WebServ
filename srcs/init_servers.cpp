/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_servers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:00:27 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.hpp"

std::vector<std::string> ft_split(std::string str1, std::string delimiter)
{
    std::vector<std::string>    tokens;
	std::string str(str1);
	
	if (str == "")
		return (tokens);
    str += delimiter[0];
    std::string::size_type  start = str.find_first_not_of(delimiter, 0);
	if (start == std::string::npos)
		return tokens;
    std::string::size_type  end = 0;
    while (1) {
        end = str.find_first_of(delimiter, start);
        if (end == std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            break;
        }
        std::string s = str.substr(start, end - start);
        tokens.push_back(s);
        if ((start = str.find_first_not_of(delimiter, end)) == std::string::npos)
            break ;
    }
    return tokens;
}

void ft_skip_spaces(std::string::iterator &it, std::string::iterator end)
{
	while (it != end && (*it == ' ' || *it == '\t' || *it == '\n' || *it == '\v' || *it == '\f'))
		it++;
}

bool ft_check_server(std::string::iterator it)
{
	std::string::iterator r_end;

	r_end = it;
	while (*r_end != ' ' && *r_end != '\t' && *r_end != '\n' && *r_end != '\v' && *r_end != '\f' && *r_end != '{')
		r_end++;
	std::string l(it, r_end);
	if (l == "server")
		return true;
	return false;
}

int ft_add_server(std::vector<server> &g_ret, server s, std::list<std::string> ports)
{
	std::list<std::string> back = ports;
	std::list<std::string>::iterator it;

	back.sort();
	back.unique();
	if (ports.size() != back.size() || !s.check())
		return (1);
	it = ports.begin();
	while (it != ports.end())
	{
		s.update_port(*it);
		g_ret.push_back(s);
		it++;
	}
	return (0);
}

bool parse_line(std::vector<std::string>::iterator &it, std::vector<server> &g_ret, std::vector<std::string> &file_data)
{
	std::vector<std::string> res;
	server back;
	char pwd[1024];
	int val = 0;
	std::string pwd_dir;
	std::list<std::string> ports;

	if (!getcwd(pwd, 1024))
	{
		std::cerr << RED << "Getcwd Faild: " << strerror(errno) << RESET << std::endl;
		exit(-1);
	}
	pwd_dir = pwd;
	while (it != file_data.end() && *it != "]")
	{
		res = ft_split(*it, ":");
		if (res.size() > 2 && res.front() != "error_page")
			return false;
		if (res.front() == "host")
			back.set_host(res.back());
		else if (res.front() == "port")
		{
			back.set_port(res.back());
			ports.push_back(res.back());
		}
		else if (res.front() == "server_name")
			back.set_name(res.back());
		else if (res.front() == "limit_client_body")
			back.set_limit(res.back());
		else if (res.front() == "error_page")
			back.set_error(res);
		else if (res.front() == "location")
			back.set_location(it, file_data.end());
		else if (res.front() == "allowed_methods")
			back.set_methods(res.back());
		else if (res.front() == "root")
			back.set_root(res.back());
		it++;
		if (!back.check())
			break;
	}
	if (back.get_root().size() == 0)
		back.set_root(pwd_dir);
	if (back.get_body_s().size() == 0)
		back.set_limit(tostring(MAX_BODY));
	if (back.get_method().size() == 0)
		back.set_methods("GET, HEAD");
	back.set_pwd(pwd_dir);
	back.update_location();
	if (ports.size() > 1)
		val = ft_add_server(g_ret, back, ports);
	else if (back.check())
		g_ret.push_back(back);
	if (*it == "]" && val == 0)
		return true;
	return false;
}



bool get_servers(char *file, std::vector<server> &g_ret, std::vector<std::string> &file_data)
{
	int fd;
	std::string s_file;
	std::vector<std::string>::iterator vit;
	std::string res;
	std::vector<std::string> cpy;
	int start = 0;
	struct stat st;
	int size;

	fd = open(file, O_RDONLY);
	if (stat(file, &st) < 0 || fd < 0)
        return false;
    size = st.st_size;
	char buff[size + 1];
	ft_bzero(buff, size + 1);
	if (read(fd, buff, size) < 0)
		return false;
	close(fd);
	file_data = ft_split(buff, " \n\t\v\r");
	vit = file_data.begin();
	while (vit != file_data.end())
	{
		if (*vit == "server")
		{
			start = 0;
			while (vit != file_data.end())
			{
				if (*vit == "]")
				{
					if (start == 1)
						break;
					else
						return false;
				}
				if (start == 1)
					if (!parse_line(vit, g_ret, file_data))
						return false;
				if (vit == file_data.end())
					return false;
				if (*vit == "[")
				{
					if (start == 0)
						start = 1;
					else
						return false;
				}
				if (*vit != "]")
					vit++;
			}
			start = 0;
		}
		else if (*vit != "")
			return false;
		if (vit != file_data.end())
			vit++;
	}
	if (file_data.size() <= 1)
		return (false);
	return (true);
}
