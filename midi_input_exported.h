#ifdef __WAND__
dependency[midi_input_exported.o]
target[name[midi_input_exported.h]type[include]]
#endif

#ifndef MUSTUDIO_MIDIINPUTEXPORTED_H
#define MUSTUDIO_MIDIINPUTEXPORTED_H

#include "midi_event.h"

namespace MuStudio
	{
	class Client;
	namespace MIDI
		{
		class InputExported
			{
			public:
				InputExported(Client& client,const char* name);
				~InputExported();
					
				bool eventFirstGet(Event& event,size_t n_frames);
					
				bool eventNextGet(Event& event);
				
			private:
				void* m_client;
				void* port;
				size_t event_count;
				size_t event_index;
				void* buffer;
			};
		}
	}

#endif
