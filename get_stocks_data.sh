echo Fetching FAANG stocks from the last 20 years
name=1;
for name in "$@" 
do

wget "https://www.alphavantage.co/query?function=TIME_SERIES_MONTHLY_ADJUSTED&symbol=$name&apikey=UK4XWXM1BV4OQLVE" -O $name.stock -q
sed -i 's/"//g' $name.stock
sed -i 's/{//g' $name.stock
sed -i 's/^[}{ ",\t]*//' $name.stock
egrep "^[1-4,6]|^[0-9]{4,}.*" $name.stock 1> Temp.txt
sed -i 's|^[0-9]\+\.||g'  Temp.txt
sed -i 's/ //g' Temp.txt
sed -i '1,4d' Temp.txt
awk '{printf("%s%s",$0 !~ /^[0-9]+/?"":(NR>1?RS:""),$0)} END{print ""}' Temp.txt >$name.stock
rm Temp.txt
echo Fetched $name monthly
sleep 13s
wget "https://www.alphavantage.co/query?function=EARNINGS&symbol=$name&apikey=UK4XWXM1BV4OQLVE&format=json" -O $name.esp -q
sed -i "/"quarterlyEarnings"/,/]/d" $name.esp 2> /dev/null
sed -i 's/^[}{ ",\t]*//' $name.esp
sed -i '/^$/d' $name.esp
sed -i 's/\[//g' $name.esp
sed -i '$d' $name.esp
sed -i '/^fiscal/{:loop; N;/\nfiscal/{P;D;t}; s/\n//g;b loop}' $name.esp
sed -i 's/"//g' $name.esp
sed -i 's/fiscalDateEnding: //g' $name.esp
sed -i 1,2d $name.esp
sed -i 's/-/:/1' $name.esp
sed -i 's/-/:/1' $name.esp
echo Fetched $name esp
sleep 13s

name=$((name+1));
done
