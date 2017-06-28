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


#include "../classes/SANtuple.h"

void bookHistos(std::map<string, TH1F*>& histos_1d){

    histos_1d["h_chfMax_Efficiency_HLT_170_0p1"]         = new TH1F("h_chfMax_Efficiency_HLT_170_0p1","h_chfMax_Efficiency_HLT_170_0p1",100,0,1);
    histos_1d["h_chfMax_Total_HLT_170_0p1"]        = new TH1F("h_chfMax_Total_HLT_170_0p1","h_chfMax_Total_HLT_170_0p1",100,0,1);

    histos_1d["h_pt1_Efficiency_HLT_170_0p1"]         = new TH1F("h_pt1_Efficiency_HLT_170_0p1","h_pt1_Efficiency_HLT_170_0p1",100,0,2000);
    histos_1d["h_pt1_Total_HLT_170_0p1"]        = new TH1F("h_pt1_Total_HLT_170_0p1","h_pt1_Total_HLT_170_0p1",100,0,2000);


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


int trigger_eff_wgt(){


  std::map<string, TH1F*> histos_1d;
  bookHistos(histos_1d);



  const int NSAMPLES = 6;

  double QCD_xsec[NSAMPLES] = {346400, 32010, 6842, 1203, 120.1, 25.40}; //PUMoriond17

  string QCD_Samples[NSAMPLES] = {
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT300To500_PUMoriond17_AOD/170403_170407/0000/QCD_PUMoriond17_AOD_pickevents_HT-1000To1500_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT500To700_PUMoriond17_AOD/170403_170430/0000/QCD_PUMoriond17_AOD_pickevents_HT-1000To1500_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT700To1000_PUMoriond17_AOD/170403_170456/0000/QCD_PUMoriond17_AOD_pickevents_HT-1000To1500_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1000To1500_PUMoriond17_AOD/170403_170522/0000/QCD_PUMoriond17_AOD_pickevents_HT-1000To1500_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1500To2000_PUMoriond17_AOD/170403_170547/0000/QCD_PUMoriond17_AOD_pickevents_HT-1000To1500_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_PUMoriond17_AOD/170403_170616/0000/QCD_PUMoriond17_AOD_pickevents_HT-1000To1500_"
 };
/////////
  TFile *fqcd_efficiency = TFile::Open("./Efficiency_MC_test.root");
  TH1F* num = (TH1F*)fqcd_efficiency->Get("h_chf0_HLT_Singlejet170_CF");
  TH1F* den = (TH1F*)fqcd_efficiency->Get("h_chf0_HLT_Dijet170");
  num->Rebin(5);
  den->Rebin(5);
  TH1F* eff_HLT170 = (TH1F*)num->Clone();
  eff_HLT170->Divide(den);
  eff_HLT170->Draw();



  TH1F* eff_HLT170_pt = (TH1F*)fqcd_efficiency->Get("h_pt0_HLT_Singlejet170_CF");
  eff_HLT170_pt->Reset();

  for(int b=0; b<eff_HLT170_pt->GetNbinsX(); b++){
    //cout<<eff_HLT170_pt->GetBinLowEdge(b+1)<<endl;
    if(eff_HLT170_pt->GetBinLowEdge(b+1)<120) eff_HLT170_pt->SetBinContent(b+1, 0);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==120) eff_HLT170_pt->SetBinContent(b+1, 0.00484173);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==140) eff_HLT170_pt->SetBinContent(b+1, 0.0376075);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==160) eff_HLT170_pt->SetBinContent(b+1, 0.379037);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==180) eff_HLT170_pt->SetBinContent(b+1, 0.897087);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==200) eff_HLT170_pt->SetBinContent(b+1, 0.975272);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==220) eff_HLT170_pt->SetBinContent(b+1, 0.984488);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==240) eff_HLT170_pt->SetBinContent(b+1, 0.985295);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==260) eff_HLT170_pt->SetBinContent(b+1, 0.987787);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==280) eff_HLT170_pt->SetBinContent(b+1, 0.990273);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==300) eff_HLT170_pt->SetBinContent(b+1, 0.992766);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)==320) eff_HLT170_pt->SetBinContent(b+1, 0.993569);
    if(eff_HLT170_pt->GetBinLowEdge(b+1)>=340) eff_HLT170_pt->SetBinContent(b+1, 1);
  }

