/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:17:05 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.hpp"
#include <dirent.h>
#include <iomanip>
#include "../includes/extra.hpp"

std::string ft_space_print(int v)
{
	std::string ret;
	ret.clear();
	int  max = 25 - v;
	if (max <= 0)
		return ret;
	for (int i = 0; i < max; i++)
		ret += " ";
	return (ret);
}

std::string send_auto(std::string dir, headers var, std::string method, file_log f)
{
	struct stat statbuf;
	struct dirent *dp;
    std::string parent;
	std::string full_name;
	struct tm * timeinfo;
	std::string full_msg;
	char buff[100];

	if (dir == "")
		dir = ".";
	DIR *o_dir = opendir(dir.c_str());
	if (f.first_req.size() == 0)
		f.first_req = f.location;
	std::string index_of = f.first_req;
	if (index_of[index_of.size() - 1] != '/')
		index_of += "/";
	if (o_dir == NULL){
		std::cerr << BLACK << "Error In Directory: " << dir << RESET << "\n";
		return "";
	}
	full_msg += "<!DOCTYPE HTML>\n<html>\n<head>\n<title>Index of " + index_of + "</title>\n</head>\n<body>\n<h1>Index of " + index_of + "</h1>\n";
	full_msg += "<pre><a>     </a> <a>Name</a>\t\t\t<a>Last modified</a>\t\t\t<a>Size</a>\t\t<a>Description</a>\n\n";
	while ((dp = readdir(o_dir)) != NULL)
	{
		if (ft_strcmp(dp->d_name, ".") && ft_strcmp(dp->d_name, ".."))
		{
			if (dp->d_type == DT_DIR)
				full_msg += "<a>></a>";
			else
				full_msg += "<a>*</a>";
			if (ft_strlen(dp->d_name) <= 25)
				full_msg += " <a href=\"" +  index_of + dp->d_name + "\">" + dp->d_name + "</a> ";
			else
			{
				full_name = dp->d_name;
				full_name.resize(23);
				full_msg += " <a href=\"" + index_of + dp->d_name + "\">" + full_name + "..</a> ";
			}
			full_msg += ft_space_print(ft_strlen(dp->d_name));
			full_name = dir + "/" + dp->d_name;
			stat(full_name.c_str(), &statbuf);
			timeinfo = localtime(&statbuf.st_mtime);
			strftime (buff,80,"%a, %e %b %Y %H:%M:%S",timeinfo);
			full_msg += buff;
			full_msg += "\t\t";
			full_msg += tostring(statbuf.st_size);
			full_msg += "\n";
		}
        else if (ft_strcmp(dp->d_name, "..") != 0)
        {
            full_msg +=  "<a><+ </a>";
            parent = index_of;
            parent.resize(parent.find_last_of("/"));
            parent.resize(parent.find_last_of("/") + 1);
            full_msg +=  " <a href=\"" + parent + "\">" + "Parent Directory" + "</a> \n" + "\n";
        }
	}
	full_msg += "<hr></pre>\n</body><html>\n";
	closedir(o_dir);
	var.push("Content-Length", tostring(full_msg.size()));
	if (method == "HEAD")
		var.push("Content-Type", "");
	else
		var.push("Content-Type", "text/html");
	if (method == "GET")
		full_msg = var.header_msg() + "\r\n" + full_msg;
	else
		full_msg = var.header_msg() + "\r\n";
	return (full_msg);
}
