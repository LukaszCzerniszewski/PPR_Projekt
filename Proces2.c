/* ********************************************** */
/* Na podstawie: http://xmlrpc-c.sourceforge.net  */
/* ********************************************** */
#define WIN32_LEAN_AND_MEAN  /* wymagane przez xmlrpc-c/server_abyss.h */
#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>
#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include <stdlib.h>
#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>
static void 
dieIfFaultOccurred (xmlrpc_env * const envP) {
    if (envP->fault_occurred) {
        fprintf( stderr, "ERROR: %s (%d)\n", envP->fault_string, envP->fault_code );
        exit(1);
    }
}
//======================================================================
static xmlrpc_value * sample_add(
			xmlrpc_env *   const envP,
			xmlrpc_value * const paramArrayP,
			void *         const serverInfo,
			void *         const channelInfo) {

    // xmlrpc_int32 x, y, z;
    // xmlrpc_array_get_item abc;

    /* Parsujemy tablice z argumentami ********************************/
    /* ("ii") oznacza format danych, tutaj: 2 x int *******************/
    // xmlrpc_decompose_value( envP, paramArrayP, "(ii)", &x, &y );



      xmlrpc_value * x;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(s)", &x);


    if (envP->fault_occurred)
        return NULL;

    /* Dodajemy argumenty *********************************************/
    // z = x + y;

    printf("\nProces 2 wita sie i przesyla dalej wiadomosc %s\n",x);
      snd((char *)x);







    /* Zwracamy wynik *************************************************/

    
    return xmlrpc_build_value(envP, "i", 883662149);
}


int snd(char * snd)
{
    const char * const serverUrl = "http://127.0.0.1:10003/RPC2";
    const char * const methodName = "post";
	
	/* zmienne niezainicjowane ****************************************/
    xmlrpc_env env;
    xmlrpc_value * resultP;
    xmlrpc_int32 sum;
    
    /* inicjujemy srodowisko ******************************************/
    xmlrpc_env_init(&env);

    /* inicjujemy xml-rpc po stronie klienta **************************/
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    dieIfFaultOccurred(&env);	// sprawdzamy, czy wystapil blad 

    /* wywolujemy zdalna procedure ************************************/
    /* ("ii") oznacza format danych, tutaj: 2 x int *******************/
    resultP = xmlrpc_client_call(&env, serverUrl, methodName, "(s)",snd);
    // dieIfFaultOccurred(&env);
    
    // /* pobieramy wynik ************************************************/
    // xmlrpc_read_int(&env, resultP, &sum);
    // dieIfFaultOccurred(&env);
    
    // /* wypisujemy wynik ***********************************************/
    // printf("Wynik: %d\n", sum);
    
    // /* dekrementujemy licznik referencji ******************************/
    // xmlrpc_DECREF(resultP);

    /* czyscimy srodowisko ********************************************/
    xmlrpc_env_clean(&env);
    
    /* konczymy prace klienta *****************************************/
    xmlrpc_client_cleanup();
    return 0;

}
//======================================================================
int main( void ){
    
    
    printf("Proces2\n");

	/* zmienne predefiniowane *****************************************/
	int  port   = 10002;
	//------------------------------------------------------------------
    struct xmlrpc_method_info3 const methodInfo = {
        /* .methodName     = */ "sample.add",
        /* .methodFunction = */ &sample_add,
    };
    
	/* zmienne niezainicjowane ****************************************/
    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry * registryP;
    xmlrpc_env env;

    /* inicjujemy serwer **********************************************/
    xmlrpc_env_init(&env);

	/* rejestrujemy zmienne srodowiskowe ******************************/
    registryP = xmlrpc_registry_new(&env);
    if (env.fault_occurred){
        printf( "xmlrpc_registry_new(): %s\n", env.fault_string);
        exit(1);
    }

	/* rejestrujemy nasza metode/funkcje ******************************/
    xmlrpc_registry_add_method3( &env, registryP, &methodInfo );
    if (env.fault_occurred) {
        printf( "xmlrpc_registry_add_method3(): %s\n", env.fault_string );
        exit(1);
    }

	/* ustawiamy parametry serwera ************************************/
    serverparm.config_file_name = NULL;
    serverparm.registryP        = registryP;
    serverparm.port_number      = port;
    serverparm.log_file_name    = "/tmp/xmlrpc_log";

	/* uruchamiamy serwer *********************************************/
    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(log_file_name));
    if( env.fault_occurred ){
        printf("xmlrpc_server_abyss(): %s\n", env.fault_string);
        exit(1);
    }

	/* konczymy dzialanie *********************************************/
    return 0;
}
//======================================================================


