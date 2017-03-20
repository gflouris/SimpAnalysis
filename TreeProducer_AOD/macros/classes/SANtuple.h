//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar  6 16:19:12 2017 by ROOT version 6.06/01
// from TTree SimpAnalysis/tree
// found on file: dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_PUMoriond17_AOD/170304_213629/0000/QCD_PUMoriond17_AOD_test_67.root
//////////////////////////////////////////////////////////

#ifndef SANtuple_h
#define SANtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class SANtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nEvent;
   Int_t           nRun;
   Int_t           nLumi;
   Int_t           vtx_N;
   Int_t           vtx_N_stored;
   Double_t        vtx_normalizedChi2[3];   //[vtx_N_stored]
   Int_t           vtx_ndof[3];   //[vtx_N_stored]
   Int_t           vtx_nTracks[3];   //[vtx_N_stored]
   Double_t        vtx_d0[3];   //[vtx_N_stored]
   Double_t        vtx_x[3];   //[vtx_N_stored]
   Double_t        vtx_y[3];   //[vtx_N_stored]
   Double_t        vtx_z[3];   //[vtx_N_stored]
   Int_t           nTrack_stored;
   Int_t           nTrack;
   Double_t        track_pt[10];   //[nTrack_stored]
   Double_t        track_eta[10];   //[nTrack_stored]
   Double_t        track_phi[10];   //[nTrack_stored]
   Double_t        track_normalizedChi2[10];   //[nTrack_stored]
   Int_t           track_ndof[10];   //[nTrack_stored]
   Double_t        track_ptError[10];   //[nTrack_stored]
   Double_t        track_dzError[10];   //[nTrack_stored]
   Double_t        track_dz[10];   //[nTrack_stored]
   Int_t           track_fromPV[10];   //[nTrack_stored]
   Int_t           track_purity[10];   //[nTrack_stored]
   Int_t           track_nhits[10];   //[nTrack_stored]
   Int_t           track_nPixHits[10];   //[nTrack_stored]
   Double_t        track_d0[10];   //[nTrack_stored]
   Double_t        track_dxy[10];   //[nTrack_stored]
   Int_t           nJet_stored;
   Int_t           nJet;
   Double_t        jetArea[8];   //[nJet_stored]
   Double_t        jet_vx[8];   //[nJet_stored]
   Double_t        jet_vy[8];   //[nJet_stored]
   Double_t        jet_vz[8];   //[nJet_stored]
   Double_t        jet_eta[8];   //[nJet_stored]
   Double_t        jet_phi[8];   //[nJet_stored]
   Double_t        jet_pt[8];   //[nJet_stored]
   Double_t        jet_e[8];   //[nJet_stored]
   Double_t        jet_m[8];   //[nJet_stored]
   Int_t           jet_mult_ch[8];   //[nJet_stored]
   Int_t           jet_mult_mu[8];   //[nJet_stored]
   Int_t           jet_mult_ne[8];   //[nJet_stored]
   Double_t        jet_efrac_ne_Had[8];   //[nJet_stored]
   Double_t        jet_efrac_ne_EM[8];   //[nJet_stored]
   Double_t        jet_efrac_ch_Had[8];   //[nJet_stored]
   Double_t        jet_efrac_ch_EM[8];   //[nJet_stored]
   Double_t        jet_efrac_ch_Mu[8];   //[nJet_stored]
   Double_t        jet_unc[8];   //[nJet_stored]
   Double_t        _jet_ptCor_up[8];   //[nJet_stored]
   Double_t        _jet_ptCor_down[8];   //[nJet_stored]
   Int_t           nGenJet_stored;
   Int_t           nGenJet;
   Double_t        genjetArea[4];   //[nGenJet_stored]
   Double_t        genjet_vx[4];   //[nGenJet_stored]
   Double_t        genjet_vy[4];   //[nGenJet_stored]
   Double_t        genjet_vz[4];   //[nGenJet_stored]
   Double_t        genjet_eta[4];   //[nGenJet_stored]
   Double_t        genjet_phi[4];   //[nGenJet_stored]
   Double_t        genjet_pt[4];   //[nGenJet_stored]
   Double_t        genjet_e[4];   //[nGenJet_stored]
   Double_t        genjet_m[4];   //[nGenJet_stored]
   Double_t        genjet_efrac_ch[4];   //[nGenJet_stored]
   Int_t           nPhoton_stored;
   Double_t        photon_eta[4];   //[nPhoton_stored]
   Double_t        photon_phi[4];   //[nPhoton_stored]
   Double_t        photon_pt[4];   //[nPhoton_stored]
   Int_t           photon_passLooseId[4];   //[nPhoton_stored]
   Int_t           photon_passMediumId[4];   //[nPhoton_stored]
   Int_t           photon_passTightId[4];   //[nPhoton_stored]
   Double_t        MET;
   Double_t        MET_phi;
   Int_t           HLT_DiCentralPFJet170_CFMax0p1;
   Int_t           HLT_DiCentralPFJet220_CFMax0p3;
   Int_t           HLT_DiCentralPFJet330_CFMax0p5;
   Int_t           HLT_DiCentralPFJet430;
   Int_t           HLT_DiCentralPFJet170;
   Int_t           HLT_SingleCentralPFJet170_CFMax0p1;
   Double_t        pswgt_dijet_170;
   Double_t        pswgt_singlejet_170_0p1;
   Int_t           Flag_HBHENoiseFilter;
   Int_t           Flag_HBHENoiseIsoFilter;
   Int_t           Flag_EcalDeadCellTriggerPrimitiveFilter;
   Int_t           Flag_goodVertices;
   Int_t           Flag_eeBadScFilter;
   Int_t           Flag_globalTightHalo2016Filter;

   // List of branches
   TBranch        *b_nEvent;   //!
   TBranch        *b_nRun;   //!
   TBranch        *b_nLumi;   //!
   TBranch        *b_vtx_N;   //!
   TBranch        *b_vtx_N_stored;   //!
   TBranch        *b_vtx_normalizedChi2;   //!
   TBranch        *b_vtx_ndof;   //!
   TBranch        *b_vtx_nTracks;   //!
   TBranch        *b_vtx_d0;   //!
   TBranch        *b_vtx_x;   //!
   TBranch        *b_vtx_y;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_nTrack_stored;   //!
   TBranch        *b_nTrack;   //!
   TBranch        *b_track_pt;   //!
   TBranch        *b_track_eta;   //!
   TBranch        *b_track_phi;   //!
   TBranch        *b_track_normalizedChi2;   //!
   TBranch        *b_track_ndof;   //!
   TBranch        *b_track_ptError;   //!
   TBranch        *b_track_dzError;   //!
   TBranch        *b_track_dz;   //!
   TBranch        *b_track_fromPV;   //!
   TBranch        *b_track_purity;   //!
   TBranch        *b_track_nhits;   //!
   TBranch        *b_track_nPixHits;   //!
   TBranch        *b_track_d0;   //!
   TBranch        *b_track_dxy;   //!
   TBranch        *b_nJet_stored;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_jetArea;   //!
   TBranch        *b_jet_vx;   //!
   TBranch        *b_jet_vy;   //!
   TBranch        *b_jet_vz;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_e;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_mult_ch;   //!
   TBranch        *b_jet_mult_mu;   //!
   TBranch        *b_jet_mult_ne;   //!
   TBranch        *b_jet_efrac_ne_Had;   //!
   TBranch        *b_jet_efrac_ne_EM;   //!
   TBranch        *b_jet_efrac_ch_Had;   //!
   TBranch        *b_jet_efrac_ch_EM;   //!
   TBranch        *b_jet_efrac_ch_Mu;   //!
   TBranch        *b_jet_unc;   //!
   TBranch        *b__jet_ptCor_up;   //!
   TBranch        *b__jet_ptCor_down;   //!
   TBranch        *b_nGenJet_stored;   //!
   TBranch        *b_nGenJet;   //!
   TBranch        *b_genjetArea;   //!
   TBranch        *b_genjet_vx;   //!
   TBranch        *b_genjet_vy;   //!
   TBranch        *b_genjet_vz;   //!
   TBranch        *b_genjet_eta;   //!
   TBranch        *b_genjet_phi;   //!
   TBranch        *b_genjet_pt;   //!
   TBranch        *b_genjet_e;   //!
   TBranch        *b_genjet_m;   //!
   TBranch        *b_genjet_efrac_ch;   //!
   TBranch        *b_nPhoton_stored;   //!
   TBranch        *b_photon_eta;   //!
   TBranch        *b_photon_phi;   //!
   TBranch        *b_photon_pt;   //!
   TBranch        *b_photon_passLooseId;   //!
   TBranch        *b_photon_passMediumId;   //!
   TBranch        *b_photon_passTightId;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_HLT_DiCentralPFJet170_CFMax0p1;   //!
   TBranch        *b_HLT_DiCentralPFJet220_CFMax0p3;   //!
   TBranch        *b_HLT_DiCentralPFJet330_CFMax0p5;   //!
   TBranch        *b_HLT_DiCentralPFJet430;   //!
   TBranch        *b_HLT_DiCentralPFJet170;   //!
   TBranch        *b_HLT_SingleCentralPFJet170_CFMax0p1;   //!
   TBranch        *b_pswgt_dijet_170;   //!
   TBranch        *b_pswgt_singlejet_170_0p1;   //!
   TBranch        *b_Flag_HBHENoiseFilter;   //!
   TBranch        *b_Flag_HBHENoiseIsoFilter;   //!
   TBranch        *b_Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_Flag_goodVertices;   //!
   TBranch        *b_Flag_eeBadScFilter;   //!
   TBranch        *b_Flag_globalTightHalo2016Filter;   //!

   SANtuple(TTree *tree=0);
   virtual ~SANtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
