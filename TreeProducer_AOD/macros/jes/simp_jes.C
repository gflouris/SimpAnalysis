#include "TH1F.h"
#include "TH2I.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TDirectoryFile.h"
#include "TStyle.h"
#include "TString.h"
#include "TMath.h"

#include "../classes/SANtuple.h"

#include <iostream>

#include "/user/gflouris/Tools/CMSPlots/tdrstyle.C"
#include "/user/gflouris/Tools/CMSPlots/CMS_lumi.C"

#include <boost/progress.hpp>

TCanvas *canvas_h1f(TString name, TString x_label, TH1F* hist ){
	TCanvas *canvas  = new TCanvas(name,name,800,600);
	hist->GetXaxis()->SetTitle(x_label);
	canvas->SetLogy();
	double max1 = hist->GetBinContent(hist->GetMaximumBin());
  hist->SetMaximum(5*max1);
	hist->Draw("hist");
	// writing the lumi information and the CMS "logo"
  CMS_lumi( canvas, 0, 11 );
	return canvas;

}

TCanvas *canvas_h1f(TString name, TString x_label, map<string, TH1F*> hmap){
	TCanvas *canvas  = new TCanvas(name,name,800,600);
	canvas->SetLogy();


   TLegend *leg;
   leg = new TLegend(0.52,0.63,0.91,0.90);

	int c=2;
	double max1;

	for (std::pair<std::string, TH1F*> element : hmap) {
		// Accessing KEY from element
		std::string word = element.first;
		// Accessing VALUE from element.
		TH1F* histo = element.second;
		histo->GetXaxis()->SetTitle(x_label);
		histo->SetLineColor(c);
		histo->SetMarkerStyle(1);
		histo->SetLineStyle(1);
		c++;
		histo->Draw("hist same");
		leg->AddEntry(histo,word.c_str(), "l");
		max1 = histo->GetBinContent(histo->GetMaximumBin());
		histo->SetMaximum(5*max1);
	}


	leg->SetTextFont(42);
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetBorderSize(0);
	leg->Draw();

	// writing the lumi information and the CMS "logo"
  CMS_lumi( canvas, 0, 11 );
	return canvas;

}



class Analysis {


	public:
		Analysis(){};
		Analysis(double pt, double eta, double dphi):m_pt_cut(pt),m_dphi_cut(dphi),m_eta_cut(eta) {};

		void setPtCut(double inv) {m_pt_cut = inv;}
		void setDPhiCut(double inv) {m_dphi_cut = inv;}
		void setEtaCut(double inv) {m_eta_cut = inv;}
		void setWeight(double inv) {m_weight = inv;}
		void setFileName(TString inv) {m_infile.push_back(inv);}
		void setLabel(TString inv) {m_label = inv;}
		void setJecUp(bool inv) {m_jec_up = inv;}
		void setJecDown(bool inv) {m_jec_down = inv;}

		void setHistos(std::map<std::string, TH1F*> inv) {m_histos = inv;};

		double getPtCut()   {return m_pt_cut;}
		double getDphiCut() {return m_dphi_cut;}
		double getEtaCut()  {return m_eta_cut;}
		double getWeight()  {return m_weight;}
		std::vector<TString> getFileName() {return m_infile;}
		TString getLabel() {return m_label;}

		std::map<std::string, TH1F*> getHistos() {return m_histos;}

    void producePlots();

	private:
		double m_eta_cut;
		double m_dphi_cut;
		double m_pt_cut;
		std::vector<TString> m_infile;
		std::map<std::string, TH1F*> m_histos;
		double m_weight = 1.;
		TString m_label;
    bool m_jec_up = false;
		bool m_jec_down = false;

};

//std::map<std::string, TH1F*> plots(TFile* , Analysis);

