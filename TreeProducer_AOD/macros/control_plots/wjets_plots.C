
#include "../classes/SANtuple.h"
#include "../classes/analysis.C"


int wjets_plots(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	const double LUMI = 36.5*1000.;

  double XSEC = 2788;
	double N_Entries = 22784949;

	Analysis simp_an_wjets(250.,2.0,2.0);

	for(int f=1; f<1000; f++){
   stringstream a;
   a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/WJetsToQQ_HT180_13TeV-madgraphMLM-pythia8/crab_WJets_HT180/170405_191146/0000/output_tree_SPV_QCD_wjetsqq_";
	 a<<f; a<<".root";
	 simp_an_wjets.setFileName((a.str()).c_str());
  }

	for(int f=1000; f<1600; f++){
   stringstream a;
   a<<"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/gflouris/WJetsToQQ_HT180_13TeV-madgraphMLM-pythia8/crab_WJets_HT180/170405_191146/0001/output_tree_SPV_QCD_wjetsqq_";
	 a<<f; a<<".root";
	 simp_an_wjets.setFileName((a.str()).c_str());
  }

	simp_an_wjets.setWeight(XSEC*LUMI/N_Entries);
  simp_an_wjets.setLabel("WJetsToQQ");
	simp_an_wjets.producePlots();

	std::map<std::string, TH1F*> plot_qcd300_500 = simp_an_wjets.getHistos();
	std::map<std::string, TH2F*> plot2d_qcd300_500 = simp_an_wjets.get2DHistos();

	TFile * fqcd = new TFile("Analysis_Plots_WJets_13TeV.root", "RECREATE");
  fqcd->cd();

  for (std::pair<std::string, TH1F*> element : plot_qcd300_500) {
 	 TH1F* histo = element.second;
 	 histo->Write();
  }

	for (std::pair<std::string, TH2F*> element : plot2d_qcd300_500) {
 	 TH2F* histo = element.second;
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
