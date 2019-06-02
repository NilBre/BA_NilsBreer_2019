#include "histoHelper.h"
#include "TDirectory.h"
#include <cmath>
#include <iostream>
#include "TFile.h"

using namespace std;

histoHelper::histoHelper(int pdgid) {

  // the correct order is important here, because its implicitly used in retrieving the histograms from an instance
  // hist layout: NewTH1D("hist-name", n_bins, lower-limit, upper-limit, "x-label", "y-label", ???)
  v_TH1D = new vector<TH1D*>;
  NewTH1D("TruthJetPt_before_sel", 100, 0., 100., "truth jet p_{T} [GeV]", "No. jets / bin", kZeroMax);
  NewTH1D("TruthJetEta_before_sel", 100, -5., 5., "truth jet #eta", "No. jets / bin", kZeroMax);
  NewTH1D("TruthJetPt", 100., 0., 100., "truth jet p_{T} [GeV]", "No. jets / bin", kZeroMax);
  NewTH1D("TruthJetEta", 100., -5., 5., "truth jet #eta", "No. jets / bin", kZeroMax);
  if (abs(pdgid) == 3) {
    NewTH1D("QuarkDeltaR_to_leadingTruthJet", 100., 0., 5, "#Delta R (closest (anti-)s-quark, leading truth jet)", "No. leading jets / bin", kZeroMax);
    NewTH1D("QuarkWithinLeadingTruthJet", 2., 0., 2., "Is the closest (anti-)s-quark within the leading truth jet?", "No. leading jets / bin", kZeroMax);
  }
  else if (abs(pdgid) == 1) {
    NewTH1D("QuarkDeltaR_to_leadingTruthJet", 100., 0., 5, "#Delta R (closest (anti-)d-quark, leading truth jet)", "No. leading jets / bin", kZeroMax);
    NewTH1D("QuarkWithinLeadingTruthJet", 2., 0., 2., "Is the closest (anti-)d-quark within the leading truth jet?", "No. leading jets / bin", kZeroMax);
  }
  else if (abs(pdgid) == 2) {
    NewTH1D("QuarkDeltaR_to_leadingTruthJet", 100., 0., 5, "#Delta R (closest (anti-)u-quark, leading truth jet)", "No. leading jets / bin", kZeroMax);
    NewTH1D("QuarkWithinLeadingTruthJet", 2., 0., 2., "Is the closest (anti-)u-quark within the leading truth jet?", "No. leading jets / bin", kZeroMax);
  }
  NewTH1D("TruthNKaons", 6, 0., 6., "No. of K_{S} (#rightarrow #pi^{+} #pi^{-}) that point to jet area", "No. jets / bin", kZeroMax);
  NewTH1D("TruthNKaonsWithDaughters", 6, 0., 6., "No. of K_{S} #rightarrow #pi^{+} #pi^{-} that point to jet area", "No. jets / bin", kZeroMax);
  NewTH1D("TruthPionPt_before_sel", 500., 0., 25, "#pi^{#pm} p_{T} [GeV]", "No. pions / bin", kZeroMax);
  NewTH1D("TruthPionEta_before_sel", 100., -5., 5., "#pi^{#pm} #eta", "No. pions / bin", kZeroMax);
  NewTH1D("TruthPionPt", 100., 0., 25, "#pi^{#pm} p_{T} [GeV]", "No. pions / bin", kZeroMax);
  NewTH1D("TruthPionEta", 100., -5., 5., "#pi^{#pm} #eta", "No. pions / bin", kZeroMax);
  NewTH1D("TruthPionDeltaR_to_jet", 100., 0., 5., "#Delta R (#pi^{#pm}, truth jet)", "No. pions / bin", kZeroMax);
  NewTH1D("TruthKaonPt_over_jetPt", 120., 0., 1.2, "K_{S} p_{T} / truth jet p_{T}", "No. kaons / bin", kZeroMax);
  NewTH1D("TruthKaonDeltaR_to_jet", 100., 0., 0.5, "#Delta R (K_{S}, truth jet)", "No. kaons / bin", kZeroMax);
  NewTH1D("TruthKaonInvMass", 100., 300., 650., "m(K_{S})", "No. kaons / bin", kZeroMax);
  NewTH1D("JetPt_before_sel", 100, 0., 100., "jet p_{T} [GeV]", "No. jets / bin", kZeroMax);
  NewTH1D("JetEta_before_sel", 100, -5., 5., "jet #eta", "No. jets / bin", kZeroMax);
  NewTH1D("JetPt", 100., 0., 100., "jet p_{T} [GeV]", "No. jets / bin", kZeroMax);
  NewTH1D("JetEta", 100., -5., 5., "jet #eta", "No. jets / bin", kZeroMax);
  if (abs(pdgid) == 3) {
    NewTH1D("QuarkDeltaR_to_leadingJet", 100., 0., 5, "#Delta R (closest (anti-)s-quark, leading  jet)", "No. leading jets / bin", kZeroMax);
    NewTH1D("QuarkWithinLeadingJet", 2., 0., 2., "Is the closest (anti-)s-quark within the leading truth jet?", "No. leading jets / bin", kZeroMax);
  }
  else if (abs(pdgid) == 1) {
    NewTH1D("QuarkDeltaR_to_leadingJet", 100., 0., 5, "#Delta R (closest (anti-)d-quark, leading  jet)", "No. leading jets / bin", kZeroMax);
    NewTH1D("QuarkWithinLeadingJet", 2., 0., 2., "Is the closest (anti-)d-quark within the leading truth jet?", "No. leading jets / bin", kZeroMax);
  }
  else if (abs(pdgid) == 2) {
    NewTH1D("QuarkDeltaR_to_leadingJet", 100., 0., 5, "#Delta R (closest (anti-)u-quark, leading  jet)", "No. leading jets / bin", kZeroMax);
    NewTH1D("QuarkWithinLeadingJet", 2., 0., 2., "Is the closest (anti-)u-quark within the leading  jet?", "No. leading jets / bin", kZeroMax);
  }
  NewTH1D("TrackPt_before_sel", 100., 0., 25, "track p_{T} [GeV]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackEta_before_sel", 100., -5., 5., "track #eta", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackTransVertDist_before_sel", 250., 0., 1000., "track transverse vertex distance [mm]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackPt", 500., 0., 25, "track p_{T} [GeV]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackEta", 100., -5., 5., "track #eta", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackTransVertDist", 250., 0., 1000., "track transverse vertex distance [mm]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackVertDistX", 250., -1000., 1000., "track transverse vertex distance in x [mm]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackVertDistY", 250., -1000., 1000., "track transverse vertex distance in y [mm]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackD0", 200., -1000., 1000, "track d_{0} [mm]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackDZ", 200., -1000., 1000, "track d_{z} [GeV]", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackDEta", 100., -0.5, 0.5, "track #Delta#eta", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackDPhi", 100., -0.5, 0.5, "track #Delta#phi", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackX", 120., 0., 1.2, "track p_{T} / jet p_{T}", "No. tracks / bin", kZeroMax);
  NewTH1D("TrackN", 20., 0., 20., "No. of tracks", "No. tracks / bin", kZeroMax);
  NewTH1D("RecoNKaons", 6, 0., 6., "No. of reco. K_{S} (#rightarrow #pi^{+} #pi^{-}) that point to jet area", "No. jets / bin", kZeroMax);
  NewTH1D("RecoKaoCandDeltaR_to_jet_before_sel", 100., 0., 1., "#Delta R (K_{S} cand., jet)", "No. reco. kaons / bin", kZeroMax);
  NewTH1D("RecoKaonCandInvMass_before_sel", 100., 0., 1000., "m(reco. K_{S} can.) [MeV]", "No. reco. kaons / bin", kZeroMax);
  // my hist
  NewTH1D("TruthNlambdas", 6, 0., 6., "No. of #Lambda", "No. of Jets / bin", kZeroMax);
  // neue hist: inv.Mass, pT, x, deltaR, fuer rekonstruierte kaons
  NewTH1D("KaonInvMass", 20, 470., 530., "Invariant Kaon Mass[MeV]", "No. of Kaons / bin", kZeroMax);
  NewTH1D("KaonPT", 20., 0., 35., "Kaon transverse momentum[GeV]", "No. of Kaons / bin", kZeroMax);
  NewTH1D("KaonXk", 20, 0., 1., "pT(Kaon)/pT(Jet)", "No. of Jets / bin", kZeroMax);
  NewTH1D("KaonDeltaR", 20, 0., 2*M_PI, "#Delta_R", "No. of Kaons / bin", kZeroMax);
  NewTH1D("LambdaInvMass", 40, 1000., 1400., "Invariant Lambda Mass [MeV]", "No. of Lambda / bin", kZeroMax);
  NewTH1D("LambdaPT", 30., 0., 25., "Lambda transverse momentum[GeV]", "No. of Lambda / bin", kZeroMax);
  NewTH1D("LambdaXk", 120, 0., 3.2, "pT(Lambda)/pT(Jet)", "No. of Jets / bin", kZeroMax);
  NewTH1D("LambdaDeltaR", 50, 0., 1, " #Delta_R", "No. of Lambda / bin", kZeroMax);
  NewTH1D("JetPTforKaon", 50, 0., 90., " #Pt [GeV]", "No. of kaons / bin", kZeroMax);
  NewTH1D("TruthNOtherKaons", 6, 0., 6., "No. of K_s", "No. of kaons / bin", kZeroMax);
  NewTH1D("Charge", 2, -2., 2., "multplied charge (-1 or 1) of track_charge tuple", "No. multiplied track charges / bin", kZeroMax);
  NewTH1D("DeltaR_A", 25, 0., 2*M_PI, "dist(#Lambda-Ref, track) in #eta-#phi plane", "No. Tracks / bin", kZeroMax);
  NewTH1D("DeltaR_B", 25, 0., 2*M_PI, "dist(#Lambda-Ref, track) in #eta-#phi plane", "No. Tracks / bin", kZeroMax);
  NewTH1D("LInvMass_true_p_pi", 15, 1100., 1150.,  "M(#Lambda) for T1(p), T2(#pi)", "No. of #Lambda / bin", kZeroMax);
  NewTH1D("LInvMass_fake_p_pi", 15, 1100., 1150., "M(#Lambda) for T1(p), T2(#pi), fake candidates", "No. of #Lambda / bin", kZeroMax);
  NewTH1D("LInvMass_true_pi_p", 15, 1200., 3000.,  "M(#Lambda) for T1(#pi), T2(p)", "No. of #Lambda / bin", kZeroMax);
  NewTH1D("LInvMass_fake_pi_p", 15, 1200., 3000., "M(#Lambda) for T1(#pi), T2(p), fake caandidates", "No. of #Lambda / bin", kZeroMax);
  NewTH1D("ArithMean", 30, 1000., 2000.,  "arithm mean of both candidates", "No. of #Lambda / bin", kZeroMax);
  NewTH1D("GeoMean", 30, 1000., 2000., "geometrical mean of both candidates", "No. of #Lambda / bin", kZeroMax);
  NewTH1D("Min", 30, 1000., 2000., "Minimum of both masses", "No. Tracks / bin", kZeroMax);
  NewTH1D("AntiLambdas", 30, 1000., 2300., "No. of Anti-#Lambda ", "No. Tracks / bin", kZeroMax);
   // the correct order is important here, because its implicitly used in retrieving the histograms from an instance
  v_TProfile = new vector<TProfile*>;
  //  NewTProfile("h_Jet2PartonMatch", 6, 0., 6., "bhad | blep | lq1 | lq2 | all | true found", "matching efficiency", kZeroOne);
}

histoHelper::~histoHelper() {
  for (unsigned int i = 0, n = v_TH1D->size(); i < n; ++i) {
    if ((*v_TH1D)[i]) {
      delete (*v_TH1D)[i];
      (*v_TH1D)[i] = 0x0;
    }
  }
  v_TH1D->clear();
  delete v_TH1D;
  for (unsigned int i = 0, n = v_TProfile->size(); i < n; ++i) {
    if ((*v_TProfile)[i]) {
      delete (*v_TProfile)[i];
      (*v_TProfile)[i] = 0x0;
    }
  }
  v_TProfile->clear();
  delete v_TProfile;
}

void histoHelper::finalize(TString filename) {
  TFile * f = new TFile(filename, "RECREATE");
  if (v_TH1D) {
    for (unsigned int i(0), n(v_TH1D->size()); i < n; ++i) {
      rangetype range = v_TH1D_range[i];
      TH1D * h = (*v_TH1D)[i];
      if (range == kZeroMax)
        adjustRange_ZeroMax(h);
      else if (range == kZeroOne)
        adjustRange_ZeroOne(h);
      else if (range == kMinMaxEqual)
        adjustRange_MinMaxEqual(h);
      h->Write();
    }
  }
  if (v_TProfile) {
    for (unsigned int i(0), n(v_TProfile->size()); i < n; ++i) {
      rangetype range = v_TProfile_range[i];
      TProfile * h = (*v_TProfile)[i];
      if (range == kZeroMax)
        adjustRange_ZeroMax(h);
      else if (range == kZeroOne)
        adjustRange_ZeroOne(h);
      else if (range == kMinMaxEqual)
        adjustRange_MinMaxEqual(h);
      h->Write();
    }
  }
  f->Close();
  delete f;
  cout << "INFO wrote histograms to file " << filename << endl;
}

void histoHelper::adjustRange_ZeroMax(TH1 * h) {
  if (h)
    h->GetYaxis()->SetRangeUser(0., h->GetMaximum()*1.1);
}

void histoHelper::adjustRange_ZeroOne(TH1 * h) {
  if (h)
    h->GetYaxis()->SetRangeUser(0., 1.);
}

void histoHelper::adjustRange_MinMaxEqual(TH1 * h) {
  if (h) {
    double min = fabs(h->GetMinimum());
    double max = fabs(h->GetMaximum());
    if (min > max)
      max = min;
    h->GetYaxis()->SetRangeUser(-max, max);
  }
}

TH1D * histoHelper::NewTH1D(TString name, unsigned int nbins, float xmin, float xmax, TString xtitle, TString ytitle, rangetype range) {
  TH1D * h = new TH1D(name, name, nbins, xmin, xmax);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  h->Sumw2();
  v_TH1D->push_back(h);
  v_TH1D_range.push_back(range);
  // de-register from current working directory (get rid of "Warning in <TROOT::Append>: Replacing existing TH1: <name> (Potential memory leak).")
  gDirectory->GetList()->Remove(gDirectory->GetList()->FindObject(name));
  return h;
}

TProfile * histoHelper::NewTProfile(TString name, unsigned int nbins, float xmin, float xmax, TString xtitle, TString ytitle, rangetype range) {
  TProfile * h = new TProfile(name, name, nbins, xmin, xmax);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  h->Sumw2();
  v_TProfile->push_back(h);
  v_TProfile_range.push_back(range);
  gDirectory->GetList()->Remove(gDirectory->GetList()->FindObject(name));
  return h;
}

TH1D * histoHelper::GetTH1D(histoHashTH1D hash) {
  return (*v_TH1D)[int(hash)];
}

TProfile * histoHelper::GetTProfile(histoHashTProfile hash) {
  return (*v_TProfile)[int(hash)];
}
