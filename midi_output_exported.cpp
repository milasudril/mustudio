#ifdef __WAND__
target
	[
	name[midi_output_exported.o]
	type[object]
	dependency[jack;external]
	platform[;GNU/Linux]
	]
#endif

#include "midi_output_exported.h"
#include "midi_event.h"
#include "client.h"
#include <jack/midiport.h>
#include <jack/jack.h>

MuStudio::MIDI::OutputExported::OutputExported(Client& client,const char* name)
	{
	m_client=client.connection;
	port=jack_port_register
		(
		(jack_client_t*)client.connection,name
		, JACK_DEFAULT_MIDI_TYPE,JackPortIsOutput,0
		);
	if(port==NULL)
		{throw "Could not register port";}
	}
	
MuStudio::MIDI::OutputExported::~OutputExported()
	{
	jack_port_unregister((jack_client_t*)m_client,(jack_port_t*)port);
	}

void MuStudio::MIDI::OutputExported::messageWritePrepare(size_t n_frames)
	{
	buffer=jack_port_get_buffer((jack_port_t*)port,n_frames);
	jack_midi_clear_buffer(buffer);
	}
	
void MuStudio::MIDI::OutputExported::messageWrite(const Event& e)
	{
	if(e.type==0)
		{
		jack_midi_data_t* outbuff = jack_midi_event_reserve( buffer, 0, 3);
		outbuff[0]=e.data.bytes[0];
		outbuff[1]=e.data.bytes[1];
		outbuff[2]=e.data.bytes[2];
		}
	}

