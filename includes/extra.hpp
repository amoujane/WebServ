/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:07:18 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <map>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int             ft_strncmp(const char *s1, const char *s2, size_t n);
int             ft_strcmp(char const *s1, char const *s2);
int             ft_atoi(const char *str);
size_t          ft_strlen(const char *str);
char           *ft_strdup(const char *s1);
char           *ft_strsub(char const *s, unsigned int start, size_t len);
char           *ft_strjoin(char const *s1, char const *s2);
char           *ft_strchr(const char *s, int c);
char			*ft_inet_ntoa(struct in_addr adr);
void			ft_write_string(int fd, std::string str);
int				ft_strlen(char *str);
std::string     tostring(int n);
unsigned long   hex2dec(std::string hex);
std::string     base64_decode(std::string const& encoded_string);
void            ft_bzero(void * s, size_t n);
bool            is_digits(const std::string &str);
bool			check_host(std::string host);
