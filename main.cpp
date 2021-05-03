/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:32:03 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:32:07 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/header.hpp"

std::map<std::string, std::string> chunked_bodies;

int ft_isuppercase(std::string val)
{
	for (std::string::iterator i = val.begin(); i != val.end(); i++)
	{
		if (*i > 'Z' || *i < 'A')
			return (0);
	}
	return (1);
}

bool check_status(std::string str, server &s)
{
	file_log f;
	std::vector<std::string> head = ft_split(str, "\n\r");
	if (head.size() == 0)
		return true;
	std::string method = head[0].substr(0, head[0].find_first_of(" "));
	std::string file = head[0].substr(head[0].find_first_of(" ") + 1, head[0].find_last_of(" ") - head[0].find_first_of(" ") - 1);
	std::string HTTP = head[0].substr(head[0].find_last_of(" ") + 1, head[0].length());
	s.get_req_file(file, method);
	f = s.get_f_log();
	s.set_method(method);
	if ("HTTP/1.1" != HTTP)
	{
		s.set_pg_val(505);
		return true;
	}
	if (!ft_isuppercase(method) || file[0] != '/')
	{
		s.set_pg_val(400);
		return true;
	}
	return false;
}

int ft_get_max(int val, std::vector<client*>  *cl, int len)
{
	int ret = val;
	int i = 0;
	while (i < len)
	{
		std::vector<client*> ::iterator it = cl[i].begin();
		while (it != cl[i].end())
		{
			if ((*it)->get_fd() > ret)
				ret = (*it)->get_fd();
			it++;
		}
		i++;
	}
	return (ret);
}

void ft_close_done_clients(std::vector<int> &pending_close)
{
	std::vector<int>::iterator it = pending_close.begin();

	if (pending_close.size() == 0)
		return ;
	while (it != pending_close.end())
	{
		close(*it);
		it++;
	}
	pending_close.clear();
}

void run_webserver(std::vector<server> g_ret, std::multimap<std::string, server> extra)
{
	// Storing FDS
	fd_set	readfds;
	fd_set	writefds;
	fd_set	activefds;
	fd_set	activewritefds;
	int		max_server = 0;
	int 	val = -1;

	// Managing Clients
	std::vector<client*> running_c[g_ret.size() + 1];
	std::vector<server>::iterator it = g_ret.begin();

	// Client
	int					client_fd;
	struct sockaddr_in	addr; 
	int					addrlen = sizeof(addr);
	std::string 		server_response;
	int 				value_ret = 0;
	
	// Extra
	int 		wr_value = 0;
	int			s_ret = 0;
	int 		c_u = 0;
	
	FD_ZERO(&activefds);
	FD_ZERO(&activewritefds);
	it = g_ret.begin();
	while (it != g_ret.end())
	{
		FD_SET((*it).get_fd_server(), &activefds);
		max_server = (max_server > (*it).get_fd_server()) ? max_server : (*it).get_fd_server();
		it++;
	}
	while (1)
	{
		readfds = activefds;
		writefds = activewritefds;
		max_server = ft_get_max(max_server, running_c, g_ret.size());
		if ((s_ret = select(max_server + 1, &readfds,  &writefds, NULL, NULL)) < 0 )
		{
			std::cerr << RED << "select failed: " << strerror(errno) << RESET << std::endl;
			return ;
		}
		it = g_ret.begin();
		c_u = 0;
		while (it != g_ret.end())
		{
			server s = *it;
			addr = s.get_server_address();
			val = s.get_fd_server();
			if (FD_ISSET(val,  &readfds)) // NEW CLIENT
			{
				if ((client_fd = accept(val, (struct sockaddr *)&addr, (socklen_t*)&addrlen)) < 0)
					std::cerr << RED << "Accepting Client: " << strerror(errno) << RESET << std::endl;
				else
				{
					client *c = new client(client_fd, ft_inet_ntoa(addr.sin_addr));
					running_c[c_u].push_back(c);
					FD_SET(client_fd, &activefds);
				}
			}
			std::vector<client*> ::iterator ci = running_c[c_u].begin();
			while (ci != running_c[c_u].end())
			{
				client* c = *ci;
				std::multimap<std::string, server>::iterator m_ea;
				client_fd = c->get_fd();
				if (FD_ISSET(client_fd, &readfds))
				{
					c->ft_read();
					value_ret = c->request_done();
					if (value_ret == 1)
					{
						server_response.clear();
						s.get_header_var().set_http(200, "OK");
						check_status(c->get_status_header(), s);
						s.set_header((char*)c->get_request().c_str());
						if (s.get_header_var().get_key("Host").size() == 0)
							s.set_pg_val(400);
						else
						{
							m_ea = extra.find(s.get_host() + ":" + s.get_port() + "#" + s.get_header_var().get_key("Host"));
							if (m_ea != extra.end())
							{
								s = m_ea->second;
								check_status(c->get_status_header(), s);
								s.set_header((char*)c->get_request().c_str());
							}
						}
						s.ft_cgi_exist();
						c->set_method(s.get_method());
						s.set_client_ip(c->get_ip());
						if (s.get_f_log().limit_body < (int)c->get_body().size())
							s.set_pg_val(413);
						s.set_qu_string(c->get_body());
						if (s.ft_allowed() && s.get_pg_error() == 0 && s.ft_access())
							server_response = s.run_method();
						else if (s.get_pg_error())
							server_response = s.run_error(s.get_pg_error());
						else
							server_response = s.run_error(405);
						s.set_pg_val(0);
						c->set_write_index(0);
						c->set_response(server_response);
						FD_CLR(client_fd, &activefds);
						FD_SET(client_fd, &activewritefds);
					}
					else if (value_ret == 2)
					{
						c->set_response("");
						server_response.clear();
						FD_CLR(client_fd, &activefds);
						FD_SET(client_fd, &activewritefds);
					}
				}
				else if (FD_ISSET(client_fd, &writefds))
				{
					wr_value = 0;
					if (c->get_response().size() > 0)
						wr_value = c->ft_write();
					if (wr_value || server_response.size() == 0)
					{
						FD_CLR(client_fd, &activewritefds);
						FD_SET(client_fd, &activefds);
						if (wr_value != 0)
							c->client_finished();
						if (c->client_closed() || c->get_response().find("Connection: close") != std::string::npos)
						{
							ci = running_c[c_u].erase(ci);
							FD_CLR(client_fd, &activefds);
							usleep(100);
							close(client_fd);
							c->rest();
							delete c;
							if (running_c[c_u].size() == 0)
								break;
							else
							{
								ci = running_c[c_u].begin();
								continue;
							}
						}
						c->rest();
					}
				}
				ci++;
			}
			c_u++;
			it++;
		}
	}
}

