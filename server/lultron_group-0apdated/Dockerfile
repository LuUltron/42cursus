# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lultron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/12 23:34:32 by lultron           #+#    #+#              #
#    Updated: 2020/08/12 23:34:36 by lultron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

EXPOSE 80 443

LABEL maintainer="lultron@student.21-school.ru"

RUN apt-get update -y && apt-get install -y vim wget nginx openssl \
	mariadb-server php php-fpm php-mysql php-mbstring

COPY srcs/wp-config.php /tmp/
COPY srcs/luannasite /tmp/
COPY srcs/newdb.sql /tmp/
COPY srcs/autoindex.sh /tmp/
COPY srcs/start.sh /tmp/

CMD ["sh","/tmp/start.sh"]