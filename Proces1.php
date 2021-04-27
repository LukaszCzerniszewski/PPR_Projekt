#!/usr/bin/php

<?php
	#===================================================================
	print("Proces 1 rozpoczal swoje dzialanie\n");
	while(true) {
	$line = readline("Podaj wiadomosc do przekonwertowania ");
	
	$port 	= 10002;
	$host 	= '127.0.0.1';

	#-------------------------------------------------------------------
	$req = xmlrpc_encode_request(
		"sample.add", 
		[$line]
	);
	#-------------------------------------------------------------------
	$ctx = stream_context_create(
		array(
			'http' => array(
				'method' 	=> "POST",
				'header' 	=> array( "Content-Type: text/xml" ),
				'content' 	=> $req
			)
		)
	);
	#-------------------------------------------------------------------
	$xml = file_get_contents( "http://$host:$port/RPC2", false, $ctx );
	#-------------------------------------------------------------------
	// $res = xmlrpc_decode( $xml );
	// #-------------------------------------------------------------------
	// if( $res && xmlrpc_is_fault( $res ) ){
	// 	print "xmlrpc: $res[faultString] ($res[faultCode])";
	// 	exit( 1 );
	// } else {
	// 	print_r( $res );
	// }
	#===================================================================
	}
?>
