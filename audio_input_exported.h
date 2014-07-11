#ifdef __WAND__
target[name[audio_input_exported.h]type[include]]
dependency[audio_input_exported.o]
#endif

#ifndef MUSTIDIO_AUDIOINPUTEXPORTED_H
#define MUSTIDIO_AUDIOINPUTEXPORTED_H

#include "audio_sampletype.h"
#include <cstddef>

namespace MuStudio
	{
	class Client;
	namespace Audio
		{
		class InputExported
			{
			public:
				InputExported(Client& client,const char* name);
				~InputExported();
					
				const sample_t* bufferGet(size_t n_frames) const;

			private:
				void* m_client;
				void* port;
			};
		}
	}

#endif
