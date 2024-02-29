#include <dlfcn.h>
#include <iostream>

#include "PEngine/PicassoEngine.h"

int main(int argc, char **argv)
{
  void *handle = dlopen("PEngine/libPEngine.so", RTLD_LAZY);

  if (!handle)
  {
    std::cout << "[PRUNNER] Unable to open the dynamic library: " << dlerror() << "\n";
    return 1;
  }

  Picasso::PEngine *(*create)() = nullptr;
  void (*destroy)(Picasso::PEngine *) = nullptr;

  create = (Picasso::PEngine * (*)()) dlsym(handle, "create_object");

  if (!create)
  {
    std::cout << "[PRUNNER] Unable to find the 'create_object' symbol in the dynamic library.\n";
    dlclose(handle);
    return 1;
  }

  destroy = (void (*)(Picasso::PEngine *))dlsym(handle, "destroy_object");

  if (!destroy)
  {
    std::cout << "[PRUNNER] Unable to find the 'destroy_object' symbol in the dynamic library.\n";
    dlclose(handle);
    return 1;
  }

  Picasso::PEngine *picassoEngine = create();

  if (!picassoEngine)
  {
    std::cout << "[PRUNNER] Failed to create a Picasso::PEngine object.\n";
    dlclose(handle);
    return 1;
  }

  // engine config
  Picasso::Config::AppConfig config = {
      1,
      1,
      1920,
      1080,
      "Picasso Engine v 0.1"};

  // main loop
  picassoEngine->Run(&config);

  destroy(picassoEngine);

  dlclose(handle); // Chiudi la libreria dinamica quando hai finito

  return 0; // Ritorno con successo
}