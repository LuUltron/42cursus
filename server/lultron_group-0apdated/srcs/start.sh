#!bin/sh

mkdir /var/www/luannasite

service mysql start
mysql -u root -e "CREATE USER 'luanna'@'localhost' IDENTIFIED BY 'pw'" 
mysql -u root -e "CREATE DATABASE newdb"
mysql -u root -e "GRANT ALL PRIVILEGES ON newdb.* TO 'luanna'@'localhost'"
mysql -u root -e "FLUSH PRIVILEGES"
mysql newdb -u root --password=  < /tmp/newdb.sql

wget https://files.phpmyadmin.net/phpMyAdmin/5.0.2/phpMyAdmin-5.0.2-all-languages.tar.gz
tar -xf phpMyAdmin-5.0.2-all-languages.tar.gz
rm phpMyAdmin-5.0.2-all-languages.tar.gz
mv phpMyAdmin-5.0.2-all-languages /var/www/luannasite/phpmyadmin

wget https://wordpress.org/latest.tar.gz
tar -xf latest.tar.gz -C /var/www/luannasite/
rm latest.tar.gz 
cp /tmp/wp-config.php /var/www/luannasite/wordpress
ln -s /var/www/luannasite/wordpress/index.php /var/www/luannasite/index.php

mkdir /etc/nginx/ssl
openssl req -x509 -nodes -newkey rsa:2048 -sha512 -keyout /etc/nginx/ssl/luannasite-key.key -out /etc/nginx/ssl/luannasite.crt -subj "/C=RU/ST=Moscow/L=Moscow/O=OOORogaIKopyta/OU=luanna/CN=luannasite"

cp /tmp/luannasite /etc/nginx/sites-available/
rm -rf ./etc/nginx/sites-enabled/default
rm -rf ./etc/nginx/sites-available/default
ln -s /etc/nginx/sites-available/luannasite /etc/nginx/sites-enabled/

chown -R www-data:www-data /var/www/luannasite
service mysql start
service php7.3-fpm start
service nginx start
bash
