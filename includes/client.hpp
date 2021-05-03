/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:45:59 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <map>
#include "extra.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */

// GET   1
// HEAD  2
// PUT   3
// POST  4
// OPTIONS 5
// DELETE 6

class client
{
private:
    int fd;
    int run;
    int write_index;
    int req_done;
    time_t last_req;
    std::string ip;
    int req_tab[7];
    std::string client_request;
    std::string client_response;
    std::string client_body;
public:
    client(/* args */);
    client(int fd, std::string str);
    ~client();
    void update_time();
    bool still_alive();
    int get_fd();
    void set_fd(int fd);
    void set_ip(std::string str);
    std::string get_ip();
    void ft_read();
    int ft_write();
    int request_done();
    int client_closed();
    void ft_unchunck_body();
    std::string get_request();
    std::string get_body();
    std::string get_response();
    void set_response(std::string str);
    std::string get_status_header();
    void set_write_index(int val);
    void rest();
    void set_client_closed(int val);
    void set_method(std::string m);
    void client_finished();
};
