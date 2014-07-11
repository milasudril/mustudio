#ifdef __WAND__
dependency[midi_output_exported.o]
target[name[midi_output_exported.h]type[include]]
#endif

#ifndef MUSTUDIO_MIDIOUTPUTEXPORTED_H
#define MUSTUDIO_MIDIOUTPUTEXPORTED_H

#include "midi_event.h"

namespace MuStudio
	{
	class Client;
	namespace MIDI
		{
		class OutputExported
			{
			public:
				OutputExported(Client& client,const char* name);
				~OutputExported();
				
				void messageWrite(Message msg);
				
				void messageWritePrepare(size_t n_frames);
				
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
