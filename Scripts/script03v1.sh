# take three arguments:
# • The path of the “source” directory to look for images in, 
# • the path to the search folder,
# • The path to the output folder.
# If the output folder doesn’t already exist, then your script should create it. If the folder already exists, then your script should delete its content.

# execute our build script
./Scripts/build.sh


if test -d $3; then
    rm ./$3/*
else
    mkdir $3
fi


for img in $1/*.tga
do
    echo "executing matchSearch for $img $2 $3"
    ./matchSearch $img $2 $3
done
