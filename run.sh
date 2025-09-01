type=exe
if [ "$#" -gt 0 ]; then
    type=$1
fi


if [ "$type" == "lib" ]; then
    ./cbuild archivebuildall --settings-file=settings-staticlib-linux.txt
else
    ./cbuild buildall --settings-file=settings-linux.txt
    ./build/cbtest
fi