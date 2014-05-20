detector
========

this is a simple code, purpose is capture network data, match my keyword

you need install this libnet, libpcap, catdoc

programme run 
	0 make compile this programme
		make
	1 make a directory for work run this script
		./make_mydir.sh
	2 start to nfex, update nfexstart.sh as your network device default "eth1" 
	  and run this script
		./nfexstart.sh
	3 update ssl_client.c NETDEV as your network default "eth1"
		./cli
