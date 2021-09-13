#!/bin/sh

docker build -t spim_panel .
docker run --name spim_panel -p 1337:1337 -d spim_panel