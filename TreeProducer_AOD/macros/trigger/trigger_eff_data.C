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


    histos_1d["h_pt_num_330"]  = new TH1F("h_pt_num_330","h_pt_num_330",100,0,2000);
    histos_1d["h_pt_den_330"]     = new TH1F("h_pt_den_330","h_pt_den_330",100,0,2000);

    histos_1d["h_pt_num_170"]  = new TH1F("h_pt_num_170","h_pt_num_170",100,0,2000);
    histos_1d["h_pt_den_170"]     = new TH1F("h_pt_den_170","h_pt_den_170",100,0,2000);
    histos_1d["h_pt_num_170_chf1"]  = new TH1F("h_pt_num_170_chf1","h_pt_num_170_chf1",100,0,2000);
    histos_1d["h_pt_den_170_chf1"]     = new TH1F("h_pt_den_170_chf1","h_pt_den_170_chf1",100,0,2000);
    histos_1d["h_pt_num_170_chfmax"]  = new TH1F("h_pt_num_170_chfmax","h_pt_num_170_chfmax",100,0,2000);
    histos_1d["h_pt_den_170_chfmax"]     = new TH1F("h_pt_den_170_chfmax","h_pt_den_170_chfmax",100,0,2000);


    histos_1d["h_chf330_den"]  = new TH1F("h_chf330_den","h_chf330_den",100,0,1);
    histos_1d["h_chf170_den"]  = new TH1F("h_chf170_den","h_chf170_den",100,0,1);
    histos_1d["h_chf330_num"]  = new TH1F("h_chf330_num","h_chf330_num",100,0,1);
    histos_1d["h_chf170_num"]  = new TH1F("h_chf170_num","h_chf170_num",100,0,1);

    histos_1d["h_chf170_Dijet430_den"]  = new TH1F("h_chf170_Dijet430_den","h_chf170_Dijet430_den",100,0,1);
    histos_1d["h_chf170_Dijet430_num"]  = new TH1F("h_chf170_Dijet430_num","h_chf330_Dijet430_num",100,0,1);


    histos_1d["h_pt0_HLT_Dijet170"]            = new TH1F("h_pt0_HLT_Dijet170","h_pt0_HLT_Dijet170",100,0,2000);
    histos_1d["h_pt1_HLT_Dijet170"]            = new TH1F("h_pt1_HLT_Dijet170","h_pt1_HLT_Dijet170",100,0,2000);
    histos_1d["h_chf0_HLT_Dijet170"]            = new TH1F("h_chf0_HLT_Dijet170","h_chf0_HLT_Dijet170",100,0,1);
    histos_1d["h_chf1_HLT_Dijet170"]            = new TH1F("h_chf1_HLT_Dijet170","h_chf1_HLT_Dijet170",100,0,1);

    histos_1d["h_pt0_HLT_Dijet430"]         = new TH1F("h_pt_HLT_Dijet430","h_pt_HLT_Dijet430",100,0,2000);
    histos_1d["h_pt1_HLT_Dijet430"]        = new TH1F("h_pt1_HLT_Dijet430","h_pt1_HLT_Dijet430",100,0,2000);
    histos_1d["h_chf0_HLT_Dijet430"]         = new TH1F("h_chf0_HLT_Dijet430","h_chf0_HLT_Dijet430",100,0,1);
    histos_1d["h_chf1_HLT_Dijet430"]         = new TH1F("h_chf1_HLT_Dijet430","h_chf1_HLT_Dijet430",100,0,1);


    histos_1d["h_pt0_HLT_Dijet170_CF"]         = new TH1F("h_pt0_HLT_Dijet170_CF","h_pt0_HLT_Dijet170_CF",100,0,2000);
    histos_1d["h_pt1_HLT_Dijet170_CF"]         = new TH1F("h_pt1_HLT_Dijet170_CF","h_pt1_HLT_Dijet170_CF",100,0,2000);
    histos_1d["h_chf0_HLT_Dijet170_CF"]         = new TH1F("h_chf0_HLT_Dijet170_CF","h_chf0_HLT_Dijet170_CF",100,0,1);
    histos_1d["h_chf1_HLT_Dijet170_CF"]         = new TH1F("h_chf1_HLT_Dijet170_CF","h_chf1_HLT_Dijet170_CF",100,0,1);

    histos_1d["h_pt0_HLT_Dijet330_CF"]         = new TH1F("h_pt0_HLT_Dijet330_CF","h_pt0_HLT_Dijet330_CF",100,0,2000);
    histos_1d["h_pt1_HLT_Dijet330_CF"]         = new TH1F("h_pt1_HLT_Dijet330_CF","h_pt1_HLT_Dijet330_CF",100,0,2000);
    histos_1d["h_chf0_HLT_Dijet330_CF"]         = new TH1F("h_chf0_HLT_Dijet330_CF","h_chf0_HLT_Dijet330_CF",100,0,1);
    histos_1d["h_chf1_HLT_Dijet330_CF"]         = new TH1F("h_chf1_HLT_Dijet330_CF","h_chf1_HLT_Dijet330_CF",100,0,1);


    histos_1d["h_pt0_HLT_Singlejet170_CF"]     = new TH1F("h_pt0_HLT_Singlejet170_CF","h_pt0_HLT_Singlejet170_CF",100,0,2000);
    histos_1d["h_pt1_HLT_Singlejet170_CF"]     = new TH1F("h_pt1_HLT_Singlejet170_CF","h_pt1_HLT_Singlejet170_CF",100,0,2000);
    histos_1d["h_chf0_HLT_Singlejet170_CF"]     = new TH1F("h_chf0_HLT_Singlejet170_CF","h_chf0_HLT_Singlejet170_CF",100,0,1);
    histos_1d["h_chf1_HLT_Singlejet170_CF"]    = new TH1F("h_chf1_HLT_Singlejet170_CF","h_chf1_HLT_Singlejet170_CF",100,0,1);

    histos_1d["h_chf0_HLT_Dijet430_pt500"]     = new TH1F("h_chf0_HLT_Dijet430_pt500","h_chf0_HLT_Dijet430_pt500",100,0,1);
    histos_1d["h_chf1_HLT_Dijet430_pt500"]     = new TH1F("h_chf1_HLT_Dijet430_pt500","h_chf1_HLT_Dijet430_pt500",100,0,1);
    histos_1d["h_chf0_HLT_Singlejet170_CF_pt500"]     = new TH1F("h_chf0_HLT_Singlejet170_CF_pt500","h_chf0_HLT_Singlejet170_CF_pt500",100,0,1);
    histos_1d["h_chf1_HLT_Singlejet170_CF_pt500"]     = new TH1F("h_chf1_HLT_Singlejet170_CF_pt500","h_chf1_HLT_Singlejet170_CF_pt500",100,0,1);


    histos_1d["h_chfmax_HLT_Singlejet170_CF_pt500"]     = new TH1F("h_chfmax_HLT_Singlejet170_CF_pt500","h_chfmax_HLT_Singlejet170_CF_pt500",100,0,1);
    histos_1d["h_chfmax_HLT_Dijet430_pt500"]     = new TH1F("h_chfmax_HLT_Dijet430_pt500","h_chfmax_HLT_Dijet430_pt500",100,0,1);
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




