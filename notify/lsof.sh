#!/bin/bash - 
#===============================================================================
#
#          FILE: lsof.sh
# 
#         USAGE: ./lsof.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
#  ORGANIZATION: FH Südwestfalen, Iserlohn, Germany
#       CREATED: 2018年04月20日 20:23
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

for foo in /proc/*/fd/*; do readlink -f $foo; done | grep inotify | sort | wc -l
