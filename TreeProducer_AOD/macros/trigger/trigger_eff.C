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




int trigger_eff(){

const int NSAMPLES = 6;

double QCD_xsec[NSAMPLES] = {346400, 32010, 6842, 1203, 120.1, 25.40}; //PUMoriond17

string QCD_Samples[NSAMPLES] = {
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT300To500_PUMoriond17_AOD/170304_210059/0000/QCD_PUMoriond17_AOD_test_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT500To700_PUMoriond17_AOD/170304_210449/0000/QCD_PUMoriond17_AOD_test_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT700To1000_PUMoriond17_AOD/170305_212329/0000/QCD_PUMoriond17_AOD_test_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1000To1500_PUMoriond17_AOD/170304_211150/0000/QCD_PUMoriond17_AOD_test_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT1500To2000_PUMoriond17_AOD/170305_211927/0000/QCD_PUMoriond17_AOD_test_",
"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT2000ToInf_PUMoriond17_AOD/170304_213629/0000/QCD_PUMoriond17_AOD_test_"
};


  TH1F* h_chf_01      = new TH1F("h_chf_01","h_chf_01",20,0,1);
  TH1F* h_chf_03      = new TH1F("h_chf_03","h_chf_03",20,0,1);
  TH1F* h_chf_05      = new TH1F("h_chf_05","h_chf_05",20,0,1);
  TH1F* h_chf_01_den  = new TH1F("h_chf_01_den","h_chf_01_den",20,0,1);
  TH1F* h_chf_03_den  = new TH1F("h_chf_03_den","h_chf_03_den",20,0,1);
  TH1F* h_chf_05_den  = new TH1F("h_chf_05_den","h_chf_05_den",20,0,1);

  TH1F* h_pt_01      = new TH1F("h_pt_01","h_pt_01",100,0,2000);
  TH1F* h_pt_03      = new TH1F("h_pt_03","h_pt_03",100,0,2000);
  TH1F* h_pt_05      = new TH1F("h_pt_05","h_pt_05",100,0,2000);
  TH1F* h_pt_05_den         = new TH1F("h_pt_05_den","h_pt_05_den",100,0,2000);
  TH1F* h_pt_03_den         = new TH1F("h_pt_03_den","h_pt_03_den",100,0,2000);
  TH1F* h_pt_01_den         = new TH1F("h_pt_01_den","h_pt_01_den",100,0,2000);


  int event_selection = 0;
  int event_selection01 = 0;

  int event_selection_trig01 = 0;
  int event_selection_trig03 = 0;
  int event_selection_trig05 = 0;


TChain *tchain_corr[NSAMPLES];
for(int S=0; S<NSAMPLES; S++){

  cout<<"Reading sample "<<S<<endl;
  tchain_corr[S] = new TChain("treeCorr/SimpAnalysis");

  for(int i=1; i<400; i++){
   stringstream a;
   a<<QCD_Samples[S]<<i<<".root";
   tchain_corr[S]->Add((a.str()).c_str());
  }
 cout<<endl;

  SANtuple c_tree;
  c_tree.Init(tchain_corr[S]);

  Long64_t nentries = tchain_corr[S]->GetEntries();

  tchain_corr[S]->SetWeight(QCD_xsec[S]/nentries,"global");

  const double eta_cut = 2.0, dphi_cut= 2.0, pt_cut = 250.;


   for (Long64_t i=0; i<nentries; i++) {

    c_tree.GetEntry(i);
    if(i%100000 == 0) cout<<i<<" / "<<nentries<<"\r"<<flush;
      ///Object Selection

      double deltajet_phi = c_tree.jet_phi[0] - c_tree.jet_phi[1];
      if(deltajet_phi > TMath::Pi()) deltajet_phi -= 2*TMath::Pi();
      if(deltajet_phi < -TMath::Pi()) deltajet_phi += 2*TMath::Pi();


      double deltaphi_jet1photon = c_tree.jet_phi[0] - c_tree.photon_phi[0];
      if(deltaphi_jet1photon > TMath::Pi()) deltaphi_jet1photon -= 2*TMath::Pi();
      if(deltaphi_jet1photon < -TMath::Pi()) deltaphi_jet1photon += 2*TMath::Pi();
      double deltaphi_jet2photon = c_tree.jet_phi[1] - c_tree.photon_phi[0];
      if(deltaphi_jet2photon > TMath::Pi()) deltaphi_jet2photon -= 2*TMath::Pi();
      if(deltaphi_jet2photon < -TMath::Pi()) deltaphi_jet2photon += 2*TMath::Pi();

      double deltaeta_jet1photon = c_tree.jet_eta[0] - c_tree.photon_eta[0];
      double deltaeta_jet2photon = c_tree.jet_eta[1] - c_tree.photon_eta[0];

      double dR1 = TMath::Sqrt(deltaphi_jet1photon*deltaphi_jet1photon + deltaeta_jet1photon*deltaeta_jet1photon);
      double dR2 = TMath::Sqrt(deltaphi_jet2photon*deltaphi_jet2photon + deltaeta_jet2photon*deltaeta_jet2photon);

      if(c_tree.photon_passLooseId[0] == 1 || (c_tree.photon_passLooseId[0] == 0 && dR1 <= 0.1 && dR2 <= 0.1)) continue;


    	if( fabs(c_tree.jet_eta[0])<eta_cut && fabs(c_tree.jet_eta[1])<eta_cut && deltajet_phi>dphi_cut ){
            event_selection++;

            double djet_chf    = c_tree.jet_efrac_ch_Had[0] + c_tree.jet_efrac_ch_EM[0] + c_tree.jet_efrac_ch_Mu[0];
            double djet_chf1    = c_tree.jet_efrac_ch_Had[1] + c_tree.jet_efrac_ch_EM[1] + c_tree.jet_efrac_ch_Mu[1];
            if(djet_chf1>djet_chf) djet_chf = djet_chf1;


    		    if( c_tree.jet_pt[0]>250 && c_tree.jet_pt[1]>250) {
              h_chf_01_den->Fill(djet_chf, c_tree.fChain->GetWeight());
            }
            if(c_tree.HLT_DiCentralPFJet170_CFMax0p1 && c_tree.jet_pt[0]>250 && c_tree.jet_pt[1]>250) {
              event_selection_trig01++;
              h_chf_01->Fill(djet_chf, c_tree.fChain->GetWeight());
            }

            if( c_tree.jet_pt[0]>350 && c_tree.jet_pt[1]>350) {
              h_chf_03_den->Fill(djet_chf, c_tree.fChain->GetWeight());
            }
            if(c_tree.HLT_DiCentralPFJet220_CFMax0p3 && c_tree.jet_pt[0]>350 && c_tree.jet_pt[1]>350) {
              event_selection_trig03++;
              h_chf_03->Fill(djet_chf, c_tree.fChain->GetWeight());
          }

            if( c_tree.jet_pt[0]>400 && c_tree.jet_pt[1]>400) {
              h_chf_05_den->Fill(djet_chf, c_tree.fChain->GetWeight());
            }
            if(c_tree.HLT_DiCentralPFJet330_CFMax0p5 && c_tree.jet_pt[0]>400 && c_tree.jet_pt[1]>400) {
              event_selection_trig05++;
              h_chf_05->Fill(djet_chf, c_tree.fChain->GetWeight());
            }

    	}

      if( fabs(c_tree.jet_eta[0])<eta_cut && fabs(c_tree.jet_eta[1])<eta_cut && deltajet_phi>dphi_cut ){
        //cout<<c_tree.fChain->GetWeight()<<endl;

        double djet_chf0    = c_tree.jet_efrac_ch_Had[0] + c_tree.jet_efrac_ch_EM[0] + c_tree.jet_efrac_ch_Mu[0];
        double djet_chf1    = c_tree.jet_efrac_ch_Had[1] + c_tree.jet_efrac_ch_EM[1] + c_tree.jet_efrac_ch_Mu[1];

        if(djet_chf0<0.3 and djet_chf1<0.3) h_pt_05_den->Fill(c_tree.jet_pt[1], c_tree.fChain->GetWeight());
        if(djet_chf0<0.2 and djet_chf1<0.2) h_pt_03_den->Fill(c_tree.jet_pt[1], c_tree.fChain->GetWeight());
        if(djet_chf0<0.05 and djet_chf1<0.05) h_pt_01_den->Fill(c_tree.jet_pt[1], c_tree.fChain->GetWeight());

        if(c_tree.HLT_DiCentralPFJet170_CFMax0p1 and djet_chf0<0.05 and djet_chf1<0.05) h_pt_01->Fill(c_tree.jet_pt[1], c_tree.fChain->GetWeight());
        if(c_tree.HLT_DiCentralPFJet220_CFMax0p3 and djet_chf0<0.2 and djet_chf1<0.2) h_pt_03->Fill(c_tree.jet_pt[1], c_tree.fChain->GetWeight());
        if(c_tree.HLT_DiCentralPFJet330_CFMax0p5 and djet_chf0<0.3 and djet_chf1<0.3) h_pt_05->Fill(c_tree.jet_pt[1], c_tree.fChain->GetWeight());

        //if(c_tree.HLT_DiCentralPFJet170_CFMax0p1 and djet_chf0<chf_cut and djet_chf1<chf_cut) h_pt_05->Fill(c_tree.jet_pt[1], c_tree.fChain->GetWeight());

       }

   }


}
    cout<<"Events passing selection =\t"<<event_selection<<endl;
    cout<<"Events passing selection +chf<0.1 =\t"<<event_selection01<<endl;

    cout<<"Events passing selection +HLT_DiCentralPFJet170_CFMax0p1 =\t"<<event_selection_trig01<<endl;
    cout<<"Events passing selection +HLT_DiCentralPFJet220_CFMax0p3 =\t"<<event_selection_trig03<<endl;
    cout<<"Events passing selection +HLT_DiCentralPFJet330_CFMax0p5 =\t"<<event_selection_trig05<<endl;


    //
    //
    //
    // TEfficiency *pt_eff = new TEfficiency("pt_eff_05","pt_eff_05",80,400,800);
    // pt_eff->SetPassedHistogram(*h_pt_05,"f");
    // pt_eff->SetTotalHistogram(*h_pt_05_den,"f");
    // TCanvas *c1 = new TCanvas("c1","c1",800,600);
    // c1->cd();
    // pt_eff->SetTitle("HLT_DiCentralPFJet330_CFMax0p5; Jet p_{T2}; Efficiency");
    // pt_eff->Draw();
    //
    //
    //
    // TEfficiency *pt_eff03 = new TEfficiency("pt_eff_03","pt_eff_03",80,400,800);
    // pt_eff03->SetPassedHistogram(*h_pt_03,"f");
    // pt_eff03->SetTotalHistogram(*h_pt_03_den,"f");
    // TCanvas *c2 = new TCanvas("c2","c2",800,600);
    // c2->cd();
    // pt_eff03->SetTitle("HLT_DiCentralPFJet220_CFMax0p3; Jet p_{T2}; Efficiency");
    // pt_eff03->Draw();
    //
    // TEfficiency *pt_eff_01 = new TEfficiency("pt_eff_01","pt_eff_01",80,400,800);
    // pt_eff_01->SetPassedHistogram(*h_pt_01,"f");
    // pt_eff_01->SetTotalHistogram(*h_pt_01_den,"f");
    // TCanvas *c3 = new TCanvas("c3","c3",800,600);
    // c3->cd();
    // pt_eff_01->SetTitle("HLT_DiCentralPFJet170_CFMax0p1; Jet p_{T2}; Efficiency");
    // pt_eff_01->Draw();
    //
    //
    //
    //
    //
    // TEfficiency *chf_eff_01 = new TEfficiency("chf_eff_01","chf_eff_01;Max ChF;#epsilon;",20,0,1);
    // chf_eff_01->SetPassedHistogram(*h_chf_01,"f");
    // chf_eff_01->SetTotalHistogram(*h_chf_01_den,"f");
    // TCanvas *c4 = new TCanvas("c4","c4",800,600);
    // c4->cd();
    // chf_eff_01->SetTitle("HLT_DiCentralPFJet170_CFMax0p1; Max ChF; Efficiency");
    // chf_eff_01->Draw();
    //
    //
    // TEfficiency *chf_eff_03 = new TEfficiency("chf_eff_03","chf_eff_03;Max ChF;#epsilon;",20,0,1);
    // chf_eff_03->SetPassedHistogram(*h_chf_03,"f");
    // chf_eff_03->SetTotalHistogram(*h_chf_03_den,"f");
    // TCanvas *c5 = new TCanvas("c5","c5",800,600);
    // c5->cd();
    // chf_eff_03->SetTitle("HLT_DiCentralPFJet220_CFMax0p3; Max ChF; Efficiency");
    // chf_eff_03->Draw();
    //
    // TEfficiency *chf_eff_05 = new TEfficiency("chf_eff_05","chf_eff_05;Max ChF;#epsilon;",20,0,1);
    // chf_eff_05->SetPassedHistogram(*h_chf_05,"f");
    // chf_eff_05->SetTotalHistogram(*h_chf_05_den,"f");
    // TCanvas *c6 = new TCanvas("c6","c6",800,600);
    // c6->cd();
    // chf_eff_05->SetTitle("HLT_DiCentralPFJet330_CFMax0p5; Max ChF; Efficiency");
    // chf_eff_05->Draw();
    //
    //
    // TCanvas *c7 = new TCanvas("c7","c7",800,600);
    // c7->cd();
    // h_chf_01_den->Draw();


    TFile *fout = new TFile("Efficiency_QCD2.root", "RECREATE");
    fout->cd();
    h_chf_05_den->Write();
    h_chf_05->Write();
    h_chf_03_den->Write();
    h_chf_03->Write();
    h_chf_01_den->Write();
    h_chf_01->Write();

    h_pt_05_den->Write();
    h_pt_05->Write();
    h_pt_03_den->Write();
    h_pt_03->Write();
    h_pt_01_den->Write();
    h_pt_01->Write();



    fout->Close();

    return 0;
}
