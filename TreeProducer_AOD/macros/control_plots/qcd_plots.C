#include "../classes/SANtuple.h"
#include "../classes/analysis.C"

#include <iostream>

int qcd_plots(){

  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	const double LUMI = 36.5*1000.;
	double QCD_xsec[6] = {346400, 32010, 6842, 1203, 120.1, 25.40}; //PUMoriond17
	double N_Entries[6] = {17035891, 	18852895, 	15629253,	4825904, 	3970819,	1991645};

	Analysis simp_an_qcd_300_500(250.,2.0,2.0);
	simp_an_qcd_300_500.setFileName("../SIMPs_QCD_HT300To500_PUMoriond17.root");
	simp_an_qcd_300_500.setWeight(QCD_xsec[0]*LUMI/N_Entries[0]);
  simp_an_qcd_300_500.setLabel("QCD_HT300To500");
	simp_an_qcd_300_500.producePlots();

	Analysis simp_an_qcd_500_700(250.,2.0,2.0);
	simp_an_qcd_500_700.setFileName("../SIMPs_QCD_HT500To700_PUMoriond17.root");
	simp_an_qcd_500_700.setWeight(QCD_xsec[1]*LUMI/N_Entries[1]);
  simp_an_qcd_500_700.setLabel("QCD_HT500To700");
	simp_an_qcd_500_700.producePlots();

	Analysis simp_an_qcd_700_1000(250.,2.0,2.0);
	simp_an_qcd_700_1000.setFileName("../SIMPs_QCD_HT700To1000_PUMoriond17.root");
	simp_an_qcd_700_1000.setWeight(QCD_xsec[2]*LUMI/N_Entries[2]);
  simp_an_qcd_700_1000.setLabel("QCD_HT700To1000");
	simp_an_qcd_700_1000.producePlots();

	Analysis simp_an_qcd_1000_1500(250.,2.0,2.0);
	simp_an_qcd_1000_1500.setFileName("../SIMPs_QCD_HT1000To1500_PUMoriond17.root");
	simp_an_qcd_1000_1500.setWeight(QCD_xsec[3]*LUMI/N_Entries[3]);
  simp_an_qcd_1000_1500.setLabel("QCD_HT1000To1500");
	simp_an_qcd_1000_1500.producePlots();

	Analysis simp_an_qcd_1500_2000(250.,2.0,2.0);
	simp_an_qcd_1500_2000.setFileName("../SIMPs_QCD_HT1500To2000_PUMoriond17.root");
	simp_an_qcd_1500_2000.setWeight(QCD_xsec[4]*LUMI/N_Entries[4]);
  simp_an_qcd_1500_2000.setLabel("QCD_HT1500To2000");
	simp_an_qcd_1500_2000.producePlots();

	Analysis simp_an_qcd_2000_Inf(250.,2.0,2.0);
	simp_an_qcd_2000_Inf.setFileName("../SIMPs_QCD_HT2000ToInf_PUMoriond17.root");
	simp_an_qcd_2000_Inf.setWeight(QCD_xsec[5]*LUMI/N_Entries[5]);
  simp_an_qcd_2000_Inf.setLabel("QCD_HT2000ToInf");
	simp_an_qcd_2000_Inf.producePlots();


	std::map<std::string, TH1F*> plot_qcd300_500 = simp_an_qcd_300_500.getHistos();
	std::map<std::string, TH1F*> plot_qcd500_700 = simp_an_qcd_500_700.getHistos();
	std::map<std::string, TH1F*> plot_qcd700_1000 = simp_an_qcd_700_1000.getHistos();
	std::map<std::string, TH1F*> plot_qcd1000_1500 = simp_an_qcd_1000_1500.getHistos();
	std::map<std::string, TH1F*> plot_qcd1500_2000 = simp_an_qcd_1500_2000.getHistos();
	std::map<std::string, TH1F*> plot_qcd2000_Inf = simp_an_qcd_2000_Inf.getHistos();


	std::map<std::string, TH2F*> plot2d_qcd300_500 = simp_an_qcd_300_500.get2DHistos();
	std::map<std::string, TH2F*> plot2d_qcd500_700 = simp_an_qcd_500_700.get2DHistos();
	std::map<std::string, TH2F*> plot2d_qcd700_1000 = simp_an_qcd_700_1000.get2DHistos();
	std::map<std::string, TH2F*> plot2d_qcd1000_1500 = simp_an_qcd_1000_1500.get2DHistos();
	std::map<std::string, TH2F*> plot2d_qcd1500_2000 = simp_an_qcd_1500_2000.get2DHistos();
	std::map<std::string, TH2F*> plot2d_qcd2000_Inf = simp_an_qcd_2000_Inf.get2DHistos();




	TFile * fqcd = new TFile("Analysis_Plots_QCD_13TeV_test.root", "RECREATE");
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


	for (std::pair<std::string, TH2F*> element : plot2d_qcd300_500) {
 	 TH2F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH2F*> element : plot2d_qcd500_700) {
 	 TH2F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH2F*> element : plot2d_qcd700_1000) {
 	 TH2F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH2F*> element : plot2d_qcd1000_1500) {
 	 TH2F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH2F*> element : plot2d_qcd1500_2000) {
 	 TH2F* histo = element.second;
 	 histo->Write();
  }
	for (std::pair<std::string, TH2F*> element : plot2d_qcd2000_Inf) {
 	 TH2F* histo = element.second;
 	 histo->Write();
  }


   fqcd->Close();

	return 0;
}
