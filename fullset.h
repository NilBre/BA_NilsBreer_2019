//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 12 08:57:39 2019 by ROOT version 6.06/02
// from TTree fullset/fullset
// found on file: /tmp/sbars-small-sample-2019-03-12/events_fullset.root
//////////////////////////////////////////////////////////

#ifndef fullset_h
#define fullset_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class fullset {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          Particle_size;
   vector<int>     *Particle_PID;
   vector<float>   *Particle_Mass; // Teilchen Masse
   vector<float>   *Particle_E; // ...Energy
   vector<float>   *Particle_PT; // ...Transversalimpuls
   vector<float>   *Particle_Eta; // ...einer der streuwinkel
   vector<float>   *Particle_Phi; // ...anderer streuwinkel
   vector<float>   *Particle_Px; // ...teilchen 3er impulse
   vector<float>   *Particle_Py;
   vector<float>   *Particle_Pz;
   UInt_t          Jet_size;
   vector<float>   *Jet_PT; // analog fuer jets
   vector<float>   *Jet_Eta;
   vector<float>   *Jet_Phi;
   vector<float>   *Jet_T;
   vector<float>   *Jet_Mass;
   vector<float>   *Jet_DeltaEta;
   vector<float>   *Jet_DeltaPhi;
   vector<unsigned int> *Jet_Flavor; // evtl pruefen ob das ding protonen mit pdgid sehen kann
   vector<unsigned int> *Jet_FlavorAlgo;
   vector<unsigned int> *Jet_FlavorPhys;
   vector<unsigned int> *Jet_BTag;
   vector<unsigned int> *Jet_BTagAlgo;
   vector<unsigned int> *Jet_BTagPhys;
   vector<unsigned int> *Jet_TauTag;
   vector<int>     *Jet_Charge;
   vector<float>   *Jet_EhadOverEem;
   vector<int>     *Jet_NCharged;
   vector<int>     *Jet_NNeutrals;
   vector<float>   *Jet_Beta;
   vector<float>   *Jet_BetaStar;
   vector<float>   *Jet_MeanSqDeltaR;
   vector<float>   *Jet_PTD;
   UInt_t          GenJet_size;
   vector<float>   *GenJet_PT;
   vector<float>   *GenJet_Eta;
   vector<float>   *GenJet_Phi;
   vector<float>   *GenJet_T;
   vector<float>   *GenJet_Mass;
   vector<float>   *GenJet_DeltaEta;
   vector<float>   *GenJet_DeltaPhi;
   vector<unsigned int> *GenJet_Flavor;
   vector<unsigned int> *GenJet_FlavorAlgo;
   vector<unsigned int> *GenJet_FlavorPhys;
   vector<unsigned int> *GenJet_BTag;
   vector<unsigned int> *GenJet_BTagAlgo;
   vector<unsigned int> *GenJet_BTagPhys;
   vector<unsigned int> *GenJet_TauTag;
   vector<int>     *GenJet_Charge;
   vector<float>   *GenJet_EhadOverEem;
   vector<int>     *GenJet_NCharged;
   vector<int>     *GenJet_NNeutrals;
   vector<float>   *GenJet_Beta;
   vector<float>   *GenJet_BetaStar;
   vector<float>   *GenJet_MeanSqDeltaR;
   vector<float>   *GenJet_PTD;
   UInt_t          Track_size;
   vector<int>     *Track_PID; //
   vector<int>     *Track_Charge; //
   vector<float>   *Track_PT; // ist verschmiert a la gauss kurve
   vector<float>   *Track_Eta; // genau
   vector<float>   *Track_Phi; // genau
   vector<float>   *Track_X;
   vector<float>   *Track_Y;
   vector<float>   *Track_Z;
   vector<float>   *Track_D0;
   vector<float>   *Track_DZ;
   UInt_t          KaonShort_size; //
   vector<int>     *KaonShort_PID;
   vector<float>   *KaonShort_PT; //
   vector<float>   *KaonShort_Eta;
   vector<float>   *KaonShort_Phi;
   UInt_t          KaonShortDaughter1_size;
   vector<int>     *KaonShortDaughter1_PID;
   vector<float>   *KaonShortDaughter1_PT;
   vector<float>   *KaonShortDaughter1_Eta;
   vector<float>   *KaonShortDaughter1_Phi;
   UInt_t          KaonShortDaughter2_size;
   vector<int>     *KaonShortDaughter2_PID;
   vector<float>   *KaonShortDaughter2_PT;
   vector<float>   *KaonShortDaughter2_Eta;
   vector<float>   *KaonShortDaughter2_Phi;
   UInt_t          Lambda_size;
   vector<int>     *Lambda_PID;
   vector<float>   *Lambda_PT; //
   vector<float>   *Lambda_Eta;
   vector<float>   *Lambda_Phi;

   UInt_t          LambdaDaughter1_size;
   vector<int>     *LambdaDaughter1_PID; // das hier...
   vector<float>   *LambdaDaughter1_PT;
   vector<float>   *LambdaDaughter1_Eta;
   vector<float>   *LambdaDaughter1_Phi;
   UInt_t          LambdaDaughter2_size;
   vector<int>     *LambdaDaughter2_PID; // und das hier funktionieren besser
   vector<float>   *LambdaDaughter2_PT;
   vector<float>   *LambdaDaughter2_Eta;
   vector<float>   *LambdaDaughter2_Phi; //
   UInt_t          Electron_size;
   vector<float>   *Electron_PT;
   vector<float>   *Electron_Eta;
   vector<float>   *Electron_Phi;
   vector<float>   *Electron_T;
   vector<int>     *Electron_Charge;
   vector<float>   *Electron_EhadOverEem;
   vector<float>   *Electron_IsolationVar;
   vector<float>   *Electron_IsolationVarRhoCorr;
   vector<float>   *Electron_SumPtCharged;
   vector<float>   *Electron_SumPtNeutral;
   vector<float>   *Electron_SumPtChargedPU;
   vector<float>   *Electron_SumPt;
   UInt_t          Photon_size;
   vector<float>   *Photon_PT;
   vector<float>   *Photon_Eta;
   vector<float>   *Photon_Phi;
   vector<float>   *Photon_E;
   vector<float>   *Photon_T;
   vector<float>   *Photon_EhadOverEem;
   vector<float>   *Photon_IsolationVar;
   vector<float>   *Photon_IsolationVarRhoCorr;
   vector<float>   *Photon_SumPtCharged;
   vector<float>   *Photon_SumPtNeutral;
   vector<float>   *Photon_SumPtChargedPU;
   vector<float>   *Photon_SumPt;
   UInt_t          Muon_size;
   vector<float>   *Muon_PT;
   vector<float>   *Muon_Eta;
   vector<float>   *Muon_Phi;
   vector<float>   *Muon_T;
   vector<int>     *Muon_Charge;
   vector<float>   *Muon_IsolationVar;
   vector<float>   *Muon_IsolationVarRhoCorr;
   vector<float>   *Muon_SumPtCharged;
   vector<float>   *Muon_SumPtNeutral;
   vector<float>   *Muon_SumPtChargedPU;
   vector<float>   *Muon_SumPt;
   Float_t         MissingET_MET;
   Float_t         MissingET_Eta;
   Float_t         MissingET_Phi;
   Float_t         ScalarHT_HT;

   // List of branches
   TBranch        *b_Particle_size;   //!
   TBranch        *b_Particle_PID;   //!
   TBranch        *b_Particle_Mass;   //!
   TBranch        *b_Particle_E;   //!
   TBranch        *b_Particle_PT;   //!
   TBranch        *b_Particle_Eta;   //!
   TBranch        *b_Particle_Phi;   //!
   TBranch        *b_Particle_Px;   //!
   TBranch        *b_Particle_Py;   //!
   TBranch        *b_Particle_Pz;   //!
   TBranch        *b_Jet_size;   //!
   TBranch        *b_Jet_PT;   //!
   TBranch        *b_Jet_Eta;   //!
   TBranch        *b_Jet_Phi;   //!
   TBranch        *b_Jet_T;   //!
   TBranch        *b_Jet_Mass;   //!
   TBranch        *b_Jet_DeltaEta;   //!
   TBranch        *b_Jet_DeltaPhi;   //!
   TBranch        *b_Jet_Flavor;   //!
   TBranch        *b_Jet_FlavorAlgo;   //!
   TBranch        *b_Jet_FlavorPhys;   //!
   TBranch        *b_Jet_BTag;   //!
   TBranch        *b_Jet_BTagAlgo;   //!
   TBranch        *b_Jet_BTagPhys;   //!
   TBranch        *b_Jet_TauTag;   //!
   TBranch        *b_Jet_Charge;   //!
   TBranch        *b_Jet_EhadOverEem;   //!
   TBranch        *b_Jet_NCharged;   //!
   TBranch        *b_Jet_NNeutrals;   //!
   TBranch        *b_Jet_Beta;   //!
   TBranch        *b_Jet_BetaStar;   //!
   TBranch        *b_Jet_MeanSqDeltaR;   //!
   TBranch        *b_Jet_PTD;   //!
   TBranch        *b_GenJet_size;   //!
   TBranch        *b_GenJet_PT;   //!
   TBranch        *b_GenJet_Eta;   //!
   TBranch        *b_GenJet_Phi;   //!
   TBranch        *b_GenJet_T;   //!
   TBranch        *b_GenJet_Mass;   //!
   TBranch        *b_GenJet_DeltaEta;   //!
   TBranch        *b_GenJet_DeltaPhi;   //!
   TBranch        *b_GenJet_Flavor;   //!
   TBranch        *b_GenJet_FlavorAlgo;   //!
   TBranch        *b_GenJet_FlavorPhys;   //!
   TBranch        *b_GenJet_BTag;   //!
   TBranch        *b_GenJet_BTagAlgo;   //!
   TBranch        *b_GenJet_BTagPhys;   //!
   TBranch        *b_GenJet_TauTag;   //!
   TBranch        *b_GenJet_Charge;   //!
   TBranch        *b_GenJet_EhadOverEem;   //!
   TBranch        *b_GenJet_NCharged;   //!
   TBranch        *b_GenJet_NNeutrals;   //!
   TBranch        *b_GenJet_Beta;   //!
   TBranch        *b_GenJet_BetaStar;   //!
   TBranch        *b_GenJet_MeanSqDeltaR;   //!
   TBranch        *b_GenJet_PTD;   //!
   TBranch        *b_Track_size;   //!
   TBranch        *b_Track_PID;   //!
   TBranch        *b_Track_Charge;   //!
   TBranch        *b_Track_PT;   //!
   TBranch        *b_Track_Eta;   //!
   TBranch        *b_Track_Phi;   //!
   TBranch        *b_Track_X;   //!
   TBranch        *b_Track_Y;   //!
   TBranch        *b_Track_Z;   //!
   TBranch        *b_Track_D0;   //!
   TBranch        *b_Track_DZ;   //!
   TBranch        *b_KaonShort_size;   //!
   TBranch        *b_KaonShort_PID;   //!
   TBranch        *b_KaonShort_PT;   //!
   TBranch        *b_KaonShort_Eta;   //!
   TBranch        *b_KaonShort_Phi;   //!
   TBranch        *b_KaonShortDaughter1_size;   //!
   TBranch        *b_KaonShortDaughter1_PID;   //!
   TBranch        *b_KaonShortDaughter1_PT;   //!
   TBranch        *b_KaonShortDaughter1_Eta;   //!
   TBranch        *b_KaonShortDaughter1_Phi;   //!
   TBranch        *b_KaonShortDaughter2_size;   //!
   TBranch        *b_KaonShortDaughter2_PID;   //!
   TBranch        *b_KaonShortDaughter2_PT;   //!
   TBranch        *b_KaonShortDaughter2_Eta;   //!
   TBranch        *b_KaonShortDaughter2_Phi;   //!
   TBranch        *b_Lambda_size;   //!
   TBranch        *b_Lambda_PID;   //!
   TBranch        *b_Lambda_PT;   //!
   TBranch        *b_Lambda_Eta;   //!
   TBranch        *b_Lambda_Phi;   //!
   TBranch        *b_LambdaDaughter1_size;   //!
   TBranch        *b_LambdaDaughter1_PID;   //!
   TBranch        *b_LambdaDaughter1_PT;   //!
   TBranch        *b_LambdaDaughter1_Eta;   //!
   TBranch        *b_LambdaDaughter1_Phi;   //!
   TBranch        *b_LambdaDaughter2_size;   //!
   TBranch        *b_LambdaDaughter2_PID;   //!
   TBranch        *b_LambdaDaughter2_PT;   //!
   TBranch        *b_LambdaDaughter2_Eta;   //!
   TBranch        *b_LambdaDaughter2_Phi;   //!
   TBranch        *b_Electron_size;   //!
   TBranch        *b_Electron_PT;   //!
   TBranch        *b_Electron_Eta;   //!
   TBranch        *b_Electron_Phi;   //!
   TBranch        *b_Electron_T;   //!
   TBranch        *b_Electron_Charge;   //!
   TBranch        *b_Electron_EhadOverEem;   //!
   TBranch        *b_Electron_IsolationVar;   //!
   TBranch        *b_Electron_IsolationVarRhoCorr;   //!
   TBranch        *b_Electron_SumPtCharged;   //!
   TBranch        *b_Electron_SumPtNeutral;   //!
   TBranch        *b_Electron_SumPtChargedPU;   //!
   TBranch        *b_Electron_SumPt;   //!
   TBranch        *b_Photon_size;   //!
   TBranch        *b_Photon_PT;   //!
   TBranch        *b_Photon_Eta;   //!
   TBranch        *b_Photon_Phi;   //!
   TBranch        *b_Photon_E;   //!
   TBranch        *b_Photon_T;   //!
   TBranch        *b_Photon_EhadOverEem;   //!
   TBranch        *b_Photon_IsolationVar;   //!
   TBranch        *b_Photon_IsolationVarRhoCorr;   //!
   TBranch        *b_Photon_SumPtCharged;   //!
   TBranch        *b_Photon_SumPtNeutral;   //!
   TBranch        *b_Photon_SumPtChargedPU;   //!
   TBranch        *b_Photon_SumPt;   //!
   TBranch        *b_Muon_size;   //!
   TBranch        *b_Muon_PT;   //!
   TBranch        *b_Muon_Eta;   //!
   TBranch        *b_Muon_Phi;   //!
   TBranch        *b_Muon_T;   //!
   TBranch        *b_Muon_Charge;   //!
   TBranch        *b_Muon_IsolationVar;   //!
   TBranch        *b_Muon_IsolationVarRhoCorr;   //!
   TBranch        *b_Muon_SumPtCharged;   //!
   TBranch        *b_Muon_SumPtNeutral;   //!
   TBranch        *b_Muon_SumPtChargedPU;   //!
   TBranch        *b_Muon_SumPt;   //!
   TBranch        *b_MissingET_MET;   //!
   TBranch        *b_MissingET_Eta;   //!
   TBranch        *b_MissingET_Phi;   //!
   TBranch        *b_ScalarHT_HT;   //!

   fullset(TTree *tree=0);
   virtual ~fullset();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   // JE
   virtual Int_t    GetEntries() { return fChain->GetEntries(); }
};

