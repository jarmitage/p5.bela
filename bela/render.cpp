#include <Bela.h>
#include <string>
#include <WSServer.h>
#include <AuxTaskRT.h>
#include <JSON.h>

WSServer wss;
AuxTaskRT wssTask;

void wssOnConnect();
void wssOnDisconnect();
void wssOnReceive (const char* buf);
void wssSend();
void wssTaskRT();

float gSampleRate;
float gInverseSampleRate;
int gAudioPerAnalog;

int sendEvery = 1000; // millis
unsigned int sendEveryCount = 0;
std::string test = "test";

bool setup (BelaContext *context, void *userData)
{

  wss.setup (8888, "server", nullptr, nullptr, nullptr, true);

  wss.addAddress ("address",
    [] (std::string address, void* buf, int size) {
      wssOnReceive ((const char*) buf);
    },
    [] (std::string address) { wssOnConnect();    },
    [] (std::string address) { wssOnDisconnect(); }
  );

  wssTask.create ("wss-task", [] () { wssTaskRT(); });

  gSampleRate = context->audioSampleRate;
  gInverseSampleRate = 1.0f / context->audioSampleRate;
  gAudioPerAnalog = context->audioFrames / context->analogFrames;

  sendEvery *= context->audioSampleRate / 1000.0;

  return true;

}

void wssOnConnect() {

  rt_printf ("Connected\n");

  wss.send ("connected");

}

void wssOnDisconnect() {

  rt_printf ("Disconnected\n");

}

void wssTaskRT () {

  wss.send ("RT"); // send something in real-time

}

void wssOnReceive (const char* buf) {

  rt_printf ("Received data: %s\n", buf);

  // parse the data into a JSONValue
  // JSONValue *value = JSON::Parse(data);
  // if (value == NULL || !value->IsObject()){
  //   rt_printf ("could not parse JSON:\n%s\n", data);
  //   return;
  // }

  // // Look for a key
  // JSONObject root = value->AsObject();
  // if (root.find(L"event") != root.end() && root[L"event"]->IsString()){
  //   std::wstring event = root[L"event"]->AsString();
  //   if (event.compare(L"something-a") == 0){
  //     // do something with A
  //   } else if (event.compare(L"something-b") == 0){
  //     // do something with B
  //   }
  //   return;
  // }

}

void render (BelaContext *context, void *userData)
{
  for (unsigned int n = 0; n < context->audioFrames; ++n) {
    if (++sendEveryCount >= sendEvery) {
      wss.send ("address", test.c_str());
      rt_printf ("Sending test message\n");
      sendEveryCount = 0;
    }
  }

}

void cleanup (BelaContext *context, void *userData) {
  // TODO: Send a "Closing log" message to Jupyter?
}
