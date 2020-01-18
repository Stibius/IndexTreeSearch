#Compile the code
prog="search_roster"
# if the file $prog exists then remove it
if [ -f "$prog" ]; then
    rm "$prog"
fi
g++ -std=c++17 *.cpp -o "$prog"
# if the file $prog does not exit then exit the test
if [ ! -f "$prog" ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
rm -f *.out *.stderr *.stdcout *.diff

from=1
to=8
for i in `seq $from $to`; do
    ./"$prog" "A=1.txt;B="$i"k.txt;C=$i.out" 1>"$i.stdcout" 2>"$i.stderr"
    diff -iEBwu "$i.ans" "$i.out" > "$i.diff" 2>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "Test case $i    \033[1;91mFAILED.\033[0m"
    else
        echo -e "Test case $i    \033[1;92mPASSED.\033[0m"
        rm -f "$i.diff"
    fi
done
