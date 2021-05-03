/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:45:37 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "header.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
class server;
#include "location.hpp"
#include "headers.hpp"
#include "extra.hpp"
#include "cgi_env.hpp"
#include "client.hpp"
class server
{
	private:
		// Default
		std::string host;
		std::string port;
		std::string name;
		int limit_body;
		std::string limit_body_s;
		std::list<std::string> methods;
		std::map<std::string ,location> locations;
		std::string root;
        headers header_var;
		std::map<std::string ,std::string> extra_headers;
		std::map<std::string, std::string> cgi;
		std::string default_page;
		std::string file_open;

		// Server
		int server_fd;
		struct sockaddr_in address;

		// Errors
		int par_error;
		int page_error_val;
		t_error_messages _err;
		std::map<std::string, std::string> error_pg;

		// Request
		int qu_len;
		std::string file_type;
		std::string pwd_dir;
		std::string req_method;
		std::string qu_string;
		t_file_log f_log;


		// Clients
		std::string client_ip;
		std::vector<client*> clients;

		
	public:
		server(/* args */);
		~server();

        // Set Methods
		void set_host(std::string str);
		void set_port(std::string str);
		void set_name(std::string str);
		void set_limit(std::string str);
		void set_methods(std::string str);
		void set_cgi(std::string name, std::string path);
		void set_location(std::vector<std::string>::iterator &it, std::vector<std::string>::iterator end);
		void set_error(std::vector<std::string> res);
		void cgi_parse(std::vector<std::string>::iterator it, std::vector<std::string>::iterator end);
		void set_root(std::string str);
		void set_qu_string(std::string str);
		void set_pg_val(int val);
		void set_method(std::string val);
		void set_pwd(std::string p);
		void set_qu_len(std::string val);
		void set_access(std::string val);
		void set_client_ip(std::string val);
		
        // Get Methods
		std::string get_host();
		std::string get_port();
		std::list<std::string> get_methods();
		std::string get_string_methods();
		std::string get_name();
		std::string get_cgi();
		std::string get_file_type();
		std::string get_root();
		std::string get_error_page(int val);
		std::string get_method();
		std::string get_req_file(std::string val, std::string met);
		std::string get_file(std::map<std::string, location>::iterator loc, std::string val);
		std::map<std::string ,location> get_location();
		file_log get_f_log();
		headers get_header_var(void);
		std::string get_body_s();
		std::string ft_read_file(std::string val);
		int get_fd_server();
		struct sockaddr_in get_server_address();
		int get_limit();
        int value_port();
		int get_pg_error();

		// Extra
		bool check();
        void print_server();
		char **setup_env();
		cgi_env ft_add_other_headers();
		std::string get_name_headers(std::map<std::string, std::string>::iterator it);

		
        //  Launch
        void run_server();
		std::string run_error(int val);
        void set_header(char *buff);
        void reset_header();
		bool ft_allowed();
		std::string ft_cgi_exist();
		void update_location();
		int ft_access();

		// requests methods
		std::string run_file();
		std::string run_method();
		std::string put_method();
		std::string delete_method();
		std::string options_method();
		std::string run_cgi();
		std::string post_method();

		void cgi_status_code(std::string response);
		void update_port(std::string val);
};
