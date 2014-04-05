#ifdef __WAND__
target[name[client.o] type[object] dependency[jack;external] platform[;GNU/Linux]]
#endif

#include "client.h"
#include <cstdlib>
#include <jack/jack.h>

void MuStudio::Client::setErrorHandler(void(*error_handler)(const char *))
	{jack_set_error_function(error_handler);}

namespace	
	{
	int process_internal(jack_nframes_t nframes,void* arg)
		{
		MuStudio::Client* client=(MuStudio::Client*)arg;
		return client->onProcess(nframes);
		}

	int samplerate_internal (jack_nframes_t nframes, void *arg)
		{
		MuStudio::Client* client=(MuStudio::Client*)arg;
		return client->onSampleRateChanged(nframes);
		}

	void shutdown_internal(void* arg)
		{
		MuStudio::Client* client=(MuStudio::Client*)arg;
		client->onServerShutdown();
		}
	}  

MuStudio::Client::Client(const char* name_client)
	{
	const char *server_name = NULL;
	jack_options_t options = JackNullOption;
	jack_status_t status;
	connection=jack_client_open (name_client, options, &status, server_name);
	//TODO: Proper exception handler!
	if(connection==NULL)
		{throw "Could not create client!";}

	jack_set_process_callback ((jack_client_t*)connection, process_internal, this);
	jack_set_sample_rate_callback ((jack_client_t*)connection, samplerate_internal, this);
	jack_on_shutdown ((jack_client_t*)connection, shutdown_internal, this);
	}

void MuStudio::Client::activate()
	{
	jack_activate((jack_client_t*)connection);
	}

void MuStudio::Client::deactivate()
	{
	jack_deactivate((jack_client_t*)connection);
	}

MuStudio::Client::~Client()
	{jack_client_close((jack_client_t*)connection);}
	
int MuStudio::Client::onSampleRateChanged(size_t fs_new)
	{return 0;}
	
int MuStudio::Client::onServerShutdown()
	{return 0;}
