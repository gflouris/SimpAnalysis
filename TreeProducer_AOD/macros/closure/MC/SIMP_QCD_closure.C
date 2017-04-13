#include <map>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <TMath.h>
#include <TChain.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLine.h>

#include "../../classes/SANtuple.h"

void SIMP_QCD_closure(){

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
  int photon_nr;

  TH1D* histo_1leg = new TH1D("histo_1leg", "systematics from closure", 100, 0, 0.5);
  TH1D* histo_2leg = new TH1D("histo_2leg", "systematics from closure", 100, 0, 0.5);

	double chf_cuts[12] = {0.5, 0.4, 0.3, 0.2, 0.15, 0.1, 0.07, 0.05, 0.04, 0.03, 0.02, 0.01};
	double pt_bins[10] = {250, 275, 300, 350, 400, 450, 550, 700, 900, 10000};
	double eta_bins[5] = {0, 0.5, 1.0, 1.5, 2.5};

	double passed_eff[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double passed_eff1[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double passed_eff2[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double passed_effboth[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double passed_MCtruth[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double err_MCtruth[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double err_eff1[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double err_eff2[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double err_eff[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double err_effboth[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double zero[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

	double ratio_1leg[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double ratio_2leg[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double err_ratio_1leg[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	double err_ratio_2leg[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

	std::cout<<"Getting the efficiency histos...";
	TFile* efficiencies = new TFile("eff2D_QCD_PUMoriond17_AN.root", "READ");
	TH2D* eff_histos[12];
	for(int j = 0; j < 12; j++){
		std::ostringstream strs;
		double dbl = chf_cuts[j];
		strs << dbl;
		std::string cut = strs.str();
		std::string title_eff = "eff_"+cut;
		eff_histos[j] = (TH2D*) efficiencies->Get(title_eff.c_str());
	}
	std::cout<<"done"<<std::endl;

  TFile *output = new TFile("closure_test_MCtruthSPVcut_PUMoriond17_AOD_photontest_new.root", "RECREATE");

	double QCD_xsec[6] = {346400, 32010, 6842, 1203, 120.1, 25.40}; //PUMoriond17
  double Nentries[6] = {17035891, 	18852895, 	15629253,	4825904, 	3970819,	1991645};
  double lumi = 36.5*1000.;

	for (int l = 0; l < 6; l++){
		TChain* chain = chains[l];
		TChain* SPVchain = SPVchains[l];
    SANtuple corrjets;
    corrjets.Init(chain);
    SANtuple SPVjets;
    SPVjets.Init(SPVchain);


		Int_t entries = corrjets.fChain->GetEntries();
		double weight = QCD_xsec[l]*lumi/entries;
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


			for (int i = 0; i < 8; ++i){
        CHEF_SPVjet[i] = SPVjets.jet_efrac_ch_Had[i]+SPVjets.jet_efrac_ch_EM[i]+SPVjets.jet_efrac_ch_Mu[i];
				CHEF_corrjet[i] = corrjets.jet_efrac_ch_Had[i]+corrjets.jet_efrac_ch_EM[i]+corrjets.jet_efrac_ch_Mu[i];
			}

      double dRjet1 = deltaR(corrjets.jet_eta[0], corrjets.jet_phi[0], SPVjets.jet_eta[0], SPVjets.jet_phi[0]);
  		double dRjet2 = deltaR(corrjets.jet_eta[1], corrjets.jet_phi[1], SPVjets.jet_eta[1], SPVjets.jet_phi[1]);

			output->cd();


        for(int j = 0; j < 12; j++){
          if ( CHEF_corrjet[0]<chf_cuts[j] && CHEF_corrjet[1]<chf_cuts[j] && dRjet1>0.4 && dRjet2>0.4){
            passed_MCtruth[j]+= weight;
            err_MCtruth[j] += pow(weight, 2);
          }
          else  if ( CHEF_corrjet[0]<chf_cuts[j] && CHEF_SPVjet[0]<chf_cuts[j] && CHEF_corrjet[1]<chf_cuts[j] && dRjet1<0.4 && dRjet2>0.4){
            passed_MCtruth[j]+= weight;
            err_MCtruth[j] += pow(weight, 2);
          }
          else  if ( CHEF_corrjet[0]<chf_cuts[j] && CHEF_SPVjet[1]<chf_cuts[j] && CHEF_corrjet[1]<chf_cuts[j] && dRjet1>0.4 && dRjet2<0.4){
            passed_MCtruth[j]+= weight;
            err_MCtruth[j] += pow(weight, 2);
          }
          else  if ( CHEF_corrjet[0]<chf_cuts[j] && CHEF_SPVjet[0]<chf_cuts[j] && CHEF_corrjet[1]<chf_cuts[j] && CHEF_SPVjet[1]<chf_cuts[j] && dRjet1<0.4 && dRjet2<0.4){
            passed_MCtruth[j]+= weight;
            err_MCtruth[j] += pow(weight, 2);
          }

          double eff1 = eff_histos[j]->GetBinContent(eff_histos[j]->GetXaxis()->FindBin(fabs(corrjets.jet_eta[0])), eff_histos[j]->GetYaxis()->FindBin(corrjets.jet_pt[0]));
          double eff2 = eff_histos[j]->GetBinContent(eff_histos[j]->GetXaxis()->FindBin(fabs(corrjets.jet_eta[1])), eff_histos[j]->GetYaxis()->FindBin(corrjets.jet_pt[1]));
          double erreff1 = eff_histos[j]->GetBinError(eff_histos[j]->GetXaxis()->FindBin(fabs(corrjets.jet_eta[0])), eff_histos[j]->GetYaxis()->FindBin(corrjets.jet_pt[0]));
          double erreff2 = eff_histos[j]->GetBinError(eff_histos[j]->GetXaxis()->FindBin(fabs(corrjets.jet_eta[1])), eff_histos[j]->GetYaxis()->FindBin(corrjets.jet_pt[1]));

          if (CHEF_corrjet[1]<chf_cuts[j]) passed_eff1[j]+=weight*eff1;
          if (CHEF_corrjet[0]<chf_cuts[j]) passed_eff2[j]+=weight*eff2;
          passed_effboth[j]+=eff1*eff2*weight;

          err_eff1[j] += weight*weight*erreff1*erreff1;
          err_eff2[j] += weight*weight*erreff2*erreff2;
          err_effboth[j] += (eff2*eff2*weight*weight*erreff1*erreff1) + (eff1*eff1*weight*weight*erreff2*erreff2);
        }
		}
	}
	for(int j = 0; j < 12; j++){
		err_MCtruth[j] = TMath::Sqrt(err_MCtruth[j]);
		err_effboth[j] = TMath::Sqrt(err_effboth[j]);
		err_eff1[j] = TMath::Sqrt(err_eff1[j]);
		err_eff2[j] = TMath::Sqrt(err_eff2[j]);
		err_eff[j] = (err_eff1[j]+err_eff2[j])/2.0 ;
		passed_eff[j] = (passed_eff1[j]+passed_eff2[j])/2;
		ratio_1leg[j] = passed_MCtruth[j]/passed_eff[j];
		ratio_2leg[j] = passed_MCtruth[j]/passed_effboth[j];
		err_ratio_1leg[j] = ratio_1leg[j]*TMath::Sqrt((err_eff[j]*err_eff[j]/passed_eff[j]/passed_eff[j])+(err_MCtruth[j]*err_MCtruth[j]/passed_MCtruth[j]/passed_MCtruth[j]));
		err_ratio_2leg[j] = ratio_2leg[j]*TMath::Sqrt((err_effboth[j]*err_effboth[j]/passed_effboth[j]/passed_effboth[j])+(err_MCtruth[j]*err_MCtruth[j]/passed_MCtruth[j]/passed_MCtruth[j]));
	}
	for(int j = 0; j < 12; j++){
    histo_1leg->Fill(chf_cuts[j], ((passed_MCtruth[j]-passed_eff[j])/passed_MCtruth[j])+1);
    histo_2leg->Fill(chf_cuts[j], ((passed_MCtruth[j]-passed_effboth[j])/passed_MCtruth[j])+1);
  }

	TCanvas *c1 = new TCanvas("Closure test", "Closure test",1400,1000);
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  pad1->SetBottomMargin(0);
  pad1->SetLogy(1);
  pad1->Draw();
  pad1->cd();
	TGraphErrors *MC = new TGraphErrors(12, chf_cuts, passed_MCtruth, zero, err_MCtruth);
	MC->SetTitle("Closure test");
	MC->GetXaxis()->SetTitle("CHF cut");
	MC->GetYaxis()->SetTitle("# events");
	MC->SetMarkerStyle(20);
	MC->Draw("AP");

	TGraphErrors *oneleg = new TGraphErrors(12, chf_cuts, passed_eff, zero, err_eff);
	oneleg->SetMarkerStyle(20);
	oneleg->SetMarkerColor(2);
	oneleg->Draw("P");

	TGraphErrors *twoleg = new TGraphErrors(12, chf_cuts, passed_effboth, zero, err_effboth);
	twoleg->SetMarkerStyle(20);
	twoleg->SetMarkerColor(3);
	twoleg->Draw("P");

	c1->cd();
	TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->SetLogy();
  pad2->Draw();
  pad2->cd();

	TGraphErrors *ratio_oneleg = new TGraphErrors(12, chf_cuts, ratio_1leg, zero, err_ratio_1leg);
	ratio_oneleg->SetMarkerStyle(20);
	ratio_oneleg->SetMarkerColor(2);
	ratio_oneleg->Draw("AP");
  ratio_oneleg->SetTitle("");
  ratio_oneleg->GetYaxis()->SetRangeUser(0.8, 1.2);
  ratio_oneleg->GetYaxis()->SetTitle("#frac{MCtruth}{1/2-leg}");

	TGraphErrors *ratio_twoleg = new TGraphErrors(12, chf_cuts, ratio_2leg, zero, err_ratio_2leg);
	ratio_twoleg->SetMarkerStyle(20);
	ratio_twoleg->SetMarkerColor(3);
	ratio_twoleg->Draw("P");

  TLine *line = new TLine(0,1,0.55,1);
  line->SetLineColor(kViolet+5);
  line->SetLineWidth(2);
	line->Draw();

  c1->cd();
	output->Append(c1);
  histo_1leg->Write();
  histo_2leg->Write();
  output->Write();
  output->Close();
}
