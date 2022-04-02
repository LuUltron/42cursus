#!bin/sh

#if script ecexuted with some argument, all containers and images would be deleted  
if [ -n "$1" ]
then
	docker container prune -f
	docker rmi $(docker images -a -q)
else
	docker build -t newim ..
	docker run -it --name new -p 80:80 -p 443:443 newim
fi