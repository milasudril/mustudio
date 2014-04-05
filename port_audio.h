#ifdef __WAND__
target[name[port_audio.h]type[include]]
#endif

#ifndef MUSTIDIO_PORTAUDIO_H
#define MUSTIDIO_PORTAUDIO_H

#include "port.h"

namespace MuStudio
	{
	class PortAudio:public Port
		{
		public:
			typedef float sample_t;
			
			PortAudio(Client& client,const char* name,size_t flags):
				Port(client,name,flags,Type::AUDIO){}
				
			sample_t* bufferGet(size_t n_frames)
				{return (sample_t*)Port::bufferGet(n_frames);}
		};
	}

#endif
