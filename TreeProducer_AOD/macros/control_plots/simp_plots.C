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
		Analysis(double pt, double eta, double dphi):pt_cut(pt),dphi_cut(dphi),eta_cut(eta) {};

		void setPtCut(double inv) {pt_cut = inv;}
		void setDPhiCut(double inv) {dphi_cut = inv;}
		void setEtaCut(double inv) {eta_cut = inv;}
		void setWeight(double inv) {weight = inv;}
		void setFileName(TString inv) {infile = inv;}
		void setLabel(TString inv) {label = inv;}

		void setHistos(std::map<std::string, TH1F*> inv) {histos = inv;};

		double getPtCut()   {return pt_cut;}
		double getDphiCut() {return dphi_cut;}
		double getEtaCut()  {return eta_cut;}
		double getWeight()  {return weight;}
		TString getFileName() {return infile;}
		TString getLabel() {return label;}

		std::map<std::string, TH1F*> getHistos() {return histos;}

    void producePlots();

	private:
		double eta_cut;
		double dphi_cut;
		double pt_cut;
		TString infile;
		std::map<std::string, TH1F*> histos;
		double weight = 1.;
		TString label;
};

//std::map<std::string, TH1F*> plots(TFile* , Analysis);

int simp_plots(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	const double LUMI = 36.5*1000.;
	double QCD_xsec[6] = {346400, 32010, 6842, 1203, 120.1, 25.40}; //PUMoriond17
  //double lumi = 20.*1000;
	//double N_Entries[6] = {37502012, 43341392, 29783527, 10360193, 7855883, 4047360 };
	double N_Entries[6] = {17035891, 	18852895, 	15629253,	4825904, 	3970819,	1991645};
	//  Analysis simp_an_1(250.,2.0,2.0);
	//  Analysis simp_an_10(250.,2.0,2.0);
	 //Analysis simp_an_100(250.,2.0,2.0);

	//  Analysis simp_an_200(250.,2.0,2.0);
	// Analysis simp_an_400(250.,2.0,2.0);
	// Analysis simp_an_700(250.,2.0,2.0);
	// Analysis simp_an_1000(250.,2.0,2.0);


  // simp_an_1.setFileName("ROOTFiles/SIMPs_PUMoriond17_AOD_SIMP_M1.root");
	// simp_an_1.setWeight(4.43*LUMI);
	// simp_an_1.setLabel("SIMP_M1");
	// simp_an_1.producePlots();
	//
  // simp_an_10.setFileName("ROOTFiles/SIMPs_PUMoriond17_AOD_SIMP_M10.root");
	// simp_an_10.setWeight(4.42*LUMI);
	// simp_an_10.setLabel("SIMP_M10");
	// simp_an_10.producePlots();


	// simp_an_100.setFileName("ROOTFiles/SIMPs_PUMoriond17_AOD_SIMP_M100.root");
	// simp_an_100.setWeight(2.42*LUMI);
	// simp_an_100.setLabel("SIMP_M100");
	// simp_an_100.producePlots();
	//

	// simp_an_200.setFileName("ROOTFiles/SIMPs_PUMoriond17_AOD_SIMP_M200.root");
	// simp_an_200.setWeight(0.7903*LUMI);
	// simp_an_200.setLabel("SIMP_M200");
	// simp_an_200.producePlots();
	//
	//
	// simp_an_400.setFileName("ROOTFiles/SIMPs_PUMoriond17_AOD_SIMP_M400.root");
	// simp_an_400.setWeight(0.07434*LUMI);
	// simp_an_400.setLabel("SIMP_M400");
	// simp_an_400.producePlots();
	//
	//
	// simp_an_700.setFileName("ROOTFiles/SIMPs_PUMoriond17_AOD_SIMP_M700.root");
	// simp_an_700.setWeight(0.004846*LUMI);
	// simp_an_700.setLabel("SIMP_M700");
  // simp_an_700.producePlots();
	//
	//
	// simp_an_1000.setFileName("ROOTFiles/SIMPs_PUMoriond17_AOD_SIMP_M1000.root");
	// simp_an_1000.setWeight(0.0005714*LUMI);
	// simp_an_1000.setLabel("SIMP_M1000");
  // simp_an_1000.producePlots();


	Analysis simp_an_qcd_300_500(250.,2.0,2.0);
	simp_an_qcd_300_500.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/SIMPS/QCD_Skimmed/SIMPs_QCD_HT300To500_PUMoriond17.root");
	simp_an_qcd_300_500.setWeight(QCD_xsec[0]*LUMI/N_Entries[0]);
  simp_an_qcd_300_500.setLabel("QCD_HT300To500");
	simp_an_qcd_300_500.producePlots();

	Analysis simp_an_qcd_500_700(250.,2.0,2.0);
	simp_an_qcd_500_700.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/SIMPS/QCD_Skimmed/SIMPs_QCD_HT500To700_PUMoriond17.root");
	simp_an_qcd_500_700.setWeight(QCD_xsec[1]*LUMI/N_Entries[1]);
  simp_an_qcd_500_700.setLabel("QCD_HT500To700");
	simp_an_qcd_500_700.producePlots();

	Analysis simp_an_qcd_700_1000(250.,2.0,2.0);
	simp_an_qcd_700_1000.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/SIMPS/QCD_Skimmed/SIMPs_QCD_HT700To1000_PUMoriond17.root");
	simp_an_qcd_700_1000.setWeight(QCD_xsec[2]*LUMI/N_Entries[2]);
  simp_an_qcd_700_1000.setLabel("QCD_HT700To1000");
	simp_an_qcd_700_1000.producePlots();

	Analysis simp_an_qcd_1000_1500(250.,2.0,2.0);
	simp_an_qcd_1000_1500.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/SIMPS/QCD_Skimmed/SIMPs_QCD_HT1000To1500_PUMoriond17.root");
	simp_an_qcd_1000_1500.setWeight(QCD_xsec[3]*LUMI/N_Entries[3]);
  simp_an_qcd_1000_1500.setLabel("QCD_HT1000To1500");
	simp_an_qcd_1000_1500.producePlots();

	Analysis simp_an_qcd_1500_2000(250.,2.0,2.0);
	simp_an_qcd_1500_2000.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/SIMPS/QCD_Skimmed/SIMPs_QCD_HT1500To2000_PUMoriond17.root");
	simp_an_qcd_1500_2000.setWeight(QCD_xsec[4]*LUMI/N_Entries[4]);
  simp_an_qcd_1500_2000.setLabel("QCD_HT1500To2000");
	simp_an_qcd_1500_2000.producePlots();

	Analysis simp_an_qcd_2000_Inf(250.,2.0,2.0);
	simp_an_qcd_2000_Inf.setFileName("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/SIMPS/QCD_Skimmed/SIMPs_QCD_HT2000ToInf_PUMoriond17.root");
	simp_an_qcd_2000_Inf.setWeight(QCD_xsec[5]*LUMI/N_Entries[5]);
  simp_an_qcd_2000_Inf.setLabel("QCD_HT2000ToInf");
	simp_an_qcd_2000_Inf.producePlots();


	//  std::map<std::string, TH1F*> plot_m1 = simp_an_1.getHistos();
	// std::map<std::string, TH1F*> plot_m10 = simp_an_10.getHistos();
	//std::map<std::string, TH1F*> plot_m100 = simp_an_100.getHistos();

	//  std::map<std::string, TH1F*> plot_m200 = simp_an_200.getHistos();
	//  std::map<std::string, TH1F*> plot_m400 = simp_an_400.getHistos();
 // 	std::map<std::string, TH1F*> plot_m700 = simp_an_700.getHistos();
	// std::map<std::string, TH1F*> plot_m1000 = simp_an_1000.getHistos();

	std::map<std::string, TH1F*> plot_qcd300_500 = simp_an_qcd_300_500.getHistos();
	std::map<std::string, TH1F*> plot_qcd500_700 = simp_an_qcd_500_700.getHistos();
	std::map<std::string, TH1F*> plot_qcd700_1000 = simp_an_qcd_700_1000.getHistos();
	std::map<std::string, TH1F*> plot_qcd1000_1500 = simp_an_qcd_1000_1500.getHistos();
	std::map<std::string, TH1F*> plot_qcd1500_2000 = simp_an_qcd_1500_2000.getHistos();
	std::map<std::string, TH1F*> plot_qcd2000_Inf = simp_an_qcd_2000_Inf.getHistos();


	// TFile * f1 = new TFile("ROOTFiles/Analysis_Plots_SIMP_M1_13TeV.root", "RECREATE");
  // f1->cd();
  // for (std::pair<std::string, TH1F*> element : plot_m1) {
 // 	 TH1F* histo = element.second;
 // 	 histo->Write();
  // }
	//
	// TFile * f10 = new TFile("ROOTFiles/Analysis_Plots_SIMP_M10_13TeV.root", "RECREATE");
  // f10->cd();
	//
  // for (std::pair<std::string, TH1F*> element : plot_m10) {
 // 	 TH1F* histo = element.second;
 // 	 histo->Write();
  // }
	//
	// TFile * f100 = new TFile("ROOTFiles/Analysis_Plots_SIMP_M100_13TeV.root", "RECREATE");
  // f100->cd();
	//
  // for (std::pair<std::string, TH1F*> element : plot_m100) {
 // 	 TH1F* histo = element.second;
 // 	 histo->Write();
  // }


	// TFile * f200 = new TFile("ROOTFiles/Analysis_Plots_SIMP_M200_13TeV.root", "RECREATE");
  // f200->cd();
	//
	// for (std::pair<std::string, TH1F*> element : plot_m200) {
 // 	 TH1F* histo = element.second;
 // 	 histo->Write();
  // }
	// TFile * f400 = new TFile("ROOTFiles/Analysis_Plots_SIMP_M400_13TeV.root", "RECREATE");
  // f400->cd();
	//
	// for (std::pair<std::string, TH1F*> element : plot_m400) {
 // 	 TH1F* histo = element.second;
 // 	 histo->Write();
  // }
	// TFile * f700 = new TFile("ROOTFiles/Analysis_Plots_SIMP_M700_13TeV.root", "RECREATE");
  // f700->cd();
	//
  // for (std::pair<std::string, TH1F*> element : plot_m700) {
 // 	 TH1F* histo = element.second;
 // 	 histo->Write();
  // }
	// TFile * f1000 = new TFile("ROOTFiles/Analysis_Plots_SIMP_M1000_13TeV.root", "RECREATE");
  // f1000->cd();
	//
	// for (std::pair<std::string, TH1F*> element : plot_m1000) {
	//  TH1F* histo = element.second;
	//  histo->Write();
	// }
	//
	TFile * fqcd = new TFile("Analysis_Plots_QCD_13TeV.root", "RECREATE");
  fqcd->cd();

  for (std::pair<std::string, TH1F*> element : plot_qcd300_500) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH1F*> element : plot_qcd500_700) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH1F*> element : plot_qcd700_1000) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH1F*> element : plot_qcd1000_1500) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH1F*> element : plot_qcd1500_2000) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH1F*> element : plot_qcd2000_Inf) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }


  //  f1->Close();
	//  f10->Close();
	//  f100->Close();
	// f200->Close();
	// f400->Close();
	// f700->Close();
	// f1000->Close();
   fqcd->Close();

	return 0;
}

