#ifdef __WAND__
target[name[midi.h] type[include]]
#endif

#ifndef MUSTUDIO_MIDI_H
#define MUSTUDIO_MIDI_H

#include <cstddef>
#include <cstdint>

namespace MuStudio
	{
	namespace MIDI
		{
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
		}
	}

#endif