int trigger_eff_data(){

  std::map<string, TH1F*> histos_1d;
  bookHistos(histos_1d);


  int event_selection = 0;
  int event_selection_trigDijet170CF = 0;
  int event_selection_trigDijet170CF_cuts = 0;
  int wevent_selection_trigDijet170CF = 0;
  int wevent_selection_trigDijet170CF_cuts = 0;

  int event_selection_trigDijet330CF = 0;
  int event_selection_trigDijet330CF_cuts = 0;





  TChain * tchain_corr = new TChain("treeCorr/SimpAnalysis");

  for(int f=1; f<200; f++){

    stringstream runc;
    runc<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016C_rereco_AOD/170403_190623/0000/Data_AOD_test_"<<f<<".root"; //Run2016G
    tchain_corr->Add((runc.str()).c_str());
    stringstream rund;
    rund<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016D_rereco_AOD/170403_190657/0000/Data_AOD_test_"<<f<<".root"; //Run2016G
    tchain_corr->Add((rund.str()).c_str());
    stringstream rune;
    rune<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016E_rereco_AOD/170403_190730/0000/Data_AOD_test_"<<f<<".root"; //Run2016G
    tchain_corr->Add((rune.str()).c_str());
    stringstream runf;
    runf<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016F_rereco_AOD/170403_190806/0000/Data_AOD_test_"<<f<<".root"; //Run2016G
    tchain_corr->Add((runf.str()).c_str());


   stringstream rung;
   rung<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016G_rereco_AOD/170403_190918/0000/Data_AOD_test_"<<f<<".root"; //Run2016G
   tchain_corr->Add((rung.str()).c_str());
   stringstream runh2;
   runh2<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016Hv2_rereco_AOD/170403_190951/0000/Data_AOD_test_"<<f<<".root"; //Run2016G
   tchain_corr->Add((runh2.str()).c_str());
   stringstream runh3;
   runh3<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016Hv3_rereco_AOD/170403_191030/0000/Data_AOD_test_"<<f<<".root"; //Run2016G
   tchain_corr->Add((runh3.str()).c_str());

  }

  SANtuple c_tree;
  c_tree.Init(tchain_corr);



  Long64_t nentries = tchain_corr->GetEntries();


  const double eta_cut = 2.0, dphi_cut= 2.0, pt_cut = 250.;

  double weight = 1;

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


      event_selection++;

      double djet_chf    = c_tree.jet_efrac_ch_Had[0] + c_tree.jet_efrac_ch_EM[0] + c_tree.jet_efrac_ch_Mu[0];
      double djet_chf0    = c_tree.jet_efrac_ch_Had[0] + c_tree.jet_efrac_ch_EM[0] + c_tree.jet_efrac_ch_Mu[0];
      double djet_chf1    = c_tree.jet_efrac_ch_Had[1] + c_tree.jet_efrac_ch_EM[1] + c_tree.jet_efrac_ch_Mu[1];
      if(djet_chf1>djet_chf) djet_chf = djet_chf1;



        //cout<<c_tree.pswgt_dijet_170<<"\t"<<c_tree.pswgt_singlejet_170_0p1<<endl;
       if(c_tree.HLT_SingleCentralPFJet170_CFMax0p1 and c_tree.HLT_DiCentralPFJet170_CFMax0p1 ) {
         if(djet_chf0<0.1 and djet_chf1<0.1) histos_1d["h_pt_num_170"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_singlejet_170_0p1);
         if(djet_chf0<0.1 )                  histos_1d["h_pt_num_170_chf1"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_singlejet_170_0p1);
         if(djet_chf<0.1 )                   histos_1d["h_pt_num_170_chfmax"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_singlejet_170_0p1);

         if(c_tree.jet_pt[1]>250) histos_1d["h_chf170_num"]->Fill(djet_chf, c_tree.pswgt_singlejet_170_0p1);


       }
       if(c_tree.HLT_SingleCentralPFJet170_CFMax0p1 )  {
         if(djet_chf0<0.1 and djet_chf1<0.1) histos_1d["h_pt_den_170"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_singlejet_170_0p1);
         if(djet_chf0<0.1 )                  histos_1d["h_pt_den_170_chf1"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_singlejet_170_0p1);
         if(djet_chf<0.1 )                   histos_1d["h_pt_den_170_chfmax"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_singlejet_170_0p1);

         if(c_tree.jet_pt[1]>250) histos_1d["h_chf170_den"]->Fill(djet_chf, c_tree.pswgt_singlejet_170_0p1);


       }


       if(c_tree.HLT_DiCentralPFJet430 and c_tree.HLT_DiCentralPFJet170_CFMax0p1) {
         if(c_tree.jet_pt[1]>500)  histos_1d["h_chf170_Dijet430_num"]->Fill(djet_chf);
       }

       if(c_tree.HLT_DiCentralPFJet430) {
        if(c_tree.jet_pt[1]>500) histos_1d["h_chf170_Dijet430_den"]->Fill(djet_chf);
       }

       if(c_tree.HLT_DiCentralPFJet170 and c_tree.HLT_DiCentralPFJet330_CFMax0p5 ) {
         if(djet_chf0<0.3 and djet_chf1<0.3) histos_1d["h_pt_num_330"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_dijet_170);
         if(c_tree.jet_pt[1]>400) histos_1d["h_chf330_num"]->Fill(djet_chf, c_tree.pswgt_dijet_170);

       }
       if(c_tree.HLT_DiCentralPFJet170 )  {
         if(djet_chf0<0.3 and djet_chf1<0.3) histos_1d["h_pt_den_330"]->Fill(c_tree.jet_pt[1], c_tree.pswgt_dijet_170);
         if(c_tree.jet_pt[1]>400) histos_1d["h_chf330_den"]->Fill(djet_chf, c_tree.pswgt_dijet_170);

       }






              if(c_tree.HLT_DiCentralPFJet170) {
               histos_1d["h_pt0_HLT_Dijet170"]->Fill(c_tree.jet_pt[0]);
               histos_1d["h_pt1_HLT_Dijet170"]->Fill(c_tree.jet_pt[1]);
               histos_1d["h_chf0_HLT_Dijet170"]->Fill(djet_chf0);
               histos_1d["h_chf1_HLT_Dijet170"]->Fill(djet_chf1);
            }

            if(c_tree.HLT_DiCentralPFJet430) {
             histos_1d["h_pt0_HLT_Dijet430"]->Fill(c_tree.jet_pt[0]);
             histos_1d["h_pt1_HLT_Dijet430"]->Fill(c_tree.jet_pt[1]);
             histos_1d["h_chf0_HLT_Dijet430"]->Fill(djet_chf0);
             histos_1d["h_chf1_HLT_Dijet430"]->Fill(djet_chf1);
             if(c_tree.jet_pt[1]>500.) histos_1d["h_chf0_HLT_Dijet430_pt500"]->Fill(djet_chf0);
             if(c_tree.jet_pt[1]>500.) histos_1d["h_chf1_HLT_Dijet430_pt500"]->Fill(djet_chf1);
             if(c_tree.jet_pt[1]>500.) histos_1d["h_chfmax_HLT_Dijet430_pt500"]->Fill(djet_chf);

          }

              if(c_tree.HLT_SingleCentralPFJet170_CFMax0p1 and c_tree.HLT_DiCentralPFJet330_CFMax0p5) {
                histos_1d["h_pt0_HLT_Singlejet170_CF"]->Fill(c_tree.jet_pt[0]);
                histos_1d["h_pt1_HLT_Singlejet170_CF"]->Fill(c_tree.jet_pt[1]);
                histos_1d["h_chf0_HLT_Singlejet170_CF"]->Fill(djet_chf0);
                histos_1d["h_chf1_HLT_Singlejet170_CF"]->Fill(djet_chf1);
                // if(c_tree.jet_pt[1]>500.) histos_1d["h_chf0_HLT_Singlejet170_CF_pt500"]->Fill(djet_chf0, c_tree.pswgt_singlejet_170_0p1);
                // if(c_tree.jet_pt[1]>500.) histos_1d["h_chf1_HLT_Singlejet170_CF_pt500"]->Fill(djet_chf1, c_tree.pswgt_singlejet_170_0p1);
                // if(c_tree.jet_pt[1]>500.) histos_1d["h_chfmax_HLT_Singlejet170_CF_pt500"]->Fill(djet_chf, c_tree.pswgt_singlejet_170_0p1);
                if(c_tree.jet_pt[1]>500.) histos_1d["h_chf0_HLT_Singlejet170_CF_pt500"]->Fill(djet_chf0, c_tree.pswgt_singlejet_170_0p1);
                if(c_tree.jet_pt[1]>500.) histos_1d["h_chf1_HLT_Singlejet170_CF_pt500"]->Fill(djet_chf1, c_tree.pswgt_singlejet_170_0p1);
                if(c_tree.jet_pt[1]>500.) histos_1d["h_chfmax_HLT_Singlejet170_CF_pt500"]->Fill(djet_chf, c_tree.pswgt_singlejet_170_0p1);

               }
              if(c_tree.HLT_DiCentralPFJet170_CFMax0p1) {
               histos_1d["h_pt0_HLT_Dijet170_CF"]->Fill(c_tree.jet_pt[0]);
               histos_1d["h_pt1_HLT_Dijet170_CF"]->Fill(c_tree.jet_pt[1]);
               histos_1d["h_chf0_HLT_Dijet170_CF"]->Fill(djet_chf0);
               histos_1d["h_chf1_HLT_Dijet170_CF"]->Fill(djet_chf1);
              }

              if(c_tree.HLT_DiCentralPFJet330_CFMax0p5) {
               histos_1d["h_pt0_HLT_Dijet330_CF"]->Fill(c_tree.jet_pt[0]);
               histos_1d["h_pt1_HLT_Dijet330_CF"]->Fill(c_tree.jet_pt[1]);
               histos_1d["h_chf0_HLT_Dijet330_CF"]->Fill(djet_chf0);
               histos_1d["h_chf1_HLT_Dijet330_CF"]->Fill(djet_chf1);
              }




              if(c_tree.HLT_DiCentralPFJet170_CFMax0p1){
                event_selection_trigDijet170CF++;
                if(djet_chf<0.1 and c_tree.jet_pt[1]>250. and c_tree.jet_pt[1]<400. ){
                  event_selection_trigDijet170CF_cuts++;
                }
              }
              if(c_tree.HLT_DiCentralPFJet330_CFMax0p5){
                event_selection_trigDijet330CF++;
                if(djet_chf<0.1 and c_tree.jet_pt[1]>400.){
                  event_selection_trigDijet330CF_cuts++;
                }
              }


   }




    cout<<"Total events = \t"<<nentries<<endl;
    cout<<"Events passing selection = \t"<<event_selection<<endl;
    //cout<<"Events passing HLT_DiCentralPFJet170_CFMax0p1 = \t"<<event_selection_trigDijet170CF<<endl;
    //cout<<"Events passing HLT_DiCentralPFJet170_CFMax0p1 (pT>250 and ChF<0.1) = \t"<<event_selection_trigDijet170CF_cuts<<endl;

    //cout<<"Events passing HLT_DiCentralPFJet330_CFMax0p5 = \t"<<event_selection_trigDijet330CF<<endl;
    //cout<<"Events passing HLT_DiCentralPFJet330_CFMax0p5 (pT>400 and ChF<0.3) = \t"<<event_selection_trigDijet330CF_cuts<<endl;


    double perc = (double)event_selection_trigDijet170CF_cuts / (double)(event_selection_trigDijet170CF_cuts+event_selection_trigDijet330CF_cuts);
    cout<<event_selection_trigDijet170CF_cuts<<endl;
    cout<<event_selection_trigDijet330CF_cuts<<endl;
    cout<<"Percentage of events rejected if we remove 170_0p1 "<<perc<<endl;

    TFile *fout = new TFile("Efficiency_Data_test_events.root", "RECREATE");
    fout->cd();
    writeHistos(fout, histos_1d);
    fout->Close();

    return 0;
}
