#include "LorentzVectorHelper.h"
#include <iostream>

using namespace std;

const float LorentzVectorHelper::kKaonMass = 0.467611; // PDG 2018 [GeV]
const float LorentzVectorHelper::kPionMass = 0.13957061; // PDG 2018 [GeV]
const float LorentzVectorHelper::kLambdaMass = 1.115683; // PDG 2018 [GeV]
const float LorentzVectorHelper::kElectronMass = 0.510998928; // PDG 2018 [GeV]
const float LorentzVectorHelper::kProtonMass = 0.9382720813; // PDG 2018 [GeV]

TLorentzVector LorentzVectorHelper::getQuarkTLV(int pdgid) {
  int quark_idx(-1);
  for (unsigned int iParticle(0), nParticles(fTree->Particle_size); iParticle < nParticles; ++iParticle) {
    if ((*fTree->Particle_PID)[iParticle] == pdgid) {
      if (quark_idx != -1)
        cout << "ERROR in TLorentzVector::getQuarkTLV : should not have found more than one quark with pdg id = " << pdgid << endl;
      quark_idx = iParticle;
    }
  }
  if (quark_idx == -1)
    cout << "ERROR in TLorentzVector::getQuarkTLV : should have found a quark with pdg id = " << pdgid << endl;
  return getTLV((*fTree->Particle_PT)[quark_idx],
                (*fTree->Particle_Eta)[quark_idx],
                (*fTree->Particle_Phi)[quark_idx],
                (*fTree->Particle_Mass)[quark_idx]);
}

TLorentzVector LorentzVectorHelper::getKaonShortTLV(int idx) {
  return getTLV((*fTree->KaonShort_PT)[idx],
                (*fTree->KaonShort_Eta)[idx],
                (*fTree->KaonShort_Phi)[idx],
                kKaonMass);
}

TLorentzVector LorentzVectorHelper::getKaonShortDaughter1TLV(int idx) {
  return getTLV((*fTree->KaonShortDaughter1_PT)[idx],
                (*fTree->KaonShortDaughter1_Eta)[idx],
                (*fTree->KaonShortDaughter1_Phi)[idx],
                kPionMass);
}

TLorentzVector LorentzVectorHelper::getKaonShortDaughter2TLV(int idx) {
  return getTLV((*fTree->KaonShortDaughter2_PT)[idx],
                (*fTree->KaonShortDaughter2_Eta)[idx],
                (*fTree->KaonShortDaughter2_Phi)[idx],
                kPionMass);
}
//--------------
TLorentzVector LorentzVectorHelper::getLambdaDaughterP1TLV(int idx){
    return getTLV((*fTree->LambdaDaughter1_PT)[idx],
                  (*fTree->LambdaDaughter1_Eta)[idx],
                  (*fTree->LambdaDaughter1_Phi)[idx],
                  kProtonMass);
}

TLorentzVector LorentzVectorHelper::getLambdaDaughterP2TLV(int idx){
    return getTLV((*fTree->LambdaDaughter2_PT)[idx],
                  (*fTree->LambdaDaughter2_Eta)[idx],
                  (*fTree->LambdaDaughter2_Phi)[idx],
                  kProtonMass);
}

TLorentzVector LorentzVectorHelper::getLambdaDaughterPi1TLV(int idx){
    return getTLV((*fTree->LambdaDaughter1_PT)[idx],
                  (*fTree->LambdaDaughter1_Eta)[idx],
                  (*fTree->LambdaDaughter1_Phi)[idx],
                  kPionMass);
}

TLorentzVector LorentzVectorHelper::getLambdaDaughterPi2TLV(int idx){
    return getTLV((*fTree->LambdaDaughter2_PT)[idx],
                  (*fTree->LambdaDaughter2_Eta)[idx],
                  (*fTree->LambdaDaughter2_Phi)[idx],
                  kPionMass);
}
//---------
TLorentzVector LorentzVectorHelper::getGenJetTLV(int idx) {
  return getTLV((*fTree->GenJet_PT)[idx],
                (*fTree->GenJet_Eta)[idx],
                (*fTree->GenJet_Phi)[idx],
                (*fTree->GenJet_Mass)[idx]);
}

TLorentzVector LorentzVectorHelper::getJetTLV(int idx) {
  return getTLV((*fTree->Jet_PT)[idx],
                (*fTree->Jet_Eta)[idx],
                (*fTree->Jet_Phi)[idx],
                (*fTree->Jet_Mass)[idx]);
}

// fuege hier eine zeile hinzu: (*fTree->Track_Charge)[idx],
TLorentzVector LorentzVectorHelper::getTrackTLV(int idx, float masshypothesis) {
  return getTLV((*fTree->Track_PT)[idx],
                (*fTree->Track_Eta)[idx],
                (*fTree->Track_Phi)[idx],
                masshypothesis);
}

// das kenne ich ja garnicht eigentlich ...
TLorentzVector LorentzVectorHelper::getLambdaTLV(int idx) {
  return getTLV((*fTree->Lambda_PT)[idx],
                (*fTree->Lambda_Eta)[idx],
                (*fTree->Lambda_Phi)[idx],
                kLambdaMass);
}


TLorentzVector LorentzVectorHelper::getElectronTLV(int idx) {
  return getTLV((*fTree->Electron_PT)[idx],
                (*fTree->Electron_Eta)[idx],
                (*fTree->Electron_Phi)[idx],
                kElectronMass);
}

TLorentzVector LorentzVectorHelper::getParticleTLV(int idx){
    return getTLV((*fTree->Particle_PT)[idx],
                  (*fTree->Particle_Eta)[idx],
                  (*fTree->Particle_Phi)[idx],
                  kLambdaMass);
}
TLorentzVector LorentzVectorHelper::getTLV(float pt, float eta, float phi, float m) {
  TLorentzVector v;
  v.SetPtEtaPhiM(pt, eta, phi, m);
  return v;
}