void Analysis::producePlots(){

	TFile* f700 = new TFile(this->getFileName());

	TDirectory* dirl700 = (TDirectory*)f700->Get("treeCorr");
  TTree* treel700 = (TTree*)dirl700->Get("SimpAnalysis");


  SANtuple c_st700;
  c_st700.Init(treel700);


	int nentries = c_st700.fChain->GetEntries();
	TString Label = this->getLabel();

	cout<<"Reading "<<Label<<" tree with:\t"<<nentries<<"\tentries"<<endl;

	TH1F* h_jetchf   = new TH1F("h_jetchf_"+Label,"h_jetchf_"+Label,100,0,1);
  TH1F* h_jetchf0   = new TH1F("h_jetchf0_"+Label,"h_jetchf0_"+Label,100,0,1);
  TH1F* h_jetchf1   = new TH1F("h_jetchf1_"+Label,"h_jetchf1_"+Label,100,0,1);
	TH1F* h_jetnhf0   = new TH1F("h_jetnhf0_"+Label,"h_jetnhf0_"+Label,100,0,1);
  TH1F* h_jetnhf1   = new TH1F("h_jetnhf1_"+Label,"h_jetnhf1_"+Label,100,0,1);
	TH1F* h_jetcef0   = new TH1F("h_jetcef0_"+Label,"h_jetcef0_"+Label,100,0,1);


  TH1F* h_dphi     = new TH1F("h_dphi_"+Label,"h_dphi_"+Label,100,2,4);
  TH1F* h_phi      = new TH1F("h_phi_"+Label,"h_phi_"+Label,100,-4,4);
  TH1F* h_eta      = new TH1F("h_eta_"+Label,"h_eta_"+Label,100,-4,4);
  TH1F* h_pt0      = new TH1F("h_pt0_"+Label,"h_pt0_"+Label,200,0,4000);
  TH1F* h_pt1      = new TH1F("h_pt1_"+Label,"h_pt1_"+Label,200,0,4000);
	TH1F *h_njets    = new TH1F("h_njets_"+Label, "h_njets_"+Label, 20, 0, 20);



  TH1F* h_genphi      = new TH1F("h_genphi_"+Label,"h_genphi_"+Label,100,-4,4);
  TH1F* h_geneta      = new TH1F("h_geneta_"+Label,"h_geneta_"+Label,100,-4,4);
  TH1F* h_genpt      = new TH1F("h_genpt0_"+Label,"h_genpt0_"+Label,200,0,4000);
	TH1F* h_genjetcef0   = new TH1F("h_genjetcef0_"+Label,"h_genjetcef0_"+Label,100,0,1);



	TH1F *h_nvtx     = new TH1F("h_nvtx_"+Label, "h_nvtx_"+Label, 60, 0, 60);
	TH1F *h_HT       = new TH1F("h_HT_"+Label, "h_HT_"+Label, 200, 0, 4000);
	TH1F *h_METHT       = new TH1F("h_METHT_"+Label, "h_METHT_"+Label, 200, 0, 2);

	TH1F *h_jetArea1       = new TH1F("h_jetArea1_"+Label, "h_jetArea_1"+Label, 100, 0, 1);
	TH1F *h_jetArea0       = new TH1F("h_jetArea0_"+Label, "h_jetArea_0"+Label, 100, 0, 1);
	TH1F *h_genjetArea0       = new TH1F("h_genjetArea0_"+Label, "h_genjetArea_0"+Label, 100, 0, 1);
	//const double eta_cut = this->getEtaCut(), dphi_cut=this->getDphiCut(), pt_cut = this->getPtCut();
	//const double weight = this->getWeight() ;
	for(int i=0; i<nentries/10; i++){
		c_st700.GetEntry(i);
		double ht = 0;
		double NJets = 0;
		bool passed = false;
		for(int j=0; j<c_st700.nJet; j++){
			if(c_st700.nJet>=2){

				if(c_st700.jet_pt[0]>pt_cut && c_st700.jet_pt[1]>pt_cut && fabs(c_st700.jet_eta[0])<eta_cut && fabs(c_st700.jet_eta[1])<eta_cut && fabs(c_st700.jet_phi[0]-c_st700.jet_phi[1])>dphi_cut) {
					  ht+=c_st700.jet_pt[j];
						if (c_st700.jet_pt[j]>50.) NJets++;
						passed = true;
					 }

				if(c_st700.jet_pt[0]>pt_cut && c_st700.jet_pt[1]>pt_cut && fabs(c_st700.jet_eta[0])<eta_cut && fabs(c_st700.jet_eta[1])<eta_cut && fabs(c_st700.jet_phi[0]-c_st700.jet_phi[1])>dphi_cut
				   && j<2 ) {



		      //bool tightLepVetoJetID = ( c_st700.jet_efrac_ch_Had[j]>0 &&c_st700.jet_efrac_ne_Had[j]<0.90 && c_st700.jet_efrac_ne_EM[j]<0.99 && c_st700.jet_efrac_ch_Mu[j]<0.8);
					//if(tightLepVetoJetID) cout<<j<<"       FAAAAAALSE"<<endl;
					//if(tightLepVetoJetID == false) continue;
					if(j==0) {
						h_pt0->Fill(c_st700.jet_pt[j],weight);
	          h_jetchf0->Fill(c_st700.jet_efrac_ch_Had[j],weight);
						h_jetnhf0->Fill(c_st700.jet_efrac_ne_Had[j],weight);

						h_jetArea0->Fill(c_st700.jetArea[j],weight);


						h_jetcef0->Fill(c_st700.jet_efrac_ch_Had[j]+c_st700.jet_efrac_ch_EM[j]+c_st700.jet_efrac_ch_Mu[j],weight);
						h_jetchf->Fill(c_st700.jet_efrac_ch_Had[j],weight);
						h_phi->Fill(c_st700.jet_phi[j],weight);
						h_eta->Fill(c_st700.jet_eta[j],weight);

					}
					if(j==1) {
						h_dphi->Fill(fabs(c_st700.jet_phi[0]-c_st700.jet_phi[1]),weight);
						h_pt1->Fill(c_st700.jet_pt[1],weight);
            h_jetchf1->Fill(c_st700.jet_efrac_ch_Had[1],weight);
						h_jetnhf1->Fill(c_st700.jet_efrac_ne_Had[1],weight);

						h_jetArea1->Fill(c_st700.jetArea[1],weight);
					}
				}
			}
		}//for jet


		for(int gj=0; gj<c_st700.nGenJet; gj++){
				if(c_st700.genjet_pt[0]>pt_cut && c_st700.genjet_pt[1]>pt_cut && fabs(c_st700.genjet_eta[0])<eta_cut && fabs(c_st700.genjet_eta[1])<eta_cut && fabs(c_st700.genjet_phi[0]-c_st700.genjet_phi[1])>dphi_cut
				   && gj<1 ) {
						h_genpt->Fill(c_st700.genjet_pt[gj],weight);
					  h_genphi->Fill(c_st700.genjet_phi[gj],weight);
						h_geneta->Fill(c_st700.genjet_eta[gj],weight);
						h_genjetcef0->Fill(c_st700.genjet_efrac_ch[gj], weight);
						h_genjetArea0->Fill(c_st700.genjetArea[gj],weight);
				}
		}


		if(passed) {
			h_HT->Fill(ht,weight);
			//cout<<c_st700.vtx_N<<endl;
			h_nvtx->Fill(c_st700.vtx_N,weight);
			h_njets->Fill(NJets,weight);
			h_METHT->Fill(c_st700.MET/ht,weight);
			//cout<<c_st700.MET<<endl;

		}
	}


 std::map<std::string, TH1F*> histos;
 histos["h_jetchf"] = h_jetchf;
 histos["h_jetchf0"] = h_jetchf0;
 histos["h_jetchf1"] = h_jetchf1;
 histos["h_jetcef0"] = h_jetcef0;

 histos["h_pt0"] = h_pt0;
 histos["h_pt1"] = h_pt1;
 histos["h_phi"] = h_phi;
 histos["h_eta"] = h_eta;
 histos["h_dphi"] = h_dphi;

 histos["h_njets"] = h_njets;
 histos["h_HT"] = h_HT;
 histos["h_nvtx"] = h_nvtx;

 histos["h_jetArea0"] = h_jetArea0;
 histos["h_jetArea1"] = h_jetArea1;

 histos["h_jetnhf0"] = h_jetnhf0;
 histos["h_jetnhf1"] = h_jetnhf1;
 histos["h_METHT"] = h_METHT;

 histos["h_genpt"] = h_genpt;
 histos["h_genphi"] = h_genphi;
 histos["h_geneta"] = h_geneta;
histos["h_genjetcef0"] = h_genjetcef0;
histos["h_genjetArea0"] = h_genjetArea0;

 this->setHistos(histos);
/*
 TCanvas *canvas_chf  = canvas_h1f("c_chf","Jet CHF", h_jetchf);
 TCanvas *canvas_chf0 = canvas_h1f("c_chf0", "Leading Jet CHF", h_jetchf0);
 TCanvas *canvas_chf1 = canvas_h1f("c_chf1", "Sub-leading Jet CHF", h_jetchf1);
 TCanvas *canvas_dphi = canvas_h1f("c_dphi", "|#Delta#phi_{j1,j2}|", h_dphi);
 TCanvas *canvas_phi  = canvas_h1f("c_phi","Jet #phi", h_phi);
 TCanvas *canvas_eta  = canvas_h1f("c_eta","Jet #eta",h_eta);
 TCanvas *canvas_pt0  = canvas_h1f("c_pt0","Jet p_{T}",h_pt0);
 TCanvas *canvas_pt1  = canvas_h1f("c_pt1","Jet p_{T}",h_pt1);
*/

//return histos;

}
