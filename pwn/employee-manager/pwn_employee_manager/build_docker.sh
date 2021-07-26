#!/bin/sh

docker rm -f manager
docker build . -t manager
docker run --name manager -d -p 1337:1337 manager
