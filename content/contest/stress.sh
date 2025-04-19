for ((i=1; ; ++i)); do
    ./gen $i > in
    a=$(./a.out < in)
    b=$(./brute < in)
    echo "$i $a $b"
    diff -w <(echo "$a") <(echo "$b") || break
done