int simp_jes(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	const double LUMI = 33.095*1000.;


	TString MASS[7] = {"1","10", "100","200","400","700","1000"};
	float XS[7]   = {4.461, 4.402, 2.553, 0.7903, 0.07434, 0.004846, 0.0005714};

	TFile *f1 = new TFile("Systematics_JES.root", "RECREATE");

	for(int M=0; M<7; M++){

  Analysis simp_an(250.,2.0,2.0);
	cout<<MASS[M]<<endl;

  if(MASS[M]!="10") simp_an.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M"+MASS[M]+".root");
	if(MASS[M]=="10"){
		simp_an.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M"+MASS[M]+"_1.root");
		simp_an.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M"+MASS[M]+"_2.root");
		simp_an.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M"+MASS[M]+"_3.root");
	}
	simp_an.setWeight(XS[M]*LUMI);
	simp_an.setLabel("SIMP_M"+MASS[M]);



	simp_an.producePlots();
	std::map<std::string, TH1F*> simp_an_nom_plots = simp_an.getHistos();
	TH1F *hist_m1_nom = simp_an_nom_plots["h_pass_chf"];
	TH1F *hist_m1_nom_spv = simp_an_nom_plots["h_pass_chf_spv"];

	simp_an.setJecUp(true);
	simp_an.producePlots();
	std::map<std::string, TH1F*> simp_an_up_plots = simp_an.getHistos();
	TH1F *hist_m1_up = simp_an_up_plots["h_pass_chf"];
	TH1F *hist_m1_up_spv = simp_an_up_plots["h_pass_chf_spv"];

  simp_an.setJecUp(false);
	simp_an.setJecDown(true);
	simp_an.producePlots();
	std::map<std::string, TH1F*> simp_an_down_plots = simp_an.getHistos();
	TH1F *hist_m1_down = simp_an_down_plots["h_pass_chf"];
	TH1F *hist_m1_down_spv = simp_an_down_plots["h_pass_chf_spv"];

  const int NBINS = hist_m1_nom->GetNbinsX();
	TH1F *hist_m1_unc = (TH1F*)hist_m1_nom->Clone();
	hist_m1_unc->Reset();
	TH1F *hist_m1_unc_spv = (TH1F*)hist_m1_nom_spv->Clone();
	hist_m1_unc_spv->Reset();

  cout<<"SIMP_M"+MASS[M]<<endl;

	for(int i=0; i<NBINS; i++ ){

		float unc = (hist_m1_up->GetBinContent(i+1) - hist_m1_down->GetBinContent(i+1)) / (2.*hist_m1_nom->GetBinContent(i+1));
		hist_m1_unc->SetBinContent(i+1, (1.+unc));

		float unc_spv = (hist_m1_up_spv->GetBinContent(i+1) - hist_m1_down_spv->GetBinContent(i+1)) / (2.*hist_m1_nom_spv->GetBinContent(i+1));
		hist_m1_unc_spv->SetBinContent(i+1, (1.+unc_spv));

	}


	f1->cd();
	hist_m1_nom->SetName("M"+MASS[M]+"_eff");
	hist_m1_nom->Write();
	hist_m1_unc->SetName("M"+MASS[M]+"_unc");
	hist_m1_unc->Write();

	hist_m1_nom_spv->SetName("M"+MASS[M]+"_SPV_eff");
	hist_m1_nom_spv->Write();
	hist_m1_unc_spv->SetName("M"+MASS[M]+"_SPV_unc");
	hist_m1_unc_spv->Write();


	}





   ///////////////////////////////////////////////////////////////////////////////////////////////////
	 ////////////////////////////////////////////////QCD////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////


	 double QCD_xsec[6] = {346400, 32010, 6842, 1203, 120.1, 25.40}; //PUMoriond17
	 double N_Entries[6] = {17035891, 	18852895, 	15629253,	4825904, 	3970819,	1991645};


	 Analysis simp_an_qcd_300_500(250.,2.0,2.0);

	 for(int f=1; f<5; f++){
     stringstream a;
  	 a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SIMPs_QCD_HT300To500_PUMoriond17_AOD/170304_210059/0000/QCD_PUMoriond17_AOD_test_";
	   a<<f; a<<".root";
 	   simp_an_qcd_300_500.setFileName((a.str()).c_str());
	 }
 	 simp_an_qcd_300_500.setWeight(QCD_xsec[0]*LUMI/N_Entries[0]);
   simp_an_qcd_300_500.setLabel("QCD_HT300To500");
 	 simp_an_qcd_300_500.producePlots();


	 simp_an_qcd_300_500.producePlots();
 	std::map<std::string, TH1F*> simp_an_nom_plots = simp_an_qcd_300_500.getHistos();
 	TH1F *hist_m1_nom = simp_an_nom_plots["h_pass_chf"];
 	TH1F *hist_m1_nom_spv = simp_an_nom_plots["h_pass_chf_spv"];

 	simp_an_qcd_300_500.setJecUp(true);
 	simp_an_qcd_300_500.producePlots();
 	std::map<std::string, TH1F*> simp_an_up_plots = simp_an_qcd_300_500.getHistos();
 	TH1F *hist_m1_up = simp_an_up_plots["h_pass_chf"];
 	TH1F *hist_m1_up_spv = simp_an_up_plots["h_pass_chf_spv"];

   simp_an_qcd_300_500.setJecUp(false);
 	simp_an_qcd_300_500.setJecDown(true);
 	simp_an_qcd_300_500.producePlots();
 	std::map<std::string, TH1F*> simp_an_down_plots = simp_an_qcd_300_500.getHistos();
 	TH1F *hist_m1_down = simp_an_down_plots["h_pass_chf"];
 	TH1F *hist_m1_down_spv = simp_an_down_plots["h_pass_chf_spv"];

  const int NBINS = hist_m1_nom->GetNbinsX();
 	TH1F *hist_m1_unc = (TH1F*)hist_m1_nom->Clone();
 	hist_m1_unc->Reset();
 	TH1F *hist_m1_unc_spv = (TH1F*)hist_m1_nom_spv->Clone();
 	hist_m1_unc_spv->Reset();


 	for(int i=0; i<NBINS; i++ ){

 		float unc = (hist_m1_up->GetBinContent(i+1) - hist_m1_down->GetBinContent(i+1)) / (2.*hist_m1_nom->GetBinContent(i+1));
 		hist_m1_unc->SetBinContent(i+1, (1.+unc));

 		float unc_spv = (hist_m1_up_spv->GetBinContent(i+1) - hist_m1_down_spv->GetBinContent(i+1)) / (2.*hist_m1_nom_spv->GetBinContent(i+1));
 		hist_m1_unc_spv->SetBinContent(i+1, (1.+unc_spv));

 	}




	f1->cd();
	hist_m1_nom->SetName("MQCD_HT300To500_eff");
	hist_m1_nom->Write();
	hist_m1_unc->SetName("MQCD_HT300To500_unc");
	hist_m1_unc->Write();

	hist_m1_nom_spv->SetName("MQCD_HT300To500_SPV_eff");
	hist_m1_nom_spv->Write();
	hist_m1_unc_spv->SetName("MQCD_HT300To500_SPV_unc");
	hist_m1_unc_spv->Write();





	f1->Close();

	return 0;
}