#endif

#ifdef fullset_cxx
fullset::fullset(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/tmp/sbars-small-sample-2019-03-12/events_fullset.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/tmp/sbars-small-sample-2019-03-12/events_fullset.root");
      }
      f->GetObject("fullset",tree);

   }
   Init(tree);
}

fullset::~fullset()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t fullset::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t fullset::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void fullset::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Particle_PID = 0;
   Particle_Mass = 0;
   Particle_E = 0;
   Particle_PT = 0;
   Particle_Eta = 0;
   Particle_Phi = 0;
   Particle_Px = 0;
   Particle_Py = 0;
   Particle_Pz = 0;
   Jet_PT = 0;
   Jet_Eta = 0;
   Jet_Phi = 0;
   Jet_T = 0;
   Jet_Mass = 0;
   Jet_DeltaEta = 0;
   Jet_DeltaPhi = 0;
   Jet_Flavor = 0;
   Jet_FlavorAlgo = 0;
   Jet_FlavorPhys = 0;
   Jet_BTag = 0;
   Jet_BTagAlgo = 0;
   Jet_BTagPhys = 0;
   Jet_TauTag = 0;
   Jet_Charge = 0;
   Jet_EhadOverEem = 0;
   Jet_NCharged = 0;
   Jet_NNeutrals = 0;
   Jet_Beta = 0;
   Jet_BetaStar = 0;
   Jet_MeanSqDeltaR = 0;
   Jet_PTD = 0;
   GenJet_PT = 0;
   GenJet_Eta = 0;
   GenJet_Phi = 0;
   GenJet_T = 0;
   GenJet_Mass = 0;
   GenJet_DeltaEta = 0;
   GenJet_DeltaPhi = 0;
   GenJet_Flavor = 0;
   GenJet_FlavorAlgo = 0;
   GenJet_FlavorPhys = 0;
   GenJet_BTag = 0;
   GenJet_BTagAlgo = 0;
   GenJet_BTagPhys = 0;
   GenJet_TauTag = 0;
   GenJet_Charge = 0;
   GenJet_EhadOverEem = 0;
   GenJet_NCharged = 0;
   GenJet_NNeutrals = 0;
   GenJet_Beta = 0;
   GenJet_BetaStar = 0;
   GenJet_MeanSqDeltaR = 0;
   GenJet_PTD = 0;
   Track_PID = 0;
   Track_Charge = 0;
   Track_PT = 0;
   Track_Eta = 0;
   Track_Phi = 0;
   Track_X = 0;
   Track_Y = 0;
   Track_Z = 0;
   Track_D0 = 0;
   Track_DZ = 0;
   KaonShort_PID = 0;
   KaonShort_PT = 0;
   KaonShort_Eta = 0;
   KaonShort_Phi = 0;
   KaonShortDaughter1_PID = 0;
   KaonShortDaughter1_PT = 0;
   KaonShortDaughter1_Eta = 0;
   KaonShortDaughter1_Phi = 0;
   KaonShortDaughter2_PID = 0;
   KaonShortDaughter2_PT = 0;
   KaonShortDaughter2_Eta = 0;
   KaonShortDaughter2_Phi = 0;
   Lambda_PID = 0;
   Lambda_PT = 0;
   Lambda_Eta = 0;
   Lambda_Phi = 0;
   LambdaDaughter1_PID = 0;
   LambdaDaughter1_PT = 0;
   LambdaDaughter1_Eta = 0;
   LambdaDaughter1_Phi = 0;
   LambdaDaughter2_PID = 0;
   LambdaDaughter2_PT = 0;
   LambdaDaughter2_Eta = 0;
   LambdaDaughter2_Phi = 0;
   Electron_PT = 0;
   Electron_Eta = 0;
   Electron_Phi = 0;
   Electron_T = 0;
   Electron_Charge = 0;
   Electron_EhadOverEem = 0;
   Electron_IsolationVar = 0;
   Electron_IsolationVarRhoCorr = 0;
   Electron_SumPtCharged = 0;
   Electron_SumPtNeutral = 0;
   Electron_SumPtChargedPU = 0;
   Electron_SumPt = 0;
   Photon_PT = 0;
   Photon_Eta = 0;
   Photon_Phi = 0;
   Photon_E = 0;
   Photon_T = 0;
   Photon_EhadOverEem = 0;
   Photon_IsolationVar = 0;
   Photon_IsolationVarRhoCorr = 0;
   Photon_SumPtCharged = 0;
   Photon_SumPtNeutral = 0;
   Photon_SumPtChargedPU = 0;
   Photon_SumPt = 0;
   Muon_PT = 0;
   Muon_Eta = 0;
   Muon_Phi = 0;
   Muon_T = 0;
   Muon_Charge = 0;
   Muon_IsolationVar = 0;
   Muon_IsolationVarRhoCorr = 0;
   Muon_SumPtCharged = 0;
   Muon_SumPtNeutral = 0;
   Muon_SumPtChargedPU = 0;
   Muon_SumPt = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Particle_size", &Particle_size, &b_Particle_size);
   fChain->SetBranchAddress("Particle_PID", &Particle_PID, &b_Particle_PID);
   fChain->SetBranchAddress("Particle_Mass", &Particle_Mass, &b_Particle_Mass);
   fChain->SetBranchAddress("Particle_E", &Particle_E, &b_Particle_E);
   fChain->SetBranchAddress("Particle_PT", &Particle_PT, &b_Particle_PT);
   fChain->SetBranchAddress("Particle_Eta", &Particle_Eta, &b_Particle_Eta);
   fChain->SetBranchAddress("Particle_Phi", &Particle_Phi, &b_Particle_Phi);
   fChain->SetBranchAddress("Particle_Px", &Particle_Px, &b_Particle_Px);
   fChain->SetBranchAddress("Particle_Py", &Particle_Py, &b_Particle_Py);
   fChain->SetBranchAddress("Particle_Pz", &Particle_Pz, &b_Particle_Pz);
   fChain->SetBranchAddress("Jet_size", &Jet_size, &b_Jet_size);
   fChain->SetBranchAddress("Jet_PT", &Jet_PT, &b_Jet_PT);
   fChain->SetBranchAddress("Jet_Eta", &Jet_Eta, &b_Jet_Eta);
   fChain->SetBranchAddress("Jet_Phi", &Jet_Phi, &b_Jet_Phi);
   fChain->SetBranchAddress("Jet_T", &Jet_T, &b_Jet_T);
   fChain->SetBranchAddress("Jet_Mass", &Jet_Mass, &b_Jet_Mass);
   fChain->SetBranchAddress("Jet_DeltaEta", &Jet_DeltaEta, &b_Jet_DeltaEta);
   fChain->SetBranchAddress("Jet_DeltaPhi", &Jet_DeltaPhi, &b_Jet_DeltaPhi);
   fChain->SetBranchAddress("Jet_Flavor", &Jet_Flavor, &b_Jet_Flavor);
   fChain->SetBranchAddress("Jet_FlavorAlgo", &Jet_FlavorAlgo, &b_Jet_FlavorAlgo);
   fChain->SetBranchAddress("Jet_FlavorPhys", &Jet_FlavorPhys, &b_Jet_FlavorPhys);
   fChain->SetBranchAddress("Jet_BTag", &Jet_BTag, &b_Jet_BTag);
   fChain->SetBranchAddress("Jet_BTagAlgo", &Jet_BTagAlgo, &b_Jet_BTagAlgo);
   fChain->SetBranchAddress("Jet_BTagPhys", &Jet_BTagPhys, &b_Jet_BTagPhys);
   fChain->SetBranchAddress("Jet_TauTag", &Jet_TauTag, &b_Jet_TauTag);
   fChain->SetBranchAddress("Jet_Charge", &Jet_Charge, &b_Jet_Charge);
   fChain->SetBranchAddress("Jet_EhadOverEem", &Jet_EhadOverEem, &b_Jet_EhadOverEem);
   fChain->SetBranchAddress("Jet_NCharged", &Jet_NCharged, &b_Jet_NCharged);
   fChain->SetBranchAddress("Jet_NNeutrals", &Jet_NNeutrals, &b_Jet_NNeutrals);
   fChain->SetBranchAddress("Jet_Beta", &Jet_Beta, &b_Jet_Beta);
   fChain->SetBranchAddress("Jet_BetaStar", &Jet_BetaStar, &b_Jet_BetaStar);
   fChain->SetBranchAddress("Jet_MeanSqDeltaR", &Jet_MeanSqDeltaR, &b_Jet_MeanSqDeltaR);
   fChain->SetBranchAddress("Jet_PTD", &Jet_PTD, &b_Jet_PTD);
   fChain->SetBranchAddress("GenJet_size", &GenJet_size, &b_GenJet_size);
   fChain->SetBranchAddress("GenJet_PT", &GenJet_PT, &b_GenJet_PT);
   fChain->SetBranchAddress("GenJet_Eta", &GenJet_Eta, &b_GenJet_Eta);
   fChain->SetBranchAddress("GenJet_Phi", &GenJet_Phi, &b_GenJet_Phi);
   fChain->SetBranchAddress("GenJet_T", &GenJet_T, &b_GenJet_T);
   fChain->SetBranchAddress("GenJet_Mass", &GenJet_Mass, &b_GenJet_Mass);
   fChain->SetBranchAddress("GenJet_DeltaEta", &GenJet_DeltaEta, &b_GenJet_DeltaEta);
   fChain->SetBranchAddress("GenJet_DeltaPhi", &GenJet_DeltaPhi, &b_GenJet_DeltaPhi);
   fChain->SetBranchAddress("GenJet_Flavor", &GenJet_Flavor, &b_GenJet_Flavor);
   fChain->SetBranchAddress("GenJet_FlavorAlgo", &GenJet_FlavorAlgo, &b_GenJet_FlavorAlgo);
   fChain->SetBranchAddress("GenJet_FlavorPhys", &GenJet_FlavorPhys, &b_GenJet_FlavorPhys);
   fChain->SetBranchAddress("GenJet_BTag", &GenJet_BTag, &b_GenJet_BTag);
   fChain->SetBranchAddress("GenJet_BTagAlgo", &GenJet_BTagAlgo, &b_GenJet_BTagAlgo);
   fChain->SetBranchAddress("GenJet_BTagPhys", &GenJet_BTagPhys, &b_GenJet_BTagPhys);
   fChain->SetBranchAddress("GenJet_TauTag", &GenJet_TauTag, &b_GenJet_TauTag);
   fChain->SetBranchAddress("GenJet_Charge", &GenJet_Charge, &b_GenJet_Charge);
   fChain->SetBranchAddress("GenJet_EhadOverEem", &GenJet_EhadOverEem, &b_GenJet_EhadOverEem);
   fChain->SetBranchAddress("GenJet_NCharged", &GenJet_NCharged, &b_GenJet_NCharged);
   fChain->SetBranchAddress("GenJet_NNeutrals", &GenJet_NNeutrals, &b_GenJet_NNeutrals);
   fChain->SetBranchAddress("GenJet_Beta", &GenJet_Beta, &b_GenJet_Beta);
   fChain->SetBranchAddress("GenJet_BetaStar", &GenJet_BetaStar, &b_GenJet_BetaStar);
   fChain->SetBranchAddress("GenJet_MeanSqDeltaR", &GenJet_MeanSqDeltaR, &b_GenJet_MeanSqDeltaR);
   fChain->SetBranchAddress("GenJet_PTD", &GenJet_PTD, &b_GenJet_PTD);
   fChain->SetBranchAddress("Track_size", &Track_size, &b_Track_size);
   fChain->SetBranchAddress("Track_PID", &Track_PID, &b_Track_PID);
   fChain->SetBranchAddress("Track_Charge", &Track_Charge, &b_Track_Charge);
   fChain->SetBranchAddress("Track_PT", &Track_PT, &b_Track_PT);
   fChain->SetBranchAddress("Track_Eta", &Track_Eta, &b_Track_Eta);
   fChain->SetBranchAddress("Track_Phi", &Track_Phi, &b_Track_Phi);
   fChain->SetBranchAddress("Track_X", &Track_X, &b_Track_X);
   fChain->SetBranchAddress("Track_Y", &Track_Y, &b_Track_Y);
   fChain->SetBranchAddress("Track_Z", &Track_Z, &b_Track_Z);
   fChain->SetBranchAddress("Track_D0", &Track_D0, &b_Track_D0);
   fChain->SetBranchAddress("Track_DZ", &Track_DZ, &b_Track_DZ);
   fChain->SetBranchAddress("KaonShort_size", &KaonShort_size, &b_KaonShort_size);
   fChain->SetBranchAddress("KaonShort_PID", &KaonShort_PID, &b_KaonShort_PID);
   fChain->SetBranchAddress("KaonShort_PT", &KaonShort_PT, &b_KaonShort_PT);
   fChain->SetBranchAddress("KaonShort_Eta", &KaonShort_Eta, &b_KaonShort_Eta);
   fChain->SetBranchAddress("KaonShort_Phi", &KaonShort_Phi, &b_KaonShort_Phi);
   fChain->SetBranchAddress("KaonShortDaughter1_size", &KaonShortDaughter1_size, &b_KaonShortDaughter1_size);
   fChain->SetBranchAddress("KaonShortDaughter1_PID", &KaonShortDaughter1_PID, &b_KaonShortDaughter1_PID);
   fChain->SetBranchAddress("KaonShortDaughter1_PT", &KaonShortDaughter1_PT, &b_KaonShortDaughter1_PT);
   fChain->SetBranchAddress("KaonShortDaughter1_Eta", &KaonShortDaughter1_Eta, &b_KaonShortDaughter1_Eta);
   fChain->SetBranchAddress("KaonShortDaughter1_Phi", &KaonShortDaughter1_Phi, &b_KaonShortDaughter1_Phi);
   fChain->SetBranchAddress("KaonShortDaughter2_size", &KaonShortDaughter2_size, &b_KaonShortDaughter2_size);
   fChain->SetBranchAddress("KaonShortDaughter2_PID", &KaonShortDaughter2_PID, &b_KaonShortDaughter2_PID);
   fChain->SetBranchAddress("KaonShortDaughter2_PT", &KaonShortDaughter2_PT, &b_KaonShortDaughter2_PT);
   fChain->SetBranchAddress("KaonShortDaughter2_Eta", &KaonShortDaughter2_Eta, &b_KaonShortDaughter2_Eta);
   fChain->SetBranchAddress("KaonShortDaughter2_Phi", &KaonShortDaughter2_Phi, &b_KaonShortDaughter2_Phi);
   fChain->SetBranchAddress("Lambda_size", &Lambda_size, &b_Lambda_size);
   fChain->SetBranchAddress("Lambda_PID", &Lambda_PID, &b_Lambda_PID);
   fChain->SetBranchAddress("Lambda_PT", &Lambda_PT, &b_Lambda_PT);
   fChain->SetBranchAddress("Lambda_Eta", &Lambda_Eta, &b_Lambda_Eta);
   fChain->SetBranchAddress("Lambda_Phi", &Lambda_Phi, &b_Lambda_Phi);
   fChain->SetBranchAddress("LambdaDaughter1_size", &LambdaDaughter1_size, &b_LambdaDaughter1_size);
   fChain->SetBranchAddress("LambdaDaughter1_PID", &LambdaDaughter1_PID, &b_LambdaDaughter1_PID);
   fChain->SetBranchAddress("LambdaDaughter1_PT", &LambdaDaughter1_PT, &b_LambdaDaughter1_PT);
   fChain->SetBranchAddress("LambdaDaughter1_Eta", &LambdaDaughter1_Eta, &b_LambdaDaughter1_Eta);
   fChain->SetBranchAddress("LambdaDaughter1_Phi", &LambdaDaughter1_Phi, &b_LambdaDaughter1_Phi);
   fChain->SetBranchAddress("LambdaDaughter2_size", &LambdaDaughter2_size, &b_LambdaDaughter2_size);
   fChain->SetBranchAddress("LambdaDaughter2_PID", &LambdaDaughter2_PID, &b_LambdaDaughter2_PID);
   fChain->SetBranchAddress("LambdaDaughter2_PT", &LambdaDaughter2_PT, &b_LambdaDaughter2_PT);
   fChain->SetBranchAddress("LambdaDaughter2_Eta", &LambdaDaughter2_Eta, &b_LambdaDaughter2_Eta);
   fChain->SetBranchAddress("LambdaDaughter2_Phi", &LambdaDaughter2_Phi, &b_LambdaDaughter2_Phi);
   fChain->SetBranchAddress("Electron_size", &Electron_size, &b_Electron_size);
   fChain->SetBranchAddress("Electron_PT", &Electron_PT, &b_Electron_PT);
   fChain->SetBranchAddress("Electron_Eta", &Electron_Eta, &b_Electron_Eta);
   fChain->SetBranchAddress("Electron_Phi", &Electron_Phi, &b_Electron_Phi);
   fChain->SetBranchAddress("Electron_T", &Electron_T, &b_Electron_T);
   fChain->SetBranchAddress("Electron_Charge", &Electron_Charge, &b_Electron_Charge);
   fChain->SetBranchAddress("Electron_EhadOverEem", &Electron_EhadOverEem, &b_Electron_EhadOverEem);
   fChain->SetBranchAddress("Electron_IsolationVar", &Electron_IsolationVar, &b_Electron_IsolationVar);
   fChain->SetBranchAddress("Electron_IsolationVarRhoCorr", &Electron_IsolationVarRhoCorr, &b_Electron_IsolationVarRhoCorr);
   fChain->SetBranchAddress("Electron_SumPtCharged", &Electron_SumPtCharged, &b_Electron_SumPtCharged);
   fChain->SetBranchAddress("Electron_SumPtNeutral", &Electron_SumPtNeutral, &b_Electron_SumPtNeutral);
   fChain->SetBranchAddress("Electron_SumPtChargedPU", &Electron_SumPtChargedPU, &b_Electron_SumPtChargedPU);
   fChain->SetBranchAddress("Electron_SumPt", &Electron_SumPt, &b_Electron_SumPt);
   fChain->SetBranchAddress("Photon_size", &Photon_size, &b_Photon_size);
   fChain->SetBranchAddress("Photon_PT", &Photon_PT, &b_Photon_PT);
   fChain->SetBranchAddress("Photon_Eta", &Photon_Eta, &b_Photon_Eta);
   fChain->SetBranchAddress("Photon_Phi", &Photon_Phi, &b_Photon_Phi);
   fChain->SetBranchAddress("Photon_E", &Photon_E, &b_Photon_E);
   fChain->SetBranchAddress("Photon_T", &Photon_T, &b_Photon_T);
   fChain->SetBranchAddress("Photon_EhadOverEem", &Photon_EhadOverEem, &b_Photon_EhadOverEem);
   fChain->SetBranchAddress("Photon_IsolationVar", &Photon_IsolationVar, &b_Photon_IsolationVar);
   fChain->SetBranchAddress("Photon_IsolationVarRhoCorr", &Photon_IsolationVarRhoCorr, &b_Photon_IsolationVarRhoCorr);
   fChain->SetBranchAddress("Photon_SumPtCharged", &Photon_SumPtCharged, &b_Photon_SumPtCharged);
   fChain->SetBranchAddress("Photon_SumPtNeutral", &Photon_SumPtNeutral, &b_Photon_SumPtNeutral);
   fChain->SetBranchAddress("Photon_SumPtChargedPU", &Photon_SumPtChargedPU, &b_Photon_SumPtChargedPU);
   fChain->SetBranchAddress("Photon_SumPt", &Photon_SumPt, &b_Photon_SumPt);
   fChain->SetBranchAddress("Muon_size", &Muon_size, &b_Muon_size);
   fChain->SetBranchAddress("Muon_PT", &Muon_PT, &b_Muon_PT);
   fChain->SetBranchAddress("Muon_Eta", &Muon_Eta, &b_Muon_Eta);
   fChain->SetBranchAddress("Muon_Phi", &Muon_Phi, &b_Muon_Phi);
   fChain->SetBranchAddress("Muon_T", &Muon_T, &b_Muon_T);
   fChain->SetBranchAddress("Muon_Charge", &Muon_Charge, &b_Muon_Charge);
   fChain->SetBranchAddress("Muon_IsolationVar", &Muon_IsolationVar, &b_Muon_IsolationVar);
   fChain->SetBranchAddress("Muon_IsolationVarRhoCorr", &Muon_IsolationVarRhoCorr, &b_Muon_IsolationVarRhoCorr);
   fChain->SetBranchAddress("Muon_SumPtCharged", &Muon_SumPtCharged, &b_Muon_SumPtCharged);
   fChain->SetBranchAddress("Muon_SumPtNeutral", &Muon_SumPtNeutral, &b_Muon_SumPtNeutral);
   fChain->SetBranchAddress("Muon_SumPtChargedPU", &Muon_SumPtChargedPU, &b_Muon_SumPtChargedPU);
   fChain->SetBranchAddress("Muon_SumPt", &Muon_SumPt, &b_Muon_SumPt);
   fChain->SetBranchAddress("MissingET_MET", &MissingET_MET, &b_MissingET_MET);
   fChain->SetBranchAddress("MissingET_Eta", &MissingET_Eta, &b_MissingET_Eta);
   fChain->SetBranchAddress("MissingET_Phi", &MissingET_Phi, &b_MissingET_Phi);
   fChain->SetBranchAddress("ScalarHT_HT", &ScalarHT_HT, &b_ScalarHT_HT);

   Notify();
}

Bool_t fullset::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fullset::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t fullset::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef fullset_cxx
