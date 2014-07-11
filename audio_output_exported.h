#ifdef __WAND__
target[name[audio_output_exported.h]type[include]]
dependency[audio_output_exported.o]
#endif

#ifndef MUSTIDIO_AUDIOOUTPUTEXPORTED_H
#define MUSTIDIO_AUDIOOUTPUTEXPORTED_H

#include "audio_sampletype.h"
#include <cstddef>

namespace MuStudio
	{
	class Client;
	
	namespace Audio
		{
		class OutputExported
			{
			public:
				OutputExported(Client& client,const char* name);
				~OutputExported();
					
				sample_t* bufferGet(size_t n_frames);

			private:
				void* m_client;
				void* port;
			};
		}
	}

#endif
