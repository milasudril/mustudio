#ifdef __WAND__
target[name[midi_event.h] type[include]]
#endif

#ifndef MUSTUDIO_MIDI_H
#define MUSTUDIO_MIDI_H

#include <cstddef>
#include <cstdint>

namespace MuStudio
	{
	namespace MIDI
		{
		struct alignas(16) Event
			{
			uint32_t time;
			uint32_t type;
			union
				{
				uint8_t  bytes[8];
				uint16_t words[4];
				uint32_t dwords[2];
				uint64_t qwords[1];
				} data;
			};
		}
	}

#endif

