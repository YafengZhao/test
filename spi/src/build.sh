#!/bin/bash - 
#===============================================================================
#
#          FILE: build.sh
# 
#         USAGE: ./build.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
#  ORGANIZATION: FH Südwestfalen, Iserlohn, Germany
#       CREATED: 2018年05月21日 23:27
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

root=$PWD
jarname=hello.jar
cd ./main && javac ./hello/spi/chinese/Chinese.java && javac ./hello/spi/english/English.java &&  javac ./hello/spi/DemoService.java && jar -cf $root/$jarname ./hello/spi/chinese/Chinese.class ./hello/spi/english/English.class ./hello/spi/DemoService.class 

cd $root/resources/ && jar -uf $root/$jarname META-INF

cd $root && javac -cp .:$root/$jarname Main.java && java -cp .:$root/$jarname Main

