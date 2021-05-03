/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:45:45 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

client::client(/* args */)
{
    struct timeval current_time;
	gettimeofday(&current_time, NULL);

	run = 0;
	for (size_t i = 0; i < 7; i++)
		req_tab[i] = 0;
	fd = -1;
	req_done = 0;
	write_index = 0;
	last_req = current_time.tv_sec;
}

client::client(int val, std::string str)
{
	int var;
    struct timeval current_time;
	gettimeofday(&current_time, NULL);
	
	fd = val;
	run = 0;
	for (size_t i = 0; i < 7; i++)
		req_tab[i] = 0;
	req_done = 0;
	write_index = 0;
	last_req = current_time.tv_sec;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &var, sizeof(var)) < 0)
	{
		std::cerr << RED << "client setsockopt: failed" << RESET << std::endl;
		run = 1;
	}
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << RED << "client fcntl: failed" << RESET << std::endl;
		run = 1;
	}
	ip = str;
}

client::~client()
{
}

void client::update_time(){
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	this->last_req = current_time.tv_sec;
}

bool client::still_alive(){
    struct timeval current_time;
	gettimeofday(&current_time, NULL);

	if (current_time.tv_sec >= last_req + 10)
		return (false);
	return (true);
}

int client::get_fd(){
    return (fd);
}

void client::set_fd(int fd){
    this->fd = fd;
}

void client::set_write_index(int val)
{
	write_index = val;
}

void client::set_ip(std::string str)
{
	ip = str;
}

std::string client::get_ip()
{
	return (ip);
}

void client::client_finished()
{
	std::cerr << BLUE << "Client " << fd << " Received The Respond\n" << RESET;
}

void client::set_method(std::string m)
{
	int val = 0;
	if (m == "GET")
	{
		val = req_tab[0];
		val++;
		req_tab[0] = val;
		std::cerr << MAGENTA <<  "Client " << fd << " Request Method: " << m << "(" << val << ").\n" << RESET;
	}
	else if (m == "HEAD")
	{
		val = req_tab[1];
		val++;
		req_tab[1] = val;
		std::cerr << MAGENTA <<  "Client " << fd << " Request Method: " << m << "(" << val << ").\n" << RESET;
	}
	else if (m == "PUT")
	{
		val = req_tab[2];
		val++;
		req_tab[2] = val;
		std::cerr << MAGENTA <<  "Client " << fd << " Request Method: " << m << "(" << val << ").\n" << RESET;
	}
	else if (m == "POST")
	{
		val = req_tab[3];
		val++;
		req_tab[3] = val;
		std::cerr << MAGENTA <<  "Client " << fd << " Request Method: " << m << "(" << val << ").\n" << RESET;
	}
	else if (m == "OPTIONS")
	{
		val = req_tab[4];
		val++;
		req_tab[4] = val;
		std::cerr << MAGENTA <<  "Client " << fd << " Request Method: " << m << "(" << val << ").\n" << RESET;
	}
	else if (m == "DELETE")
	{
		val = req_tab[5];
		val++;
		req_tab[5] = val;
		std::cerr << MAGENTA <<  "Client " << fd << " Request Method: " << m << "(" << val << ").\n" << RESET;
	}
}

void client::ft_read()
{
	int readval = 0;
	char buff[10001];

	ft_bzero(buff, 10001);
	readval = 1;
	while (readval > 0)
	{
		readval = read(fd, buff, 10000);
		if (readval > 0)
			client_request += buff;
		ft_bzero(buff, 10001);
	}
	if (client_request == "\r\n")
		client_request.clear();
	if (readval == 0)
		req_done = 1;
}

void client::set_client_closed(int val)
{
	req_done = val;
}

int client::client_closed()
{
	return (req_done);
}

std::string client::get_response()
{
	return (client_response);
}

int client::request_done()
{
	std::string ret;
	std::string num;
	int value;
	
	if (req_done == 1)
		return (2);
	if (client_request.find("\r\n\r\n") != std::string::npos)
	{
		if (client_request.find("\r\n\r\n") + 4 > client_request.size())
			return (0);
		client_body = &client_request[client_request.find("\r\n\r\n") + 4];
		if (client_request.find("Content-Length: ") != std::string::npos && client_request.find("Transfer-Encoding: chunked") == std::string::npos)
		{
			num = &client_request[client_request.find("Content-Length: ") + 16];
			value = ft_atoi(num.c_str());
			if ((int)client_body.size() >= value)
			{
				client_body.resize(value);
				client_request = client_request.substr(0, client_request.find("\r\n\r\n"));
				return (1);
			}
		}
		else if (client_request.find("Transfer-Encoding: chunked") != std::string::npos)
		{
			if (client_request.find("\r\n0\r\n") != std::string::npos)
			{
				client_request = client_request.substr(0, client_request.find("\r\n\r\n"));
				ft_unchunck_body();
				return (1);
			}
		}
		else
			return (1);
	}
	return (0);
}

int client::ft_write()
{
	int writeval = 0;
	std::string ret;

	ret = &client_response[write_index];
	writeval = write(fd, ret.c_str(), ret.size());
	if (writeval >= 0)
		write_index += writeval;
	usleep(10);
	if ((int)client_response.size() <= write_index)
		return (1);
	return (0);
}

std::string client::get_request()
{
	return (client_request);
}

std::string client::get_body()
{
	return (client_body);
}

void client::set_response(std::string str)
{
	client_response = str;
}

void client::ft_unchunck_body()
{
	unsigned long num = 1;
	std::string hex;
	std::string tmp;
	std::string ret;
	std::map<std::string, std::string>::iterator it;

	tmp = client_body;
	while (1)
	{
		hex = tmp.substr(0, tmp.find("\r\n"));
		if (hex == "0" || hex.size() == 0)
			break;
		num = hex2dec(hex);
		ret += tmp.substr(tmp.find("\r\n") + 2, num);
		tmp = &tmp[tmp.find("\r\n") + 2 + num + 2];
	}
	client_body = ret;

	// Fast Version For Testing

    // size_t startpos = 0 , endpos;
	// std::string ret;
    // size_t lastrn = client_body.rfind("\r\n");

    // while (startpos < lastrn) {
    //     startpos = client_body.find("\r\n", startpos) + 2;
    //     endpos = client_body.find("\r\n", startpos);
    //     if (startpos == std::string::npos || endpos == std::string::npos || startpos > endpos) {
    //         break;
    //     }
    //     ret.append(client_body, startpos, endpos - startpos);
    //     startpos = endpos + 1;
    // }
	// client_body = ret;
}

std::string client::get_status_header()
{
	std::string ret;

	ret = client_request.substr(0, client_request.find("\r\n"));
	return (ret);
}

void client::rest()
{
	client_request.clear();
	client_response.clear();
	client_body.clear();
	req_done = 0;
	write_index = 0;
}
