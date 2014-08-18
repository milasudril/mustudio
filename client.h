#ifdef __WAND__
dependency[client.o]
target[name[client.h]type[include]]
#endif

#ifndef MUSTUDIO_CLIENT_H
#define MUSTUDIO_CLIENT_H

#include <cstddef>

namespace MuStudio
	{
	namespace MIDI
		{
		class InputExported;
		class OutputExported;
		}

	namespace Audio
		{
		class InputExported;
		class OutputExported;
		}

	class Client
		{
		friend class Audio::InputExported;
		friend class Audio::OutputExported;
		friend class MIDI::OutputExported;
		friend class MIDI::InputExported;

		public:
			static void setErrorHandler(void(*error_handler)(const char *));

			Client(const char* name_client);
			virtual ~Client();

			virtual int onProcess(size_t nframes)=0;
			virtual int onSampleRateChanged(size_t fs_new);
			virtual int onServerShutdown();

			void activate();
			void deactivate();
			size_t sampleRateGet();

		private:
			void* connection;
		};
	}

#endif
