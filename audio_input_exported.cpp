#ifdef __WAND__
target
	[
	name[audio_input_exported.o]
	type[object]
	dependency[jack;external]
	platform[;GNU/Linux]
	]
#endif

#include "audio_input_exported.h"
#include "client.h"
#include <jack/jack.h>

MuStudio::Audio::InputExported::InputExported(Client& client,const char* name)
	{
	m_client=client.connection;
	port=jack_port_register
		(
		(jack_client_t*)client.connection,name
		,JACK_DEFAULT_AUDIO_TYPE,JackPortIsInput,0
		);
	if(port==NULL)
		{throw "Could not register port";}
	}

const MuStudio::Audio::sample_t*
MuStudio::Audio::InputExported::bufferGet(size_t n_frames) const
	{
	return (const Audio::sample_t*)jack_port_get_buffer((jack_port_t*)port,n_frames);
	}
	
MuStudio::Audio::InputExported::~InputExported()
	{jack_port_unregister((jack_client_t*)m_client,(jack_port_t*)port);}
