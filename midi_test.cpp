#ifdef __WAND__
target[name[midi_test] type[application]]
#endif


#include "midi_sequence.h"
#include "midi_event.h"
#include <herbs/filein/filein.h>

int main()
	{
	Herbs::FileIn pattern_file(Herbs::Path(STR("pattern_0.mid")));
	MuStudio::MIDI::Sequence pattern(pattern_file);
	size_t time_div=pattern.timeDivisionGet();
	printf("Time div is %lu\n",time_div);
	
//	pattern.tracksMerge();
	
	auto track=pattern.tracksBegin();
	while(track!=pattern.tracksEnd())
		{
		auto event=track->begin();
		while(event!=track->end())
			{
			printf("%u ",event->time);
			switch(event->type)
				{
				case 0:
					switch(event->data.bytes[0]&0xf0)
						{
						case 0x80:
							printf("Note off,");
							break;
						case 0x90:
							printf("Note on,");
							break;
						case 0xb0:
							printf("Control change,");
							break;
						case 0xc0:
							printf("Program change,");
							break;
						default:
							printf("Other %x,",event->data.bytes[0]);
						}
					printf("%x,%x\n",event->data.bytes[1],event->data.bytes[2]);
					break;
				case 0x2:
					printf("Copyright message: %s\n",event->data.bytes);
					break;
				case 0x3:
					printf("Name: %s\n",event->data.bytes);
					break;
				case 0x7:
					printf("Cue message: %s\n",event->data.bytes);
					break;
				case 0x51:
					printf("Tempo: %x\n",event->data.dwords[0]);
					break;
				default:
					printf("Meta-event %x\n",event->type);
				}
			++event;
			}
		printf("=========================================\n");
		++track;
		}
	return 0;
	}