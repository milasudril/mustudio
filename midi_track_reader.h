#ifdef __WAND__
target[name[midi_track_reader.h] type[include]]
dependency [midi_track_reader.o]
#endif

#ifndef MUSTUDIO_MIDITRACKREADER_H
#define MUSTUDIO_MIDITRACKREADER_H

#include <cstdint>

namespace MuStudio
	{
	namespace MIDI
		{
		class ChunkReader;
		class Event;
		class TrackReader
			{
			public:
				explicit TrackReader(ChunkReader& reader):m_reader(reader){}
				bool eventNextGet(Event& event);
			private:
				ChunkReader& m_reader;
				uint8_t status_prev;
			};

		}
	}

#endif
