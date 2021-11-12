#! /bin/sh

if [ -z "$1" ]; then
  p="./p2"
else
  p="$1"
fi
 
dash test1.sh "$p"

in='a
ab
^ab$
aba
abba
z..z
z*(a)
/\^$'

err1=$(cat .err)
err="$err1"

error() {
  err=$((err + 1))
  echo "$err" > .err
}

echo '-1	^a		0	a	0	^ab$
-1	AAA		1	P	0	a
-F	^ab$		0	^ab$	0	aQabQabaQabbaQz..zQz*(a)Q/\^$
-E	^(a|ab)$	0	aQab	0	^ab$QabaQabbaQz..zQz*(a)Q/\^$' |
while read -r flag pat e r ev rv
do
  r=$(echo "$r" | tr -d 'P' | tr 'Q' '\n')
  rv=$(echo "$rv" | tr 'Q' '\n')
  #
  printf "\nRun: $p $flag \"$pat\"\n"
  out=$(echo "$in" | $p $flag "$pat")
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
  #
  printf "\nRun: $p -v $flag \"$pat\"\n"
  out=$(echo "$in" | $p -v $flag "$pat")
  s="$?"
  printf "$out\n\n"
  if [ "x$out" = "x$rv" ]; then
    echo "Correct!"
  else
    printf "***** WRONG - output should be:\n$rv\n"
    error
  fi
  if [ "x$s" != "x$ev" ]; then
    echo "***** WRONG exit status: $s should be $ev"
    error
  fi
done

err=$(cat .err)
err2=$((err - err1))
printf "\n${0}: $err2 errors\n"
echo "${0}: $err total errors"
