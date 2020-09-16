#! /bin/bash

if ! [[ -x owlsh ]]; then
    echo "executable does not exist"
    exit 1
fi

../tester/run-tests.sh $*


