#ifdef __WAND__
target[name[port_midi.o] type[object] dependency[jack;external] platform[;GNU/Linux]]
#endif

#include "port_midi.h"

#include <jack/midiport.h>

bool MuStudio::PortMIDI::eventFirstGet(Event& event,size_t n_frames)
	{
	buffer=bufferGet(n_frames);
	event_count=jack_midi_get_event_count(buffer);
	if(event_count==0)
		{return 0;}
	event_index=0;
	jack_midi_event_t e;
	jack_midi_event_get(&e,buffer,event_index);
	event.time=e.time;
	event.data.byte_0=e.buffer[0];
	event.data.byte_1=e.buffer[1];
	event.data.byte_2=e.buffer[2];
	event.data.padding=0;
	return 1;
	}

bool MuStudio::PortMIDI::eventNextGet(Event& event)
	{
	++event_index;
	jack_midi_event_t e;
	if(event_index<event_count)
		{
		jack_midi_event_get(&e,buffer,event_index);
		event.time=e.time;
		event.data.byte_0=e.buffer[0];
		event.data.byte_1=e.buffer[1];
		event.data.byte_2=e.buffer[2];
		event.data.padding=0;
		return 1;
		}
	return 0;
	}

void MuStudio::PortMIDI::messageWritePrepare(size_t n_frames)
	{
	buffer=bufferGet(n_frames);
	jack_midi_clear_buffer(buffer);
	}
	
void MuStudio::PortMIDI::messageWrite(Message msg)
	{
	jack_midi_data_t* outbuff = jack_midi_event_reserve( buffer, 0, 3);
	outbuff[0]=msg.byte_0;
	outbuff[1]=msg.byte_1;
	outbuff[2]=msg.byte_2;
	}