void launch_servers(std::vector<server> g_ret)
{
	std::vector<server>::iterator it = g_ret.begin();
	std::map<std::string, server> extra;
	std::map<std::string, server> ::iterator e_it = extra.begin();
	std::multimap<std::string, server> extra_map;
	std::multimap<std::string, server>::iterator m_it;

	while (it != g_ret.end())
	{
		extra_map.insert(std::make_pair((*it).get_host() + ":" + (*it).get_port() + "#" + (*it).get_name(), *it));
		extra.insert(std::make_pair((*it).get_host() + ":" + (*it).get_port(), *it));
		it++;
	}
	g_ret.clear();

	e_it = extra.begin();
	while (e_it != extra.end())
	{
		g_ret.push_back(e_it->second);
		e_it++;
	}
	it = g_ret.begin();
	while (it != g_ret.end())
	{
		// (*it).print_server(); 		View The Servers
		(*it).run_server();
		it++;
	}
	int i = 0;
	while (1)
	{
		run_webserver(g_ret, extra_map);
		i++;
		if (i == 5)
		{
			std::cerr << RED << "Can't Launch The Server\n" << RESET;
			break;
		}
	}
}

void ft_pipe(int val)
{
	(void)val;
}

void ft_ctrl_c(int val)
{
	(void)val;
	std::cerr << YELLOW << "Exiting The Server\n" << RESET;
	exit(0);
}

void ft_signals()
{
	signal(SIGPIPE, ft_pipe);
	signal(SIGINT, ft_ctrl_c);
}

int main(int ac, char **av)
{
	std::vector<server> g_ret;
	server tmp;
	std::vector<std::string> file_data;
	if (ac != 2)
	{
		std::cerr << BOLDRED << "Wrong Parameters Number, Enter The Web Server Config As An Argument" << RESET << std::endl;
		return (1);
	}
	if (!get_servers(av[1], g_ret, file_data))
	{
		std::cerr << BOLDRED << "Invalid Config File" << RESET << std::endl;
		exit(-1);
	}
	ft_signals();
	try
	{
		launch_servers(g_ret);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
