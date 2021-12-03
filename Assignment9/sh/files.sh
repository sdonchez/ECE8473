#! /bin/sh
#
# create test files for dups.sh

mkdir -p Z1/Z2

echo	"aa	F1
	 bb	F2
	 bb	F3
	 cc	F4
	 aa	Z1/F5
	 bb	Z1/Z2/F6" | while read data fname
do
  echo "creating file $fname"
  echo "$data" > "$fname"
done
