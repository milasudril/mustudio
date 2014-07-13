#ifdef __WAND__
target[name[midi_sequence.o] type[object]]
#endif

#include "midi_sequence.h"
#include "midi_event.h"
#include "midi_file_header.h"
#include "midi_track_reader.h"
#include "midi_chunk_reader.h"
#include <herbs/stringbase/stringbase.h>

MuStudio::MIDI::Sequence::Sequence(Herbs::StreamIn& source)
	{
	MuStudio::MIDI::FileHeader header;
	MuStudio::MIDI::ChunkReader chunk_reader(source,header);
	MuStudio::MIDI::TrackReader track_reader(chunk_reader);
	time_division=header.time_division;
	tracks.lengthValidSet(header.n_tracks);
	tracks.clear();
	Herbs::Stringbase<char> chunk_name;
	while(chunk_reader.headerRead(chunk_name))
		{
		tracks.append(Herbs::Array<Event>());
		auto ptr_begin=tracks.end() - 1;
		MuStudio::MIDI::Event e;
		while(track_reader.eventNextGet(e))
			{
			ptr_begin->append(e);
			}
		chunk_reader.skip();	
		}
	}
	
namespace
	{
	bool time_compare(const MuStudio::MIDI::Event& a
		,const MuStudio::MIDI::Event& b)
		{
		return a.time<b.time;
		}
	}

MuStudio::MIDI::Sequence& MuStudio::MIDI::Sequence::tracksMerge()
	{
	Herbs::Array<Herbs::Array<Event> > tracks_new(1);
	tracks_new.lengthValidSet(1);
	auto track_new=tracks_new.begin();
		{
		auto track=tracksBegin();
		while(track!=tracksEnd())
			{
			uint32_t time_tot=0;
			auto event=track->begin();
			while(event!=track->end())
				{
				auto e_temp=*event;
				e_temp.time+=time_tot;
				track_new->append(e_temp);
				time_tot+=event->time;
				++event;
				}
			++track;
			}
		
		std::sort(track_new->begin(),track_new->end(),time_compare);
		}
		
		{
		auto event=track_new->begin();
		uint32_t time_prev=0;
		while(event!=track_new->end())
			{
			auto time_current=event->time;
			event->time-=time_prev;
			time_prev=time_current;
			++event;
			}
		}
	
	tracks=tracks_new;
	
	return *this;
	}
