#include <map>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TChain.h>
#include <TH2.h>

#include "../../classes/SANtuple.h"


void SIMP_QCD_eff2D(){

  TChain* chain0 = new TChain("treeCorr/SimpAnalysis");
  chain0->Add("../../SIMPs_QCD_HT300To500_PUMoriond17.root");
  TChain* chain1 = new TChain("treeCorr/SimpAnalysis");
  chain1->Add("../../SIMPs_QCD_HT500To700_PUMoriond17.root");
  TChain* chain2 = new TChain("treeCorr/SimpAnalysis");
  chain2->Add("../../SIMPs_QCD_HT700To1000_PUMoriond17.root");
  TChain* chain3 = new TChain("treeCorr/SimpAnalysis");
  chain3->Add("../../SIMPs_QCD_HT1000To1500_PUMoriond17.root");
  TChain* chain4 = new TChain("treeCorr/SimpAnalysis");
  chain4->Add("../../SIMPs_QCD_HT1500To2000_PUMoriond17.root");
  TChain* chain5 = new TChain("treeCorr/SimpAnalysis");
  chain5->Add("../../SIMPs_QCD_HT2000ToInf_PUMoriond17.root");
	TChain* chains[6] = {chain0, chain1, chain2, chain3, chain4, chain5};

  TChain* SPVchain0 = new TChain("treeSPV/SimpAnalysis");
  SPVchain0->Add("../../SIMPs_QCD_HT300To500_PUMoriond17.root");
  TChain* SPVchain1 = new TChain("treeSPV/SimpAnalysis");
  SPVchain1->Add("../../SIMPs_QCD_HT500To700_PUMoriond17.root");
  TChain* SPVchain2 = new TChain("treeSPV/SimpAnalysis");
  SPVchain2->Add("../../SIMPs_QCD_HT700To1000_PUMoriond17.root");
  TChain* SPVchain3 = new TChain("treeSPV/SimpAnalysis");
  SPVchain3->Add("../../SIMPs_QCD_HT1000To1500_PUMoriond17.root");
  TChain* SPVchain4 = new TChain("treeSPV/SimpAnalysis");
  SPVchain4->Add("../../SIMPs_QCD_HT1500To2000_PUMoriond17.root");
  TChain* SPVchain5 = new TChain("treeSPV/SimpAnalysis");
  SPVchain5->Add("../../SIMPs_QCD_HT2000ToInf_PUMoriond17.root");
	TChain* SPVchains[6] = {SPVchain0, SPVchain1, SPVchain2, SPVchain3, SPVchain4, SPVchain5};
	std::cout<<"TChains ready"<<std::endl;

  double CHEF_SPVjet[8], CHEF_corrjet[8];

	double chf_cuts[12] = {0.5, 0.4, 0.3, 0.2, 0.15, 0.07, 0.1, 0.05, 0.04, 0.03, 0.02, 0.01};
	double pt_bins[10] = {250, 275, 300, 350, 400, 450, 550, 700, 900, 10000};
	double eta_bins[5] = {0, 0.5, 1.0, 1.5, 2.0};

  TFile *output = new TFile("eff2D_QCD_PUMoriond17_AN.root", "RECREATE");
	TH2D* total = new TH2D("total", "total", 4, eta_bins, 9, pt_bins);
	total->GetYaxis()->SetTitle("p_{T}");
	total->GetXaxis()->SetTitle("#eta");
	total->Sumw2();
	TH2D* passed[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	TH2D* eff[12]    = {0,0,0,0,0,0,0,0,0,0,0,0};

	double QCD_xsec[6] = {346400, 32010, 6842, 1203, 120.1, 25.40}; //PUMoriond17
	double lumi = 36.5*1000;

	std::cout<<"CHF cuts: ";
	for(int j = 0; j < 12; j++){
		std::ostringstream strs;
		double dbl = chf_cuts[j];
		strs << dbl;
		std::string cut = strs.str();
		std::cout<<" "<<cut<<" ";
		std::string title_passed = "passed_"+cut;
		std::string title_eff = "eff_"+cut;
		passed[j] = new TH2D(title_passed.c_str(), title_passed.c_str(), 4, eta_bins, 9, pt_bins);
		passed[j]->GetYaxis()->SetTitle("p_{T}");
		passed[j]->GetXaxis()->SetTitle("#eta");
		passed[j]->Sumw2();
		eff[j] = new TH2D(title_eff.c_str(), title_eff.c_str(), 4, eta_bins, 9, pt_bins);
		eff[j]->GetYaxis()->SetTitle("p_{T}");
		eff[j]->GetXaxis()->SetTitle("#eta");
	}
	std::cout<<std::endl;

	for (int l = 0; l < 6; l++){
		TChain* chain = chains[l];
    TChain* SPVchain = SPVchains[l];

    SANtuple corrjets;
    corrjets.Init(chain);
    SANtuple SPVjets;
    SPVjets.Init(SPVchain);

		Int_t entries = corrjets.fChain->GetEntries();
    double Nentries[6] = {17035891, 	18852895, 	15629253,	4825904, 	3970819,	1991645};
		double weight = QCD_xsec[l]*lumi/Nentries[l];
		std::cout<<"QCD bin "<<l<<": Processing "<<entries<<" entries with weight "<<weight<<std::endl;

		for(Int_t entry = 0; entry < entries; ++entry){
			if(entry%1000000==0) std::cout<<"processed "<<entry/1000000<<"M events"<<std::endl;

      corrjets.GetEntry(entry);
      SPVjets.GetEntry(entry);

      //if(corrjets.nJet!=2) continue;
      //if(corrjets.vtx_N<2)  continue;

      if(corrjets.jet_pt[0]>350. and corrjets.jet_pt[1]>350.);
      else continue;
  		if(fabs(corrjets.jet_eta[0])<2. and fabs(corrjets.jet_eta[1])<2.);
      else continue;


  		double deltajet_phi = deltaPhi(corrjets.jet_phi[0], corrjets.jet_phi[1]);
  		if(fabs(deltajet_phi) > 2.0);
  		else continue;

  		double lphoton_pt = 0, lphoton_eta = -100, lphoton_phi = -100;
  		int lphoton_id;
  		for(int p=0; p<4; p++){
  			if(corrjets.photon_pt[p]>lphoton_pt) {
  				lphoton_pt = corrjets.photon_pt[p];
  				lphoton_eta = corrjets.photon_eta[p];
  				lphoton_phi = corrjets.photon_phi[p];
  				lphoton_id = p;
  			}
  		}

  		double dR1 = deltaR(lphoton_eta, lphoton_phi, corrjets.jet_eta[0], corrjets.jet_phi[0]);
  		double dR2 = deltaR(lphoton_eta, lphoton_phi, corrjets.jet_eta[1], corrjets.jet_phi[1]);

  		if(corrjets.photon_passLooseId[lphoton_id] == 0 or (corrjets.photon_passLooseId[lphoton_id] == 1 && dR1 > 0.1 && dR2 > 0.1));
  		else continue;

			for (int i = 0; i < 8; i++){
				CHEF_SPVjet[i] = SPVjets.jet_efrac_ch_Had[i]+SPVjets.jet_efrac_ch_EM[i]+SPVjets.jet_efrac_ch_Mu[i];
				CHEF_corrjet[i] = corrjets.jet_efrac_ch_Had[i]+corrjets.jet_efrac_ch_EM[i]+corrjets.jet_efrac_ch_Mu[i];
			}

      double dRjet1 = deltaR(corrjets.jet_eta[0], corrjets.jet_phi[0], SPVjets.jet_eta[0], SPVjets.jet_phi[0]);
  		double dRjet2 = deltaR(corrjets.jet_eta[1], corrjets.jet_phi[1], SPVjets.jet_eta[1], SPVjets.jet_phi[1]);



			output->cd();


        if (dRjet1 < 0.4){
          if(CHEF_corrjet[0] > 0.5 || CHEF_SPVjet[0]>0.5){
            total->Fill(fabs(corrjets.jet_eta[1]), corrjets.jet_pt[1], weight);
            for(int j = 0; j < 12; j++){
              if (CHEF_SPVjet[1]<chf_cuts[j] && CHEF_corrjet[1]<chf_cuts[j]) passed[j]->Fill(fabs(corrjets.jet_eta[1]), corrjets.jet_pt[1], weight);
            }
          }
          if(CHEF_corrjet[1] > 0.5){
            total->Fill(fabs(corrjets.jet_eta[0]), corrjets.jet_pt[0], weight);
            for(int j = 0; j < 12; j++){
              if (CHEF_SPVjet[0]<chf_cuts[j] && CHEF_corrjet[0]<chf_cuts[j]) passed[j]->Fill(fabs(corrjets.jet_eta[0]), corrjets.jet_pt[0], weight);
            }
          }
        }else if (dRjet2 < 0.4){
          if(CHEF_corrjet[0] > 0.5){
            total->Fill(fabs(corrjets.jet_eta[1]), corrjets.jet_pt[1], weight);
            for(int j = 0; j < 12; j++){
              if (CHEF_SPVjet[1]<chf_cuts[j] && CHEF_corrjet[1]<chf_cuts[j]) passed[j]->Fill(fabs(corrjets.jet_eta[1]), corrjets.jet_pt[1], weight);
            }
          }
          if(CHEF_corrjet[1] > 0.5){
            total->Fill(fabs(corrjets.jet_eta[0]), corrjets.jet_pt[0], weight);
            for(int j = 0; j < 12; j++){
              if (CHEF_SPVjet[0]<chf_cuts[j] && CHEF_corrjet[0]<chf_cuts[j]) passed[j]->Fill(fabs(corrjets.jet_eta[0]), corrjets.jet_pt[0], weight);
            }
          }
        }else{
          if(CHEF_corrjet[0] > 0.5){
            total->Fill(fabs(corrjets.jet_eta[1]), corrjets.jet_pt[1], weight);
            for(int j = 0; j < 12; j++){
              if (CHEF_SPVjet[1]<chf_cuts[j] && CHEF_corrjet[1]<chf_cuts[j]) passed[j]->Fill(fabs(corrjets.jet_eta[1]), corrjets.jet_pt[1], weight);
            }
          }
          if(CHEF_corrjet[1] > 0.5){
            total->Fill(fabs(corrjets.jet_eta[0]), corrjets.jet_pt[0], weight);
            for(int j = 0; j < 12; j++){
              if (CHEF_SPVjet[0]<chf_cuts[j] && CHEF_corrjet[0]<chf_cuts[j]) passed[j]->Fill(fabs(corrjets.jet_eta[0]), corrjets.jet_pt[0], weight);
            }
          }
        }

		}
	}
	for(int j = 0; j < 12; j++){
		eff[j]->Divide(passed[j], total, 1, 1, "b");
	}
  output->Write();
  output->Close();
}
