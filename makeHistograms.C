#include "AtlasStyle.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <iostream>
#include "THStack.h"

using namespace std;

void draw(TFile * f1, TFile * f2, TFile * f3, TString histogramname,
          TString xaxislabel, TString unit, TString yaxislabel,
          TString legendentry1, TString legendentry2, TString legendentry3,
          bool doLogScale = false);

void drawBoth(TFile * f1, TFile * f2, TString histogramname1, TString histogramname2,
          TString xaxislabel, TString unit, TString yaxislabel,
          TString legendentry1, TString legendentry2);

double maximum(TH1 * h1, TH1 * h2, TH1 * h3);
double maximum_new(TH1 * h1, TH1 * h2, TH1 * h3, TH1 * h4);

int main() {

  // set good style
  SetAtlasStyle();

  // get file
  // ----- new samples ------
  TFile * myFile1 = new TFile("~/data/ssbar-res-phi-corrected_histograms_squarks.root");
  TFile * myFile2 = new TFile("~/data/ddbar-res-phi-corrected_histograms_dquarks.root");
  TFile * myFile3 = new TFile("~/data/uubar-res-phi-corrected_histograms_uquarks.root");
  // ------------------------
  // TFile * myFile1 = new TFile("~/data/s_10k_histograms_squarks.root");
  // TFile * myFile2 = new TFile("~/data/d_10k_histograms_dquarks.root");
  // TFile * myFile3 = new TFile("~/data/u_10k_histograms_uquarks.root");
  // ------------------------
  // TFile * myFile1 = new TFile("~/data/s_10M_histograms_squarks.root");
  // TFile * myFile2 = new TFile("~/data/d_10M_histograms_dquarks.root");
  // TFile * myFile3 = 0x0;
  // ------------------------
  cout << "INFO file no. 1 : " << myFile1->GetName() << endl;
  if (myFile2) cout << "INFO file no. 2 : " << myFile2->GetName() << endl;
  if (myFile3) cout << "INFO file no. 3 : " << myFile3->GetName() << endl;

  // text for legend
  TString legendtitle = "";
  // TString legendentry1 = "s-jets";
  // TString legendentry2 = "d-jets";
  // TString legendentry3 = "u-jets";
  // ---------------------
  // TString legendentry1 = "s-Jets_10M";
  // TString legendentry2 = "d-Jets_10M";
  // ---------------------
  TString legendentry1 = "ssbar-events-corrected";
  TString legendentry2 = "ddbar-events-corrected";
  TString legendentry3 = "uubar-events-corrected";

  // create canvas and draw histogram(s)
  draw(myFile1, myFile2, myFile3, "TruthJetPt_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthJetEta_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthJetPt", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthJetEta", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "QuarkDeltaR_to_leadingTruthJet", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "QuarkWithinLeadingTruthJet", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthNKaons", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthNKaonsWithDaughters", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthPionPt_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthPionEta_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthPionPt", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthPionEta", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthPionDeltaR_to_jet", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthKaonPt_over_jetPt", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthKaonDeltaR_to_jet", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthKaonInvMass", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "JetPt_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "JetEta_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "JetPt", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "JetEta", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "QuarkDeltaR_to_leadingJet", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "QuarkWithinLeadingJet", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackPt_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackEta_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackTransVertDist_before_sel", "", "", "", legendentry1, legendentry2, legendentry3, true);
  draw(myFile1, myFile2, myFile3, "TrackPt", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackEta", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackTransVertDist", "", "", "", legendentry1, legendentry2, legendentry3, true);
  draw(myFile1, myFile2, myFile3, "TrackVertDistX", "", "", "", legendentry1, legendentry2, legendentry3, true);
  draw(myFile1, myFile2, myFile3, "TrackVertDistY", "", "", "", legendentry1, legendentry2, legendentry3, true);
  draw(myFile1, myFile2, myFile3, "TrackD0", "", "", "", legendentry1, legendentry2, legendentry3, true);
  draw(myFile1, myFile2, myFile3, "TrackDZ", "", "", "", legendentry1, legendentry2, legendentry3, true);
  draw(myFile1, myFile2, myFile3, "TrackDEta", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackDPhi", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackX", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TrackN", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "RecoNKaons", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "RecoKaoCandDeltaR_to_jet_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "RecoKaonCandInvMass_before_sel", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthNlambdas", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "KaonInvMass", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "KaonPT", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "KaonXk", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "KaonDeltaR", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LambdaInvMass", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LambdaPT", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LambdaXk", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LambdaDeltaR", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "JetPTforKaon", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "TruthNOtherKaons", "", "", "", legendentry1, legendentry2, legendentry3);
  drawBoth(myFile1, myFile2, "TruthNKaons", "TruthNOtherKaons", "", "", "", legendentry1, legendentry2);
  draw(myFile1, myFile2, myFile3, "Charge", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "DeltaR_A", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "DeltaR_B", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LInvMass_true_p_pi", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LInvMass_fake_p_pi", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LInvMass_true_pi_p", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "LInvMass_fake_pi_p", "", "", "", legendentry1, legendentry2, legendentry3);
  drawBoth(myFile1, myFile2, "LInvMass_true_p_pi", "LInvMass_fake_p_pi", "", "", "", legendentry1, legendentry2);
  drawBoth(myFile1, myFile2, "LInvMass_true_pi_p", "LInvMass_fake_pi_p", "", "", "", legendentry1, legendentry2);
  draw(myFile1, myFile2, myFile3, "ArithMean", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "GeoMean", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "Min", "", "", "", legendentry1, legendentry2, legendentry3);
  draw(myFile1, myFile2, myFile3, "AntiLambdas", "", "", "", legendentry1, legendentry2, legendentry3);

  return 0;
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

void drawBoth(TFile * f1, TFile * f2, TString histogramname1, TString histogramname2,
          TString xaxislabel, TString unit, TString yaxislabel,
          TString legendentry1, TString legendentry2){

    // THStack *stack = new THStack();
    TH1 * hist1 = (TH1*)f1->Get(histogramname1);
    TH1 * hist2 = (TH1*)f2->Get(histogramname1);
    TH1 * hist3 = (TH1*)f1->Get(histogramname2); // vorher: TH1 * hist3 = (TH1*)f1->Get("TruthNOtherKaons");
    TH1 * hist4 = (TH1*)f2->Get(histogramname2);
  if (yaxislabel != "Efficiency"){
    hist1->Scale(1./(hist1->Integral()+hist1->GetBinContent(0)+hist1->GetBinContent(hist1->GetNbinsX()+1))); // add overflow and underflow bins
    hist2->Scale(1./(hist2->Integral()+hist2->GetBinContent(0)+hist2->GetBinContent(hist2->GetNbinsX()+1))); // add overflow and underflow bins
    hist3->Scale(1./(hist3->Integral()+hist3->GetBinContent(0)+hist3->GetBinContent(hist3->GetNbinsX()+1))); // add overflow and underflow bins
    hist4->Scale(1./(hist4->Integral()+hist4->GetBinContent(0)+hist4->GetBinContent(hist4->GetNbinsX()+1))); // add overflow and underflow bins
  }
    // histogram line styles
    hist1->SetLineColor(kRed);
    hist1->SetLineStyle(kSolid);
    hist1->SetMarkerSize(0);
    hist1->SetFillColorAlpha(kRed, 0.35);

    hist2->SetLineColor(kRed);
    hist2->SetLineStyle(kDashed);
    hist2->SetMarkerSize(0);
    hist2->SetFillColorAlpha(kRed, 0.35);

    hist3->SetLineColor(kBlue);
    hist3->SetLineStyle(kSolid);
    hist3->SetMarkerSize(0);
    hist3->SetFillColorAlpha(kBlue, 0.35);

    hist4->SetLineColor(kBlue);
    hist4->SetLineStyle(kDashed);
    hist4->SetMarkerSize(0);
    hist4->SetFillColorAlpha(kBlue, 0.35);

    double yoffset(0.);
    yoffset += 0.1;
    TLegend * l = new TLegend(0.6, 0.8-yoffset, 0.9, 0.9);
    l->SetTextAlign(12);
    l->AddEntry(hist1, legendentry1 + TString(", true candidates"), "l");
    l->AddEntry(hist2, legendentry2 + TString(", true candidates"), "l");
    l->AddEntry(hist3, legendentry1 + TString(", fake candidates"), "l");
    l->AddEntry(hist4, legendentry2 + TString(", fake candidates"), "l");
    l->SetFillColor(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.025);

    TCanvas * cs = new TCanvas("cs", "cs", 1);
    float epsilon = 0;
    if (unit != "") xaxislabel += " [" + unit + "]";
    if (xaxislabel != "") hist1->GetXaxis()->SetTitle(xaxislabel);
    if (yaxislabel == "Events / Bin") {
      double binsize = hist1->GetXaxis()->GetBinWidth(1); // assuming all bins have the same width
      yaxislabel = TString("Events / ");
      yaxislabel += Form("%4.2f", binsize);
      yaxislabel += " " + unit;
    }
    if (yaxislabel != "Efficiency")
      hist1->GetYaxis()->SetRangeUser(epsilon, maximum_new(hist1, hist2, hist3, hist4));
    if (histogramname1 == "HasBestPermutationEfficiency") {
      hist1->GetXaxis()->SetBinLabel(1, "Has at least one good permutation");
      yaxislabel = "Efficiency";
    }
    if (yaxislabel != "") hist1->GetYaxis()->SetTitle(yaxislabel);
    // ---------------------
    // stack->Add(hist4);
    // stack->Add(hist3);
    // stack->Add(hist2);
    // stack->Add(hist1);
    // stack->Draw("nostack");
    hist1->Draw("h");
    hist2->Draw("hsame");
    hist3->Draw("hsame");
    hist4->Draw("hsame");
    l->Draw();

    cs->Print(TString("output/") + histogramname1 + "_" + histogramname2 + ".png");
    cs->Print(TString("output/") + histogramname1 + "_" + histogramname2 + ".pdf");
    delete cs;
}

void draw(TFile * f1, TFile * f2, TFile * f3, TString histogramname,
          TString xaxislabel, TString unit, TString yaxislabel,
          TString legendentry1, TString legendentry2, TString legendentry3,
          bool doLogScale) {

  // get histograms and check if it worked
  TH1 * h1 = (TH1*)f1->Get(histogramname);
  if (!h1 || !f1) {
    f1->ls();
    cout << "ERROR did not find TH1 with name " << histogramname << " in file " << f1->GetName() << endl;
    return;
  }
  TH1 * h2(0);
  if (f2) {
    h2 = (TH1*)f2->Get(histogramname);
    if (!h2) {
      f2->ls();
      cout << "ERROR did not find TH1 with name " << histogramname << " in file " << f2->GetName() << endl;
      return;
    }
  }
  TH1 * h3(0);
  if (f3) {
    h3 = (TH1*)f3->Get(histogramname);
    if (!h3) {
      f3->ls();
      cout << "ERROR did not find TH1 with name " << histogramname << " in file " << f3->GetName() << endl;
      return;
    }
  }

  // normalize to unit area
  if (yaxislabel != "Efficiency") {
    h1->Scale(1./(h1->Integral()+h1->GetBinContent(0)+h1->GetBinContent(h1->GetNbinsX()+1))); // add overflow and underflow bins
    if (h2) h2->Scale(1./(h2->Integral()+h2->GetBinContent(0)+h2->GetBinContent(h2->GetNbinsX()+1))); // add overflow and underflow bins
    if (h3) h3->Scale(1./(h3->Integral()+h3->GetBinContent(0)+h3->GetBinContent(h3->GetNbinsX()+1))); // add overflow and underflow bins
  }

  // histogram line styles
  h1->SetLineColor(kBlack);
  h1->SetLineStyle(kSolid);
  h1->SetMarkerSize(0);
  if (h2) {
    h2->SetLineColor(kBlue);
    h2->SetLineStyle(kDashed);
    h2->SetMarkerSize(0);
  }
  if (h3) {
    h3->SetLineColor(kRed);
    h3->SetLineWidth(1);
    h3->SetLineStyle(kSolid);
    h3->SetMarkerSize(0);
  }

  // legend
  double yoffset(0.);
  if (h2) yoffset += 0.1;
  if (h3) yoffset += 0.1;
  TLegend * l = new TLegend(0.6, 0.8-yoffset, 0.9, 0.9);
  l->SetTextAlign(12);
  l->AddEntry(h1, legendentry1, "l");
  if (h2) l->AddEntry(h2, legendentry2, "l");
  if (h3) l->AddEntry(h3, legendentry3, "l");
  l->SetFillColor(0);
  l->SetBorderSize(0);
  l->SetTextSize(0.045);

  // draw on canvas and save
  TCanvas * c = new TCanvas("c", "c", 1);
  float epsilon = 0.;
  if (doLogScale)
    epsilon = 1.e-5;
  if (unit != "") xaxislabel += " [" + unit + "]";
  if (xaxislabel != "") h1->GetXaxis()->SetTitle(xaxislabel);
  if (yaxislabel == "Events / Bin") {
    double binsize = h1->GetXaxis()->GetBinWidth(1); // assuming all bins have the same width
    yaxislabel = TString("Events / ");
    yaxislabel += Form("%4.2f", binsize);
    yaxislabel += " " + unit;
  }
  if (yaxislabel != "Efficiency")
    h1->GetYaxis()->SetRangeUser(epsilon, maximum(h1, h2, h3));
  if (histogramname == "HasBestPermutationEfficiency") {
    h1->GetXaxis()->SetBinLabel(1, "Has at least one good permutation");
    yaxislabel = "Efficiency";
  }
  if (yaxislabel != "") h1->GetYaxis()->SetTitle(yaxislabel);
  h1->Draw("h");
  if (h2) h2->Draw("hsame");
  if (h3) h3->Draw("hsame");
  l->Draw();

  if (doLogScale) c->SetLogy();

  c->Print(TString("output/") + histogramname + ".png");
  c->Print(TString("output/") + histogramname + ".pdf");
  delete c;
}

double maximum(TH1 * h1, TH1 * h2, TH1 * h3) {
  double max = h1->GetMaximum();
  if (h2) {
    if (h2->GetMaximum() > max) max = h2->GetMaximum();
  }
  if (h3) {
    if (h3->GetMaximum() > max) max = h3->GetMaximum();
  }
  return max * 1.1;
}

double maximum_new(TH1 * h1, TH1 * h2, TH1 * h3, TH1 * h4) {
  double max = h1->GetMaximum();
  if (h2) {
    if (h2->GetMaximum() > max) max = h2->GetMaximum();
  }
  if (h3) {
    if (h3->GetMaximum() > max) max = h3->GetMaximum();
  }
  if (h4) {
    if (h4->GetMaximum() > max) max = h4->GetMaximum();
  }
  return max * 1.1;
}
