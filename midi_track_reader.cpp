#ifdef __WAND__
target[name[midi_track_reader.o] type[object]]
#endif

#include "midi_track_reader.h"
#include "midi_chunk_reader.h"
#include "midi_event.h"
#include <cstdio>
#include <cstring>
#include <algorithm>  

bool MuStudio::MIDI::TrackReader::eventNextGet(Event& event)
	{
	if(m_reader.eoc())
		{return 0;}
	
	memset(&event,0,sizeof(event));
	
	event.time=m_reader.varfieldGet();
	if(m_reader.eoc())
		{return 0;}
		
	uint8_t eventType=m_reader.byteGet();
	if(m_reader.eoc())
		{return 0;}
			
	switch(eventType)
		{
		case 0xff:
			{
			event.type=m_reader.byteGet();
			if(m_reader.eoc())
				{return 0;}
			size_t length=m_reader.varfieldGet();
			if(m_reader.eoc())
				{return 0;}
		
			auto n=std::min(length,sizeof(event.data));
			auto n_read=m_reader.dataRead(&event.data,n);
			if(n_read!=n)
				{return 0;}
			length-=n_read;
			
			if(!m_reader.skip(length))
				{return 0;}
			
			if(event.type==0x51)
				{event.data.dwords[0]=__builtin_bswap32(event.data.dwords[0])>>8;}
			}
			break;
		case 0xf7:
		case 0xf0:
			{
			size_t length=m_reader.varfieldGet();
			if(length!=0 && m_reader.eoc())
				{return 0;}
			if(!m_reader.skip(length))
				{return 0;}
			printf("Sysex message skipped\n");
			}
			break;
		default:
			event.type=0;
			if(eventType&0x80)
				{
				event.data.bytes[0]=eventType;
				if(m_reader.eoc())
					{return 0;}
				}
			else
				{
				//Running mode
				event.data.bytes[0]=status_prev;
				}
			
			event.data.bytes[1]=m_reader.byteGet();
			if(m_reader.eoc())
				{return 0;}
			event.data.bytes[2]=m_reader.byteGet();
			status_prev=event.data.bytes[0];
			break;
		}
	return 1;
	}
