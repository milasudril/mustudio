#ifdef __WAND__
target[name[midi_input.h] type[include]]
#endif

#include "midi_event.h"

namespace MuStudio
	{
	namespace MIDI
		{
		class Input
			{
			public:
				virtual bool eventFirstGet(Event& event,size_t n_frames)=0;
				virtual bool eventNextGet(Event& event)=0;
			};
		}
	}

