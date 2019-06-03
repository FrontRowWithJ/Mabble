#!/bin/bash
#compile a list of cpp files with the sfml library
compile="g++"
isSourcePresent="0"
isOutputPresent="0"
invalidOutputName="0"
outputFileFound="0"
for var in "$@"
do
    fname=$var
    format=$(cut -d'.' -f2 <<<"$fname")
    if [[ "$format" == "cpp" ]]; then
        compile=$compile" "$var
        isSourcePresent="1"
    fi

    if [[ "$outputFileFound" = "1" ]]; then
        if [[ "$format" = "$var" ]]; then
            compile=$compile" -lsfml-graphics -lsfml-window -lsfml-system -o "$var
            isOutputPresent="1"
            break
        else
            invalidOutputName="1"
        fi
    fi

    if [[ "$format" = "-o" ]]; then
        outputFileFound="1"
    fi

done 

if [[ "$outputFileFound" = "0" ]]; then
    echo "No output file found"
fi

if [ "$invalidOutputName" = "1" ]; then
        echo "The output name is incorrect ($var)"
fi
if [[ "$isOutputPresent" == "1" && "$isSourcePresent" == "1" ]]; then
    echo $compile
    $compile
fi
