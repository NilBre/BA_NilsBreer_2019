#include "fullset.h"
#include <iostream>
#include <string>
#include "TString.h"
#include <cmath>
#include "fileHelper.h"
#include "histoHelper.h"
#include "LorentzVectorHelper.h"
#include "TLorentzVector.h"
#include <map>
#include <set>
#include "TSystem.h"
#include "THStack.h"
#include <algorithm>
#include <fstream>

using namespace std;

bool sortfunction(pair<int,float> v1, pair<int,float> v2) {
  return (v1.second > v2.second); // descending order
}

int runKaonRecoEtc(string path, int pdgid, ofstream &ifile1, ofstream &ifile2) {

  gSystem->Load("AutoDict_vector_vector_float____cxx.so");

  float pdg_BR_lambda = 69.20;
  float pdg_BR_kaon = 63.9;

  // minimum jet requirements
  float minJetPt = 20.;
  float maxJetEta = 2.5;
  // radius for geometrical matching
  float jetDR = 0.5;
  // minimum track pT (used for tracks (and on truth level for pions))
  float minTrackPt = 0.1; // [GeV]
  float minTrackPT_lambda = 0.5;
  float maxTrackEta = 20;

 //  float minTrackPt_Lambda = 0.5; // [GeV]

  //  the parameters below are only needed if the aim is to reconstruct kaons
  float minTransVertDist = 4; // [mm] - inspired by ATLAS K_S and Lambda study in ttbar
  float maxTransVertDist = 450; // [mm] - inspired by ATLAS K_S and Lambda study in ttbar
  float minKaonMass = 0.0; // [GeV] - should rather be 0.4?
  float maxKaonMass = 1.0; // [GeV] - should rather be 0.6?
  float minLambdaMass = 0.9;
  float maxLambdaMass = 1.3;
  // static const int pdgLambda = 1.115683;

  // Retrieve the tree from the file
  fullset * tree = fileHelper::GetTree(path);
  if (tree == 0) {
    cout << "ERROR tree is null pointer" << endl;
    return 1;
  }

  // check that the tree is not empty
  int nEntries = tree->GetEntries();
  cout << "INFO tree contains " << nEntries << " events" << endl;
  if (nEntries == 0) {
    cout << "ERROR tree contains zero events" << endl;
    return 1;
  }
  // create a Lorentz-vector helper
  LorentzVectorHelper * lvhelp = new LorentzVectorHelper(tree);

  // create a histogram helper
  histoHelper * histohelp = new histoHelper(pdgid);

  // now loop over the events in the tree
  float counterToPi = 0; // countet nur zerfaelle in pi+pi-
  float counterToOther = 0; // zaehlt alle decays in was anderes als pi+pi-
  float KaonTotalDecay = 0; // gesamtzahl an zerfaellen
  float counterToLambda = 0; // nur zerfaelle in lambdas
  float countToOtherLambda = 0; // nur zerfaelle in was anderes als lambdas
  float LambdaTotalDecay = 0; // gesamtzahl an zerfaellen
  float counter_true = 0; // countet tracks, die als true reconstruiert werden
  float counter_fake = 0; // countet tracks, die als fake reconstruiert werden
  // fuer ROC kurve
  // float leftArea = 0;
  // float rightArea = 0;
  // float tp = 0;
  // float fp = 0;
  // float tn = 0;
  // float fn = 0;

  for (int iEntry(0); iEntry < nEntries; ++iEntry)
  {

    // get entry no. iEntry and tell every 10000th event
    tree->GetEntry(iEntry);
    // if ((iEntry+1)%10000 == 0) {
    //   cout << "INFO processing the " << iEntry+1 << "th event" << endl;
    // }
    // // // // // // // // // // // // // // // // // // // //

    // loop over all truth jets to find leading jet in pT
    int idx_leadingGenJet(-1);
    float max_GenJetPt(-1.);
    if (tree->GenJet_size == 0){
        continue;
    }
    for (unsigned int iGenJet(0), nGenJets(tree->GenJet_size); iGenJet < nGenJets; ++iGenJet)
    {
      // build Lorentz vector for truth jet
      // cout << "idx = " << idx_leadingGenJet << ", iGenJet = " << iGenJet << endl;
      float thisJetPt = lvhelp->getGenJetTLV(iGenJet).Pt();
      if (idx_leadingGenJet < 0 || thisJetPt > max_GenJetPt) {
        idx_leadingGenJet = iGenJet;
        max_GenJetPt = thisJetPt;
      }
    }

    // from here only work with leading jet in pT
    TLorentzVector vGenJet = lvhelp->getGenJetTLV(idx_leadingGenJet);

    // reject truth jets with pT < minJetPt
    histohelp->GetTH1D(histoHelper::hashTruthJetPt_before_sel)->Fill(vGenJet.Pt()); // save a histogram of the truth jet pT before selection
    if (vGenJet.Pt() < minJetPt)
      continue;

    // reject truth jets with |eta| > maxJetEta
    histohelp->GetTH1D(histoHelper::hashTruthJetEta_before_sel)->Fill(vGenJet.Eta()); // save a histogram of the truth jet eta before selection
    if (fabs(vGenJet.Eta()) > maxJetEta)
      continue;

    // reject truth jets that are not matched to either a truth quark of type pdgid or a truth anti-quark (of type -pdgid)
    TLorentzVector vQuark = lvhelp->getQuarkTLV(pdgid);
    TLorentzVector vAntiQuark = lvhelp->getQuarkTLV(-pdgid);
    float deltaR_min_quarks = min(vGenJet.DeltaR(vQuark), vGenJet.DeltaR(vAntiQuark));
    histohelp->GetTH1D(histoHelper::hashQuarkDeltaR_to_leadingTruthJet)->Fill(deltaR_min_quarks);
    if (deltaR_min_quarks > jetDR)
      histohelp->GetTH1D(histoHelper::hashQuarkWithinLeadingTruthJet)->Fill(false);
    else
      histohelp->GetTH1D(histoHelper::hashQuarkWithinLeadingTruthJet)->Fill(true);
    // pdg seite 157
    // lambda -> p + pi-
    // anders als K0(short) wo 2 pionen im endzustand sind ~69% + ~30%
    // this is for TRUTH-LEVEL
    // -----------------------------------
    float nLambdasInTruth(0);
    float countOtherLamb(0);
    for (unsigned int iLambda(0), nLambdas(tree->Lambda_size); iLambda < nLambdas; iLambda++)
    {
    // cout << (*tree->LambdaDaughter1_PID)[iLambda] << " " << (*tree->LambdaDaughter2_PID)[iLambda] << endl;
      TLorentzVector vLambda = lvhelp->getLambdaTLV(iLambda);
      if (vGenJet.DeltaR(vLambda) > jetDR) { // ereignisse ausserhalb des cones
          continue;
      }
      if ((*tree->LambdaDaughter1_PID)[iLambda] != 2212 &&
          (*tree->LambdaDaughter2_PID)[iLambda] != 211)
          {
              countOtherLamb++;
              countToOtherLambda += countOtherLamb;
              continue;
          }
          nLambdasInTruth++;
          counterToLambda += nLambdasInTruth;
      // if (((*tree->LambdaDaughter1_PID)[iLambda] == 2212 && (*tree->LambdaDaughter2_PID)[iLambda] == -211)
      // || ((*tree->LambdaDaughter1_PID)[iLambda] == -211 && (*tree->LambdaDaughter2_PID)[iLambda] == 2212)){
      //     nLambdasInTruth++;
      //     counterToLambda += nLambdasInTruth;
      // }
      // else{
      //     countOtherLamb++;
      //     countToOtherLambda += countOtherLamb;
      //     continue;
      // }

      // TLorentzVector vLDaughterP1 = lvhelp->getLambdaDaughterP1TLV(iLambda); // in TLorentzVectoren sind jeweils immer Pt, eta, phi, evtl mass gespeichert
      // TLorentzVector vLDaughterP2 = lvhelp->getLambdaDaughterP2TLV(iLambda);
      // TLorentzVector vLDaughterPi1 = lvhelp->getLambdaDaughterPi1TLV(iLambda); // in TLorentzVectoren sind jeweils immer Pt, eta, phi, evtl mass gespeichert
      // TLorentzVector vLDaughterPi2 = lvhelp->getLambdaDaughterPi2TLV(iLambda);
  }
  histohelp->GetTH1D(histoHelper::hashTruthNlambdas)->Fill(nLambdasInTruth);
      // -----------------------------------

    // find all K_S that point to the truth jet (radius parameter R = jetDR) and decay to pi+ pi-
    // and track whether the decay products also point to the truth jet
    vector<float> kaonX(0);
    vector<float> kaonDR(0);
    float nKaonsBeforeDaughtersPointing(0);
    float countAll(0);
    // initialisiere iKaon mit 0, initialisiere nKaon mit der size (setze n Kaon auf das ende)
    for (unsigned int iKaon(0), nKaons(tree->KaonShort_size); iKaon < nKaons; ++iKaon)
    {
      TLorentzVector vKaon = lvhelp->getKaonShortTLV(iKaon);
      if (vGenJet.DeltaR(vKaon) > jetDR)
      {
        continue;
      }
      // 211 ist die particle data group ID (pdgid) von geladenen pionen
      // teste ob zerfall in pi+pi-
      if ((*tree->KaonShortDaughter1_PID)[iKaon] != 211 &&
          (*tree->KaonShortDaughter2_PID)[iKaon] != 211)
          {
              countAll++;
              counterToOther += countAll;
              continue;
          }
      // countAll++;
      nKaonsBeforeDaughtersPointing++;
      counterToPi += nKaonsBeforeDaughtersPointing;

      // now also check if the two daughters point to the truth jet, too
      // and check that their pT is > minTrackPt and |eta| < maxTrackEta
      TLorentzVector vDaughter1 = lvhelp->getKaonShortDaughter1TLV(iKaon); // in TLorentzVectoren sind jeweils immer Pt, eta, phi, evtl mass gespeichert
      TLorentzVector vDaughter2 = lvhelp->getKaonShortDaughter2TLV(iKaon);

      if (vGenJet.DeltaR(vDaughter1) > jetDR || vGenJet.DeltaR(vDaughter2) > jetDR)
        continue;
      histohelp->GetTH1D(histoHelper::hashTruthPionPt_before_sel)->Fill(vDaughter1.Pt()); // save the pion pT before selection
      histohelp->GetTH1D(histoHelper::hashTruthPionPt_before_sel)->Fill(vDaughter2.Pt()); // save the pion pT before selection
      if (vDaughter1.Pt() < minTrackPt || vDaughter2.Pt() < minTrackPt)
        continue;
      histohelp->GetTH1D(histoHelper::hashTruthPionEta_before_sel)->Fill(vDaughter1.Eta()); // save the pion eta before selection
      histohelp->GetTH1D(histoHelper::hashTruthPionEta_before_sel)->Fill(vDaughter2.Eta()); // save the pion eta before selection
      if (fabs(vDaughter1.Eta()) > maxTrackEta || fabs(vDaughter2.Eta()) > maxTrackEta)
        continue;

      kaonX.push_back(vKaon.Pt() / vGenJet.Pt());
      kaonDR.push_back(vKaon.DeltaR(vGenJet));
      histohelp->GetTH1D(histoHelper::hashTruthPionPt)->Fill(vDaughter1.Pt());
      histohelp->GetTH1D(histoHelper::hashTruthPionPt)->Fill(vDaughter2.Pt());
      histohelp->GetTH1D(histoHelper::hashTruthPionEta)->Fill(vDaughter1.Eta());
      histohelp->GetTH1D(histoHelper::hashTruthPionEta)->Fill(vDaughter2.Eta());
      histohelp->GetTH1D(histoHelper::hashTruthPionDeltaR_to_jet)->Fill(vDaughter1.DeltaR(vGenJet));
      histohelp->GetTH1D(histoHelper::hashTruthPionDeltaR_to_jet)->Fill(vDaughter2.DeltaR(vGenJet));
      histohelp->GetTH1D(histoHelper::hashTruthKaonPt_over_jetPt)->Fill(kaonX.back());
      histohelp->GetTH1D(histoHelper::hashTruthKaonDeltaR_to_jet)->Fill(kaonDR.back());
      histohelp->GetTH1D(histoHelper::hashTruthKaonInvMass)->Fill(vKaon.M()*1000);
    }

    histohelp->GetTH1D(histoHelper::hashTruthNOtherKaons)->Fill(countAll);
    histohelp->GetTH1D(histoHelper::hashTruthNKaons)->Fill(nKaonsBeforeDaughtersPointing);
    histohelp->GetTH1D(histoHelper::hashTruthNKaonsWithDaughters)->Fill(kaonX.size());
    histohelp->GetTH1D(histoHelper::hashTruthJetPt)->Fill(vGenJet.Pt());
    histohelp->GetTH1D(histoHelper::hashTruthJetEta)->Fill(vGenJet.Eta());

    // // // // // // // // // // // // // // // // ///
    // loop over all jets to find leading jet in pT
    int idx_leadingJet(-1);
    float max_JetPt(-1.);
    for (unsigned int iJet(0), nJets(tree->Jet_size); iJet < nJets; ++iJet)
    {
      // build Lorentz vector for jet
      float thisJetPt = lvhelp->getJetTLV(iJet).Pt();
      if (idx_leadingJet < 0 || thisJetPt > max_JetPt) {
        idx_leadingJet = iJet;
        max_JetPt = thisJetPt;
      }
    }
    // from here only work with leading jet in pT
    TLorentzVector vJet = lvhelp->getJetTLV(idx_leadingJet);

    // reject jets with pT < minJetPt
    histohelp->GetTH1D(histoHelper::hashJetPt_before_sel)->Fill(vJet.Pt()); // save a histogram of the jet pT before selection
    if (vJet.Pt() < minJetPt)
      continue;

    // reject jets with |eta| > maxJetEta
    histohelp->GetTH1D(histoHelper::hashJetEta_before_sel)->Fill(vJet.Eta()); // save a histogram of the jet eta before selection
    if (fabs(vJet.Eta()) > maxJetEta)
      continue;

    // reject jets that are not matched to either a truth quark of type pdgid or a truth anti-quark
    deltaR_min_quarks = min(vJet.DeltaR(vQuark), vJet.DeltaR(vAntiQuark));
    histohelp->GetTH1D(histoHelper::hashQuarkDeltaR_to_leadingJet)->Fill(deltaR_min_quarks);
    if (deltaR_min_quarks > jetDR)
      histohelp->GetTH1D(histoHelper::hashQuarkWithinLeadingJet)->Fill(false);
    else
      histohelp->GetTH1D(histoHelper::hashQuarkWithinLeadingJet)->Fill(true);

    // find all tracks that point to the jet (radius parameter R = jetDR)
    // and have a minimum pT of minTrackPt and |eta| < maxTrackEta
    // and have a vertex (X,Y,Z) position that is incompatible with the PV
    vector<int> trackCandIdx(0);
    vector<float> trackPt(0);
    vector<float> trackDEta(0);
    vector<float> trackDPhi(0);
    vector<float> trackX(0);
    vector<float> trackD0(0);
    vector<float> trackDZ(0);
    vector<float> trackVtxDistX(0);
    vector<float> trackVtxDistY(0);

    // order tracks in pT
    // diese funktion aendere ich kurz so, dass sie fuer meine lambdas funktioniert
    // kPionMass -> kLambdaMass
    // minTrackPt solange rausnehmen
    vector<pair<int,float> > track_pt_idx(0);
    for (unsigned int iTrack(0), nTracks(tree->Track_size); iTrack < nTracks; ++iTrack)
    {
      TLorentzVector vTrack = lvhelp->getTrackTLV(iTrack, LorentzVectorHelper::kLambdaMass);
      track_pt_idx.push_back(pair<int,float>(iTrack,vTrack.Pt()));
    }
    sort(track_pt_idx.begin(), track_pt_idx.end(), sortfunction);
    // then loop over tracks in that order
    for (unsigned int i_idx(0), n_idx(track_pt_idx.size()); i_idx < n_idx; ++i_idx)
    {
      unsigned int iTrack = track_pt_idx[i_idx].first;
      TLorentzVector vTrack = lvhelp->getTrackTLV(iTrack, LorentzVectorHelper::kLambdaMass);

      if (vJet.DeltaR(vTrack) > jetDR)
        continue;

      histohelp->GetTH1D(histoHelper::hashTrackPt_before_sel)->Fill(vTrack.Pt());
      if (vTrack.Pt() < minTrackPT_lambda)
        continue;

      histohelp->GetTH1D(histoHelper::hashTrackEta_before_sel)->Fill(vTrack.Eta());
      if (fabs(vTrack.Eta()) > maxTrackEta)
        continue;

      float vertexX = (*tree->Track_X)[iTrack];
      float vertexY = (*tree->Track_Y)[iTrack];
      float transVertexDistance = sqrt(vertexX*vertexX + vertexY*vertexY);
      histohelp->GetTH1D(histoHelper::hashTrackTransVertDist_before_sel)->Fill(transVertexDistance);
      if (transVertexDistance < minTransVertDist || transVertexDistance > maxTransVertDist)
        continue;

      trackCandIdx.push_back(iTrack);

      trackPt.push_back(vTrack.Pt());
      trackDEta.push_back(vTrack.Eta()-vJet.Eta());
      trackDPhi.push_back(vTrack.DeltaPhi(vJet));
      trackX.push_back(vTrack.Pt() / vJet.Pt());
      trackD0.push_back((*tree->Track_D0)[iTrack]);
      trackDZ.push_back((*tree->Track_DZ)[iTrack]);
      trackVtxDistX.push_back((*tree->Track_X)[iTrack]);
      trackVtxDistY.push_back((*tree->Track_Y)[iTrack]);
    }

    // only fill histograms now
    histohelp->GetTH1D(histoHelper::hashTrackN)->Fill(trackCandIdx.size());
    for (unsigned int i_idx(0), n_idx(track_pt_idx.size()); i_idx < n_idx; ++i_idx)
    {
      unsigned int iTrack = track_pt_idx[i_idx].first;
      TLorentzVector vTrack = lvhelp->getTrackTLV(iTrack, LorentzVectorHelper::kLambdaMass);

      float vertexX = (*tree->Track_X)[iTrack];
      float vertexY = (*tree->Track_Y)[iTrack];
      float transVertexDistance = sqrt(vertexX*vertexX + vertexY*vertexY);

      histohelp->GetTH1D(histoHelper::hashTrackPt)->Fill(vTrack.Pt());
      histohelp->GetTH1D(histoHelper::hashTrackEta)->Fill(vTrack.Eta());
      histohelp->GetTH1D(histoHelper::hashTrackTransVertDist)->Fill(transVertexDistance);
      histohelp->GetTH1D(histoHelper::hashTrackVertDistX)->Fill((*tree->Track_X)[iTrack]);
      histohelp->GetTH1D(histoHelper::hashTrackVertDistY)->Fill((*tree->Track_Y)[iTrack]);
      histohelp->GetTH1D(histoHelper::hashTrackD0)->Fill((*tree->Track_D0)[iTrack]);
      histohelp->GetTH1D(histoHelper::hashTrackDZ)->Fill((*tree->Track_DZ)[iTrack]);
      histohelp->GetTH1D(histoHelper::hashTrackDEta)->Fill(vTrack.Eta()-vJet.Eta());
      histohelp->GetTH1D(histoHelper::hashTrackDPhi)->Fill(vTrack.DeltaPhi(vJet));
      histohelp->GetTH1D(histoHelper::hashTrackX)->Fill(vTrack.Pt() / vJet.Pt());
    }

    // loop over tracks to find track pairs
    vector<pair<int,int>> trackPairs(0);
    for (unsigned int iTrack1(0), nTracks1(trackCandIdx.size()); iTrack1 < nTracks1; ++iTrack1)
    {
      float vertexX1 = (*tree->Track_X)[trackCandIdx[iTrack1]];
      float vertexY1 = (*tree->Track_Y)[trackCandIdx[iTrack1]];

      // find second track with the same vertex (vertices are not smeared in Delphes)
      for (unsigned int iTrack2(iTrack1+1), nTracks2(trackCandIdx.size()); iTrack2 < nTracks2; ++iTrack2)
      {
        float vertexX2 = (*tree->Track_X)[trackCandIdx[iTrack2]];
        float vertexY2 = (*tree->Track_Y)[trackCandIdx[iTrack2]];
        float epsilon = 1.e-9; // avoid float == float comparisons
        if (fabs(vertexX1 - vertexX2) < epsilon && fabs(vertexY1 - vertexY2) < epsilon) {
            trackPairs.push_back(pair<int,int>(trackCandIdx[iTrack1],trackCandIdx[iTrack2]));
        }
      }
    }
    // der vector trackPairs beinhaltet NUR paare von tracks, die zu einem gemeinsamen vertex zeigen!

    // -------------------------
    // KaonInvMass, PT, Xk and deltaR for reconstructed kaons
    vector<int> KaonKandidat(0);
    for (unsigned int iTrackPair(0), nTrackPairs(trackPairs.size()); iTrackPair < nTrackPairs; ++iTrackPair)
    {

        TLorentzVector visKaonJetPT = lvhelp->getJetTLV(idx_leadingJet);
        TLorentzVector vTrack1 = lvhelp->getTrackTLV(trackPairs[iTrackPair].first, LorentzVectorHelper::kPionMass);
        TLorentzVector vTrack2 = lvhelp->getTrackTLV(trackPairs[iTrackPair].second, LorentzVectorHelper::kPionMass);
        TLorentzVector isKaonKand = vTrack1 + vTrack2;

        float InvariantKaonMass = isKaonKand.M(); // invariant kaon mass

        float deltaR = isKaonKand.DeltaR(visKaonJetPT);
        if (deltaR > jetDR){
            continue;
        }
        histohelp->GetTH1D(histoHelper::hashKaonDeltaR)->Fill(deltaR);
        histohelp->GetTH1D(histoHelper::hashJetPTforKaon)->Fill(visKaonJetPT.Pt()); // tarnsverse momentum of kaonjet
        histohelp->GetTH1D(histoHelper::hashKaonInvMass)->Fill(InvariantKaonMass*1000); // inv. mass
        histohelp->GetTH1D(histoHelper::hashKaonPT)->Fill(isKaonKand.Pt());  // kaonPT
        histohelp->GetTH1D(histoHelper::hashKaonXk)->Fill(isKaonKand.Pt() / visKaonJetPT.Pt()); // kaon xk
        if (InvariantKaonMass < minKaonMass || InvariantKaonMass > maxKaonMass){
            continue;
        }
        KaonKandidat.push_back(iTrackPair);
    }
    // ------------------------------------------
    // LAMBDA RECONSTRUCTION ALGORITHM
    vector<int> LambdaCand(0);
    for (unsigned int iTrackPair(0), nTrackPairs(trackPairs.size()); iTrackPair < nTrackPairs; ++iTrackPair)
    {
        float T_Charge = (*tree->Track_Charge)[trackPairs[iTrackPair].first] * (*tree->Track_Charge)[trackPairs[iTrackPair].second];
        histohelp->GetTH1D(histoHelper::hashCharge)->Fill(T_Charge);
        if (T_Charge > 0){
            continue;
        }
        for (int i = 0, nTrackPairs(trackPairs.size()); i < nTrackPairs; i++)
        {
            TLorentzVector vLambda_Ref = lvhelp->getLambdaTLV(i); // lambda referenz
            TLorentzVector vIsLambdaJet = lvhelp->getJetTLV(idx_leadingJet);
            if (vJet.DeltaR(vLambda_Ref) < 0.5) // cut auf deltaR = 0.5: alles kleiner sind true lambdas, alles > 0.5 sind fakes
            { // true teilchen, wenn dR < 0.5
                TLorentzVector vTrack1 = lvhelp->getTrackTLV(trackPairs[iTrackPair].first, LorentzVectorHelper::kProtonMass);
                TLorentzVector vTrack2 = lvhelp->getTrackTLV(trackPairs[iTrackPair].second, LorentzVectorHelper::kPionMass);
                if (vTrack1.DeltaR(vJet) > 0.5 || vTrack2.DeltaR(vJet) > 0.5)
                {
                    continue;
                }
                TLorentzVector LambdaCandidate_A = vTrack1 + vTrack2;
                float dR_A3 = LambdaCandidate_A.DeltaR(vIsLambdaJet); // deltaR zwischen candidate und jet -> muesste eigentlich mit vIsLambdaJet verglichen werden...
                float LInvMass_p_pi = LambdaCandidate_A.M(); // invariante masse von T1 und T2, also dem candidate
                if (LambdaCandidate_A.Pt() < 0.5){ // minimum candidate Pt von 500 MeV
                    continue;
                }
                // bestimme die PIDs der spuren
                float TrackPID1 = (*tree->Track_PID)[trackPairs[iTrackPair].first];  // pids beider spuren
                float TrackPID2 = (*tree->Track_PID)[trackPairs[iTrackPair].second];
                // wirft alle pi+pi- paare raus->in die fakes
                if ((TrackPID1 == 211 && TrackPID2 == -211) || (TrackPID1 == -211 && TrackPID2 == 211)) // wirf alle uebrigen kaon candidates raus
                {
                    histohelp->GetTH1D(histoHelper::hashLInvMass_fake_p_pi)->Fill(LInvMass_p_pi*1000);
                    counter_fake += 1;
                    continue;
                }
                else
                {
                    float LambdaPtA = LambdaCandidate_A.Pt();
                    float JetPtA = vIsLambdaJet.Pt();
                    float X_Lambda = LambdaPtA / JetPtA;
                    // vertexpositionen x, y:
                    float Vx1 = (*tree->Track_X)[trackPairs[iTrackPair].first];
                    float Vy1 = (*tree->Track_Y)[trackPairs[iTrackPair].second];
                    float d1 = sqrt(Vx1*Vx1 + Vy1*Vy1);
                    // histohelp->GetTH1D(histoHelper::hashDeltaR_A)->Fill(dR_A1);
                    histohelp->GetTH1D(histoHelper::hashDeltaR_A3)->Fill(dR_A3);
                    histohelp->GetTH1D(histoHelper::hashabsvertex1)->Fill(d1);
                    histohelp->GetTH1D(histoHelper::hashLInvMass_true_p_pi)->Fill(LInvMass_p_pi*1000); // fill histogram with invariant mass for that candidate
                    histohelp->GetTH1D(histoHelper::hashPTLambda_A)->Fill(LambdaPtA);
                    histohelp->GetTH1D(histoHelper::hashXLambda)->Fill(X_Lambda);

                    if (pdgid == 3){
                        ifile1 << LInvMass_p_pi << endl;
                    }
                    if (pdgid == 1){
                        ifile1 << LInvMass_p_pi << endl;
                    }
                    if (pdgid == 2){
                        ifile1 << LInvMass_p_pi << endl;
                    }
                    counter_true += 1;
                }
                // schauen ob sie auch die korrekte masse haben
                if (LInvMass_p_pi < minLambdaMass || LInvMass_p_pi > maxLambdaMass)
                {
                    continue;
                }
            }
            else // wenn deltaR > 0.5 -> fake teilchen
            {
                TLorentzVector vTrack1 = lvhelp->getTrackTLV(trackPairs[iTrackPair].first, LorentzVectorHelper::kProtonMass);
                TLorentzVector vTrack2 = lvhelp->getTrackTLV(trackPairs[iTrackPair].second, LorentzVectorHelper::kPionMass);
                TLorentzVector LambdaCandidate_A = vTrack1 + vTrack2;
                float LInvMass_p_pi = LambdaCandidate_A.M();
                float dR_A3 = LambdaCandidate_A.DeltaR(vIsLambdaJet);
                float LambdaPtA = LambdaCandidate_A.Pt();
                float JetPtA = vIsLambdaJet.Pt();
                float X_Lambda = LambdaPtA / JetPtA;
                // fill histogram with invariant mass for this same candidate but result in plot for fakes
                // cout << dR_A << endl;
                histohelp->GetTH1D(histoHelper::hashLInvMass_fake_p_pi)->Fill(LInvMass_p_pi*1000);
                // histohelp->GetTH1D(histoHelper::hashDeltaR_A_fake)->Fill(dR_A1);
                histohelp->GetTH1D(histoHelper::hashDeltaR_A3_fake)->Fill(dR_A3);
                histohelp->GetTH1D(histoHelper::hashPTLambda_A_fake)->Fill(LambdaPtA);
                histohelp->GetTH1D(histoHelper::hashXLambda_fake)->Fill(X_Lambda);
            }
        }
        LambdaCand.push_back(iTrackPair);
    }

// ---------------
// for lambda:
// remove duplicates:
// if two (or more) Kaon candidates share a track, choose the one with the mass closer to the Kaon mass
set<int> rmIdx_for_lambda_cand; // using a set helps to avoid double-removal of an entry
for (unsigned int iLambdaCand1(0); iLambdaCand1 < LambdaCand.size(); ++iLambdaCand1)
{
  int idx1a = trackPairs[LambdaCand[iLambdaCand1]].first;
  int idx1b = trackPairs[LambdaCand[iLambdaCand1]].second;
  for (unsigned int iLambdaCand2(iLambdaCand1+1); iLambdaCand2 < LambdaCand.size(); ++iLambdaCand2)
  {
    int idx2a = trackPairs[LambdaCand[iLambdaCand2]].first;
    int idx2b = trackPairs[LambdaCand[iLambdaCand2]].second;

    if (idx1a == idx2a || idx1a == idx2b || idx1b == idx2a || idx1b == idx2b) {

      TLorentzVector vTrack1a = lvhelp->getTrackTLV(idx1a, LorentzVectorHelper::kProtonMass);
      TLorentzVector vTrack1b = lvhelp->getTrackTLV(idx1b, LorentzVectorHelper::kPionMass);
      TLorentzVector LambdaCandidate1 = vTrack1a+vTrack1b;
      TLorentzVector vTrack2a = lvhelp->getTrackTLV(idx2a, LorentzVectorHelper::kProtonMass);
      TLorentzVector vTrack2b = lvhelp->getTrackTLV(idx2b, LorentzVectorHelper::kPionMass);
      TLorentzVector LambdaCandidate2 = vTrack2a+vTrack2b;

      float invmass_diff_to_Lambdamass_1 = fabs(LambdaCandidate1.M() - LorentzVectorHelper::kLambdaMass);
      float invmass_diff_to_Lambdamass_2 = fabs(LambdaCandidate2.M() - LorentzVectorHelper::kLambdaMass);

      if (invmass_diff_to_Lambdamass_1 < invmass_diff_to_Lambdamass_2)
        rmIdx_for_lambda_cand.insert(iLambdaCand2);
      else
        rmIdx_for_lambda_cand.insert(iLambdaCand1);
    }
  }
}
// ---------------
    // loop over track pairs, find kaon candidates
    // and require them to point to the jet
    vector<int> kaonCand(0);
    for (unsigned int iTrackPair(0), nTrackPairs(trackPairs.size()); iTrackPair < nTrackPairs; ++iTrackPair)
    {
    // cout << (*tree->Track_PID)[trackPairs[iTrackPair].first] << " " << (*tree->Track_PID)[trackPairs[iTrackPair].second] << endl;
      TLorentzVector vTrack1 = lvhelp->getTrackTLV(trackPairs[iTrackPair].first, LorentzVectorHelper::kPionMass);
      TLorentzVector vTrack2 = lvhelp->getTrackTLV(trackPairs[iTrackPair].second, LorentzVectorHelper::kPionMass);
      TLorentzVector kaonCandidate = vTrack1+vTrack2;

      float invmass = kaonCandidate.M();
      float dR = kaonCandidate.DeltaR(vJet);

      histohelp->GetTH1D(histoHelper::hashRecoKaonCandDeltaR_to_jet_before_sel)->Fill(dR);
      if (dR > jetDR)
        continue;

      histohelp->GetTH1D(histoHelper::hashRecoKaonCandInvMass_before_sel)->Fill(invmass*1000);
      if (invmass < minKaonMass || invmass > maxKaonMass)
        continue;

      kaonCand.push_back(iTrackPair);
    }

    // remove duplicates:
    // if two (or more) Kaon candidates share a track, choose the one with the mass closer to the Kaon mass
    set<int> rmIdx_for_kaonCand; // using a set helps to avoid double-removal of an entry
    for (unsigned int iKaonCand1(0); iKaonCand1 < kaonCand.size(); ++iKaonCand1)
    {
      int idx1a = trackPairs[kaonCand[iKaonCand1]].first;
      int idx1b = trackPairs[kaonCand[iKaonCand1]].second;
      for (unsigned int iKaonCand2(iKaonCand1+1); iKaonCand2 < kaonCand.size(); ++iKaonCand2)
      {
        int idx2a = trackPairs[kaonCand[iKaonCand2]].first;
        int idx2b = trackPairs[kaonCand[iKaonCand2]].second;

        if (idx1a == idx2a || idx1a == idx2b || idx1b == idx2a || idx1b == idx2b) {

          TLorentzVector vTrack1a = lvhelp->getTrackTLV(idx1a, LorentzVectorHelper::kPionMass);
          TLorentzVector vTrack1b = lvhelp->getTrackTLV(idx1b, LorentzVectorHelper::kPionMass);
          TLorentzVector kaonCandidate1 = vTrack1a+vTrack1b;
          TLorentzVector vTrack2a = lvhelp->getTrackTLV(idx2a, LorentzVectorHelper::kPionMass);
          TLorentzVector vTrack2b = lvhelp->getTrackTLV(idx2b, LorentzVectorHelper::kPionMass);
          TLorentzVector kaonCandidate2 = vTrack2a+vTrack2b;

          float invmass_diff_to_kaonmass_1 = fabs(kaonCandidate1.M() - LorentzVectorHelper::kKaonMass);
          float invmass_diff_to_kaonmass_2 = fabs(kaonCandidate2.M() - LorentzVectorHelper::kKaonMass);

          if (invmass_diff_to_kaonmass_1 < invmass_diff_to_kaonmass_2)
            rmIdx_for_kaonCand.insert(iKaonCand2);
          else
            rmIdx_for_kaonCand.insert(iKaonCand1);
        }
      }
    }
    // the set is sorted in ascending order
    // start removing from the back, so the lower indices remain valid
    for (set<int>::reverse_iterator it(rmIdx_for_kaonCand.rbegin()), itend(rmIdx_for_kaonCand.rend()); it != itend; ++it)
    {
      kaonCand.erase(kaonCand.begin() + *it);
    }

    histohelp->GetTH1D(histoHelper::hashRecoNKaons)->Fill(kaonCand.size());
    histohelp->GetTH1D(histoHelper::hashJetPt)->Fill(vJet.Pt());
    histohelp->GetTH1D(histoHelper::hashJetEta)->Fill(vJet.Eta());

  }

  // finalize histograms and output tree
  TString histofilename;
  if (abs(pdgid) == 3)
    histofilename = TString(path).ReplaceAll(".root", "_histograms_squarks.root");
  else if (abs(pdgid) == 1)
    histofilename = TString(path).ReplaceAll(".root", "_histograms_dquarks.root");
  else if (abs(pdgid) == 2)
    histofilename = TString(path).ReplaceAll(".root", "_histograms_uquarks.root");
  histohelp->finalize(histofilename);

  // ------------------
  // wegspeichern der bineintraege in python array
  // ------------------
  float w0 = histohelp->GetTH1D(histoHelper::hashXLambda)->GetBinWidth(0);
  int N = 1/w0;
  for (int j = 0; j < N; j++){
      float bins_xlambda[100] = {};
      float bins_deltaR[100] = {};
      float bins_deltaR3[100] = {};
      float bins_Lmass[100] = {};
      float bins_vertex[100] = {};
      bins_xlambda[j] = (histohelp->GetTH1D(histoHelper::hashXLambda)->GetBinContent(j));
      bins_deltaR[j] = (histohelp->GetTH1D(histoHelper::hashDeltaR_A)->GetBinContent(j));
      bins_deltaR3[j] = (histohelp->GetTH1D(histoHelper::hashDeltaR_A3)->GetBinContent(j));
      bins_Lmass[j] = (histohelp->GetTH1D(histoHelper::hashLInvMass_true_p_pi)->GetBinContent(j));
      bins_vertex[j] = (histohelp->GetTH1D(histoHelper::hashabsvertex1)->GetBinContent(j));
      if (pdgid == 3){
          // fuer ssbar, jeweils xlambda und deltaR
          ifile2 << j << "\t" << bins_xlambda[j] << "\t" << bins_deltaR[j] << "\t" << bins_Lmass[j] << "\t" << bins_deltaR3[j] << "\t" << bins_vertex[j] << endl;
      }
      if (pdgid == 1){
          // fuer ddbar
          ifile2 << j << "\t" << bins_xlambda[j] << "\t" << bins_deltaR[j] << "\t" << bins_Lmass[j] << "\t" << bins_deltaR3[j] << "\t" << bins_vertex[j] << endl;
      }
      if (pdgid == 2){
          // fuer uubar
          ifile2 << j << "\t" << bins_xlambda[j] << "\t" << bins_deltaR[j] << "\t" << bins_Lmass[j] << "\t" << bins_deltaR3[j] << "\t" << bins_vertex[j] << endl;
      }
  }
  //
  // float wvv = histohelp->GetTH1D(histoHelper::hashabsvertex1)->GetBinWidth(0);
  // float lbordervv = histohelp->GetTH1D(histoHelper::hashabsvertex1)->GetBinLowEdge(0);
  // float cutsvxvy[29] = {100., 90., 80., 70., 60., 50., 40., 30., 20., 19., 18., 17., 16., 15., 14., 13., 12., 11., 10., 9., 8., 7., 6., 5., 4., 3., 2., 1., 0.};
  // for (int j = 0; j < 29; j++){
  //     float distvv = abs(lbordervv - cutsvxvy[j]);
  //     int N = distvv / wvv;
  //     float end = 75; // anzahl an bins des histogramms -> am besten fuer alle gleich!
  //     float leftAreavv = 0;
  //     float rightAreavv = 0;
  //     for (int a = 0; a < N; a++){
  //         leftAreavv += (histohelp->GetTH1D(histoHelper::hashabsvertex1)->GetBinContent(a));
  //     }
  //     for (int b = N; b < end; b++){
  //         rightAreavv += (histohelp->GetTH1D(histoHelper::hashabsvertex1)->GetBinContent(b));
  //     }
  //     // cout << "j = " << j << ", a: " << leftArea << ", b: " << rightArea << endl;
  //     if (pdgid == 3){
  //         ifile3 << j << "\t" << leftAreavv << "\t" << rightAreavv << endl;
  //     }
  //     if (pdgid == 1){
  //         ifile3 << j << "\t" << leftAreavv << "\t" << rightAreavv << endl;
  //     }
  //     if (pdgid == 2){
  //         ifile3 << j << "\t" << leftAreavv << "\t" << rightAreavv << endl;
  //     }
  // }
// ------------------

  // clean up and end program happily
  delete lvhelp;
  delete histohelp;

  // ergebnisse
  cout << "/////////////" << endl;
  cout << "//  Start  //" << endl;
  cout << "/////////////" << endl;
  cout << endl;
  cout << "///////////////////////////" << endl;
  cout << "//  Truth-Level Results  //" << endl;
  cout << "///////////////////////////" << endl;
  cout << " Kaons: " << endl;
  cout << " N(K_s -> π+π-) and point to truth jet: " << counterToPi << endl;
  cout << " N(other than π+π- final state): " << counterToOther << endl;
  KaonTotalDecay = (counterToPi + counterToOther);
  cout << " N(total decays): " << KaonTotalDecay << endl;
  // fuer lambda
  cout << " Lambdas: " << endl;
  cout << " N(Λ -> p π-) and point to truth jet: " << counterToLambda << endl;
  cout << " N(to other than p π- final state): " << countToOtherLambda << endl;
  LambdaTotalDecay = (counterToLambda + countToOtherLambda);
  cout << " N(total decays): " << LambdaTotalDecay << endl;

  cout << endl;
  // branching rations for kaons
  cout << " branching ratios: " << endl;
  float BR_kaon = counterToPi / KaonTotalDecay;
  cout << " BR(K_s -> π+ π-): " << BR_kaon << endl;

  // branching rations for Lambdas
  float BR_lambda = counterToLambda / LambdaTotalDecay;
  cout << " BR(Λ -> p π-): " << BR_lambda << endl;
  cout << endl;
  float abweichung_kaon = (abs(pdg_BR_kaon - BR_kaon) / pdg_BR_kaon) * 100;
  float abweichung_lambda = (abs(pdg_BR_lambda - BR_lambda) / pdg_BR_lambda) * 100;
  cout << " error to pdg value: " << endl;
  cout << " abweichung[percent]: " << 100 - abweichung_kaon << endl;
  cout << " abweichung[percent]: " << 100 - abweichung_lambda << endl;
  // results for lambda reco algorithm
  cout << endl;
  cout << "//////////////////////////" << endl;
  cout << "//  Reco-Level results  //" << endl;
  cout << "//////////////////////////" << endl;
  cout << endl;
  // es kann sein, dass die alle doppelt gezaehlt werden
  cout << " true Λ: " << counter_true << endl;
  cout << " fake Λ: " << counter_fake << endl;
  cout << endl;
  cout << "////////////////////" << endl;
  cout << "//  ROC - Kurven  //" << endl;
  cout << "////////////////////" << endl;
  cout << endl;
  cout << "siehe Python skript." << endl;
  cout << endl;
  cout << "/////////////////////////" << endl;
  cout << "//  python rechnungen  //" << endl;
  cout << "/////////////////////////" << endl;
  cout << endl;
  cout << "MIttelwerte /pm error, ssbar: "  << "(1116.09 +- 0.11) MeV" << endl;
  cout << "MIttelwerte /pm error, ddbar: "  << "(1116.35 +- 0.24) MeV" << endl;
  cout << "MIttelwerte /pm error, uubar: "  << "(1116.89 +- 0.39) MeV" << endl;
  cout << endl;
  cout << "///////////" << endl;
  cout << "//  End  //" << endl;
  cout << "///////////" << endl;
  return 0;
}

