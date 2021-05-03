/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:44:22 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <fstream>  
#include <string>
#include <list>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#define MAX_BODY 1000000000
class cgi_env;
class server;
#include "headers.hpp"
#include "extra.hpp"
#include "location.hpp"

extern int errno;

typedef struct s_file_info
{
    int size;
    int works;
    char *tab;
    int fd;
    
    s_file_info(std::string file){
        size = 0;
        works = 0;
        tab = NULL;
        struct stat st; 
        fd = open(file.c_str(), O_RDONLY);
        if (fd < 0)
            return ;
        if (stat(file.c_str(), &st) < 0)
            return ;
        size = st.st_size;
        if (!(tab = (char*)malloc(sizeof(char) * size + 1)))
        {
            std::cerr << "Malloc Faild: "  << strerror(errno) << std::endl; // internal server 500
            works = -5;
            return ;
        }
        ft_bzero(tab, size + 1);
        if (read(fd, tab, size) < 0)
        {
            std::cerr << BLACK << "Error Read: " << file << RESET << std::endl;
            works = -1;
            close(fd);
            return ;
        }
        works = 1;
    }
    ~s_file_info(){
        if (fd != -1)
            close(fd);
    }
}             t_file_info;

typedef struct s_error_messages
{
    std::map<int, std::string> _data;
    s_error_messages(){
        _data[204] = "No Content"; // POST update
        _data[400] = "Bad Request";
        _data[401] = "Unauthorized";
        _data[403] = "Forbidden"; // WWW-Authenticate or necessary permissions
        _data[404] = "Not Found";
        _data[405] = "Not Allowed";
        _data[406] = "Not Acceptable";
        _data[413] = "Payload Too Large";
        _data[415] = "Unsupported Media Type";
        _data[500] = "Internal Server Error";
        _data[501] = "Not Implemented";
        _data[503] = "Service Unavailable";
        _data[505] = "HTTP Version Not Supported";
    };
    std::string print_error_val(int value){
        std::string ret;

        ret.clear();
        ret += "<!DOCTYPE HTML><html><head>\n<style>h1 {text-align: center;}</style>\n";
        ret += "<title>" + tostring(value) + "  " + _data[value] + "</title>\n";
        ret += "</head><body>";
        ret += "<h1>" + tostring(value) + "  " + _data[value] + "</h1></body><html>"; // \n
        return (ret);
    };
}   t_error_messages;


typedef struct file_log
{
    std::string file;
    int size;
    std::string location;
    std::string first_req;
    int auto_index;
    struct stat st;
    int valid;
    int erno_val;
    int limit_body;
    std::string req;
    std::string q_string;
    std::string s_file;
    
    void rest(){
        file.clear();
        location.clear();
        first_req.clear();
        size = 0;
        auto_index = 0;
        valid = 0;
        erno_val = 0;
        limit_body = MAX_BODY;
        req.clear();
        q_string.clear();
        s_file.clear();
    };
    void set_size(){
        valid = 0;
        if (stat(file.c_str(), &st) < 0)
        {
            valid = -1;
            size = 0;
            erno_val = errno;
            return ;
        }
        else if (S_ISREG(st.st_mode))
            valid = 1;
        size = st.st_size;
    };
    void set_method(std::string val)
    {
        req = val;
    }
    void info(){
        std::cout << "file: " << file << "\n";
        std::cout << "size: " << size << "\n";
        std::cout << "location: " << location  << "\n";
        std::cout << "first request: " << first_req << "\n";
        std::cout << "autoindex: " << auto_index << "\n";
        std::cout << "Req: " << req << "\n";
        if (valid == -1)
            std::cout << "working: " << "no\n";
        else if (valid == 1)
            std::cout << "working: " << "yes\n";
        else
            std::cout << "working: ?\n";
    }
} t_file_log;
#include "server.hpp"



// functions
std::vector<std::string> ft_split(std::string cpy, std::string delimiter);
void ft_skip_spaces(std::string::iterator &it, std::string::iterator end);
bool ft_check_server(std::string::iterator it);
int ft_strlen(char *str);
bool parse_line(std::vector<std::string>::iterator &it, std::vector<server> &g_ret, std::vector<std::string> &file_data);
bool get_servers(char *file, std::vector<server> &g_ret, std::vector<std::string> &file_data);
void ft_print_servers();
void ft_print_header();
void get_header(char *str);
void ft_init_header();
bool get_servers(char *file);
std::string ft_remove_whitespaces(std::string str);
std::string send_auto(std::string dir, headers var, std::string method, file_log f);
unsigned long hex2dec(std::string hex);
void ft_write_string(int fd, std::string str);
void free_env_tab(char **var);
void pending_write(int fd, std::string str);
