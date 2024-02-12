#pragma once
#include <iostream>

//logs a message to the console
//   When this is written               Replaces with this
#define GL_LOG(cn, msg) std::cout << cn << " | " << msg << std::endl