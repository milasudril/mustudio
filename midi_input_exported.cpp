#ifdef __WAND__
target
	[
	name[midi_input_exported.o]
	type[object]
	dependency[jack;external]
	platform[;GNU/Linux]
	]
#endif

#include "midi_input_exported.h"
#include "midi_event.h"
#include "client.h"
#include <jack/midiport.h>
#include <jack/jack.h>

MuStudio::MIDI::InputExported::InputExported(Client& client,const char* name)
	{
	m_client=client.connection;
	port=jack_port_register
		(
		(jack_client_t*)client.connection,name
		, JACK_DEFAULT_MIDI_TYPE,JackPortIsInput,0
		);
	if(port==NULL)
		{throw "Could not register port";}
	}

MuStudio::MIDI::InputExported::~InputExported()
	{
	jack_port_unregister((jack_client_t*)m_client,(jack_port_t*)port);
	}

bool MuStudio::MIDI::InputExported::eventFirstGet(Event& event,size_t n_frames)
	{
	buffer=jack_port_get_buffer((jack_port_t*)port,n_frames);
	event_count=jack_midi_get_event_count(buffer);
	if(event_count==0)
		{return 0;}
	event_index=0;
	jack_midi_event_t e;
	jack_midi_event_get(&e,buffer,event_index);
	event.time=e.time;
	event.data.bytes[0]=e.buffer[0];
	event.data.bytes[1]=e.buffer[1];
	event.data.bytes[2]=e.buffer[2];
	event.data.bytes[3]=0;
	return 1;
	}

bool MuStudio::MIDI::InputExported::eventNextGet(Event& event)
	{
	++event_index;
	jack_midi_event_t e;
	if(event_index<event_count)
		{
		jack_midi_event_get(&e,buffer,event_index);
		event.time=e.time;
		event.data.bytes[0]=e.buffer[0];
		event.data.bytes[1]=e.buffer[1];
		event.data.bytes[2]=e.buffer[2];
		event.data.bytes[3]=0;
		return 1;
		}
	return 0;
	}
