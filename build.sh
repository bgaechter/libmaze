#!/usr/bin/env bash

debug_dir="`pwd`/debug"
release_dir="`pwd`/release"
build_dir="`pwd`/build"
project_dir="`pwd`"
platform=$(uname)
number_of_cores=1


if [ $platform = "Darwin" ]; then
    number_of_cores=$(sysctl -n hw.ncpu)
elif [ $platform = "Linux" ]; then
    number_of_cores=$(grep -c ^processor /proc/cpuinfo 2>/dev/null)
fi

function clean
{
	rm -rf ${build_dir}/*
}

function build
{
	configuration=$1
	cd ${build_dir}
	cmake -DCMAKE_BUILD_TYPE=${configuration} ${project_dir}
	make -j${number_of_cores}
	ctest --output-on-failure
}

case $(echo "${@: -1}") in
    -a|"")
        build "debug"   && \
        build "release"
        ;;
    -c)
        clean
        ;;
    -d)
        build "debug"
        ;;
    -r)
        build "release"
        ;;
    *)
        exit 1
        ;;
esac