int main() {
    ofstream mittel1;
    mittel1.open("lambda_mittelwerte1.txt");
    ofstream mittel2;
    mittel2.open("lambda_mittelwerte2.txt");
    ofstream mittel3;
    mittel3.open("lambda_mittelwerte3.txt");

    // LR: left right ~ bezieht sich auf die flaechen
    // for DeltaR
    ofstream rocdata1;
    rocdata1.open("rocwerte_ssbar.txt");
    ofstream rocdata2;
    rocdata2.open("rocwerte_ddbar.txt");
    ofstream rocdata3;
    rocdata3.open("rocwerte_uubar.txt");

    // for absvertex1
    // ofstream vxvy1;
    // vxvy1.open("vxvywerte_ssbar.txt");
    // ofstream vxvy2;
    // vxvy2.open("vxvywerte_ddbar.txt");
    // ofstream vxvy3;
    // vxvy3.open("vxvywerte_uubar.txt");

  // runKaonRecoEtc("../data/s_10k.root", 3);
  // runKaonRecoEtc("../data/d_10k.root", 1);
  // runKaonRecoEtc("../data/u_10k.root", 2);
  // runKaonRecoEtc("../data/s_10M.root", 3);
  // runKaonRecoEtc("../data/d_10M.root", 1);
  runKaonRecoEtc("../../data/ssbar-res-phi-corrected.root", 3, mittel1, rocdata1);
  runKaonRecoEtc("../../data/ddbar-res-phi-corrected.root", 1, mittel2, rocdata2);
  runKaonRecoEtc("../../data/uubar-res-phi-corrected.root", 2, mittel3, rocdata3);
  mittel1.close();
  mittel2.close();
  mittel3.close();
  rocdata1.close();
  rocdata2.close();
  rocdata3.close();
  // vxvy1.close();
  // vxvy2.close();
  // vxvy3.close();
  // end happily
  return 0;
}
