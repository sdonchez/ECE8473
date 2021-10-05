subs=$(../bin/SubsCipher|grep "subs:"|cut -b7-)
sed -i "s/subs=\"[[:alnum:]]*\"/subs=\"$subs\"/" ./subs.sh
./subs.sh < ../data/subs.txt