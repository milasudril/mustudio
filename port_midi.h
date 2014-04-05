#ifdef __WAND__
dependency[port_midi.o]
target[name[port_midi.h]type[include]]
#endif

#ifndef MUSTUDIO_PORTMIDI_H
#define MUSTUDIO_PORTMIDI_H

#include "port.h"
#include <cstdint>

namespace MuStudio
	{
	class PortMIDI:public Port
		{
		public:
			struct Message
				{
				uint8_t byte_0;
				uint8_t byte_1;
				uint8_t byte_2;
				uint8_t padding;
				};
			
			struct Event
				{
				size_t time;
				Message data;
				};
			
			PortMIDI(Client& client,const char* name,size_t flags):
				Port(client,name,flags,Type::MIDI){}
				
			bool eventFirstGet(Event& event,size_t n_frames);
				
			bool eventNextGet(Event& event);
			
			void messageWrite(Message msg);
			
			void messageWritePrepare(size_t n_frames);
			
		private:
			size_t event_count;
			size_t event_index;
			void* buffer;
		};
	}

#endif