//   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


SANtuple::SANtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   //Init(tree);
}

SANtuple::~SANtuple()
{
   if (!fChain) return;
 //  delete fChain->GetCurrentFile();
}

Int_t SANtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SANtuple::LoadTree(Long64_t entry)
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

void SANtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nEvent", &nEvent, &b_nEvent);
   fChain->SetBranchAddress("nRun", &nRun, &b_nRun);
   fChain->SetBranchAddress("nLumi", &nLumi, &b_nLumi);
   fChain->SetBranchAddress("vtx_N", &vtx_N, &b_vtx_N);
   fChain->SetBranchAddress("vtx_N_stored", &vtx_N_stored, &b_vtx_N_stored);
   fChain->SetBranchAddress("vtx_normalizedChi2", vtx_normalizedChi2, &b_vtx_normalizedChi2);
   fChain->SetBranchAddress("vtx_ndof", vtx_ndof, &b_vtx_ndof);
   fChain->SetBranchAddress("vtx_nTracks", vtx_nTracks, &b_vtx_nTracks);
   fChain->SetBranchAddress("vtx_d0", vtx_d0, &b_vtx_d0);
   fChain->SetBranchAddress("vtx_x", vtx_x, &b_vtx_x);
   fChain->SetBranchAddress("vtx_y", vtx_y, &b_vtx_y);
   fChain->SetBranchAddress("vtx_z", vtx_z, &b_vtx_z);
   fChain->SetBranchAddress("nTrack_stored", &nTrack_stored, &b_nTrack_stored);
   fChain->SetBranchAddress("nTrack", &nTrack, &b_nTrack);
   fChain->SetBranchAddress("track_pt", track_pt, &b_track_pt);
   fChain->SetBranchAddress("track_eta", track_eta, &b_track_eta);
   fChain->SetBranchAddress("track_phi", track_phi, &b_track_phi);
   fChain->SetBranchAddress("track_normalizedChi2", track_normalizedChi2, &b_track_normalizedChi2);
   fChain->SetBranchAddress("track_ndof", track_ndof, &b_track_ndof);
   fChain->SetBranchAddress("track_ptError", track_ptError, &b_track_ptError);
   fChain->SetBranchAddress("track_dzError", track_dzError, &b_track_dzError);
   fChain->SetBranchAddress("track_dz", track_dz, &b_track_dz);
   fChain->SetBranchAddress("track_fromPV", track_fromPV, &b_track_fromPV);
   fChain->SetBranchAddress("track_purity", track_purity, &b_track_purity);
   fChain->SetBranchAddress("track_nhits", track_nhits, &b_track_nhits);
   fChain->SetBranchAddress("track_nPixHits", track_nPixHits, &b_track_nPixHits);
   fChain->SetBranchAddress("track_d0", track_d0, &b_track_d0);
   fChain->SetBranchAddress("track_dxy", track_dxy, &b_track_dxy);
   fChain->SetBranchAddress("nJet_stored", &nJet_stored, &b_nJet_stored);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jetArea", jetArea, &b_jetArea);
   fChain->SetBranchAddress("jet_vx", jet_vx, &b_jet_vx);
   fChain->SetBranchAddress("jet_vy", jet_vy, &b_jet_vy);
   fChain->SetBranchAddress("jet_vz", jet_vz, &b_jet_vz);
   fChain->SetBranchAddress("jet_eta", jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_e", jet_e, &b_jet_e);
   fChain->SetBranchAddress("jet_m", jet_m, &b_jet_m);
   fChain->SetBranchAddress("jet_mult_ch", jet_mult_ch, &b_jet_mult_ch);
   fChain->SetBranchAddress("jet_mult_mu", jet_mult_mu, &b_jet_mult_mu);
   fChain->SetBranchAddress("jet_mult_ne", jet_mult_ne, &b_jet_mult_ne);
   fChain->SetBranchAddress("jet_efrac_ne_Had", jet_efrac_ne_Had, &b_jet_efrac_ne_Had);
   fChain->SetBranchAddress("jet_efrac_ne_EM", jet_efrac_ne_EM, &b_jet_efrac_ne_EM);
   fChain->SetBranchAddress("jet_efrac_ch_Had", jet_efrac_ch_Had, &b_jet_efrac_ch_Had);
   fChain->SetBranchAddress("jet_efrac_ch_EM", jet_efrac_ch_EM, &b_jet_efrac_ch_EM);
   fChain->SetBranchAddress("jet_efrac_ch_Mu", jet_efrac_ch_Mu, &b_jet_efrac_ch_Mu);
   fChain->SetBranchAddress("jet_unc", jet_unc, &b_jet_unc);
   fChain->SetBranchAddress("_jet_ptCor_up", _jet_ptCor_up, &b__jet_ptCor_up);
   fChain->SetBranchAddress("_jet_ptCor_down", _jet_ptCor_down, &b__jet_ptCor_down);
   fChain->SetBranchAddress("nGenJet_stored", &nGenJet_stored, &b_nGenJet_stored);
   fChain->SetBranchAddress("nGenJet", &nGenJet, &b_nGenJet);
   fChain->SetBranchAddress("genjetArea", genjetArea, &b_genjetArea);
   fChain->SetBranchAddress("genjet_vx", genjet_vx, &b_genjet_vx);
   fChain->SetBranchAddress("genjet_vy", genjet_vy, &b_genjet_vy);
   fChain->SetBranchAddress("genjet_vz", genjet_vz, &b_genjet_vz);
   fChain->SetBranchAddress("genjet_eta", genjet_eta, &b_genjet_eta);
   fChain->SetBranchAddress("genjet_phi", genjet_phi, &b_genjet_phi);
   fChain->SetBranchAddress("genjet_pt", genjet_pt, &b_genjet_pt);
   fChain->SetBranchAddress("genjet_e", genjet_e, &b_genjet_e);
   fChain->SetBranchAddress("genjet_m", genjet_m, &b_genjet_m);
   fChain->SetBranchAddress("genjet_efrac_ch", genjet_efrac_ch, &b_genjet_efrac_ch);
   fChain->SetBranchAddress("nPhoton_stored", &nPhoton_stored, &b_nPhoton_stored);
   fChain->SetBranchAddress("photon_eta", photon_eta, &b_photon_eta);
   fChain->SetBranchAddress("photon_phi", photon_phi, &b_photon_phi);
   fChain->SetBranchAddress("photon_pt", photon_pt, &b_photon_pt);
   fChain->SetBranchAddress("photon_passLooseId", photon_passLooseId, &b_photon_passLooseId);
   fChain->SetBranchAddress("photon_passMediumId", photon_passMediumId, &b_photon_passMediumId);
   fChain->SetBranchAddress("photon_passTightId", photon_passTightId, &b_photon_passTightId);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("HLT_DiCentralPFJet170_CFMax0p1", &HLT_DiCentralPFJet170_CFMax0p1, &b_HLT_DiCentralPFJet170_CFMax0p1);
   fChain->SetBranchAddress("HLT_DiCentralPFJet220_CFMax0p3", &HLT_DiCentralPFJet220_CFMax0p3, &b_HLT_DiCentralPFJet220_CFMax0p3);
   fChain->SetBranchAddress("HLT_DiCentralPFJet330_CFMax0p5", &HLT_DiCentralPFJet330_CFMax0p5, &b_HLT_DiCentralPFJet330_CFMax0p5);
   fChain->SetBranchAddress("HLT_DiCentralPFJet430", &HLT_DiCentralPFJet430, &b_HLT_DiCentralPFJet430);
   fChain->SetBranchAddress("HLT_DiCentralPFJet170", &HLT_DiCentralPFJet170, &b_HLT_DiCentralPFJet170);
   fChain->SetBranchAddress("HLT_SingleCentralPFJet170_CFMax0p1", &HLT_SingleCentralPFJet170_CFMax0p1, &b_HLT_SingleCentralPFJet170_CFMax0p1);
   fChain->SetBranchAddress("pswgt_dijet_170", &pswgt_dijet_170, &b_pswgt_dijet_170);
   fChain->SetBranchAddress("pswgt_singlejet_170_0p1", &pswgt_singlejet_170_0p1, &b_pswgt_singlejet_170_0p1);
   fChain->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter, &b_Flag_HBHENoiseFilter);
   fChain->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter, &b_Flag_HBHENoiseIsoFilter);
   fChain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, &b_Flag_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices, &b_Flag_goodVertices);
   fChain->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter, &b_Flag_eeBadScFilter);
   fChain->SetBranchAddress("Flag_globalTightHalo2016Filter", &Flag_globalTightHalo2016Filter, &b_Flag_globalTightHalo2016Filter);
   Notify();
}

Bool_t SANtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SANtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SANtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SANtuple_cxx
