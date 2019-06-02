#ifndef LorentzVectorHelper_h
#define LorentzVectorHelper_h

#include "TLorentzVector.h"
#include "fullset.h"

using namespace std;

class LorentzVectorHelper {

 public :

  LorentzVectorHelper(fullset * tree) { fTree = tree; };
  ~LorentzVectorHelper() {};

  TLorentzVector getQuarkTLV(int pdgid);
  TLorentzVector getKaonShortTLV(int idx);
  TLorentzVector getKaonShortDaughter1TLV(int idx);
  TLorentzVector getKaonShortDaughter2TLV(int idx);

  TLorentzVector getLambdaDaughterP1TLV(int idx);
  TLorentzVector getLambdaDaughterP2TLV(int idx);
  TLorentzVector getLambdaDaughterPi1TLV(int idx);
  TLorentzVector getLambdaDaughterPi2TLV(int idx);

  TLorentzVector getGenJetTLV(int idx);
  TLorentzVector getJetTLV(int idx);
  TLorentzVector getTrackTLV(int idx, float masshypothesis);
  TLorentzVector getLambdaTLV(int idx); // kenne ich eigentlich nicht
  TLorentzVector getElectronTLV(int idx);
  TLorentzVector getParticleTLV(int idx);

  static const float kKaonMass;
  static const float kPionMass;
  // von mir: pdg 2018
  static const float kLambdaMass;
  static const float kElectronMass;
  static const float kProtonMass;
 private :

  TLorentzVector getTLV(float pt, float eta, float phi, float m);
  // damit kann man arbeiten

  const fullset * fTree;

};

#endif
