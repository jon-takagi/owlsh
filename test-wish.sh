#! /bin/bash

if ! [[ -x wish ]]; then
    echo "executable does not exist"
    exit 1
fi

../tester/run-tests.sh $*
