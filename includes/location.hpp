/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:47:22 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <list>
class location;
#include "header.hpp"

class location
{
	private:
		std::string path;							// Location Name
		std::string root;							// Root Directory
		std::vector<std::string> default_file;		// Default Index Files
		std::vector<std::string> allowed;			// Allowed Methods
		std::string body_s;							// Limit Body String
		int index;									// index ON or OFF
		int par_error;								// Parse Error Happen
		int limit_client_body;						// max body size
		std::string _access;						// access file path

	public:
		location(/* args */);
		~location();
		
		// set
		void set_path(std::string path);
		void set_root(std::string root);
		void set_default(std::string def);
		void set_index(std::string index);
		void set_methods(std::string methods);
		void set_limit_body_size(std::string var);
		void set_access(std::string val);

		// get
		std::string get_path();
		std::string get_root();
		std::vector<std::string> get_default();
		std::vector<std::string> get_methods();
		std::string get_body_s();
		std::string get_string_methods();
		int get_limit();
		int get_index();
		int valid();
		void print_location();
		int ft_method_check(std::string val);
		std::string get_access();
};
