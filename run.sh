file="input.txt"
f='-'
i=0
while read line
do
if [ $line != $f ];
then 
	i=$[$i+1]
	if [ $i -eq 1 ];
	then
		file1=$line
	fi
		
	if [ $i -eq 2 ];
	then
		file2=$line
	fi
	
	if [ $i -eq 3 ];
	then
		file3=$line
	fi

	if [ $i -eq 4 ];
	then
		file4=$line
	fi

	if [ $i -eq 5 ];
	then
		file5=$line
	fi

	if [ $i -eq 6 ];
	then
		file6=$line
	fi

	if [ $i -eq 7 ];
	then
		file7=$line
	fi
else
	if [ $i -eq 1 ];
	then
		g++ main.cpp md5.cpp packet.cpp LRUcash.cpp AES.cpp PacketDB.cpp -ldb_cxx -o main -lpcap -lcryptopp
		./main offline tcp $file1 >> output.txt
	fi
		
	if [ $i -eq 2 ];
	then
		g++ main.cpp md5.cpp packet.cpp LRUcash.cpp AES.cpp PacketDB.cpp -ldb_cxx -o main -lpcap -lcryptopp
		./main offline tcp $file1 $file2 >> output.txt
	fi
	
	if [ $i -eq 3 ];
	then
		g++ main.cpp md5.cpp packet.cpp LRUcash.cpp AES.cpp PacketDB.cpp -ldb_cxx -o main -lpcap -lcryptopp
		./main offline tcp $file1 $file2 $file3 >> output.txt
	fi

	if [ $i -eq 4 ];
	then
		g++ main.cpp md5.cpp packet.cpp LRUcash.cpp AES.cpp PacketDB.cpp -ldb_cxx -o main -lpcap -lcryptopp
		./main offline tcp $file1 $file2 $file3 $file4 >> output.txt
	fi

	if [ $i -eq 5 ];
	then
		g++ main.cpp md5.cpp packet.cpp LRUcash.cpp AES.cpp PacketDB.cpp -ldb_cxx -o main -lpcap -lcryptopp
		./main offline tcp $file1 $file2 $file3 $file4 $file5 >> output.txt
	fi

	if [ $i -eq 6 ];
	then
		g++ main.cpp md5.cpp packet.cpp LRUcash.cpp AES.cpp PacketDB.cpp -ldb_cxx -o main -lpcap -lcryptopp
		./main offline tcp $file1 $file2 $file3 $file4 $file5 $file6 >> output.txt
	fi

	if [ $i -eq 7 ];
	then
		g++ main.cpp md5.cpp packet.cpp LRUcash.cpp AES.cpp PacketDB.cpp -ldb_cxx -o main -lpcap -lcryptopp
		./main offline tcp $file1 $file2 $file3 $file4 $file5 $file6 $file7 >> output.txt
	fi
	
	i=0
fi
done < $file

