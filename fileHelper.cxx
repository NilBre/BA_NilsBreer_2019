#include "fileHelper.h"
#include "TSystem.h"
#include <iostream>
#include "TFile.h"

using namespace std;

fullset * fileHelper::GetTree(string path) {
  TChain * chain = new TChain("fullset");
  Long_t tmp_a, tmp_b, tmp_c, tmp_d;
  if (gSystem->GetPathInfo(path.data(), &tmp_a, &tmp_b, &tmp_c, &tmp_d) != 0) {
    cout << "ERROR no file present in path " << path << endl;
    return 0;
  }
  chain->AddFile(path.data());
  return new fullset(chain);
}

