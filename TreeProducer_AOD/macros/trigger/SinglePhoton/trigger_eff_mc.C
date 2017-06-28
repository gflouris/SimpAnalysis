#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TDirectoryFile.h"
#include "TDirectory.h"
#include "TCut.h"
#include "TBranch.h"
#include "TString.h"
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include <algorithm>
#include "TH1F.h"
#include "TMath.h"

#include <vector>


#include "../../classes/SANtuple.h"

void bookHistos(std::map<string, TH1F*>& histos_1d){
    //
    //
    // histos_1d["h_pt_num_330"]  = new TH1F("h_pt_num_330","h_pt_num_330",100,0,2000);
    // histos_1d["h_pt_den_330"]     = new TH1F("h_pt_den_330","h_pt_den_330",100,0,2000);
    //
    // histos_1d["h_pt_num_170"]  = new TH1F("h_pt_num_170","h_pt_num_170",100,0,2000);
    // histos_1d["h_pt_den_170"]     = new TH1F("h_pt_den_170","h_pt_den_170",100,0,2000);
    // histos_1d["h_pt_num_170_chf1"]  = new TH1F("h_pt_num_170_chf1","h_pt_num_170_chf1",100,0,2000);
    // histos_1d["h_pt_den_170_chf1"]     = new TH1F("h_pt_den_170_chf1","h_pt_den_170_chf1",100,0,2000);
    // histos_1d["h_pt_num_170_chfmax"]  = new TH1F("h_pt_num_170_chfmax","h_pt_num_170_chfmax",100,0,2000);
    // histos_1d["h_pt_den_170_chfmax"]     = new TH1F("h_pt_den_170_chfmax","h_pt_den_170_chfmax",100,0,2000);
    //
    //
    // histos_1d["h_chf330_den"]  = new TH1F("h_chf330_den","h_chf330_den",100,0,1);
    // histos_1d["h_chf170_den"]  = new TH1F("h_chf170_den","h_chf170_den",100,0,1);
    // histos_1d["h_chf330_num"]  = new TH1F("h_chf330_num","h_chf330_num",100,0,1);
    // histos_1d["h_chf170_num"]  = new TH1F("h_chf170_num","h_chf170_num",100,0,1);
    //
    // histos_1d["h_chf170_Dijet430_den"]  = new TH1F("h_chf170_Dijet430_den","h_chf170_Dijet430_den",100,0,1);
    // histos_1d["h_chf170_Dijet430_num"]  = new TH1F("h_chf170_Dijet430_num","h_chf330_Dijet430_num",100,0,1);
    //
    //
    // histos_1d["h_pt0_HLT_Dijet170"]            = new TH1F("h_pt0_HLT_Dijet170","h_pt0_HLT_Dijet170",100,0,2000);
    // histos_1d["h_pt1_HLT_Dijet170"]            = new TH1F("h_pt1_HLT_Dijet170","h_pt1_HLT_Dijet170",100,0,2000);
    // histos_1d["h_chf0_HLT_Dijet170"]            = new TH1F("h_chf0_HLT_Dijet170","h_chf0_HLT_Dijet170",100,0,1);
    // histos_1d["h_chf1_HLT_Dijet170"]            = new TH1F("h_chf1_HLT_Dijet170","h_chf1_HLT_Dijet170",100,0,1);
    //
    // histos_1d["h_pt0_HLT_Dijet430"]         = new TH1F("h_pt_HLT_Dijet430","h_pt_HLT_Dijet430",100,0,2000);
    // histos_1d["h_pt1_HLT_Dijet430"]        = new TH1F("h_pt1_HLT_Dijet430","h_pt1_HLT_Dijet430",100,0,2000);
    // histos_1d["h_chf0_HLT_Dijet430"]         = new TH1F("h_chf0_HLT_Dijet430","h_chf0_HLT_Dijet430",100,0,1);
    // histos_1d["h_chf1_HLT_Dijet430"]         = new TH1F("h_chf1_HLT_Dijet430","h_chf1_HLT_Dijet430",100,0,1);
    //
    //
    // histos_1d["h_pt0_HLT_Dijet170_CF"]         = new TH1F("h_pt0_HLT_Dijet170_CF","h_pt0_HLT_Dijet170_CF",100,0,2000);
    // histos_1d["h_pt1_HLT_Dijet170_CF"]         = new TH1F("h_pt1_HLT_Dijet170_CF","h_pt1_HLT_Dijet170_CF",100,0,2000);
    // histos_1d["h_chf0_HLT_Dijet170_CF"]         = new TH1F("h_chf0_HLT_Dijet170_CF","h_chf0_HLT_Dijet170_CF",100,0,1);
    // histos_1d["h_chf1_HLT_Dijet170_CF"]         = new TH1F("h_chf1_HLT_Dijet170_CF","h_chf1_HLT_Dijet170_CF",100,0,1);
    //
    // histos_1d["h_pt0_HLT_Dijet330_CF"]         = new TH1F("h_pt0_HLT_Dijet330_CF","h_pt0_HLT_Dijet330_CF",100,0,2000);
    // histos_1d["h_pt1_HLT_Dijet330_CF"]         = new TH1F("h_pt1_HLT_Dijet330_CF","h_pt1_HLT_Dijet330_CF",100,0,2000);
    // histos_1d["h_chf0_HLT_Dijet330_CF"]         = new TH1F("h_chf0_HLT_Dijet330_CF","h_chf0_HLT_Dijet330_CF",100,0,1);
    // histos_1d["h_chf1_HLT_Dijet330_CF"]         = new TH1F("h_chf1_HLT_Dijet330_CF","h_chf1_HLT_Dijet330_CF",100,0,1);
    //
    //
    // histos_1d["h_pt0_HLT_Singlejet170_CF"]     = new TH1F("h_pt0_HLT_Singlejet170_CF","h_pt0_HLT_Singlejet170_CF",100,0,2000);
    // histos_1d["h_pt1_HLT_Singlejet170_CF"]     = new TH1F("h_pt1_HLT_Singlejet170_CF","h_pt1_HLT_Singlejet170_CF",100,0,2000);
    // histos_1d["h_chf0_HLT_Singlejet170_CF"]     = new TH1F("h_chf0_HLT_Singlejet170_CF","h_chf0_HLT_Singlejet170_CF",100,0,1);
    // histos_1d["h_chf1_HLT_Singlejet170_CF"]    = new TH1F("h_chf1_HLT_Singlejet170_CF","h_chf1_HLT_Singlejet170_CF",100,0,1);
    //
    // histos_1d["h_chf0_HLT_Dijet430_pt500"]     = new TH1F("h_chf0_HLT_Dijet430_pt500","h_chf0_HLT_Dijet430_pt500",100,0,1);
    // histos_1d["h_chf1_HLT_Dijet430_pt500"]     = new TH1F("h_chf1_HLT_Dijet430_pt500","h_chf1_HLT_Dijet430_pt500",100,0,1);
    // histos_1d["h_chf0_HLT_Singlejet170_CF_pt500"]     = new TH1F("h_chf0_HLT_Singlejet170_CF_pt500","h_chf0_HLT_Singlejet170_CF_pt500",100,0,1);
    // histos_1d["h_chf1_HLT_Singlejet170_CF_pt500"]     = new TH1F("h_chf1_HLT_Singlejet170_CF_pt500","h_chf1_HLT_Singlejet170_CF_pt500",100,0,1);
    //
    // histos_1d["h_chfmax_HLT_Singlejet170_CF_pt500"]     = new TH1F("h_chfmax_HLT_Singlejet170_CF_pt500","h_chfmax_HLT_Singlejet170_CF_pt500",100,0,1);
    // histos_1d["h_chfmax_HLT_Dijet430_pt500"]     = new TH1F("h_chfmax_HLT_Dijet430_pt500","h_chfmax_HLT_Dijet430_pt500",100,0,1);
    //


        histos_1d["h_pt0_HLT_Singlejet170"]     = new TH1F("h_pt0_HLT_Singlejet170","h_pt0_HLT_Singlejet170",100,0,2000);
        histos_1d["h_pt0_HLT_Singlejet170_Trigger"]     = new TH1F("h_pt0_HLT_Singlejet170_Trigger","h_pt0_HLT_Singlejet170_Trigger",100,0,2000);

        histos_1d["h_pt0_HLT_Singlejet170_Trigger_nop"]     = new TH1F("h_pt0_HLT_Singlejet170_Trigger_nop","h_pt0_HLT_Singlejet170_Trigger_nop",100,0,2000);
        histos_1d["h_pt0_HLT_Photon"]     = new TH1F("h_pt0_HLT_Photon","h_pt0_HLT_Photon",100,0,2000);

        histos_1d["h_chf_HLT_Singlejet170_Trigger"]     = new TH1F("h_chf_HLT_Singlejet170_Trigger","h_chf_HLT_Singlejet170_Trigger",100,0,1);
        histos_1d["h_chf_HLT_Singlejet170"]     = new TH1F("h_chf_HLT_Singlejet170","h_chf_HLT_Singlejet170",100,0,1);

}

