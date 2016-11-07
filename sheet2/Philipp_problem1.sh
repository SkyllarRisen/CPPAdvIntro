#!/bin/bash

timestamp() {
  date +"%T"
}
n=1
while [ $n -le 5 ]
do
	echo "$(timestamp): my message!" | mutt -s "my subject" -- email@adress.to
	n=$(( n+1 ))
done

exit 0