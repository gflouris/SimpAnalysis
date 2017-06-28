#include "../classes/SANtuple.h"
#include "../classes/analysis.C"

#include <iostream>

int simp_plots(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	const double LUMI = 36.5*1000.;

	Analysis simp_an_1(250.,2.0,2.0);
	Analysis simp_an_10(250.,2.0,2.0);
	Analysis simp_an_100(250.,2.0,2.0);
	Analysis simp_an_200(250.,2.0,2.0);
	Analysis simp_an_400(250.,2.0,2.0);
	Analysis simp_an_700(250.,2.0,2.0);
	Analysis simp_an_1000(250.,2.0,2.0);


  simp_an_1.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M1.root");
	simp_an_1.setWeight(4.43*LUMI);
	simp_an_1.setLabel("SIMP_M1");
	simp_an_1.producePlots();

	simp_an_10.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M10_1.root");
	simp_an_10.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M10_2.root");
	simp_an_10.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M10_3.root");
	simp_an_10.setWeight(4.42*LUMI);
	simp_an_10.setLabel("SIMP_M10");
	simp_an_10.producePlots();


	simp_an_100.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M100.root");
	simp_an_100.setWeight(2.42*LUMI);
	simp_an_100.setLabel("SIMP_M100");
	simp_an_100.producePlots();


	simp_an_200.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M200.root");
	simp_an_200.setWeight(0.7903*LUMI);
	simp_an_200.setLabel("SIMP_M200");
	simp_an_200.producePlots();


	simp_an_400.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M400.root");
	simp_an_400.setWeight(0.07434*LUMI);
	simp_an_400.setLabel("SIMP_M400");
	simp_an_400.producePlots();


	simp_an_700.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M700.root");
	simp_an_700.setWeight(0.004846*LUMI);
	simp_an_700.setLabel("SIMP_M700");
  simp_an_700.producePlots();


	simp_an_1000.setFileName("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/isdebruy/SIMPs/Ntuples/SIMPs_PUMoriond17_AOD_M1000.root");
	simp_an_1000.setWeight(0.0005714*LUMI);
	simp_an_1000.setLabel("SIMP_M1000");
  simp_an_1000.producePlots();


	std::map<std::string, TH1F*> plot_m1 = simp_an_1.getHistos();
	std::map<std::string, TH1F*> plot_m10 = simp_an_10.getHistos();
	std::map<std::string, TH1F*> plot_m100 = simp_an_100.getHistos();
	std::map<std::string, TH1F*> plot_m200 = simp_an_200.getHistos();
	std::map<std::string, TH1F*> plot_m400 = simp_an_400.getHistos();
	std::map<std::string, TH1F*> plot_m700 = simp_an_700.getHistos();
	std::map<std::string, TH1F*> plot_m1000 = simp_an_1000.getHistos();

	std::map<std::string, TH2F*> plot2d_m1 = simp_an_1.get2DHistos();
	std::map<std::string, TH2F*> plot2d_m10 = simp_an_10.get2DHistos();
	std::map<std::string, TH2F*> plot2d_m100 = simp_an_100.get2DHistos();
	std::map<std::string, TH2F*> plot2d_m200 = simp_an_200.get2DHistos();
	std::map<std::string, TH2F*> plot2d_m400 = simp_an_400.get2DHistos();
	std::map<std::string, TH2F*> plot2d_m700 = simp_an_700.get2DHistos();
	std::map<std::string, TH2F*> plot2d_m1000 = simp_an_1000.get2DHistos();

	TFile * f1 = new TFile("Analysis_Plots_SIMP_13TeV.root", "RECREATE");
  f1->cd();
  for (std::pair<std::string, TH1F*> element : plot_m1) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }

  for (std::pair<std::string, TH1F*> element : plot_m10) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }

  for (std::pair<std::string, TH1F*> element : plot_m100) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }

	for (std::pair<std::string, TH1F*> element : plot_m200) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }

	for (std::pair<std::string, TH1F*> element : plot_m400) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }

  for (std::pair<std::string, TH1F*> element : plot_m700) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }

	for (std::pair<std::string, TH1F*> element : plot_m1000) {
	 TH1F* histo = element.second;
	 histo->Write();
	}

	for (std::pair<std::string, TH2F*> element : plot2d_m1) {
	 TH2F* histo = element.second;
	 histo->Write();
	}

	for (std::pair<std::string, TH2F*> element : plot2d_m10) {
	 TH2F* histo = element.second;
	 histo->Write();
	}

	for (std::pair<std::string, TH2F*> element : plot2d_m100) {
	 TH2F* histo = element.second;
	 histo->Write();
	}

	for (std::pair<std::string, TH2F*> element : plot2d_m200) {
	 TH2F* histo = element.second;
	 histo->Write();
	}

	for (std::pair<std::string, TH2F*> element : plot2d_m400) {
	 TH2F* histo = element.second;
	 histo->Write();
	}

	for (std::pair<std::string, TH2F*> element : plot2d_m700) {
	 TH2F* histo = element.second;
	 histo->Write();
	}

	for (std::pair<std::string, TH2F*> element : plot2d_m1000) {
	 TH2F* histo = element.second;
	 histo->Write();
	}
   f1->Close();

	return 0;
}
