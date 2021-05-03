/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:39:51 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.hpp"


headers::headers(/* args */)
{
    _data.insert(std::make_pair("Accept-Charsets", "utf-8"));
    _data.insert(std::make_pair("Accept-Language", "en"));
    _data.insert(std::make_pair("Allow", ""));
    _data.insert(std::make_pair("Authorization", ""));
    _data.insert(std::make_pair("Content-Language", "en"));
    _data.insert(std::make_pair("Content-Length", ""));
    _data.insert(std::make_pair("Content-Location", ""));
    _data.insert(std::make_pair("Content-Type", ""));
    _data.insert(std::make_pair("Date", ""));
    _data.insert(std::make_pair("Host", ""));
    _data.insert(std::make_pair("Last-Modified", ""));
    _data.insert(std::make_pair("Location", ""));
    _data.insert(std::make_pair("Referer", ""));
    _data.insert(std::make_pair("Retry-After", ""));
    _data.insert(std::make_pair("Server", "Webserver/HTTP1.1"));
    _data.insert(std::make_pair("Transfer-Encoding", ""));
    _data.insert(std::make_pair("User-Agent", ""));
    _data.insert(std::make_pair("WWW-Authenticate", ""));
    _data.insert(std::make_pair("Requested_file", ""));
    http_status = "HTTP 200 OK";
    def = http_status;
}

headers::~headers()
{
}

void headers::reset_header()
{
    push("Accept-Charsets", "utf-8, iso-8859-1");
    push("Accept-Language", "*");
    push("Allow", "");
    push("Authorization", "");
    push("Content-Language", "en");
    push("Content-Length", "");
    push("Content-Location", "");
    push("Content-Type", "");
    push("Date", "");
    push("Host", "");
    push("Last-Modified", "");
    push("Location", "");
    push("Referer", "");
    push("Retry-After", "");
    push("Server", "Webserver/HTTP1.1");
    push("Transfer-Encoding", "");
    push("User-Agent", "");
    push("WWW-Authenticate", "");
    push("Requested_file", "");
    push("Connection", "keep-alive");
    set_http(200, "OK");
}

void headers::push(std::string key, std::string value)
{
    _data[key] = value;
}

void headers::set_http(int value, std::string stat)
{
    http_status = "HTTP/1.1 ";
    http_status += tostring(value);
    http_status += " ";
    http_status += stat;
}

std::string headers::get_file()
{
    return (_data["Requested_file"]);
}

void headers::print_header(int fd)
{
    std::map<std::string, std::string>::iterator it = _data.begin();
    
    ft_write_string(fd, http_status + "\r\n");
    while (it != _data.end())
    {
        if (it->second != "" && it->first != "Requested_file")
            ft_write_string(fd, it->first + ": " + it->second + "\r\n");
        it++;
    }
}

std::string headers::header_msg()
{
    std::string ret;
    std::map<std::string, std::string>::iterator it = _data.begin();
    
    ret = http_status + "\r\n";
    while (it != _data.end())
    {
        if (it->second != "" && it->first != "Requested_file")
            ret += it->first + ": " + it->second + "\r\n";
        it++;
    }
    return (ret);
}

std::string headers::get_key(std::string key)
{
    std::string ret;
    std::map<std::string, std::string>::iterator it = _data.find(key);
    ret.clear();
    
    if (it == _data.end())
        return (ret);
    ret = it->second;
    return (ret);
}
