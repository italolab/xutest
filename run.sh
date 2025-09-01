type=exe
if [ "$#" -gt 0 ]; then
    type=$1
fi


if [ "$type" == "lib" ]; then
    ./cbuild archivebuildall --settings-file=settings-staticlib-linux.txt
else
    ./cbuild testbuildall --settings-file=settings-linux.txt
fi