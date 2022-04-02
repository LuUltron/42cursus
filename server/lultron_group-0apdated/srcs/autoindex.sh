#!bin/sh

if grep -q "autoindex off;" /etc/nginx/sites-available/luannasite
then
	sed -i 's/autoindex off;/autoindex on;/' /etc/nginx/sites-available/luannasite
	ln -s /var/www/luannasite/wordpress/index.php /var/www/luannasite/index.php
	echo "autoindex ON"
else
	sed -i 's/autoindex on;/autoindex off;/' /etc/nginx/sites-available/luannasite
	rm /var/www/luannasite/index.php
	echo "autoindex OFF"
fi
service nginx restart