type=exe
if [ "$#" -gt 0 ]; then
    type=$1
fi


if [ "$type" == "lib" ]; then
    ./cbuild buildall --settings-file=settings-staticlib-linux.txt
else
    ./cbuild build --settings-file=settings-linux.txt
    ./build/cbtest
fi