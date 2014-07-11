#ifdef __WAND__
target
	[
	name[audio_output_exported.o]
	type[object]
	dependency[jack;external]
	platform[;GNU/Linux]
	]
#endif

#include "audio_output_exported.h"
#include "client.h"
#include <jack/jack.h>

MuStudio::Audio::OutputExported::OutputExported(Client& client,const char* name)
	{
	m_client=client.connection;
	port=jack_port_register
		(
		(jack_client_t*)client.connection,name
		,JACK_DEFAULT_AUDIO_TYPE,JackPortIsOutput,0
		);
	if(port==NULL)
		{throw "Could not register port";}
	}

MuStudio::Audio::sample_t*
MuStudio::Audio::OutputExported::bufferGet(size_t n_frames)
	{
	return (Audio::sample_t*)jack_port_get_buffer((jack_port_t*)port,n_frames);
	}
	
MuStudio::Audio::OutputExported::~OutputExported()
	{jack_port_unregister((jack_client_t*)m_client,(jack_port_t*)port);}
