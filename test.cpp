#ifdef __WAND__
target[type[application]name[mustudio-test]platform[;GNU/Linux]]
#endif

#include "client.h"
#include "audio_input_exported.h"
#include "midi_input_exported.h"
#include "audio_output_exported.h"

#include <unistd.h>
#include <cstdio>
#include <cstring>

using namespace MuStudio;

class MuStudioTest:public Client
	{
	public:
		MuStudioTest():Client("MuStudioTest")
			,in_L(*this,"In/L")
			,in_R(*this,"In/R")
			,notes(*this,"MIDI IN")
			,out_L(*this,"Out/L")
			,out_R(*this,"Out/R")
			{
			activate();
			}
		
		int onProcess(size_t n_frames)
			{
			auto* in_L_buff=in_L.bufferGet(n_frames);
			auto* in_R_buff=in_R.bufferGet(n_frames);
			
			auto* out_L_buff=out_L.bufferGet(n_frames);
			auto* out_R_buff=out_R.bufferGet(n_frames);
			
			memcpy(out_L_buff,in_L_buff,sizeof(Audio::sample_t)*n_frames);
			memcpy(out_R_buff,in_R_buff,sizeof(Audio::sample_t)*n_frames);
			
			MIDI::Event event;
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
		Audio::InputExported in_L;
		Audio::InputExported in_R;
		MIDI::InputExported notes;
		
		Audio::OutputExported out_L;
		Audio::OutputExported out_R;
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