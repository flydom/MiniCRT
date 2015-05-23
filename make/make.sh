#!/bin/bash

MAKE_DIR=$(pwd)
FIRST_PARA=$1
SECOND_PARA=$2

help()
{
echo ===========================================================
echo Make MiniCRT ...
echo ===========================================================
echo "./make.sh [target] [clean]"
echo ...
echo ===========================================================
}

clean()
{
cd $MAKE_DIR/../minicrt
make clean -f $MAKE_DIR/../minicrt/Makefile

cd $MAKE_DIR/../main
make clean -f $MAKE_DIR/../main/Makefile
}

minicrt()
{
cd $MAKE_DIR/../minicrt
make -f $MAKE_DIR/../minicrt/Makefile
}

main()
{
cd $MAKE_DIR/../main
make -f $MAKE_DIR/../main/Makefile
}

case $FIRST_PARA in
"minicrt")minicrt;;
"main")main;;
"clean")clean;;
*)help;;
esac