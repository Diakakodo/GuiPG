#!/bin/bash

make
mv Makefile Makefile_guipg
mv Makefile_tests Makefile
make
mv Makefile Makefile_tests
mv Makefile_guipg Makefile
cd ../src/mypty && make

exit
