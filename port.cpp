#ifdef __WAND__
target[name[port.o] type[object] dependency[jack;external] platform[;GNU/Linux]]
#endif

#include "port.h"
#include "client.h"

#include <jack/jack.h>

#include <cstdlib>

static const char* types[]={ JACK_DEFAULT_AUDIO_TYPE,JACK_DEFAULT_MIDI_TYPE};
MuStudio::Port::Port(Client& client, const char* name, size_t flags
	,Type type):m_client(client)
	{
	port=jack_port_register
		(
		(jack_client_t*)client.connection,name
		,types[(unsigned int)type],flags,0
		);
	if(port==NULL)
		{throw "Could not register port";}
	}

void* MuStudio::Port::bufferGet(size_t n_frames)
	{
	return jack_port_get_buffer((jack_port_t*)port,n_frames);
	}

MuStudio::Port::~Port()
	{
	jack_port_unregister((jack_client_t*)m_client.connection,(jack_port_t*)port);
	}