void writeHistos(TFile*& outf, std::map<string, TH1F*> histos){
        outf->cd();
        for (std::pair<std::string, TH1F*> element : histos) {
                // Accessing KEY from element
                std::string word = element.first;
                // Accessing VALUE from element.
                TH1F* histo = element.second;
                histo->Write();
        }
}


int trigger_eff_mc(){


  std::map<string, TH1F*> histos_1d;
  bookHistos(histos_1d);


  int event_selection = 0;
  int event_selection01 = 0;

  int event_selection_trigDijet170 = 0;
  int event_selection_trigSingle170 = 0;
  int event_selection_trigDijet170CF = 0;
  int event_selection_trigSingleDijet170CF = 0;

  double event_selection_trigDijet170CF_cuts = 0;
  double event_selection_trigDijet330CF_cuts = 0;
  double event_selection_trigDijet170CF_cuts_nw = 0;
  double event_selection_trigDijet330CF_cuts_nw = 0;


  const int NSAMPLES = 4;



  double QCD_xsec[NSAMPLES] = {9235., 2298., 277.6, 93.47}; //PUMoriond17
  double lumi = 33.095*1000;
  string QCD_Samples[NSAMPLES] = {

"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_MC_GJets/170614_143807/0000/output_tree_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_MC_GJets/170614_144143/0000/output_tree_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_MC_GJets/170614_144227/0000/output_tree_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_MC_GJets/170614_144255/0000/output_tree_",

  };

  TChain *tchain_corr[NSAMPLES];
  for(int S=0; S<NSAMPLES; S++){

    cout<<"Reading sample "<<S<<endl;
    tchain_corr[S] = new TChain("treeCorr/SimpAnalysis");

    for(int i=1; i<80; i++){
     stringstream a;
     a<<QCD_Samples[S]<<i<<".root";
     tchain_corr[S]->Add((a.str()).c_str());
    }
   cout<<endl;

    SANtuple c_tree;
    c_tree.Init(tchain_corr[S]);

    Long64_t nentries = tchain_corr[S]->GetEntries();

    tchain_corr[S]->SetWeight(lumi*QCD_xsec[S]/nentries,"global");


  const double eta_cut = 2.0, dphi_cut= 2.0, pt_cut = 250.;

  double weight =  (lumi*QCD_xsec[S])/nentries;

   for (Long64_t i=0; i<nentries; i++) {


    c_tree.GetEntry(i);
    cout<<flush;
    if(i%100000 == 0) cout<<i<<" / "<<nentries<<"\r"<<flush;

      if(c_tree.vtx_N<=1) continue;
      if(c_tree.nJet<1) continue;

          struct pjobjects{
            double pt,eta,phi,chf;
            int id;
            bool operator<(const pjobjects& rhs) const { return pt > rhs.pt; }
          };

          vector<pjobjects> photons;
          photons.clear();

          for(int p=0; p<4; p++){
            if( c_tree.photon_passTightId[p]==1 )    {
              photons.push_back({c_tree.photon_pt[p], c_tree.photon_eta[p], c_tree.photon_phi[p], 0, p});
            }
          }
          std::sort(photons.begin(), photons.end());
          if (photons.size()==0) continue;

          vector<pjobjects> cleanjet, photonjet;

          if(c_tree.jet_efrac_ch_EM[0]>0.7) continue;

          for(int j=0; j<2; j++){
            if(c_tree.jet_pt[j]<1.) continue;
            double djet_chf    = c_tree.jet_efrac_ch_Had[j] + c_tree.jet_efrac_ch_EM[j] + c_tree.jet_efrac_ch_Mu[j];
            //cout<<"\t"<<c_tree.jet_pt[j]<<"\t"<<c_tree.jet_phi[j]<<"\t"<<c_tree.jet_eta[j]<<"\t"<<djet_chf<<endl;
            double mindR = 100;
            for(uint p=0; p<photons.size(); p++){
              double dR = deltaR(photons[p].eta, photons[p].phi, c_tree.jet_eta[j], c_tree.jet_phi[j]);
              if (dR<mindR) mindR= dR;
            }
            //cout<<mindR<<endl;
            if(mindR>0.1) cleanjet.push_back({c_tree.jet_pt[j], c_tree.jet_eta[j], c_tree.jet_phi[j], djet_chf, j});
            if(mindR<0.1) photonjet.push_back({c_tree.jet_pt[j], c_tree.jet_eta[j], c_tree.jet_phi[j], djet_chf, photons[j].id});
          }
          std::sort(photonjet.begin(), photonjet.end());

          if(photonjet.size()==0) continue;
          if(cleanjet.size()==0) continue;

          if(fabs(photonjet[0].eta)>2.0) continue;



          double deltajet_phi = deltaPhi(photonjet[0].phi, cleanjet[0].phi);
          if(fabs(deltajet_phi) > 2.0);
          else continue;


          if(c_tree.HLT_SingleCentralPFJet170_CFMax0p1 and photonjet[0].pt>250.) {
            histos_1d["h_pt0_HLT_Singlejet170_Trigger"]->Fill(photonjet[0].pt, weight);
            histos_1d["h_chf_HLT_Singlejet170_Trigger"]->Fill(photonjet[0].chf, weight);
            //if(photonjet[0].chf>0.8){
              // cout<<"----------------------"<<endl;
              // cout<<c_tree.nRun<<":"<<c_tree.nLumi<<":"<<c_tree.nEvent<<endl;
              // cout<<"\t"<<c_tree.jet_pt[0]<<"\t"<<c_tree.jet_phi[0]<<"\t"<<c_tree.jet_eta[0]<<"\t"<<c_tree.jet_efrac_ch_Had[0]<<"\t"<<c_tree.jet_efrac_ch_EM[0]<<"\t"<<c_tree.jet_efrac_ch_Mu[0]<<endl;
              //
              // for(uint p=0; p<4; p++){
              //     cout<<c_tree.photon_pt[p]<<"\t"<<c_tree.photon_phi[p]<<"\t"<<c_tree.photon_eta[p]<<"\t"<<c_tree.photon_passTightId[p]<<endl;
              // }
            //}
          }
          if( photonjet[0].pt>250. ) {
            histos_1d["h_pt0_HLT_Singlejet170"]->Fill(photonjet[0].pt,weight);
            histos_1d["h_chf_HLT_Singlejet170"]->Fill(photonjet[0].chf,weight);
          }


   }//for nentries
}//for SAMPLES
    TFile *fout = new TFile("Efficiency_MC_lowEMF.root", "RECREATE");
    fout->cd();
    writeHistos(fout, histos_1d);
    fout->Close();



    return 0;
}
