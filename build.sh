CMAKE_FLAGS=""

while getopts dxc opt; do
	case ${opt} in
	x)
		if [ -d "./build" ]; then
			rm -rf build
		fi
		exit
		;;
	d)
		CMAKE_FLAGS="$CMAKE_FLAGS -DCMAKE_BUILD_TYPE=Debug"
		;;
	c)
		CMAKE_FLAGS="$CMAKE_FLAGS -DCMAKE_EXPORT_COMPILE_COMMANDS=1"
		;;
	esac
done

if [ ! -d "./build" ]; then
	mkdir build
fi
cd build
cmake ..
if [ -f "./compile_commands.json" ]; then
	mv compile_commands.json ../
fi
make
