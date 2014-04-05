#ifdef __WAND__
dependency[port.o]
target[name[port.h]type[include]]
#endif

#ifndef MUSTIDIO_PORT_H
#define MUSTIDIO_PORT_H

#include <cstddef>

namespace MuStudio
	{
	class Client;

	class Port
		{
		public:
			enum class Type:unsigned int{AUDIO,MIDI};
			
			static const size_t PORT_IS_INPUT = 0x1;
			static const size_t PORT_IS_OUTPUT = 0x2;
			
			Port(Client& client, const char* name, size_t flags, Type type);
			void* bufferGet(size_t n_frames);
			~Port();
			
		private:
			Client& m_client;
			void* port;
		};
	}

#endif
