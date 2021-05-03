/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:55:17 by amoujane          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:21 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/extra.hpp"
#include <netinet/in.h>  

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*t;

	i = 0;
	while (s1[i])
		i++;
	if (!(t = (char*)malloc(sizeof(char) * (i + 1))))
		return ((char*)"");
	i = 0;
	while (s1[i])
	{
		t[i] = s1[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*fresh;
	int		i;

	if (!s)
		return (NULL);
	fresh = (char*)malloc((len + 1) * sizeof(char));
	i = 0;
	if (!fresh)
		return (NULL);
	fresh[len] = '\0';
	while (len--)
	{
		fresh[i] = s[start];
		i++;
		start++;
	}
	return (fresh);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(s3 = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*a;

	a = (unsigned char *)s;
	while (*a)
	{
		if (*a == (unsigned char)c)
			return ((char*)a);
		a++;
	}
	if (*a == (unsigned char)c)
		return ((char*)a);
	return (NULL);
}

int	return_f(char **tab, int n, char **line, int fd)
{
	char	*temp;
	int		i;

	i = 0;
	while (tab[fd][i] && tab[fd][i] != '\n')
		i++;
	*line = ft_strsub(tab[fd], 0, i);
	if (!tab[fd][i])
	{
		temp = tab[fd];
		tab[fd] = NULL;
		free(temp);
		return (0);
	}
	else
	{
		temp = tab[fd];
		tab[fd] = ft_strdup((tab[fd]) + i + 1);
		free(temp);
	}
	if (!tab[fd] || !*line)
		return (-1);
	if (n || (n == 0 && tab[fd] != NULL))
		return (1);
	return (-1);
}

int		ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	num;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
				str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		(str[i] == '-') ? sign = -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		num = num * 10 + (str[i] - '0');
		if (sign == 1 && num < 0)
			return (-1);
		if (sign == -1 && num < 0)
			return (0);
		i++;
	}
	return (num * sign);
}

int		ft_strcmp(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

double ft_power(int a, int b)
{
	double num;
	int i = 0;

	num = 1;
	while (i < b)
	{
		num *= a;
		i++;
	}
	return (num);
}

unsigned long hex2dec(std::string hex)
{
	unsigned long result = 0;
	for (int i=0 ; i < (int) hex.length(); i++) {
		if (hex[i]>=48 && hex[i]<=57)
		{
			result += (hex[i]-48) * ft_power(16,(int)hex.length()-i-1);
		} else if (hex[i]>=65 && hex[i]<=70) {
			result += (hex[i]-55) * ft_power(16,(int)hex.length( )-i-1);
		} else if (hex[i]>=97 && hex[i]<=102) {
			result += (hex[i]-87) * ft_power(16,(int)hex.length()-i-1);
		}
	}
	return result;
}

static unsigned int i2a(char* dest,unsigned int x) {
	unsigned int tmp=x;
	unsigned int len=0;
	if (x >= 100)
	{
		*dest++ = tmp / 100 +'0';
		tmp = tmp % 100;
		++len;
	}
	if (x >= 10)
	{
		*dest++ = tmp/10 + '0';
		tmp = tmp % 10;
		++len;
	}
	*dest++ = tmp + '0';
	return len+1;
}

char *ft_inet_ntoa(struct in_addr in) {
	static char buf[20];
	unsigned int len;
	unsigned char *ip=(unsigned char*)&in;
	len=i2a(buf,ip[0]); buf[len]='.'; ++len;
	len+=i2a(buf+ len,ip[1]); buf[len]='.'; ++len;
	len+=i2a(buf+ len,ip[2]); buf[len]='.'; ++len;
	len+=i2a(buf+ len,ip[3]); buf[len]=0;
	return buf;
}

void ft_write_string(int fd, std::string str)
{
	write(fd, str.c_str(), str.size());
}

void free_env_tab(char **var)
{
	for (size_t i = 0; var[i] != NULL; i++)
		free(var[i]);
	free(var);
}

void pending_write(int fd, std::string str)
{
	int k = 0;
	int num = 0;
	std::string n_str;

	while (k < (int)str.size())
	{
		n_str = &str[k];
		if ((num = write(fd, n_str.c_str(), n_str.size())) > 0)
			k += num;
		n_str.clear();
	}
}

int ft_strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

std::string tostring(int n)
{
    std::string ss;
    if (n == 0)
        ss = "0";
    while (n) {
        char i = '0' + (n % 10);
        n /= 10;
        ss = i + ss;
    }
    return ss;
}

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    return ret;
}

void ft_bzero(void * s, size_t n)
{
  char * c = (char*)s;
  size_t i;
  for (i = 0; i < n; ++i)
    c[i] = '\0';
}

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

bool check_host(std::string host)
{
	std::string tmp;
	std::string str;
	int i = 0;
	
	if (host.size() == 0)
		return true;
	str = host;
	while (i < 4)
	{
		tmp = str.substr(0, str.find("."));
		if (!is_digits(tmp))
			return false;
		str = &str[str.find(".") + 1];
		i++;
	}
	if (!is_digits(str) || str.size() == 0)
		return false;
	return true;
}
