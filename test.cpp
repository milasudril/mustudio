#ifdef __WAND__
target[type[application]name[mustudio-test]platform[;GNU/Linux]]
#endif

#include "client.h"
#include "port_audio.h"
#include "port_midi.h"

#include <unistd.h>
#include <cstdio>
#include <cstring>

using namespace MuStudio;

class MuStudioTest:public Client
	{
	public:
		MuStudioTest():Client("MuStudioTest")
			,in_L(*this,"In/L",Port::PORT_IS_INPUT)
			,in_R(*this,"In/R",Port::PORT_IS_INPUT)
			,notes(*this,"MIDI IN",Port::PORT_IS_INPUT)
			,out_L(*this,"Out/L",Port::PORT_IS_OUTPUT)
			,out_R(*this,"Out/R",Port::PORT_IS_OUTPUT)
			{
			activate();
			}
		
		int onProcess(size_t n_frames)
			{
			PortAudio::sample_t* in_L_buff=in_L.bufferGet(n_frames);
			PortAudio::sample_t* in_R_buff=in_R.bufferGet(n_frames);
			PortAudio::sample_t* out_L_buff=out_L.bufferGet(n_frames);
			PortAudio::sample_t* out_R_buff=out_R.bufferGet(n_frames);
			
			memcpy(out_L_buff,in_L_buff,sizeof(PortAudio::sample_t)*n_frames);
			memcpy(out_R_buff,in_R_buff,sizeof(PortAudio::sample_t)*n_frames);
			
			PortMIDI::Event event;
			bool has_events=notes.eventFirstGet(event,n_frames);
			while(has_events)
				{
				printf("%x %x %x\n",event.data.byte_0,event.data.byte_1,event.data.byte_2);
				has_events=notes.eventNextGet(event);
				}
			
			return 0;
			}
		
		~MuStudioTest()
			{
			deactivate();
			}
		
	private:
		PortAudio in_L;
		PortAudio in_R;
		PortMIDI notes;
		
		PortAudio out_L;
		PortAudio out_R;
	};
	
void errlog(const char* message)
	{fprintf(stderr,"%s\n",message);}
	

int main()
	{
	Client::setErrorHandler(errlog);
	MuStudioTest foo;
	while(1)
		{sleep(1);}
	return 0;
	}