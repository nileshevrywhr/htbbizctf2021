#!/bin/bash

docker build . -t backtrack
docker run --rm --name backtrack -p 1337:1337 -p 31337:31337 backtrack
