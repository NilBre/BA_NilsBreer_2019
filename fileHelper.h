#ifndef fileHelper_h
#define fileHelper_h

#include "fullset.h"
#include "string.h"
#include "TTree.h"
#include "TH1F.h"

class fileHelper {

 public :
  static fullset * GetTree(std::string path);

};

#endif