//////////

  TChain *tchain_corr[NSAMPLES];
  for(int S=0; S<NSAMPLES; S++){

    cout<<"Reading sample "<<S<<endl;
    tchain_corr[S] = new TChain("treeCorr/SimpAnalysis");

    for(int i=1; i<200; i++){
     stringstream a;
     a<<QCD_Samples[S]<<i<<".root";
     tchain_corr[S]->Add((a.str()).c_str());
    }
   cout<<endl;

    SANtuple c_tree;
    c_tree.Init(tchain_corr[S]);

    Long64_t nentries = tchain_corr[S]->GetEntries();

  const double eta_cut = 2.0, dphi_cut= 2.0, pt_cut = 250.;

  double weight =  (QCD_xsec[S]/nentries)*1000.*16.146;

   for (Long64_t i=0; i<nentries; i++) {

    c_tree.GetEntry(i);
    if(i%100000 == 0) cout<<i<<" / "<<nentries<<"\r"<<flush;
      ///Object Selection

      if(c_tree.vtx_N<=1) continue;

   	        double njets = 0;
      for (int k = 0; k < 8; ++k){
  		   if (c_tree.jet_pt[k] > 30) njets++;
  		}
  		if(njets!=2) continue;

      if(c_tree.jet_pt[0]<pt_cut or c_tree.jet_pt[1]<pt_cut) continue;
      if(fabs(c_tree.jet_eta[0])>2. or fabs(c_tree.jet_eta[1])>2.) continue;


      double deltajet_phi = deltaPhi(c_tree.jet_phi[0], c_tree.jet_phi[1]);
      if(fabs(deltajet_phi) > 2.0);
      else continue;

      double lphoton_pt = 0, lphoton_eta = -100, lphoton_phi = -100;
      int lphoton_id = 0;
      for(int p=0; p<4; p++){
        if(c_tree.photon_pt[p]>lphoton_pt) {
          lphoton_pt = c_tree.photon_pt[p];
          lphoton_eta = c_tree.photon_eta[p];
          lphoton_phi = c_tree.photon_phi[p];
          lphoton_id = p;
        }
      }

      double dR1 = deltaR(lphoton_eta, lphoton_phi, c_tree.jet_eta[0], c_tree.jet_phi[0]);
      double dR2 = deltaR(lphoton_eta, lphoton_phi, c_tree.jet_eta[1], c_tree.jet_phi[1]);


      bool pass_conv_1 = true;
      bool pass_conv_2 = true;
      if(c_tree.jet_efrac_photon[0]>0.8 and c_tree.convtracks_pt[lphoton_id]/c_tree.photon_pt[lphoton_id] > 0.3 and dR1<0.2) pass_conv_1 = false;
      if(c_tree.jet_efrac_photon[1]>0.8 and c_tree.convtracks_pt[lphoton_id]/c_tree.photon_pt[lphoton_id] > 0.3 and dR2<0.2) pass_conv_2 = false;

      if( (c_tree.photon_passLooseId[lphoton_id] == 0 or (c_tree.photon_passLooseId[lphoton_id] == 1 && dR1 > 0.1 && dR2 > 0.1) )  and (pass_conv_1 and pass_conv_2) );
      else continue;


      double djet_chf    = c_tree.jet_efrac_ch_Had[0] + c_tree.jet_efrac_ch_EM[0] + c_tree.jet_efrac_ch_Mu[0];
      double djet_chf0    = c_tree.jet_efrac_ch_Had[0] + c_tree.jet_efrac_ch_EM[0] + c_tree.jet_efrac_ch_Mu[0];
      double djet_chf1    = c_tree.jet_efrac_ch_Had[1] + c_tree.jet_efrac_ch_EM[1] + c_tree.jet_efrac_ch_Mu[1];
      if(djet_chf1>djet_chf) djet_chf = djet_chf1;



       if(c_tree.HLT_DiCentralPFJet170_CFMax0p1) {
        histos_1d["h_chfMax_Total_HLT_170_0p1"]->Fill(djet_chf, weight);
        double eff_1 = eff_HLT170->GetBinContent(eff_HLT170->FindBin(djet_chf0));
        double eff_2 = eff_HLT170->GetBinContent(eff_HLT170->FindBin(djet_chf1));
        double eff = eff_1 * eff_2 * weight;
        histos_1d["h_chfMax_Efficiency_HLT_170_0p1"]->Fill(djet_chf, eff);

        histos_1d["h_pt1_Total_HLT_170_0p1"]->Fill(c_tree.jet_pt[1], weight);
        double effpt_1 = eff_HLT170_pt->GetBinContent(eff_HLT170_pt->FindBin(c_tree.jet_pt[0]));
        double effpt_2 = eff_HLT170_pt->GetBinContent(eff_HLT170_pt->FindBin(c_tree.jet_pt[1]));
        double effpt = effpt_1 * effpt_2 * weight ;
        histos_1d["h_pt1_Efficiency_HLT_170_0p1"]->Fill(c_tree.jet_pt[1], effpt);


       }


   }


}

    TFile *fout = new TFile("Efficiency_MC_wgt_pt_test.root", "RECREATE");
    fout->cd();
    writeHistos(fout, histos_1d);
    fout->Close();

    return 0;
}
