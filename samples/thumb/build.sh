#!/bin/sh

 cc -g -O0 -Wall -Werror -I../../include -L../.. sample_thumb.c -lunicorn -lpthread -o sample_thumb
