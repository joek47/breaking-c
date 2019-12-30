echo "Running unit tests:"

for i in tests/*_tests
do
    # -f flag
    # FILE exists and is a regular file
    if test -f $i
    then
        # The > operator redirects the output usually to a file but it can be to 
        # a device. You can also use >> to append.  If you don't specify a number then 
        # the standard output stream is assumed but you can also redirect errors 
        # > file redirects stdout to file 
        # 1> file redirects stdout to file 
        # 2> file redirects stderr to file 
        # &> file redirects stdout and stderr to file 
        # /dev/null is the null device it takes any input you want and throws it away. It can be used to suppress any output.  

        if $VALGRIND ./$i 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""