void Analysis::producePlots(){

	//TFile* f700 = new TFile(this->getFileName();

	TChain* treel700 = new TChain("treeCorr/SimpAnalysis");

	TChain* treespv = new TChain("treeSPV/SimpAnalysis");

  std::vector<TString> files = this->getFileName();

	for(unsigned int f=0; f<files.size(); f++){
		cout<<files[f]<<endl;
		treel700->Add(files[f]);
		treespv->Add(files[f]);
	}

	SANtuple c_ntuple;
  c_ntuple.Init(treel700);

	SANtuple c_spvntuple;
  c_spvntuple.Init(treespv);


	int nentries = c_ntuple.fChain->GetEntries();
	TString Label = this->getLabel();

	cout<<"Reading "<<Label<<" tree with:\t"<<nentries<<"\tentries"<<endl;


	//const double eta_cut = this->getEtaCut(), dphi_cut=this->getDphiCut(), pt_cut = this->getPtCut();
	double weight = m_weight / nentries;

	int passed_eta_cut = 0;
	int passed_pt_cut = 0;
	int passed_dphi_cut = 0;
	int passed_photon_cut = 0;

	int passed_chf[23] = {0};
	int passed_spv_chf[23] = {0};

 	double chf_cuts[23] = {0.9, 0.85, 0.8, 0.75, 0.7, 0.65, 0.6, 0.55, 0.5, 0.45, 0.4, 0.35, 0.3, 0.25, 0.2, 0.15, 0.1, 0.07, 0.05, 0.04, 0.03, 0.02, 0.01};

	double chf_bins[24];
	for(int b=0; b<23; b++){
		chf_bins[b] = chf_cuts[22-b];
	}
	chf_bins[23] = 1.0;

	TH1F *h_pass_chf = new TH1F("h_pass_chf", "h_pass_chf", 23, chf_bins );
	TH1F *h_pass_chf_spv = new TH1F("h_pass_chf_spv", "h_pass_chf_spv", 23, chf_bins );

	for(int i=0; i<nentries; i++){
		c_ntuple.GetEntry(i);
		c_spvntuple.GetEntry(i);


		if(fabs(c_ntuple.jet_eta[0])<m_eta_cut && fabs(c_ntuple.jet_eta[1])<m_eta_cut) passed_eta_cut++;
		else continue;


		double pt_0 = c_ntuple.jet_pt[0];
		double pt_1 = c_ntuple.jet_pt[1];
		if(m_jec_up){
		 pt_0 = c_ntuple._jet_ptCor_up[0];
     pt_1 = c_ntuple._jet_ptCor_up[1];
	  }
		if(m_jec_down){
		  pt_0 = c_ntuple._jet_ptCor_down[0];
		  pt_1 = c_ntuple._jet_ptCor_down[1];
	  }

		if(pt_0>m_pt_cut && pt_1>m_pt_cut)     passed_pt_cut++;
		else continue;

		double deltajet_phi = c_ntuple.jet_phi[0] - c_ntuple.jet_phi[1];
		if(deltajet_phi > TMath::Pi()) deltajet_phi -= 2*TMath::Pi();
		if(deltajet_phi < -TMath::Pi()) deltajet_phi += 2*TMath::Pi();
		if(fabs(deltajet_phi) > m_dphi_cut) passed_dphi_cut++;
		else continue;

		double deltaphi_jet1photon = c_ntuple.jet_phi[0] - c_ntuple.photon_phi[0];
    if(deltaphi_jet1photon > TMath::Pi()) deltaphi_jet1photon -= 2*TMath::Pi();
    if(deltaphi_jet1photon < -TMath::Pi()) deltaphi_jet1photon += 2*TMath::Pi();
    double deltaphi_jet2photon = c_ntuple.jet_phi[1] - c_ntuple.photon_phi[0];
    if(deltaphi_jet2photon > TMath::Pi()) deltaphi_jet2photon -= 2*TMath::Pi();
    if(deltaphi_jet2photon < -TMath::Pi()) deltaphi_jet2photon += 2*TMath::Pi();
		double deltaeta_jet1photon = c_ntuple.jet_eta[0] - c_ntuple.photon_eta[0];
		double deltaeta_jet2photon = c_ntuple.jet_eta[1] - c_ntuple.photon_eta[0];

		double dR1 = TMath::Sqrt(deltaphi_jet1photon*deltaphi_jet1photon + deltaeta_jet1photon*deltaeta_jet1photon);
    double dR2 = TMath::Sqrt(deltaphi_jet2photon*deltaphi_jet2photon + deltaeta_jet2photon*deltaeta_jet2photon);

    if(c_ntuple.photon_passLooseId[0] == 0 || (c_ntuple.photon_passLooseId[0] == 1 && dR1 > 0.1 && dR2 > 0.1)) passed_photon_cut++;
		else continue;

		double jet_chf_0 = c_ntuple.jet_efrac_ch_Mu[0] + c_ntuple.jet_efrac_ch_EM[0] + c_ntuple.jet_efrac_ch_Had[0];
		double jet_chf_1 = c_ntuple.jet_efrac_ch_Mu[1] + c_ntuple.jet_efrac_ch_EM[1] + c_ntuple.jet_efrac_ch_Had[1];


		double jet_chf_spv_0 = c_spvntuple.jet_efrac_ch_Mu[0] + c_spvntuple.jet_efrac_ch_EM[0] + c_spvntuple.jet_efrac_ch_Had[0];
		double jet_chf_spv_1 = c_spvntuple.jet_efrac_ch_Mu[1] + c_spvntuple.jet_efrac_ch_EM[1] + c_spvntuple.jet_efrac_ch_Had[1];

		for(int C=0; C<23; C++) {
			if(jet_chf_0<chf_cuts[C] and jet_chf_1<chf_cuts[C]) passed_chf[C]++;
			if(jet_chf_0<chf_cuts[C] and jet_chf_1<chf_cuts[C] and jet_chf_spv_0<chf_cuts[C] and jet_chf_spv_1<chf_cuts[C]) passed_spv_chf[C]++;
		}


	}


	//cout<<passed_eta_cut*weight<<endl;
	//cout<<passed_pt_cut*weight<<endl;
	//cout<<passed_dphi_cut*weight<<endl;
	//cout<<passed_photon_cut*weight<<endl;
	cout<<Label<<endl;
	for(int i=0; i<23; i++){
		//cout<<chf_cuts[i]<<"\t"<<passed_spv_chf[i]*weight<<endl;
		h_pass_chf->SetBinContent(22-i+1, passed_chf[i]*weight);
		h_pass_chf_spv->SetBinContent(22-i+1, passed_spv_chf[i]*weight);

	}
	cout<<"===================================================="<<endl;

std::map<std::string, TH1F*> histos;
histos["h_pass_chf"] = h_pass_chf;
histos["h_pass_chf_spv"] = h_pass_chf_spv;

setHistos(histos);


delete treespv;
delete treel700;
	//for(int i=0; i<11; i++)
	//	cout<<passed_spv_chf[i]*weight<<endl;

	}
