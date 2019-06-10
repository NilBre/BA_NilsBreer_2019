#ifndef histoHelper_h
#define histoHelper_h

#include "TH1D.h"
#include "TProfile.h"
#include <vector>
#include "TString.h"

using namespace std;

class histoHelper {

// in this enumeration include the new histogramm for lambda or so
 public :

  enum histoHashTH1D {
    hashTruthJetPt_before_sel,
    hashTruthJetEta_before_sel,
    hashTruthJetPt,
    hashTruthJetEta,
    hashQuarkDeltaR_to_leadingTruthJet,
    hashQuarkWithinLeadingTruthJet,
    hashTruthNKaons,
    hashTruthNKaonsWithDaughters,
    hashTruthPionPt_before_sel,
    hashTruthPionEta_before_sel,
    hashTruthPionPt,
    hashTruthPionEta,
    hashTruthPionDeltaR_to_jet,
    hashTruthKaonPt_over_jetPt, // fuer aufgabe 3
    hashTruthKaonDeltaR_to_jet,
    hashTruthKaonInvMass,
    hashJetPt_before_sel,
    hashJetEta_before_sel,
    hashJetPt,
    hashJetEta,
    hashQuarkDeltaR_to_leadingJet,
    hashQuarkWithinLeadingJet,
    hashTrackPt_before_sel,
    hashTrackEta_before_sel,
    hashTrackTransVertDist_before_sel,
    hashTrackPt,
    hashTrackEta,
    hashTrackTransVertDist,
    hashTrackVertDistX,
    hashTrackVertDistY,
    hashTrackD0,
    hashTrackDZ,
    hashTrackDEta,
    hashTrackDPhi,
    hashTrackX,
    hashTrackN,
    hashRecoNKaons,
    hashRecoKaonCandDeltaR_to_jet_before_sel,
    hashRecoKaonCandInvMass_before_sel,
    hashTruthNlambdas,
    hashKaonInvMass,
    hashKaonPT,
    hashKaonXk,
    hashKaonDeltaR,
    hashLambdaInvMass,
    hashLambdaPT,
    hashLambdaXk,
    hashLambdaDeltaR,
    hashJetPTforKaon,
    hashTruthNOtherKaons,
    hashCharge,
    hashDeltaR_A,
    hashDeltaR_B,
    hashLInvMass_true_p_pi,
    hashLInvMass_fake_p_pi,
    hashLInvMass_true_pi_p,
    hashLInvMass_fake_pi_p,
    hashArithMean,
    hashGeoMean,
    hashMin,
    // hashAntiLambdas,
    hashPTLambda_A,
    hashPTLambda_B,
    hashXLambda,
    hashDeltaR_A_fake,
    hashPTLambda_A_fake,
    hashXLambda_fake,
    hashabsvertex1
    };

  enum histoHashTProfile {
    hashJet2PartonMatch
  };

  histoHelper(int pdgid);
  ~histoHelper();

  void finalize(TString filename);

  TH1D * GetTH1D(histoHashTH1D hash);
  TProfile * GetTProfile(histoHashTProfile hash);

 private :

  enum rangetype { kZeroMax, kZeroOne, kMinMaxEqual };

  TH1D * NewTH1D(TString name, unsigned int nbins, float xmin, float xmax, TString xtitle, TString ytitle, rangetype range);
  TProfile * NewTProfile(TString name, unsigned int nbins, float xmin, float xmax, TString xtitle, TString ytitle, rangetype range);

  void adjustRange_ZeroMax(TH1 * h);
  void adjustRange_ZeroOne(TH1 * h);
  void adjustRange_MinMaxEqual(TH1 * h);

  vector<TH1D*> * v_TH1D;
  vector<TProfile*> * v_TProfile;
  vector<rangetype> v_TH1D_range;
  vector<rangetype> v_TProfile_range;

};

#endif
