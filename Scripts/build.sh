# This script named build.sh takes no argument and simply builds the executables of all the applications that you implemented.

# loop throught the c programs in the application directory
# complile them including our Image Library
for file in ./Applications/*.c
do
    build=${file%.*};
    executable=${build##*/};
    gcc -Wall -I ./ImageLibrary/include  ./ImageLibrary/src/*.c $file -o $executable;
done
