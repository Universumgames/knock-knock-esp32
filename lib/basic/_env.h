#pragma once

#ifdef ENVIRONMENT_DEVICE_ESP
#define ENV_IS_ESP32 1
#define ENV_IS_NATIVE 0
#elif ENVIRONMENT_DEVICE_NATIVE
#define ENV_IS_ESP32 0
#define ENV_IS_NATIVE 1
#endif