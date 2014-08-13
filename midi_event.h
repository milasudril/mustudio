#ifdef __WAND__
target[name[midi_event.h] type[include]]
#endif

#ifndef MUSTUDIO_MIDI_EVENT_H
#define MUSTUDIO_MIDI_EVENT_H

#include <cstddef>
#include <cstdint>

namespace MuStudio
	{
	namespace MIDI
		{
		struct alignas(8) Event
			{
			uint32_t time;
			union
				{
				uint8_t  bytes[4];
				uint16_t words[2];
				uint32_t dwords[1];
				} data;
			};
		}
	}

#endif

