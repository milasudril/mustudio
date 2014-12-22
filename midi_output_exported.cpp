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
	if(port==nullptr)
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
	int length;
	if(e.data.bytes[0] < 0xF0)
		{length = (e.data.bytes[0] >= 0xC0 &&  e.data.bytes[0] <= 0xDF) ? 2 : 3;}
	else
	if(e.data.bytes[0] >= 0xF8)
		{length = 1;}
	else
		{
		switch (e.data.bytes[0])
			{
			case 0xF1:
			case 0xF3:
				length = 2;
				break;
			case 0xF2:
				length = 3;
				break;
			case 0xF6:
				length = 1;
				break;
			default:
				return;
			}
		}
	jack_midi_data_t* outbuff = jack_midi_event_reserve( buffer, 0, length);
	while(length--)
		{outbuff[length]=e.data.bytes[length];}
	}
