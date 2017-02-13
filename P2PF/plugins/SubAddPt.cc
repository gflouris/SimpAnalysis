//-------------------------------------------------
//
//   Class: SubAddPt
//
//   SubAddPt
//
//
//   Author :
//   G. Flouris               VUB        Jan. 2016
//--------------------------------------------------

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include <FWCore/Framework/interface/ConsumesCollector.h>
#include <FWCore/Framework/interface/one/EDProducer.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>
#include <DataFormats/HepMCCandidate/interface/GenParticle.h>
#include <DataFormats/JetReco/interface/PFJet.h>
#include <DataFormats/JetReco/interface/Jet.h>
#include "DataFormats/JetReco/interface/GenJet.h"
#include <DataFormats/Math/interface/deltaR.h>

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include "TRandom.h"

using namespace std;

class SubAddPt: public edm::one::EDProducer<edm::one::SharedResources> {
public:
  SubAddPt(const edm::ParameterSet & pset);
  virtual ~SubAddPt() {}
  virtual void produce(edm::Event & e, const edm::EventSetup& c);
  double Resolution(double pt);

private:
  edm::EDGetToken m_partons, m_particlef;
  bool m_addpt;
  TRandom *rnd;// = new TRandom();

};


SubAddPt::SubAddPt(const edm::ParameterSet & pset) {
m_partons      = consumes<vector<reco::GenParticle> >(pset.getParameter<edm::InputTag>("Partons_Source"));
m_particlef    = consumes<vector<reco::PFJet> >(pset.getParameter<edm::InputTag>("ParticleFlow_Source"));
m_addpt       = pset.getParameter<bool>("AddPt_Bool");
rnd = new TRandom();

produces<vector<reco::PFJet> >("SubAddPFJets");

}
double SubAddPt::Resolution(double pt){
//a + b/(pow(x,c) +d*x)
  double res = 0;
  const double A = 1.37861*pow(10,-2);
  const double B = 2.09447*pow(10,-2);
  const double C = -3.08390*pow(10,-1);
  const double D = 4.27909*pow(10,-4);
  res = A + B/(pow(pt,C) + D*pt);
  return res;

}


void SubAddPt::produce(edm::Event& e, const edm::EventSetup& c) {
  using namespace reco;
  using namespace edm;
  using namespace std;
  typedef reco::Particle::LorentzVector LorentzVector;

  edm::Handle<vector<reco::GenParticle> > H_partons;
  edm::Handle<vector<reco::PFJet> >       H_pfjets;
  e.getByToken(m_partons, H_partons);
  e.getByToken(m_particlef, H_pfjets);



  std::auto_ptr<vector<reco::PFJet> > out_PFJets(new vector<reco::PFJet>);
  int index=-1, itr=0;
    for (vector<reco::PFJet>::const_iterator thepfjets = H_pfjets->begin();  thepfjets != H_pfjets->end(); ++thepfjets){
      for (vector<reco::GenParticle>::const_iterator thepartons = H_partons->begin();  thepartons != H_partons->end(); ++thepartons){

        double dR = deltaR(thepartons->eta() , thepartons->phi() ,thepfjets->eta(), thepfjets->phi());
        if(dR<0.4 && index!=itr) {
          reco::PFJet tmpJet(*thepfjets);
          LorentzVector p4diff;
          if(m_addpt) {


            double sig = Resolution(thepartons->pt());
            double xrnd = rnd->Gaus(1,sig);
            LorentzVector p4difftmp;
            p4difftmp = thepfjets->p4() + thepartons->p4();

            p4diff.SetPxPyPzE(p4difftmp.px()* xrnd,p4difftmp.py()* xrnd,p4difftmp.pz()* xrnd,p4difftmp.energy()); //neutron gun
          }



          else if(!m_addpt) p4diff = thepfjets->p4() - thepartons->p4();
          //cout<<thepfjets->pt()<<"\t"<<thepartons->pt()<<endl;
          tmpJet.setP4(p4diff);

          out_PFJets->push_back(tmpJet);
          //cout<<tmpJet.pt()<<endl;
          index=itr;

        }
       itr++;
      }
    }
  // LorentzVector tmpPfCand;
  // double genPart_pt = 0;
  // ///Partons
  //   for (vector<reco::GenParticle>::const_iterator thepartons = H_partons->begin();  thepartons != H_partons->end(); ++thepartons){
  //      if(thepartons->fromHardProcessFinalState()){
  //         genPart_pt = thepartons->pt();
  //     }//genParticles
  //   }


  //PFCandidate( Charge q, const LorentzVector & p4, ParticleType particleId );
  e.put(out_PFJets,"SubAddPFJets");
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(SubAddPt);
