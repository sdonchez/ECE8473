#! /bin/sh

if [ -z "$1" ]; then
  p="./p1"
else
  p="$1"
fi

in='a
ab
^ab$
aba
abba
z..z
z*(a)
/\^$'
 
printf "\ninput data:\n---\n$in\n"

err=0
echo "$err" > .err

error() {
  err=$((err + 1))
  echo "$err" > .err
}

echo '^ab$		0	ab
^ab		0	abQabaQabba
\^\$		0	/\^$
ZabaZ		1
z\(z		2' |
while read -r pat e r
do
  r=$(echo "$r" | tr 'Q' '\n')
  printf "\nRun: $p \"$pat\"\n"
  out=$(printf "$in\n" | $p "$pat")
  s="$?"
  printf "$out\n\n"
  if [ "x$out" = "x$r" ]; then
    echo "Correct!"
  else
    printf "***** WRONG - output should be:\n$r\n"
    error
  fi
  if [ "x$s" != "x$e" ]; then
    echo "***** WRONG exit status: $s should be $e"
    error
  fi
done

printf "\n${0}: $(cat .err) errors\n"
